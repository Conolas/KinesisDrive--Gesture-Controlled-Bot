# Glove Controller

ESP32-based wearable motion controller for KinesisDrive.

This module captures hand orientation using the MPU6050 IMU, processes pitch and roll values, converts them into proportional steering and throttle commands, and transmits them wirelessly using the ESP-NOW protocol.

---

# Features

- MPU6050 IMU-based orientation sensing
- Real-time gesture processing
- Proportional throttle and steering mapping
- Deadzone handling and directional remapping
- ESP-NOW low-latency wireless communication
- User-defined orientation calibration

---

# Hardware Used

- ESP32 DevKit V1
- MPU6050 IMU
- 18650 Li-ion battery
- Wearable glove assembly

---

# Pin Connections

| MPU6050 | ESP32 |
|--------|--------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

# Working Principle

1. MPU6050 captures hand orientation data
2. ESP32 computes pitch and roll values
3. Relative motion is calculated using calibrated origin offsets
4. Motion values are scaled into proportional steering and throttle outputs
5. Commands are transmitted wirelessly to the robotic platform using ESP-NOW

---

# Calibration

1. Power on the glove controller
2. Hold the glove in the desired neutral position
3. Open Serial Monitor
4. Press:

```text
c
