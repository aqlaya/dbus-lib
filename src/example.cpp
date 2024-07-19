#include <iostream>
#include "service.hpp"
#include <string>

int main() {
    const std::vector<std::string> supportedFormats =  {"txt"};
    

    auto onOpenFile = [](const std::string &path) {
         
    };

    SharingService service("com.example.system", supportedFormats, onOpenFile);


    return service.start();

}