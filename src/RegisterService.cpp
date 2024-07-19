#include "method.hpp"



void RegisterService(sdbus::MethodCall call)
{

    std::string service_name;
    call >> service_name;


    std::vector<std::string> supportedFormats;
    call >> supportedFormats;

    if (supportedFormats.empty()) {
        throw sdbus::Error(sdbus::Error::Name{"com.system.sharing.RegisterService.Error"}, "No formats provided"); 
    }

    std::ofstream config;
    config.open("./sharing.conf", std::ios::app);

    config << service_name << " ";

    for (std::string& format: supportedFormats ) 
    {
        config << format << " ";
    }

    config << std::endl;

    auto reply = call.createReply();
    reply << true;
    reply.send();
}

