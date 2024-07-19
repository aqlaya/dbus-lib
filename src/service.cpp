#include "service.hpp"


SharingService::SharingService(std::string&& str, std::vector<std::string>& supportedFormats, func&  lambda )
    : _supportedFormats(supportedFormats)
    , _serviceName(std::move(str))
    , _openFile(lambda)
{
} 

int SharingService::start() 
{
    std::unique_ptr<sdbus::IConnection> connection;
    try 
    {
        connection = sdbus::createBusConnection(sdbus::ServiceName{_serviceName});
    }
    catch (sdbus::Error& error) 
    {
        throw;
    }

    auto sharing = sdbus::createObject(*connection, sdbus::ObjectPath{"/"});


    sharing->addVTable(sdbus::registerMethod("OpenFile").implementedAs(_openFile)).forInterface(std::move(_serviceName));

    {  
        /* set sharing.conf using method RegisterService */

        sdbus::ServiceName SharingServiceName{"com.system.sharing"};
        sdbus::MethodName SharingMethodName{"RegisterName"};
        sdbus::InterfaceName SharingInterfaceName{"com.system.sharing"};

        auto ProxyObject = sdbus::createProxy(std::move(SharingServiceName) , sdbus::ObjectPath{"/"});

        auto method = ProxyObject->createMethodCall(SharingInterfaceName, SharingMethodName);
        method << _serviceName << _supportedFormats;

        try {
            ProxyObject->callMethod(method);
        }
        catch (sdbus::Error& error) {
            throw;
        }
    }


    connection->enterEventLoop();

    return 0;
}