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
