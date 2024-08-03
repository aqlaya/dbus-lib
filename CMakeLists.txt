cmake_minimum_required(VERSION 3.14)

project(dbus VERSION 2.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

set(CMAKE_CXX_STANDARD 20)


set(SOURCE_PATH  ${CMAKE_SOURCE_DIR}/src)
set(SOURCE_EXAMPLE_SERVICE ${CMAKE_SOURCE_DIR}/example_final_service)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)


# file containig method d-bus 
set(
    source_method 

    ${SOURCE_PATH}/OpenFile.cpp
    ${SOURCE_PATH}/OpenFileUsingService.cpp
    ${SOURCE_PATH}/RegisterService.cpp
)

#second task
add_library(handler SHARED ${SOURCE_PATH}/SharingService.cpp)

# create simlink
set_target_properties(handler PROPERTIES VERSION 1.0.0 SOVERSION 1)

#thirty task
add_executable(example_dbus ${SOURCE_EXAMPLE_SERVICE}/use_shared_lib.cpp)


#first task
add_executable(dbus 
    ${SOURCE_PATH}/main.cpp     
    ${SOURCE_PATH}/RegisterService.cpp
    ${SOURCE_PATH}/OpenFileUsingService.cpp
    ${SOURCE_PATH}/OpenFile.cpp
)


#simple example 
add_executable(service_mp4 ${SOURCE_EXAMPLE_SERVICE}/service_mp4.cpp)
 

include_directories(${INCLUDE_PATH})

find_package(sdbus-c++ REQUIRED)

# link to sdbus-lib

#target_link_libraries(client PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(dbus PRIVATE SDBusCpp::sdbus-c++)

target_link_libraries(service_mp4 PRIVATE SDBusCpp::sdbus-c++)

target_link_libraries(handler PRIVATE SDBusCpp::sdbus-c++)

target_link_libraries(example_dbus PRIVATE SDBusCpp::sdbus-c++)


target_link_libraries(example_dbus PRIVATE handler)

#install target

install(TARGETS handler
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

