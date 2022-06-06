# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include($ENV{PICO_SDK_PATH}/tools/CMakeLists.txt)

# Set name of project (as PROJECT_NAME) and C/C   standards
project(PicoMacro C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

target_sources(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/lib/wsLED.h
        ${CMAKE_CURRENT_LIST_DIR}/lib/wsLED.cpp
        ${CMAKE_CURRENT_LIST_DIR}/lib/usb_descriptors.h
        ${CMAKE_CURRENT_LIST_DIR}/lib/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/usb_hid.h
        ${CMAKE_CURRENT_LIST_DIR}/lib/usb_hid.cpp
        ${CMAKE_CURRENT_LIST_DIR}/lib/stdio_usb.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/kbScan.h
        ${CMAKE_CURRENT_LIST_DIR}/lib/kbScan.cpp
        )

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR}/lib
        )

# Create C header file with the name <pio program>.pio.h
pico_generate_pio_header(${PROJECT_NAME}  
        ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_pio
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb output, disable uart output
# TODO
# bring back USB prinflater
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)