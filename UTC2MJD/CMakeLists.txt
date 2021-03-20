cmake_minimum_required(VERSION 3.2)

project(UTC LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UTC2JMD UTC2MJD.cpp)
