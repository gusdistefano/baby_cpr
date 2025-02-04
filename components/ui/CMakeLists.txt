# Recursively get all .c files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# Exclude a specific directory from the list of sources
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/modified/.*")

#Register the component in ESP-IDF, including the .c files but excluding those in dir_to_exclude
idf_component_register(SRCS "ui_events.c" ${SOURCES}
                    INCLUDE_DIRS .
                    REQUIRES "lvgl buzzer hall_sensor")

