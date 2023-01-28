cmake_minimum_required(VERSION 3.5)

project(OtusHomework_4_IpPrint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_4_IpPrint main.cpp)

install(TARGETS OtusHomework_4_IpPrint
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
