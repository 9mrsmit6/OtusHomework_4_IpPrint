cmake_minimum_required(VERSION 3.5)

project(print_ip LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(print_ip main.cpp printIp.hpp)

install(TARGETS print_ip
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
