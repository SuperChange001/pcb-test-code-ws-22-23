cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH /home/chao/workspace/RP2040/pico-sdk)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


# rest of your project
if (TARGET tinyusb_device)
    add_executable(hello_usb
            hello.c)

    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(hello_usb hardware_i2c pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hello_usb 1)
    pico_enable_stdio_uart(hello_usb 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hello_usb)



    add_executable(i2c_bus
            bus_scan.c)

    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(i2c_bus hardware_i2c pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(i2c_bus 1)
    pico_enable_stdio_uart(i2c_bus 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(i2c_bus)

    add_executable(hello_adc
            hello_adc.c)

    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(hello_adc hardware_adc hardware_dma pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hello_adc 1)
    pico_enable_stdio_uart(hello_adc 0)

    # creadd_executableate map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hello_adc)

    add_executable(hardware_test hardware_test.c sht31.c adxl345.c)
    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(hardware_test hardware_adc hardware_dma pico_stdlib hardware_i2c)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(hardware_test 1)
    pico_enable_stdio_uart(hardware_test 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hardware_test)


elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()