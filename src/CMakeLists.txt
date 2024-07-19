
add_executable(client sharing_client.cpp)

add_executable(dbus main.cpp method.hpp OpenFile.cpp OpenFileUsingService.cpp RegisterService.cpp)

add_executable(service_handler_mp4 service_mp4.cpp)

