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
    # creates test_pac193x executable
    add_executable(test_pac193x app/test_pac193x.c)
    target_include_directories(test_pac193x PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_pac193x pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_pac193x 1)
    pico_enable_stdio_uart(test_pac193x 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_pac193x)
    ################################################################################
    # creates test_pac193x executable
    add_executable(test_sht31 app/test_sht31.c)
    target_include_directories(test_sht31 PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_sht31 pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_sht31 1)
    pico_enable_stdio_uart(test_sht31 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_sht31)
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
    # creates test_hello executable
    add_executable(test_hello app/test_hello.c)
    target_include_directories(test_hello PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_hello pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_hello 1)
    pico_enable_stdio_uart(test_hello 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_hello)
    ################################################################################
    # creates test_echo executable
    add_executable(test_echo app/test_echo.c)
    target_include_directories(test_echo PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_echo pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_echo 1)
    pico_enable_stdio_uart(test_echo 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_echo)
    ################################################################################
    # creates test_data_adc_10_times executable
    add_executable(test_data_adc_10_times app/test_data_adc_10_times.c)
    target_include_directories(test_data_adc_10_times PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_data_adc_10_times pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_data_adc_10_times 1)
    pico_enable_stdio_uart(test_data_adc_10_times 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_data_adc_10_times)
    ################################################################################
    # creates test_data_adc_batch_reading executable
    add_executable(test_data_adc_batch_reading app/test_data_adc_batch_reading.c)
    target_include_directories(test_data_adc_batch_reading PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(test_data_adc_batch_reading pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(test_data_adc_batch_reading 1)
    pico_enable_stdio_uart(test_data_adc_batch_reading 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(test_data_adc_batch_reading)



    
    ################################################################################

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()