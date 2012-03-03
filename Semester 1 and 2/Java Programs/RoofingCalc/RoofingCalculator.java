import java.lang.*;
import java.util.Scanner;
/** This program will take the input of hours worked and display the invoice 
 * subtotal, the sales tax, and the invoice total. It will then take the amount
 * payed by the customer, and then determine how much change is due.
 * @version 1
 * @author William Collins
 *
 */

public class RoofingCalculator {
	public static void main(String args[]) {
		
		Scanner input = new Scanner (System.in);
		
		int hoursWorked = 0;
		double invoiceSubtotal = 0;
		double invoiceTax = 0;
		double invoiceTotal = 0;
		double amountPayed = 0;
		double changeDue = 0;
		
		System.out.print("Welcome to the Roofing Invoicer!");
		System.out.print("\nPlease enter the amount of hours worked:");
		
		hoursWorked = input.nextInt();
			while (hoursWorked < 1) {
				System.out.print("That is an invalid input.\nPlease enter the number of hours worked: ");
				hoursWorked = input.nextInt();
			}
		invoiceSubtotal = hoursWorked * 100;
		System.out.print("\nInvoice Subtotal: $" + invoiceSubtotal);
		
		invoiceTax = invoiceSubtotal * 0.13;
		System.out.print("\nInvoice Tax: $" + invoiceTax);
		
		invoiceTotal = invoiceSubtotal + invoiceTax;
		System.out.print("\nInvoice Total: $" + invoiceTotal);
		
		System.out.print("\n\nPlease enter payment amount: ");
		amountPayed = input.nextDouble();
			while (amountPayed < invoiceTotal) {
				System.out.print("You must pay the entire invoice.\nPlease enter the amount payed: ");
				amountPayed = input.nextDouble();
			}
		changeDue = amountPayed - invoiceTotal;
		System.out.print("Total Change: $" + changeDue);
		
		
	}
}
