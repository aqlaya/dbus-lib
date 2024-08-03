#include <iostream>
#include <string>
#include <vector>
#include <sdbus-c++/sdbus-c++.h>
#include <memory>
#include <fstream>

sdbus::IObject* handler_mp4;

void OpenFile(sdbus::MethodCall call) 
{
    std::string path;
    call >> path;

    std::fstream file(path, std::ios::app | std::ios::in | std::ios::out);

    if (file.is_open())
    {
        // ...

        std::cerr << "File was opened: " << path << std::endl;

        file.close();


        auto reply = call.createReply();
        reply.send();
    }
    else 
    {
        throw sdbus::Error(sdbus::Error::Name{"com.system.sharing.Eror"}, "Fail open file");
    }


} 

int main() {
    sdbus::ServiceName ServiceName{"com.system.mp4"};
    sdbus::ObjectPath ObjectPath{"/"};


    std::unique_ptr<sdbus::IConnection> connection      = sdbus::createBusConnection(ServiceName);
    std::unique_ptr<sdbus::IObject>     handler         = sdbus::createObject(*connection, std::move(ObjectPath));


    handler_mp4 = handler.get();

    sdbus::MethodName MethodName{"OpenFile"};
    sdbus::InterfaceName InterfaceName{"com.system.mp4"};

    handler->addVTable(
        sdbus::MethodVTableItem{MethodName, sdbus::Signature{"s"}, {}, sdbus::Signature{""}, {}, &OpenFile, {}}
    ).forInterface(InterfaceName);


    connection->enterEventLoop();

    return 0;
}