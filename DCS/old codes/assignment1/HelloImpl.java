import java.rmi.*;
import java.rmi.server.*;

public class HelloImpl extends UnicastRemoteObject implements Hello {
    HelloImpl() throws RemoteException {}
    public String sayHello(String name) {
        return "Hello " + name + "!";
    }
}
