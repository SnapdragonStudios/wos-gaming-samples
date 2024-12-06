cmake_minimum_required(VERSION 3.20)

project(DisplayAdapterDetect)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} DisplayAdapterDetect.cpp)

target_link_libraries(${PROJECT_NAME} "DXGI.lib")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Cmake 3.20 - 3.30 conflicting preprocessor defines. Fixed in Cmake 3.31.0
# https://gitlab.kitware.com/cmake/cmake/-/issues/25537
if(CMAKE_VS_PLATFORM_NAME MATCHES "ARM64EC")
    message("Using Cmake ARM64EC preprocessor defines workaround")
    string(REPLACE "/DARM64EC" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/DAMD64"   "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/DARM64EC" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    string(REPLACE "/DAMD64"   "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()
