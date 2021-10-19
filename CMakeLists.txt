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




# rest of your project
#add_library(sensor_lib)

if (TARGET tinyusb_device)

    add_executable(hardware_test hardware_test.c)
    add_subdirectory(sensor_lib)

    # Pull in our pico_stdlib which aggregates commonly used features
    target_link_libraries(hardware_test hardware_adc hardware_dma pico_stdlib hardware_i2c sensor_lib)


    # enable usb output, disable uart output
    pico_enable_stdio_usb(hardware_test 1)
    pico_enable_stdio_uart(hardware_test 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(hardware_test)


elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()