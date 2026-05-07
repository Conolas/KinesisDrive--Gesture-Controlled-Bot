
---

# 📄 `bot_receiver/README.md`

```md id="bot_readme_md"
# Bot Receiver

ESP32-based receiver and motor control module for KinesisDrive.

This module receives real-time wireless control commands from the glove controller using ESP-NOW and drives the robotic platform using BTS7960 motor drivers and differential drive control logic.

---

# Features

- ESP-NOW wireless command reception
- Differential drive motor mixing
- Proportional steering and throttle control
- Dynamic steering gain adjustment
- Curve-sensitive steering response
- Smooth acceleration and deceleration handling

---

# Hardware Used

- ESP32 DevKit V1
- 2x BTS7960 motor drivers
- Differential drive robotic chassis
- High torque DC motors
- Li-ion battery pack

---

# Motor Driver Pin Mapping

## Left Motor Driver

| Function | GPIO |
|----------|------|
| LL_EN | 12 |
| LR_EN | 13 |
| L_LPWM | 27 |
| L_RPWM | 14 |

---

## Right Motor Driver

| Function | GPIO |
|----------|------|
| RL_EN | 25 |
| RR_EN | 26 |
| R_LPWM | 32 |
| R_RPWM | 33 |

---

# Working Principle

1. ESP32 receives wireless command packets via ESP-NOW
2. Commands are parsed into throttle and steering components
3. Differential drive motor-mixing logic computes left and right motor outputs
4. Dynamic steering gain and smoothing algorithms optimize maneuverability
5. PWM outputs drive BTS7960 motor drivers in real time

---

# Example Received Commands

```text
F255R000
F180L090
B120R255
F000R000
