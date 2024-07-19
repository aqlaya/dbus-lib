
# file containig method d-bus 
set(
    source_method

    OpenFile.cpp
    OpenFileUsingService.cpp
    RegisterService.cpp
)

#second task
add_library(handler SHARED service.cpp)


#first task
add_executable(dbus main.cpp ${source_method})

#simple example 
add_executable(service_mp4 ${CMAKE_CURRENT_SOURCE_DIR}/example_final_service/service_mp4.cpp)

target_compile_options(handler PUBLIC "-std=c++17")

target_include_directories(dbus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ) 


target_include_directories(handler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )

target_compile_options(dbus   PUBLIC "-std=c++17")