cmake_minimum_required(VERSION 3.14)

project(dbus-test VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/)


find_package(sdbus-c++ REQUIRED)

add_subdirectory(src)

target_link_libraries(client PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(dbus PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(service_handler_mp4 PRIVATE SDBusCpp::sdbus-c++)
