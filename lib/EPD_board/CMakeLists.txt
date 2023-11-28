include(pico_sdk_import.cmake)
pico_sdk_init()

add_library(EPD_board STATIC
	src/DEV.cpp
	src/EPD.cpp
)

target_link_libraries(EPD_board PUBLIC
	pico_stdlib
	hardware_spi
)

target_include_directories(EPD_board PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)