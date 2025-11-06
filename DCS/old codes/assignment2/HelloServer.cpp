#include <iostream>
#include <omniORB4/CORBA.h>
#include "Hello.hh"

using namespace HelloApp;

class Hello_impl : public POA_Hello {
public:
    virtual char* sayHello() {
        std::cout << "sayHello() invoked by client" << std::endl;
        return CORBA::string_dup("Hello from CORBA server!");
    }
};

int main(int argc, char** argv) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
        PortableServer::POAManager_var mgr = poa->the_POAManager();

        Hello_impl* helloImpl = new Hello_impl();
        PortableServer::ObjectId_var oid = poa->activate_object(helloImpl);
        CORBA::Object_var ref = helloImpl->_this();

        CORBA::String_var refStr = orb->object_to_string(ref);
        std::ofstream refFile("Hello.ref");
        refFile << refStr;
        refFile.close();

        std::cout << "Server ready and waiting..." << std::endl;

        mgr->activate();
        orb->run();

    } catch (CORBA::Exception& e) {
        std::cerr << "CORBA Exception: " << e._name() << std::endl;
    }
    return 0;
}
