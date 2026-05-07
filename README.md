# KinesisDrive - Gesture Controlled Bot

Real-time wireless gesture-controlled robotic platform built using ESP32, MPU6050 IMU, ESP-NOW, and BTS7960 motor drivers.

KinesisDrive translates hand orientation and motion into proportional robotic movement using a wearable IMU-based controller glove and low-latency peer-to-peer communication.

---

# Features

* Real-time gesture-based robotic control
* Low-latency ESP-NOW wireless communication
* MPU6050 IMU-based orientation sensing
* Proportional throttle and steering control
* Differential drive motor mixing
* Deadzone handling and directional remapping
* Responsive embedded control pipeline
* Wearable glove-based control interface

---

# System Architecture

```text
MPU6050 IMU
      ↓
ESP32 Glove Controller
      ↓  ESP-NOW
ESP32 Bot Receiver
      ↓
BTS7960 Motor Drivers
      ↓
Differential Drive Motors
```

---

# Hardware Used

## Controller Unit

* ESP32 DevKit V1
* MPU6050 IMU
* 2x 18650 Li-ion Battery
* Glove-mounted sensor assembly

## Robot Unit

* ESP32 DevKit V1
* 2x BTS7960 Motor Drivers
* High torque 500rpm 12v DC Johnsons motors
* Differential drive robotic chassis
* 3s 80C Lipo battery pack

---

# Software Stack

* Embedded C
* Arduino IDE
* ESP-NOW Protocol
* I2C Communication
* Real-time sensor processing
* Differential drive control algorithms

---

# Control Pipeline

1. MPU6050 captures hand orientation data
2. ESP32 processes pitch and roll values
3. Sensor values are calibrated relative to a user-defined origin
4. Motion values are scaled to proportional throttle and steering commands
5. Commands are transmitted wirelessly using ESP-NOW
6. Receiver ESP32 performs motor mixing and dynamic steering control
7. BTS7960 drivers actuate the motors in real time

---

# Communication Protocol

ESP-NOW is used for low-latency peer-to-peer communication between the glove controller and robotic platform.

Example transmitted command strings:

```text
F255R000
F180L090
B120R255
F000R000
```

Where:

* `F` = Forward throttle
* `B` = Backward throttle
* `L` = Left steering
* `R` = Right steering

---

# Repository Structure

```text
KinesisDrive/
│
├── glove_controller/
│   └── glove_controller.ino
│
├── bot_receiver/
│   └── bot_receiver.ino
│
├── images/
│   ├── glove_setup.jpg
│   ├── bot_setup.jpg
│   └── system_architecture.png
│
├── README.md
└── LICENSE
```

---

# Setup Instructions

## Glove Controller

1. Connect MPU6050 to ESP32 using I2C
2. Update receiver MAC address in transmitter code
3. Upload `glove_controller.ino`
4. Open Serial Monitor
5. Hold glove in neutral position
6. Press `c` for calibration

## Robot Receiver

1. Connect BTS7960 drivers to ESP32
2. Configure motor driver pins
3. Upload `bot_receiver.ino`
4. Power the robotic platform
5. Verify ESP-NOW communication

---

# Applications

* Gesture-controlled robotic systems
* Motion-controlled vehicles
* Teleoperation systems
* Embedded robotics platforms
* Human-machine interaction systems
* Wireless robotic control systems

---

# Future Improvements

* IMU sensor fusion using complementary/Kalman filtering
* Adaptive sensitivity tuning
* Wireless telemetry dashboard
* Gesture-triggered mode switching
* Haptic feedback integration
* Drone and robotic arm control support

---

# Demo

Add project demonstration videos and images inside the `images/` directory.

Recommended additions:

* Controller glove images
* Robot chassis images
* Wiring diagrams
* Real-time control demonstration videos

---

# Author

Jatin Hosmani ( Conolas )

* LinkedIn: [https://linkedin.com/in/jatin-hosmani](https://linkedin.com/in/jatin-hosmani)
* GitHub: [https://github.com/Conolas](https://github.com/Conolas)
