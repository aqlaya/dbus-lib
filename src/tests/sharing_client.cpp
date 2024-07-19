#include <iostream>
#include <string>
#include <vector>
#include <sdbus-c++/sdbus-c++.h>

int main(int args, char** argv) {

    sdbus::ServiceName destination{"com.system.sharing"};
    sdbus::ObjectPath objectPath{"/"};



    std::unique_ptr<sdbus::IProxy> sharingProxy;
    try 
    {
        sharingProxy = sdbus::createProxy(std::move(destination), std::move(objectPath));
    }
    catch (const sdbus::Error& error) {
        std::cerr << "Here error" << std::endl;
    }

    sdbus::InterfaceName interfaceName{"com.system.sharing"};
    sdbus::MethodName MethodNameRegisterService{"RegisterService"};
    sdbus::MethodName MethodNameOpenFile{"OpenFile"};


    // request #1 RegisterService
    {
        bool result;
        auto method = sharingProxy->createMethodCall(interfaceName, MethodNameRegisterService );
        method << "com.handler.mp4.handler" << std::vector<std::string>{"mp4"};
        auto reply = sharingProxy->callMethod(method);
        reply >> result;
        assert(result);    
    }

    // request #2 RegisterService
    {
        bool result;
        auto method = sharingProxy->createMethodCall(interfaceName, MethodNameRegisterService);
        method <<  "com.handler.photos.handler" << std::vector<std::string>{"jpg", "jpeg"};
        auto reply = sharingProxy->callMethod(method);
        reply >> result;
        assert(result);
    }

    // request #3 OpenFile
    { 
        auto method = sharingProxy->createMethodCall(interfaceName, MethodNameOpenFile);
        method << "/home/adelaida/Desktop/dbus-lib/example_file/file.mp4";
        auto reply = sharingProxy->callMethod(method);
    }

    // request #4 OpenFile
    {
        bool result;
        auto method = sharingProxy->createMethodCall(interfaceName, MethodNameOpenFile);
        method << "./Desktop/del/adelaida.jpeg";
        auto reply = sharingProxy->callMethod(method);
        reply >> result;
        assert(result);
    }


}