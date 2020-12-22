cmake_minimum_required(VERSION 3.15)
project(TwoFish)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp TwoFish.cpp cmake-build-debug/TwoFish.hpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)