#include <sdbus-c++/sdbus-c++.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <filesystem>


/* Method of D-Bus object */

void OpenFile(sdbus::MethodCall call);

void RegisterService(sdbus::MethodCall call);

void OpenFileUsingService(sdbus::MethodCall call);



/* Function to call the final service method */
void OpenServiceForFile(const sdbus::ServiceName&, const sdbus::ObjectPath&, const std::string&);

