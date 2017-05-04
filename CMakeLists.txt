cmake_minimum_required (VERSION 2.6)

set(ARDU_RUNTIME_CONFIG_FILE ${CMAKE_SOURCE_DIR}/runtime.txt)
set(ARDU_PLATFORM_PATH "/home/nazgee/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/multiarch-arduino-cmake/cmake/ToolchainESP.cmake)

project(first C CXX ASM)
add_subdirectory(blinky)

