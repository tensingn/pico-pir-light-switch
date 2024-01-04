# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/nicktensing/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(servo_pir C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_library(setup_pin INTERFACE)

target_sources(setup_pin INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/setup_pin/setup_pin.c)

add_library(servo INTERFACE)

target_sources(servo INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/servo/servo.c)

# Add executable. Default name is the project name, version 0.1

add_executable(servo_pir src/servo_pir.c )

pico_set_program_name(servo_pir "servo_pir")
pico_set_program_version(servo_pir "0.1")

pico_enable_stdio_uart(servo_pir 1)
pico_enable_stdio_usb(servo_pir 0)

# Add the standard library to the build
target_link_libraries(servo_pir
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(servo_pir PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(servo_pir 
  hardware_pwm
  setup_pin
  servo
        )

pico_add_extra_outputs(servo_pir)

