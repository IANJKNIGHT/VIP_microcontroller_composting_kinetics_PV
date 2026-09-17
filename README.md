# “Can a microcontroller-based adaptive system maximize composting kinetics (k) using, variable, passive photovoltaic energy inputs?”
---

## 📌 Project Overview
This project seeks to maximize the composting kinetics using a 12V PWM DC blower powered by a solar voltaic cell and battery pack.

---

## 🏗️ System Architecture & Hardware
* **Microcontroller:** ESP32 (Dual-core 240MHz, Wi-Fi/Bluetooth stack), ESP32 Camera
* **Power Subsystem:** Solar panel array, 12V battery, INA219 current sensors, 
* **Actuation:** 
  * 4-Wire PWM 12V DC blowers  (Tachometer speed feedback & duty-cycle control)
* **Telemetry & Sensing:** Ambient Temperature, Temperature inside each of the experimental and control groups, and solar irradiance sensors

---

### Project Milestones & Integration Timeline

| Phase / Target Date | Ian Knight | Anushka Erra | System Integration & Field Testing |
| :--- | :--- | :--- | :--- |
| **Week 4: Designing Subsystems** | • gather data on power usage, fan RPM, ambient temperature and store it on an SD card<br>• create 3 different run modes for the fans<br>• look for websites the show light and shadow data<br>| • get caught up on research papers and look up more if interested<br>• stream the esp32 camera over the computer<br>1. add any UDF and initialization functions for the camera in esp32_cam.c<br>2. add UDFs and global vars (if any under designated location in main.c<br>3. add whatever code necessary between #if defined(TEST_ESP32_CAM) and #endif<br>4. add camera datasheet to main branch<br>| **Gateway 1:** Affectively record camera data, temperature, and power on the SD card, and timestamp it. |


## 🛠️ Software & Build Setup

### Prerequisites
* [ESP-IDF v6.1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
* Git

### Building & Flashing

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/IANJKNIGHT/VIP_microcontroller_composting_kinetics_PV
.git](https://github.com/IANJKNIGHT/VIP_microcontroller_composting_kinetics_PV
.git)

2. **Running the Code:**
   1. uncomment your test and comment out other unnecessary ones
   2. press new terminal
   3. (in that terminal) type 'idf.py build'
   4. resolve all compiler issues
   5. make sure to connect esp32
   6. type 'idf.py flash'
   7. type 'idf.py monitor'
   8. ctrl + ] if you need to stop monitoring or execution

### Committing Code to the repository
1. in the terminal type 'git pull'
2. Be careful about resolving any conflicts
3. if none 'git add .'
4. git commit -m '[some descriptive commit message that explains why you added this code]'
5. git push 
   
   

