
import java.util.Scanner;  // Import the Scanner class

public class HelloWorld {

    public static void main(String[] args) {
        Scanner myObj = new Scanner(System.in);  // Create a Scanner object
        //System.out.println("Enter username");

        String userName = myObj.nextLine();  // Read user input
        //System.out.println("Username is: " + userName);  // Output user input
    }

    public static void loops() {

        int i = 0 ;
        while(i<100){
            i+=1;
        }
    }

    public static void expressions(){
        int a; 
        a = 1;

        if(a<1){
            a = a % 2;
        }
        else if(a >= 3){
            a = -a;
        }


    
    }

    public static void vardef(){
        int a;
        int b;
        int c;


        a = b = c = 1;
    }
}


