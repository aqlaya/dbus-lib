#include "method.hpp"
#include "SharingService.hpp"

void process(const std::string& path);

int main(int args, char** argv)
{
    const std::vector<std::string> supportedFormat = {"txt"};

    auto onOpenFile = [](const std::string& path, const Response& req) {
        if (!std::filesystem::exists(path)) {
            req.sendErrorResponse("File wasn't found");
        }
        else {
            process(path); 
            req.sendSuccessResponse();
        }
    };

    SharingService service("com.example.outputText", supportedFormat, onOpenFile);

    return service.start();
}

void process(const std::string& path)
{
    std::fstream file;
    file.open(path, std::ios::app | std::ios::in);
    std::cerr << "Your file was opened!\n" << std::endl;
    if (file.is_open())
    {
        for (std::string str ; std::getline(file, str); ) 
        {
            std::cerr << str << std::endl;            
        }
    }
    file.close();
}