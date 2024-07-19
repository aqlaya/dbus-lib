#include "method.hpp"



void OpenFileUsingService(sdbus::MethodCall call) 
{
    std::string path, service;
    call >> path >> service;

    sdbus::ServiceName ServiceName{service};
    sdbus::ObjectPath  ObjectPath{"/"};

    bool find_connection = false;

    try {
        std::unique_ptr<sdbus::IConnection> connection = sdbus::createBusConnection(sdbus::ServiceName{service}); 
    }
    catch (const sdbus::Error& error) {
        std::cerr << "Error name: " << error.getName() << "\n";
        std::cerr << error.getMessage() << std::endl;


        std::cerr << "Requier service was found: " << service << std::endl;

        find_connection = true;    
    }

    if (!find_connection)
        throw sdbus::Error{sdbus::Error::Name{"com.system.sharing.OpenFileUsingService"}, "Service not found"};


    OpenServiceForFile(ServiceName, ObjectPath, path);    
}