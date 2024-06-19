cmake_minimum_required(VERSION 3.5)

project(SH110X)

add_subdirectory(Pi-Pico-SDK-Adafruit-GFX-Library)
add_library(SH110X STATIC
    SH1106.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(SH110X pico_stdlib Adafruit_GFX)
target_include_directories(SH110X PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
