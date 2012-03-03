import java.lang.*;
import java.util.Scanner;
import java.lang.String;
/** A bank program, which simulates the use of a chequing and savings account
 * 
 * @author Willy Collins
 *
 */
public class Bank {
	public static void main (String args[]) {
		
		Client [] Bank = new Client[1000];
		Scanner input = new Scanner(System.in);
		String anyKey = new String();
		
		
		int interact = 1;
		int action = 0;
		int numClients = 0;
		int clientAccess = 0;
		  
		System.out.print("\n                        ********************************");
		System.out.print("\n                           National Bank of Greatness   ");
		System.out.print("\n                        ********************************");
		
		System.out.print("\n Welcome to the interactive account manager of the National Bank of Greatness!!");
		
		// Choose to create or modify a client
		
		while (interact !=0) {
		
			do {
				System.out.print("\n\nWhat would you like to do? ");
				System.out.print("\n0 - Exit");
				System.out.print("\n1 - Create a new Client Profile");
				System.out.print("\n2 - Review current clients" );
				System.out.print("\n3 - Choose client to edit\n");
		
				interact = input.nextInt();
			}
			while (interact < 0 || interact > 3);
		
			if (interact == 0) {
				break;
			}
		
			if (interact == 1) {
				
				
				// Create a new client with two accounts for the database
				if (numClients < 1000) {
					
					Bank[numClients] = new Client();
					Bank[numClients].createClient();
					clientAccess = numClients;
					numClients++;
					
				}
				else {
					System.out.print("\nClient list is full!!");
					break;
				}
			}
			
			//Review Client List
			if (interact == 2) {
				for (int i = 1; i <= numClients; i++) {
					System.out.print("\n" + i + " - " + Bank[i-1].displayName());
				}
				System.out.print("\n\nPlease press enter to continue: \n");
				anyKey = input.nextLine();
				anyKey = input.nextLine();
			}
				
			if (interact == 1 || interact == 3) {	
				
				// Choose an existing client to edit
				do {
					if (interact == 3) {
						System.out.print("\nEnter the client number you wish to access(0 to exit): ");
						clientAccess = input.nextInt();
						if (clientAccess == 0) {
							break;
						}
					}
				}	
				while (clientAccess < 0 || clientAccess > numClients);
							
						
			
				// Choose what actions to do to the Client
				
					do {
						if (clientAccess == 0) {
							break;
						}
						do {
							System.out.print("\n" + Bank[clientAccess - 1].displayName());
							System.out.print("\n****************");
							System.out.print("\nWhat action would you like to perform?");
							System.out.print("\n0 - Exit ");
							System.out.print("\n1 - Display account info");
							System.out.print("\n2 - Deposit");
							System.out.print("\n3 - Withdraw\n");
					
							action = input.nextInt();
						}
						while (action < 0 || action > 3);
						
						if (action == 0) {
							break;
						}
					
						// Deposit
						if (action == 2) {
							Bank[clientAccess - 1].deposit();
							System.out.print("\nPress enter to continue: ");
							anyKey = input.nextLine();
							anyKey = input.nextLine();
						}
						// Withdraw
						else if (action == 3) {
							Bank[clientAccess - 1].withdraw();
							System.out.print("\nPress enter to continue: ");
							anyKey = input.nextLine();
							anyKey = input.nextLine();
						}
						// Show account info
						else if (action == 1) {
							Bank[clientAccess - 1].display();
							System.out.print("\nPress enter to continue: ");
							anyKey = input.nextLine();
							anyKey = input.nextLine();
						}	
		
					}
					while (action != 0);
				
			}
		
		}
		
		System.out.print("\n**********************************************************");
		System.out.print("\n    Thank you for using the National Bank of Greatness    ");
		System.out.print("\n**********************************************************");
		
				
	}

}
