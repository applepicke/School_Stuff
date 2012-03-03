import java.lang.*;
import java.util.Scanner;

/** BankAccount class for Bank program
 * 
 * @author Willy Collins
 *
 */

public class BankAccount {
	private int accNumber;
	private double accBalance;
	
	Scanner input = new Scanner(System.in);
	
	public BankAccount() {
		accNumber = 0;
		accBalance = 0.00d;
	
	}
	
	public BankAccount(int num, double bal) {
		accNumber = num;
		accBalance = bal;
	}
	
	public void createAccount() {
		do {
			System.out.print("Please enter a 5 digit account number: ");
			accNumber = input.nextInt();
		}	
		while (accNumber <= 9999 || accNumber >= 100000);
		
		do {
			System.out.print("Please enter the starting account balance: $");
			accBalance = input.nextDouble();
		}
		while (accBalance <= 0);
	}
		

	public void deposit(double d) {
		if (d > 0) 
		 accBalance += d;
		
	}
	
	public boolean withdraw(double w) {
		
		if (w > accBalance || w < 0) {
			return false;
		}	
		else {
			accBalance -= w;
			return true;
		}
	}
	
	public void display() {
		System.out.print("\nAccount Number: " + accNumber);
		System.out.print("\nAccount Balance: $" +  accBalance);
	}
	
	public double returnBalance() {
		return accBalance;
	}
	
	public int returnAccount() {
		return accNumber;
	}
	
	

}
