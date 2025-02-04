# Buzzer Driver for ESP-IDF

This library provides an easy-to-use interface for controlling a passive buzzer with the ESP-IDF framework. It includes functions to initialize the buzzer and play tones with or without volume control, making it ideal for generating sound alerts or feedback in embedded systems.

## Features

- **Buzzer Initialization:** Prepares the buzzer for playing sounds by configuring the necessary GPIO pins.

- **Music and Tone Playback with Volume Control:** Play tones or musical notes at specific frequencies and durations, with adjustable volume.

- **Tone and Music Playback with Preconfigured Volume:** Plays tones or music using the default volume configured via `menuconfig`.

- **Configurable Pin and Default Volume:** The buzzer pin (`BUZZER_PIN`) and default volume (`DEFAULT_VOLUME`) can be set through the `idf.py menuconfig` tool.

- **Flexible API:**
  
  - `play_music`: Play musical notes with explicit volume control.
  
  - `play_music_nv`: Play musical notes using preconfigured volume.
  
  - `play_tone`: Play simple tones for alerts or feedback using the system volume.

- **Preprogrammed Melodies:** Includes popular melodies such as "Pirates of the Caribbean," "Super Mario," and "Star Wars" themes, ready to play on the buzzer.
  Additional features and improvements will be added over time to enhance the buzzer's capabilities.

## Installation

1. Copy the `buzzer` module into the `components/` directory of your ESP-IDF project.
   
   The project structure should look like this:
   
   ```plaintext
   your_project/
   ├── CMakeLists.txt
   ├── main/
   │   ├── CMakeLists.txt
   │   └── your_main_file.c
   └── components/
       └── buzzer/
          ├── include/
          │   └── buzzer.h
          │   └── melody.h
          └── buzzer.c
          └── melody.c
   ```

2. In the root `CMakeLists.txt` file of your project, add the following line to include the `components/` directory:
   
   ```cmake
   set(EXTRA_COMPONENT_DIRS ./components/)
   ```

3. In the `CMakeLists.txt` file of your main application (e.g., in the `main/` directory), include the `buzzer` and `melody` components:
   
   ```cmake
   idf_component_register(SRCS "your_main_file.c"
                       INCLUDE_DIRS "include"
                       REQUIRES "buzzer" "melody")
   ```

4. In your source files where you will use the buzzer functions, include the libraries:
   
   ```c
   #include "buzzer.h"
   #include "melody.h"
   ```

## Configuration

Before using the buzzer, configure the GPIO pin and the default volume level via the ESP-IDF configuration tool (`idf.py menuconfig`):

- **BUZZER_PIN:** Set the GPIO pin that controls the buzzer.
- **DEFAULT_VOLUME:** Set the default volume level for tone generation without explicit volume control.

To access these settings, run:

```bash
idf.py menuconfig
```

Navigate to the Buzzer configuration section to set the pin and volume as needed.

## Example Usage

### Initializing the Buzzer

To initialize the buzzer before playing tones:

```c
#include "buzzer.h"

init_buzzer();
```

### Playing a Music with Volume Control

To play a musical note with a specific frequency, duration, and volume:

```c
#include "buzzer.h"

uint32_t frequency = 4400;  // 440 Hz tone
uint32_t duration = 500;    // 500 milliseconds
uint32_t volume = 10;       // Volume level (hardware-specific)

play_music(frequency, duration, volume);
```

### Playing a Music without Volume Control

To play a musical note using the default or preconfigured volume:

```c
#include "buzzer.h"

uint32_t frequency = 4400;  // 4400 Hz tone
uint32_t duration = 500;    // 500 milliseconds

play_tone_nv(frequency, duration);
```

### Playing a simple tone

For alerts, beeps, or other feedback tones using the system-wide volume configuration:

```c

```



## Playing Preprogrammed Melodies

The library also includes functions to play popular melodies using the buzzer:

- **"Pirates of Caribbean" Theme:**
  
  ```c
  #include "melody.h"
  
  play_pirate();
  ```

- **"Super Mario" Theme:**
  
  ```c
  #include "melody.h"
  
  play_super_mario();
  ```

- **"Star Wars" Theme:**
  
  ```c
  #include "melody.h"
  
  play_star_wars();
  ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the buzzer driver or add new features.

## Contact

For any inquiries or suggestions, please contact Gus Di Stefano at [narniancoder@gmail.com](mailto:narniancoder@gmail.com).
