#include "method.hpp"

/* function to call the final service method */
void OpenServiceForFile(const std::string& service, const std::string& path) 
{
    sdbus::ServiceName ServiceName{service};

    auto ProxyObject = sdbus::createProxy(ServiceName, sdbus::ObjectPath{"/"});

    sdbus::InterfaceName InterfaceName{service};
    sdbus::MethodName MethodName{"OpenFile"};

    auto method = ProxyObject->createMethodCall(InterfaceName, MethodName);

    method << path;

    auto reply = ProxyObject->callMethod(method);
    

    std::cerr << "The OpenFile method was called" << std::endl; 
}


int main() {

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
    sharing->addVTable( sdbus::MethodVTableItem{sdbus::MethodName{"RegisterService"}, sdbus::Signature{"sas"}, {}, sdbus::Signature{"s"}, {}, &RegisterService, {}},
                        sdbus::MethodVTableItem{sdbus::MethodName{"OpenFile"}, sdbus::Signature{"s"}, {}, sdbus::Signature{"s"}, {}, &OpenFile, {} },
                        sdbus::MethodVTableItem{sdbus::MethodName{"OpenFileUsingService"}, sdbus::Signature{"ss"}, {}, sdbus::Signature{"s"}, {}, &OpenFileUsingService, {}} 
    ).forInterface(interfaceName);

    // Run the I/O event loop on the bus connection.
    connection->enterEventLoop();


    return 0;
}