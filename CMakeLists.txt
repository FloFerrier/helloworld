cmake_minimum_required(VERSION 3.19)

project(helloworld C)

#set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_STANDARD_REQUIRED ON)
#set(CMAKE_C_EXTENSIONS ON)

################
#### MODULE ####
################

## BSP Led
add_library(bsp_led OBJECT led.c)
add_library(bsp::led ALIAS bsp_led)

## BSP Serial
add_library(bsp_serial OBJECT serial.c)
add_library(bsp::serial ALIAS bsp_serial)

##################
#### FIRMWARE ####
##################
add_executable(firmware)
target_sources(firmware PRIVATE main.c)
target_link_libraries(firmware bsp::led bsp::serial)

##############
#### TEST ####
##############
include(cmake/cmocka.cmake)
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

###################
#### PACKAGING ####
###################
if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CPACK_PACKAGE_NAME "name")
    set(CPACK_PACKAGE_VENDOR "vendor")
    set(CPACK_PACKAGE_VERSION_MAJOR 1)
    set(CPACK_PACKAGE_VERSION_MINOR 0)
    set(CPACK_PACKAGE_VERSION_PATCH 0)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_CHECKSUM "SHA256")
    set(CPACK_PACKAGE_FILE_NAME "filename-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

    if(TARGET firmware)
        execute_process(COMMAND git rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_STRIP_TRAILING_WHITESPACE
            OUTPUT_VARIABLE GIT_HASH
        )
        set_target_properties(firmware PROPERTIES OUTPUT_NAME firmware-${GIT_HASH})
    endif()

    install(TARGETS firmware DESTINATION .)
    install(FILES Readme.md DESTINATION .)

    include(CPack)
endif()