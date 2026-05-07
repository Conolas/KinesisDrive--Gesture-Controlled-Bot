#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>

#define MPU_ADDR 0x68
#define ACCEL_SCALE 16384.0

// 🔥 BOT MAC ADDRESS
uint8_t receiverAddress[] = {
  0xD4, 0x8C, 0x49, 0xE5, 0x00, 0xE8
};

// =============================
// DATA PACKET
// =============================

typedef struct {
  char command[20];
} ControlData;

ControlData data;

// =============================

float pitch_offset = 0;
float roll_offset = 0;

// tuning
float deadzone = 15;
float max_angle = 45.0;
int min_output = 40;

// =============================
void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  // Wake MPU
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // ESP NOW
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP NOW INIT FAILED");
    return;
  }

  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr,
         receiverAddress,
         6);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);

  Serial.println("🧤 GLOVE READY");
  Serial.println("Press 'c' to calibrate");
}

// =============================
void loop() {

  float pitch, roll;

  readAngles(pitch, roll);

  // =============================
  // CALIBRATION

  if (Serial.available()) {

    if (Serial.read() == 'c') {

      float ps = 0;
      float rs = 0;

      for (int i = 0; i < 100; i++) {

        float p, r;

        readAngles(p, r);

        ps += p;
        rs += r;

        delay(10);
      }

      pitch_offset = ps / 100.0;
      roll_offset  = rs / 100.0;

      Serial.println("✅ ORIGIN SET");
    }
  }

  // =============================
  // RELATIVE ANGLES

  float rel_pitch = pitch - pitch_offset;
  float rel_roll  = roll  - roll_offset;

  // ROTATED CONTROL
  float rotated_pitch = -rel_roll;
  float rotated_roll  = rel_pitch;

  int throttle = scaleValue(rotated_pitch);
  int steering = scaleValue(rotated_roll);

  // =============================
  // BUILD STRING

  char throttleDir;
  int throttleVal;

  char steeringDir;
  int steeringVal;

  // THROTTLE
  if (throttle >= 0) {
    throttleDir = 'F';
    throttleVal = throttle;
  }
  else {
    throttleDir = 'B';
    throttleVal = abs(throttle);
  }

  // STEERING
  if (steering >= 0) {
    steeringDir = 'R';
    steeringVal = steering;
  }
  else {
    steeringDir = 'L';
    steeringVal = abs(steering);
  }

  // ALWAYS FULL FORMAT
  sprintf(data.command,
          "%c%03d%c%03d",
          throttleDir,
          throttleVal,
          steeringDir,
          steeringVal);

  // SEND
  esp_now_send(receiverAddress,
               (uint8_t *) &data,
               sizeof(data));

  // DEBUG
  Serial.println(data.command);

  delay(50);
}

// =============================
// SCALE FUNCTION
// =============================

int scaleValue(float angle) {

  if (abs(angle) < deadzone)
    return 0;

  float sign =
      (angle > 0) ? 1 : -1;

  float effective_angle =
      abs(angle) - deadzone;

  float usable_range =
      max_angle - deadzone;

  float norm =
      effective_angle / usable_range;

  norm = constrain(norm, 0, 1);

  int output =
      min_output +
      norm * (255 - min_output);

  return sign * output;
}

// =============================
// MPU READ
// =============================

void readAngles(float &pitch,
                float &roll) {

  Wire.beginTransmission(MPU_ADDR);

  Wire.write(0x3B);

  Wire.endTransmission(false);

  Wire.requestFrom(MPU_ADDR,
                   14,
                   true);

  int16_t ax =
      Wire.read() << 8 | Wire.read();

  int16_t ay =
      Wire.read() << 8 | Wire.read();

  int16_t az =
      Wire.read() << 8 | Wire.read();

  Wire.read();
  Wire.read();

  float ax_g = ax / ACCEL_SCALE;
  float ay_g = ay / ACCEL_SCALE;
  float az_g = az / ACCEL_SCALE;

  roll =
      atan2(ay_g, az_g) * 180 / PI;

  pitch =
      atan2(
          -ax_g,
          sqrt(ay_g * ay_g +
               az_g * az_g)
      ) * 180 / PI;
}
