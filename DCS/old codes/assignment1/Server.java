import java.rmi.*;
import java.rmi.registry.*;

public class Server {
    public static void main(String[] args) {
        try {
            HelloImpl obj = new HelloImpl();
            LocateRegistry.createRegistry(2000); // RMI registry on port 2000
            Naming.rebind("rmi://localhost:2000/HelloService", obj);
            System.out.println("Server ready... waiting for client request...");
        } catch (Exception e) {
            System.out.println("Server error: " + e);
        }
    }
}
