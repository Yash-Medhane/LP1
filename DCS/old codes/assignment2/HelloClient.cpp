#include <iostream>
#include <fstream>
#include <string>
#include <omniORB4/CORBA.h>
#include "Hello.hh"

using namespace HelloApp;

int main(int argc, char** argv) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        std::ifstream refFile("Hello.ref");
        std::string refStr;
        std::getline(refFile, refStr);
        refFile.close();

        CORBA::Object_var obj = orb->string_to_object(refStr.c_str());
        Hello_var hello = Hello::_narrow(obj);

        if (CORBA::is_nil(hello)) {
            std::cerr << "Invalid object reference" << std::endl;
            return 1;
        }

        CORBA::String_var response = hello->sayHello();
        std::cout << "Server response: " << response.in() << std::endl;

    } catch (CORBA::Exception& e) {
        std::cerr << "CORBA Exception: " << e._name() << std::endl;
    }

    return 0;
}
