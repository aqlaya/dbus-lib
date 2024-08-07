#include "method.hpp"

#include <algorithm>
#include <memory>

/* note in file name service */
void note_config_file(std::string&, std::vector<std::string>&);

/* create note for config file */
auto create_place_keep_formats(const size_t, std::vector<std::string>&) 
                                                -> std::shared_ptr<char[]>;


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


    /* write in file (update note)*/
    note_config_file(service_name, supportedFormats);

    auto reply = call.createReply();
    reply << "The name of the service is written to the file";
    reply.send();

}

void note_config_file(std::string& service_name, std::vector<std::string>& supportedFormats)
{

    /* amount character for note size formats */ 
    const size_t size_formats = 60;

    /* open file  */
    std::fstream config;
    config.open("sharing.conf",  std::ios::in | std::ios::out);

    config.seekg(0, std::ios::beg);

    /* bool variable: have service_name into config file */ 
    auto have_note_in_config = false;

    std::string currentStr;

    /* function for write/udpate to config file */
    auto write_to_file = [&config, &size_formats, &have_note_in_config, &service_name, &supportedFormats]() {
        config.clear();
        auto raw_ptr = create_place_keep_formats(size_formats, supportedFormats);

        /* update formats */
        if (have_note_in_config) {
            config.seekg(config.tellg() - (size_formats + 1) );
        }

        /* write service_name */
        else {
            config.write(service_name.c_str(), service_name.size());
        }

        /* write foramats */
        config.write(raw_ptr.get(), size_formats);
        config << "\n";
    };


    /* read file */
    while (std::getline(config, currentStr))
    {
        /* update Formats information */
        if (currentStr.substr(0, currentStr.find('[')) == service_name)
        {
            std::cerr << "Update Formats inforamtion" << std::endl;
            have_note_in_config = true;
            write_to_file();
            break;
        }
    }
    /* write service name and format information */
    if (!have_note_in_config)
    { 
        std::cerr << "Write service name" << std::endl;
        write_to_file();
    }
}

/* create note for config file */
auto create_place_keep_formats(const size_t size_formats, std::vector<std::string>& supportedFormats) 
    -> std::shared_ptr<char[]>
{
    std::shared_ptr<char[]> raw_ptr = std::make_shared<char[]>(size_formats,  ' ');

    raw_ptr[0] = '[';
    char* curIt {raw_ptr.get() + 1};
    for (size_t i {0}; i < supportedFormats.size(); ++i)
    {
        std::string curString {supportedFormats[i]};
        std::copy(curString.c_str(), curString.c_str() + curString.size(), curIt);
        curIt += (curString.size() + 1);
 
        *(curIt - 1) = (supportedFormats.size() - 1 != i) ? ',' : ']';
    }

    return raw_ptr;
}




