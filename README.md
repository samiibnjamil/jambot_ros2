# ROS2 Jazzy Jalisco 4-Wheeled Robot Project

## Overview
This project involves building a sophisticated 4-wheeled robot controlled by an ESP32 and a Raspberry Pi. The robot is equipped with various sensors, including an ultrasonic sensor, LiDAR, and a camera, and can be controlled via a Bluetooth joystick connected to a laptop. The system utilizes ROS2 Jazzy Jalisco to achieve advanced functionalities such as SLAM, obstacle detection, and path planning.

### Project Goals
- **Wireless control:** Bluetooth joystick for real-time robot control.
- **Obstacle avoidance:** Ultrasonic sensor to detect and avoid obstacles.
- **SLAM and path planning:** LiDAR and camera for simultaneous localization and mapping.
- **Distributed processing:** ESP32 for motor and ultrasonic control, Raspberry Pi for sensor data processing, and a laptop for advanced computations.
- **Future expansion:** Possibility of upgrading to Jetson Nano for enhanced performance.

---

## Hardware Components
1. **ESP32-C3:**
   - Motor control and communication with Raspberry Pi.
   - Ultrasonic sensor data processing.

2. **Raspberry Pi:**
   - LiDAR and camera data processing.
   - Running SLAM, obstacle detection, and path planning nodes.

3. **Laptop:**
   - Handles advanced SLAM algorithms.
   - GPU-accelerated object detection and remote monitoring.

4. **Sensors:**
   - Ultrasonic sensor for obstacle avoidance.
   - LiDAR for SLAM and environment mapping.
   - Camera for visual data and object detection.

5. **Actuators:**
   - Motors for locomotion controlled by ESP32.

6. **Other:**
   - Bluetooth joystick for control.

---

## Software Architecture
- **ROS2 Jazzy Jalisco:** Middleware to handle communication between different nodes.
- **ESP32:** Runs FreeRTOS for real-time motor and sensor control.
- **Communication Protocols:**
  - USB serial and UDP between ESP32 and Raspberry Pi.
  - Bluetooth for joystick control.
- **Laptop:**
  - Advanced SLAM algorithms.
  - Object detection using a GPU.

---

## Features
1. **Wireless Control:** Seamless control using a Bluetooth joystick.
2. **Obstacle Avoidance:** Ultrasonic sensor data processed by ESP32.
3. **SLAM and Path Planning:** LiDAR and camera enable dynamic path adjustment.
4. **Distributed Processing:** Clear task distribution among ESP32, Raspberry Pi, and laptop.
5. **Future Upgrades:** Designed for scalability with the option to integrate Jetson Nano.

---

## Installation and Setup
### Prerequisites
- ROS2 Jazzy Jalisco installed on Ubuntu 24.
- micro-ROS on ESP32-C3.
- Ensure WSL2 is configured if running ROS2 on Windows.

### Step-by-Step Setup
1. **Clone the repository:**
   ```bash
   git clone <repository_url>
   cd <repository_folder>
   ```

2. **Install dependencies:**
   ```bash
   sudo apt update && sudo apt install -y ros-foxy-<required-packages>
   ```

3. **Flash the ESP32:**
   - Use the following Wi-Fi credentials in the code:
     ```cpp
     #define WIFI_SSID "BELL777"
     #define WIFI_PASSWORD "****"
     ```
   - Follow the micro-ROS documentation to flash the firmware.

4. **Launch the ROS2 workspace:**
   ```bash
   colcon build
   source install/setup.bash
   ```

5. **Run nodes:**
   - Start ESP32 communication node.
   - Launch LiDAR SLAM node on Raspberry Pi.
   - Run advanced SLAM and monitoring on the laptop.

6. **Connect the joystick:**
   - Pair your Bluetooth joystick with the laptop.
   - Verify connection and run the joystick teleoperation node.

---

## Usage
1. Turn on the robot and ensure all devices are connected.
2. Launch the ROS2 nodes as described above.
3. Use the joystick to control the robot's movement.
4. Monitor SLAM and sensor data in real time on the laptop.

---

## Future Work
- **Jetson Nano Integration:** Enhance SLAM and object detection capabilities.
- **Improved SLAM Algorithms:** Explore AI-driven SLAM for better efficiency.
- **Additional Sensors:** Integrate IMU and GPS for improved localization.

---

## Troubleshooting
- **ESP32 not connecting:**
  - Verify Wi-Fi credentials.
  - Check micro-ROS configuration.
- **SLAM performance issues:**
  - Ensure LiDAR and camera are functioning correctly.
  - Optimize algorithms on the laptop.
- **Joystick not responding:**
  - Re-pair the Bluetooth joystick.
  - Test the joystick with a diagnostic tool.

---

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---

## Contributing
Feel free to fork the repository and submit pull requests for improvements or bug fixes.

---

## Acknowledgments
Special thanks to the ROS2 and micro-ROS communities for their excellent documentation and support.

