#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <iostream>


using func = std::function<void(const std::string&)>;

class SharingService 
{
    public:
        /* constructor */
        SharingService(std::string&&, const std::vector<std::string>& , func );


        /* remove copy constructor */
        SharingService(const SharingService& obj) = delete;
        SharingService operator=(const SharingService& ob) = delete;


        /* method for start to work d-bus*/
        int start();

    private:
        const std::vector<std::string>& _supportedFormats;
        std::string _serviceName;
        func _openFile;
};



