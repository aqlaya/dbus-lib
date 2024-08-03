#include "SharingService.hpp"

SharingService::SharingService(std::string&& str, const std::vector<std::string>& supportedFormats, func  lambda )
    : _serviceName(std::move(str))
    , _supportedFormats(supportedFormats)
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

    sharing->addVTable(sdbus::registerMethod("OpenFile").implementedAs(_openFile),
            sdbus::registerSignal("openfile").withParameters<>()).forInterface(_serviceName);

    {  
        /* set sharing.conf using method RegisterService */

        std::string result;

        sdbus::ServiceName SharingServiceName{"com.system.sharing"};
        sdbus::MethodName SharingMethodName{"RegisterService"};
        sdbus::InterfaceName SharingInterfaceName{"com.system.sharing"};

        auto ProxyObject = sdbus::createProxy(std::move(SharingServiceName) , sdbus::ObjectPath{"/"});

        auto method = ProxyObject->createMethodCall(SharingInterfaceName, SharingMethodName);
        method << _serviceName << _supportedFormats;
        

        try {
            auto reply = ProxyObject->callMethod(method);
            reply >> result;
            std::cerr << result << std::endl;
        }
        catch (sdbus::Error& error) {        class Response;
            throw;
        }
    }

    connection->enterEventLoop();

    return 0;
}




