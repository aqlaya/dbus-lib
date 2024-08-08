#pragma once


#include <memory>
#include <string>
#include <iostream>
#include <sdbus-c++/sdbus-c++.h>

class Response {
    private:
        std::unique_ptr<sdbus::IObject>& _object;
        std::string& _serviceName;
    public:
        Response(std::unique_ptr<sdbus::IObject>& object, std::string& serviceName)
            : _object{object}
            , _serviceName{serviceName}
        {

        }
        Response(const Response& obj) = delete;

        void sendErrorResponse(const std::string& explainError) const
        {
            throw sdbus::Error(sdbus::Error::Name("com.sharing.OpenFunc.Error"), 
                                                                explainError );
        }
        void sendSuccessResponse() const
        {
            _object->emitSignal("fileopen").onInterface(_serviceName);
        }

};
