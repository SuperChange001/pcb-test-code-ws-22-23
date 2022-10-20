cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

if (TARGET tinyusb_device)

    # adds sensor lib dependency as Interface
    add_subdirectory(sensor_lib)

    # adds hardware_setup dependency
    add_subdirectory(setup)
    ################################################################################
    # creates test_led executable
    add_executable(test_led app/test_led.c)
    target_include_directories(test_led PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_led pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_led 1)
    pico_enable_stdio_uart(test_led 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_led)
    ################################################################################
    # creates i2c_bus_scan executable
    add_executable(i2c_bus_scan app/i2c_bus_scan.c)
    target_include_directories(i2c_bus_scan PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(i2c_bus_scan pico_stdlib hardware_i2c)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(i2c_bus_scan 1)
    pico_enable_stdio_uart(i2c_bus_scan 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(i2c_bus_scan)
    ################################################################################
    # creates test_adxl345 executable
    add_executable(test_adxl345 app/test_adxl345.c)
    target_include_directories(test_adxl345 PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_adxl345 pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_adxl345 1)
    pico_enable_stdio_uart(test_adxl345 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_adxl345)
    ################################################################################
    # creates test_adc_vol executable
    add_executable(test_adc_vol app/test_adc_voltage_measure.c)
    target_include_directories(test_adc_vol PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_adc_vol pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_adc_vol 1)
    pico_enable_stdio_uart(test_adc_vol 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_adc_vol)
    ################################################################################
    # creates test_adc_vol executable
    add_executable(test_adc_mic app/test_adc_microphone.c)
    target_include_directories(test_adc_mic PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_adc_mic pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_adc_mic 1)
    pico_enable_stdio_uart(test_adc_mic 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_adc_mic)
    ################################################################################
    # creates test_all_sensor executable
    add_executable(test_all_sensors app/test_all_sensors.c)
    target_include_directories(test_all_sensors PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_all_sensors pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_all_sensors 1)
    pico_enable_stdio_uart(test_all_sensors 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_all_sensors)
    ################################################################################

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()