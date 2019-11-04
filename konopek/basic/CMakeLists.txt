cmake_minimum_required(VERSION 3.15)
project(crypto_pals_basic)

set(CMAKE_CXX_STANDARD 17)

add_executable(crypto_pals_basic main.cpp simpleXor.hpp base64.hpp)