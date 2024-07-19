#include "method.hpp"

/* function to call the final service method */
void OpenServiceForFile(const sdbus::ServiceName& service, const sdbus::ObjectPath& objectpath, const std::string& path) 
{
    std::cerr << "Method will invoked" << std::endl;

    auto ProxyObject = sdbus::createProxy(service, objectpath);

    sdbus::InterfaceName InterfaceName{"com.system.sharing"};
    sdbus::MethodName MethodName{"OpenFile"};

    auto method = ProxyObject->createMethodCall(InterfaceName, MethodName);

    method << path;

    auto reply = ProxyObject->callMethod(method);


    std::cerr << "Method was invoked" << std::endl;
 
}


int main(int args, char* argv[]) {

    sdbus::IObject* sharing_object; 

    sdbus::ServiceName serviceName{"com.system.sharing"};

    /* create connection on session bus */
    std::unique_ptr<sdbus::IConnection> connection = sdbus::createBusConnection(serviceName);

    sdbus::ObjectPath objectPath{"/"};

    /* create D-bus object */
    auto sharing = sdbus::createObject(*connection, std::move(objectPath));

    sharing_object = sharing.get();

    sdbus::InterfaceName interfaceName{"com.system.sharing"};

    // register D-Bus methods and signals on the concatenator object, and exports the object.
    sharing->addVTable( sdbus::MethodVTableItem{sdbus::MethodName{"RegisterService"}, sdbus::Signature{"sas"}, {}, sdbus::Signature{""}, {}, &RegisterService, {}},
                        sdbus::MethodVTableItem{sdbus::MethodName{"OpenFile"}, sdbus::Signature{"s"}, {}, sdbus::Signature{""}, {}, &OpenFile, {} },
                        sdbus::MethodVTableItem{sdbus::MethodName{"OpenFileUsingService"}, sdbus::Signature{"ss"}, {}, sdbus::Signature{""}, {}, &OpenFileUsingService, {}} 
    ).forInterface(interfaceName);

    // Run the I/O event loop on the bus connection.
    connection->enterEventLoop();


    return 0;
}