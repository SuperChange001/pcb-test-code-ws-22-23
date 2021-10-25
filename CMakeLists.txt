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
   
    # creates hardware_test executable
    add_executable(hardware_test app/hardware_test.c)
    target_include_directories(hardware_test PUBLIC .)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(hardware_test pico_stdlib hardware_setup)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hardware_test 1)
    pico_enable_stdio_uart(hardware_test 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hardware_test)


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



elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()