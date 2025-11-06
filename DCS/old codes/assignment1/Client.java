import java.rmi.*;
import java.util.*;

public class Client {
    public static void main(String[] args) {
        try {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter your name: ");
            String name = sc.nextLine();

            Hello stub = (Hello) Naming.lookup("rmi://localhost:2000/HelloService");
            System.out.println(stub.sayHello(name));
        } catch (Exception e) {
            System.out.println("Client error: " + e);
        }
    }
}
