#include "method.hpp"

/* checks if the service exists */
void check_service(std::fstream& file, const std::string& service);



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
    config.open("sharing.conf", std::ios::app | std::ios::out | std::ios::in);

    check_service(config, service_name);

    config.seekg(0, std::ios_base::end);

    config << "\n" << service_name << " ";


    /* add supported formts separated by space (there is also a space at the end) */
    for (std::string& format: supportedFormats ) 
    {
        config << format << " ";
    }

    config.close();

    auto reply = call.createReply();
    reply.send();
}



void check_service(std::fstream& file, const std::string& service) 
{
    while (!file.eof()) {
        std::string in_service;
        file >> in_service;

        std::cerr << in_service << std::endl;

        /* if record with such service already exists */
        if (in_service == service) {
            throw sdbus::Error(sdbus::Error::Name{"com.system.sharing.RegisterService"}, "An entry with such a service already exists");
        } 
        file.ignore(255, '\n');
    }
}
