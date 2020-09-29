cmake_minimum_required(VERSION 3.13)

project(vectr)

add_library(vectr INTERFACE)
target_include_directories(vectr INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_features(vectr INTERFACE cxx_std_17)

add_executable(vectr_example example.cpp)
target_compile_features(vectr_example PRIVATE cxx_std_17)
target_link_libraries(vectr PRIVATE)