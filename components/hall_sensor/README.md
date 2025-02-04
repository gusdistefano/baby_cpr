# Hall Sensor Library for ESP-IDF

This library provides functionalities to read data from a Hall sensor and manage the data flow between producer and consumer tasks using FreeRTOS queues.

## Features

- **Hall Sensor Data Structure:** Stores raw, filtered, and accumulated ADC values along with a timestamp.
- **Data Producer:** Starts a task that continuously reads data from the Hall sensor and sends it to a FreeRTOS queue.
- **Data Consumer Example:** Provides an example of how to receive and process Hall sensor data from the queue.

## Installation

1. Copy the `hall_sensor` module into the `components/` directory of your ESP-IDF project.
   
   The project structure should look like this:
   
   ```plaintext
   your_project/
   ├── CMakeLists.txt
   ├── main/
   │   ├── CMakeLists.txt
   │   └── your_main_file.c
   └── components/
       └── hall_sensor/
           ├── include/
           │   └── hall_sensor.h
           └── hall_sensor.c
   ```

2. In the root `CMakeLists.txt` file of your project, add the following line to include the `components/` directory:
   
   ```cmake
   set(EXTRA_COMPONENT_DIRS ./components/)
   ```

3. In the `CMakeLists.txt` file of your main application (e.g., in the `main/` directory), include the `hall_sensor` component:
   
   ```cmake
   idf_component_register(SRCS "your_main_file.c"
                          INCLUDE_DIRS "include"
                          REQUIRES "dsp esp_adc driver hall_sensor")
   ```

4. In your source files where you will use the Hall sensor functions, include the library:
   
   ```c
   #include "hall_sensor.h"
   ```

## Example Usage

### Hall Sensor Data Producer

To start reading data from the Hall sensor, simply call:

```c
hall_sensor_start();
```

### Consumer Task Example

Here is an example of how to create a consumer task that receives and processes Hall sensor data from the queue:

```c
#include "hall_sensor.h"

extern QueueHandle_t hall_sensor_data_queue;

void consumer_task(void *pvParameter)
{
    hall_sensor_data_t received_data;

    while (1)
    {
        // Receive data from the queue
        if (xQueueReceive(hall_sensor_data_queue, &received_data, portMAX_DELAY) == pdTRUE)
        {
            printf("> filtered: %.2f\n", received_data.filtered_value);
            printf("> adc_acum: %.2f\n", received_data.adc_acum);
            printf("> raw_value: %i\n", received_data.raw_value);
            printf("> time: %li\n", received_data.timestamp);
        }
    }
}

void app_main()
{
    hall_sensor_start();
    xTaskCreate(consumer_task, "Consumer Task", 2048, NULL, 5, NULL);
}
```

## License

This software and its associated documentation files (the "Software") are the property of the copyright holder.  
The unauthorized reproduction, modification, distribution, sublicense, or sale of the Software is prohibited unless explicitly permitted by the copyright holder.  

Permission is hereby granted, free of charge, to authorized individuals or entities for the sole purpose of using the Software in accordance with the terms set forth by the copyright holder. This permission is non-transferable and may be revoked at any time.  

Redistribution of this Software, whether in source or binary form, is strictly forbidden without prior written permission from the copyright holder.  

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions to this library are welcome! Feel free to open issues or submit pull requests to add new features or improve existing ones.

## Contact

For any inquiries or suggestions, please contact Gus Di Stefano at [narniancoder@gmail.com](mailto:narniancoder@gmail.com).
