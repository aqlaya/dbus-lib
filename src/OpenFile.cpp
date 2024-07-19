#include "method.hpp"


void OpenFile(sdbus::MethodCall call) {
    std::string path;
    call >> path;

    std::string extention = path.substr(path.find_last_of('.') + 1);

    
    if (!std::filesystem::exists("./sharing.conf")) {
        std::fstream file("sharing.conf", std::ios::out);
        file.close();
    }

    std::fstream file;
    file.open("sharing.conf", std::ios::in | std::ios::out);

    sdbus::MethodName MethodName{"OpenFile"};
    sdbus::InterfaceName InterfaceName{"com.system.sharing"};
    sdbus::ObjectPath ObjectPath{"/"}; 

    bool find_connection = false; 
      
    std::string name_service;


    /* parsing config file */
    while (!file.eof()) 
    {
        file >> name_service;
        
        std::string in_extention;
        while (file.peek() != '\n' && file.peek() != EOF)
        {
            file >> in_extention;
            
            if (extention == in_extention) {
                try {
                    
                    std::cerr << "I want to connect to: " << name_service << std::endl;

                    auto connection_service = sdbus::createBusConnection(sdbus::ServiceName{name_service}); 
                }                  
                catch (const sdbus::Error& error) 
                {
                    std::cerr << "Error name: " << error.getName() << std::endl;
                    std::cerr << "The required service was found: " << name_service << std::endl;

                    find_connection = true;
                    break;
                }
            }
            /* miss space */
            file.get(); 
        }
        if (find_connection) break;
    }
        
    if (!find_connection)
    {
        throw sdbus::Error{sdbus::Error::Name{"com.system.sharing.OpenFile.Error"}, "No suitable service"};
    }

    OpenServiceForFile(sdbus::ServiceName{name_service}, ObjectPath, path);

    auto reply = call.createReply();
    reply.send();

}


