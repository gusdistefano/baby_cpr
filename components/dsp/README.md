# DSP - Digital Signal Processing

### Filtros Varios

1 - Kalman

2 - **Filtro de Media Exponencial** o **Filtro de Primer Orden**, también conocido como **Filtro de Suavizado Exponencial** o **Filtro Pasa Bajas de Primer Orden**.

Aquí tienes el `README.md` actualizado con la estructura correcta del componente:

```markdown
# DSP Library for ESP-IDF

This library provides digital signal processing (DSP) utilities for the ESP-IDF framework, including implementations of a Kalman filter and an Exponential Moving Average (Low Pass Filter). The library is designed for use in embedded systems where signal smoothing and state estimation are required.

## Features

- **Kalman Filter:** Helps estimate the true value of a signal by minimizing the noise and uncertainties in the measurements.
- **Exponential Moving Average (Low Pass Filter):** Smooths out sensor data and reduces noise in the measurements.

Additional DSP functions will be added over time to expand the capabilities of this library.

## Installation

1. Copy the `dsp` module into the `components/` directory of your ESP-IDF project.

   The project structure should look like this:

   ```plaintext
   your_project/
   ├── CMakeLists.txt
   ├── main/
   │   ├── CMakeLists.txt
   │   └── your_main_file.c
   └── components/
       └── dsp/
           ├── include/
           │   └── dsp.h
           └── dsp.c
```

2. In the root `CMakeLists.txt` file of your project, add the following line to include the `components/` directory:
   
   ```cmake
   set(EXTRA_COMPONENT_DIRS ./components/)
   ```

3. In the `CMakeLists.txt` file of your main application (e.g., in the `main/` directory), include the `dsp` component:
   
   ```cmake
   idf_component_register(SRCS "your_main_file.c"
                          INCLUDE_DIRS "include"
                          REQUIRES "esp_timer esp_adc driver dsp")
   ```

4. In your source files where you will use the DSP functions, include the library:
   
   ```c
   #include "dsp.h"
   ```

## Example Usage

### Kalman Filter

To initialize and use the Kalman filter:

```c
#include "dsp.h"

kalmanFilter_t kf;
kalman_init(&kf, 0.01, 1.0, 0.0);  // Initialize with q, r, and initial state.

float measurement = 0.5;  // Example sensor measurement.
float estimated_value = kalman_update(&kf, &measurement);
```

### Low Pass Filter (Exponential Moving Average)

To apply a low pass filter to smooth sensor data:

```c
#include "dsp.h"

float filtered_value = 0.0;  // Start with an initial filtered value.
float current_measurement = 1.2;  // New sensor data.
float alpha = 0.7;  // Smoothing factor.

low_pass_filter(&filtered_value, &current_measurement, alpha);
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions to this library are welcome! As this is an ongoing project, feel free to open issues or submit pull requests to add new DSP functions or improve existing ones.

## Contact

For any inquiries or suggestions, please contact Gus Di Stefano at [narniancoder@gmail.com](mailto:narniancoder@gmail.com).
