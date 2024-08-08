#include "method.hpp"
#include "SharingService.hpp"

void process(const std::string& path);

int main(int args, char** argv)
{
    const std::vector<std::string> supportedFormat = {"txt"};

    auto onOpenFile = [](const std::string& path, const Response& req) {
        if (!std::filesystem::exists(path)) {
            throw sdbus::Error(sdbus::Error::Name("com.sharing.OpenFunc.Error"), "Not found file!");
        }
        else {
            process(path);
        }
    };

    SharingService service("com.example.mediaplayer", supportedFormat, onOpenFile);

    return service.start();
}

void process(const std::string& path)
{
    std::fstream file;
    file.open(path, std::ios::app | std::ios::in);
    std::cerr << "Your file was opened!\n" << std::endl;
    file.close();
}