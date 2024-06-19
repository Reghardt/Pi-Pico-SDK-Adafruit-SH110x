cmake_minimum_required(VERSION 3.5)

project(SH1106)

add_library(SH1106 STATIC
    SH1106.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(SH1106 pico_stdlib Adafruit_GFX)
target_include_directories(SH1106 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
