cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(rushDisplay C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(rush_display
	rush_display.cpp
)

pico_enable_stdio_usb(rush_display 1)

pico_add_extra_outputs(rush_display)

add_subdirectory(
	lib/EPD_board
)

target_link_libraries(rush_display PUBLIC
	pico_stdlib
	hardware_spi
	EPD_board
	)

pico_enable_stdio_usb(rush_display 1)
pico_enable_stdio_uart(rush_display 0)

# target_include_directories(rush_display PUBLIC
# 	"${PROJECT_BINARY_DIR}"
# 	"${PROJECT_SOURCE_DIR}/lib/EPD_board"
# )