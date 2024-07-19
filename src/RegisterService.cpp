#include "method.hpp"

/* method for writing to a configuration file */
void RegisterService(sdbus::MethodCall call)
{

    std::string service_name;
    call >> service_name;

    std::vector<std::string> supportedFormats;
    call >> supportedFormats;


    /* if empty vector for supportedformated */
    if (supportedFormats.empty()) {
        throw sdbus::Error(sdbus::Error::Name{"com.system.sharing.RegisterService.Error"}, "No formats provided"); 
    }

    std::fstream config;
    config.open("sharing.conf", std::ios::app | std::ios::out);
    
   config << service_name << " ";

    std::cerr << "Service was written in file" << std::endl;

    /* add supported formts separated by space (there is also a space at the end) */
    for (std::string& format: supportedFormats ) 
    {
        config << format << " ";
    }
    config << '\n';

    config.close();

    auto reply = call.createReply();
    reply << "The name of the service is written to the file";
    reply.send();
}




