add_executable(app_speech_recognize)

target_include_directories(app_speech_recognize
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/
)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.cc ${CMAKE_CURRENT_LIST_DIR}/*.cxx ${CMAKE_CURRENT_LIST_DIR}/*.h ${CMAKE_CURRENT_LIST_DIR}/*.hpp)

target_sources(app_speech_recognize
    PRIVATE
    ${SRC}
)

pico_enable_stdio_usb(app_speech_recognize 1)
pico_enable_stdio_uart(app_speech_recognize 0)

target_link_libraries(app_speech_recognize 
	pico_stdlib
	pico-tflmicro
	hardware_spi
	hardware_adc
	hardware_dma
	hardware_irq
	pico_multicore
)

pico_add_extra_outputs(app_speech_recognize)