cmake_minimum_required(VERSION 3.2)
project(UTC2JD_MJD LANGUAGES CXX)

set(CMAKE_LANGUAGE_STANDARD 11)
set(CMAKE_LANGUAGE_STANDARD_REQUIRED ON)
find_package(CURL)
include_directories(CURL_INCLUDE_DIR)
add_executable(test main.cpp tz.cpp)
target_link_libraries(test ${CURL_LIBRARIES})

