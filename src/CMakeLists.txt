
# file containig method d-bus 
set(
    source_method

    OpenFile.cpp
    OpenFileUsingService.cpp
    RegisterService.cpp
)

add_executable(dbus main.cpp method.hpp ${source_method})

target_include_directories(dbus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ) 

target_compile_options(dbus PUBLIC "-Wall" PUBLIC "-Wextra" PUBLIC "-std=c++20")