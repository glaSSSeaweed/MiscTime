cmake_minimum_required(VERSION 3.2)

project(UTC2GPST LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(CURL)
include_directories(CURL_INCLUDE_DIR)
add_executable(UTC2GPST UTC2GPS.cpp tz.cpp)
target_link_libraries(UTC2GPST ${CURL_LIBRARIES} )
