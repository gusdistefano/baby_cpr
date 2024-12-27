# Simulador de Mediana Fidelidad para RCP Neonatal

## Descripción del Proyecto

Este repositorio contiene el desarrollo del proyecto "Simulador para RCP Neonatal", realizado como parte del Proyecto Final de la Especialización en Sistemas Embebidos de la UNER. El objetivo principal fue diseñar un dispositivo accesible y económico que permita transformar maniquíes de baja fidelidad en simuladores de mediana fidelidad para el entrenamiento en RCP neonatal. 

### Características Principales:

- Transformación de maniquíes de baja fidelidad en simuladores de mediana fidelidad.
- Retroalimentación en tiempo real sobre la profundidad y frecuencia de las compresiones.
- Modos de entrenamiento y evaluación.
- Basado en un microcontrolador ESP32, con un sensor de efecto Hall y una pantalla táctil.
- Diseño modular y escalable compatible con FreeRTOS y LVGL.
- Alineado con el ODS 4 para garantizar una educación inclusiva y sostenible.

## Requisitos del Sistema

### Hardware

- **Microcontrolador:** ESP32 NodeMCU
- **Sensor:** Sensor de efecto Hall A1321
- **Pantalla táctil:** Display LCD con controlador ILI9341
- **Otros:** Imán de neodimio, chaleco adaptador para maniquí

### Software

- ESP-IDF (Framework de desarrollo de Espressif)
- FreeRTOS
- LVGL (Light and Versatile Graphics Library)
- KiCad (diseño de PCB)
- SquareLine Studio (diseño de interfaz gráfica)

## Instalación y Uso

### Preparación del Hardware

1. Montar el sensor de efecto Hall en el chaleco adaptador para maniquí.
2. Conectar el display LCD táctil al ESP32 mediante el bus SPI.
3. Integrar el circuito electrónico diseñado con el prototipo.

### Configuración del Entorno de Desarrollo

1. Clonar este repositorio:
   
   ```bash
   git clone https://github.com/tu_usuario/simulador-rcp-neonatal.git
   ```

2. Configurar el entorno ESP-IDF siguiendo la [documentación oficial](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/).

3. Compilar el proyecto:
   
   ```bash
   idf.py build
   ```

4. Flashear el firmware en el ESP32:
   
   ```bash
   idf.py flash
   ```

5. Monitorizar la salida en serie:
   
   ```bash
   idf.py monitor
   ```

### Modos de Operación

- **Modo Entrenamiento:** Retroalimentación en tiempo real con métricas visuales y sonoras.
- **Modo Evaluación:** Registro de datos para análisis posterior.

## Resultados y Pruebas

El sistema ha sido validado en entornos de simulación en la Cruz Roja Argentina filial Santa Fe, demostrando:

- Alta precisión en la detección de compresiones.
- Uso eficiente de los recursos del ESP32 (picos de carga de CPU < 20%).
- Compatibilidad con torsos neonatales gracias a un rango de detección de hasta 7.5 cm.

## Futuras Mejoras

- Conectividad Bluetooth y Wi-Fi para monitoreo remoto y actualizaciones OTA.
- Desarrollo de una interfaz web para eliminar la necesidad de un display físico.
- Optimización del algoritmo de detección para escenarios más exigentes.

## Licencia

Este proyecto está bajo la licencia MIT, salvo por el módulo propietario asociado al sensor de efecto Hall. Consulta el archivo `LICENSE` para más detalles.

## Contacto

**Autor:** Gustavo Di Stefano  
**Correo:** [narniancoder@gmail.com](mailto:narniancoder@gmail.com)  
**Institución:** UNER, Especialización en Sistemas Embebidos

---

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
