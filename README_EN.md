# Medium-Fidelity Neonatal CPR Simulator

## Project Description

This repository contains the development of the "Neonatal CPR Simulator" project, carried out as part of the Final Project for the Embedded Systems Specialization at UNER. The main objective was to design an accessible and cost-effective device that transforms low-fidelity mannequins into medium-fidelity simulators for neonatal CPR training.

### Key Features:

- Transformation of low-fidelity mannequins into medium-fidelity simulators.
- Real-time feedback on compression depth and frequency.
- Training and evaluation modes.
- Based on an ESP32 microcontroller, a Hall effect sensor, and a touch screen.
- Modular and scalable design compatible with FreeRTOS and LVGL.
- Aligned with SDG 4 to ensure inclusive and sustainable education.

## System Requirements

### Hardware

- **Microcontroller:** ESP32 NodeMCU
- **Sensor:** Hall effect sensor A1321
- **Touchscreen:** LCD display with ILI9341 controller
- **Others:** Neodymium magnet, adapter vest for mannequin

### Software

- ESP-IDF (Espressif Development Framework)
- FreeRTOS
- LVGL (Light and Versatile Graphics Library)
- KiCad (PCB design)
- SquareLine Studio (GUI design)

## Installation and Usage

### Hardware Setup

1. Mount the Hall effect sensor on the mannequin adapter vest.
2. Connect the touch LCD display to the ESP32 via the SPI bus.
3. Integrate the designed electronic circuit with the prototype.

### Development Environment Setup

1. Clone this repository:
   
   ```bash
   git clone https://github.com/your_user/neonatal-cpr-simulator.git
   ```

2. Set up the ESP-IDF environment following the [official documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/).

3. Build the project:
   
   ```bash
   idf.py build
   ```

4. Flash the firmware onto the ESP32:
   
   ```bash
   idf.py flash
   ```

5. Monitor the serial output:
   
   ```bash
   idf.py monitor
   ```

### Operating Modes

- **Training Mode:** Real-time feedback with visual and audible metrics.
- **Evaluation Mode:** Data logging for post-analysis.

## Results and Tests

The system has been validated in simulation environments at the Cruz Roja Argentina, Santa Fe branch, demonstrating:

- High precision in compression detection.
- Efficient use of ESP32 resources (CPU load peaks < 20%).
- Compatibility with neonatal torsos thanks to a detection range of up to 7.5 cm.

## Future Improvements

- Bluetooth and Wi-Fi connectivity for remote monitoring and OTA updates.
- Development of a web interface to eliminate the need for a physical display.
- Optimization of the detection algorithm for more demanding scenarios.

## License

This project is licensed under the MIT License, except for the proprietary module associated with the Hall effect sensor. See the `LICENSE` file for more details.

## Contact

**Author:** Gustavo Di Stefano  
**Email:** [narniancoder@gmail.com](mailto:narniancoder@gmail.com)  
**Institution:** UNER, Embedded Systems Specialization
