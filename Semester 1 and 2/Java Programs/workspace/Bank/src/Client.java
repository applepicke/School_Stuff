import java.lang.*;
import java.util.Scanner;
import java.lang.String;
/** Client class for Bank program.
 * 
 * @author Willy Collins
 *
 */

public class Client {
	
	
	Scanner input = new Scanner(System.in);
	String name = new String();
	BankAccount savingsAccount = new BankAccount();
	BankAccount chequingAccount = new BankAccount();
	
	
	
	private int whichAcc;
	private double amount;
	
	
	public Client() {
		whichAcc = 0;
		amount = 0;
		
		
	}
	
	public void createClient() {
		System.out.print("\nPlease enter the full name of the client: ");
		name = input.nextLine();
		
		System.out.print("\n**Both accounts cannot be the same number**\n");
		
		System.out.println("\nSavings Account");
		System.out.println("***************");
		savingsAccount.createAccount();
		
		do {
		System.out.println("\nChequing Account");
		System.out.println("****************");
		chequingAccount.createAccount();
		}
		while (savingsAccount.returnAccount() == chequingAccount.returnAccount());
	}
	
	
	
	public void deposit() {
		
		do {
			System.out.print("\nWhich bank account would you like to deposit into?");
			System.out.print("\n1 - Savings Account");
			System.out.print("\n2 - Chequing Account\n");
			whichAcc = input.nextInt();
		}
		while (whichAcc > 2 || whichAcc < 1);
		
		
		do {
			System.out.print("\nEnter the amount of money you would like to depost: $");
			amount = input.nextDouble();
		}
		while (amount < 0);
		
		if (whichAcc == 1) {
			savingsAccount.deposit(amount);	
		}
		else if (whichAcc == 2) {
			chequingAccount.deposit(amount);
		}
	}
		
	
	
	public void withdraw() {
		
		do {
			System.out.print("\nWhich account would you like to withdraw from?");
			System.out.print("\n1 - Savings Account");
			System.out.print("\n2 - Chequing Account\n");
			whichAcc = input.nextInt();
		}
		while (whichAcc > 2 || whichAcc < 1);
		
		
		do {
			System.out.print("\nEnter the amount you wish to withdraw: $");
			amount = input.nextDouble();
		}
		while (amount < 0);
		
		if (whichAcc == 1) {
			
			if (savingsAccount.withdraw(amount) == false) {
				System.out.print("\nTransaction failed - Insufficient funds!\n");
			}
			else 
				System.out.print("\nTransaction Successful!\n");
		}
		else if (whichAcc == 2) {
			
			if (chequingAccount.withdraw(amount) == false) {
				System.out.print("\nTransaction failed - Insufficient funds!\n");
			}
			else 
				System.out.print("\nTransaction Successful!\n");
		}
		
	}
	
	
	public void display() {
		
		
		System.out.print("\n\n   " + name);
		System.out.print("\n***********************\n");
		
		System.out.print("\n   Savings Account   ");
		System.out.print("\n**************************");
		savingsAccount.display();
		System.out.print("\n**************************\n");
		
		System.out.print("\n  Chequing Account   ");
		System.out.print("\n**************************");
		chequingAccount.display();
		System.out.print("\n**************************\n");
	}
	
	public String displayName() {
		return name;
	}

}
