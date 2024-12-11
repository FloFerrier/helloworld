cmake_minimum_required(VERSION 3.19)

project(helloworld C)

#set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_C_EXTENSIONS ON)

include(cmake/cmocka.cmake)

## BSP Led
add_library(bsp_led OBJECT led.c)
add_library(bsp::led ALIAS bsp_led)

## BSP Serial
add_library(bsp_serial OBJECT serial.c)
add_library(bsp::serial ALIAS bsp_serial)

## Firmware
add_executable(firmware)
target_sources(firmware PRIVATE main.c)
target_link_libraries(firmware bsp::led bsp::serial)

## Test Suite
include(CTest)
enable_testing()

## Test Led
add_executable(test_led test_led.c)
target_link_libraries(test_led cmocka-static bsp::led)
add_executable(test::led ALIAS test_led)
add_test(NAME test::led COMMAND test::led)

## Test Serial
add_executable(test_serial test_serial.c)
target_link_libraries(test_serial cmocka-static bsp::serial)
add_executable(test::serial ALIAS test_serial)
add_test(NAME test::serial COMMAND test::serial)
