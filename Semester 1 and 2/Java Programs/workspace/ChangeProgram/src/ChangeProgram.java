import java.lang.*;
import java.util.Scanner;
/** Takes an amount from 1 - 25 and give back change
  * @version 1.0
  * @author William Collins
  */

public class ChangeProgram {
	public static void main(String args[]) {
		
		Scanner input = new Scanner (System.in);
		
		int pennies = 0;
		int dimes = 0;
		int nickels = 0;
		int quarters = 0;
		int loonies = 0;
		int toonies = 0;
		double amount = 0;
		double refund = 0;
		
		System.out.print("\nEnter an amount of money between $0.01 and $5.00: ");
		amount = input.nextDouble();
		
		while ( amount >= 5.01 )  {
			System.out.print("Invalid input \n\nEnter an amount of money between $0.01 and $5.00: ");
			amount = input.nextDouble();
		}
		while ( amount <= 0.00 ) {
			System.out.print("Invalid input \n\nEnter an amount of money between $0.01 and $5.00: ");
			amount = input.nextDouble();
		}
		refund = 5.00 - amount;
			
		while (refund >= 2.00) {
			toonies = toonies + 1;
			refund = refund - 2.00;
		}
		while (refund >= 1.00) {
			loonies = loonies + 1;
			refund = refund - 1.00;
		}
		while (refund >= 0.25) {
			quarters = quarters + 1;
			refund = refund - 0.25;
		}
		while (refund >= 0.1) {
			dimes = dimes + 1;
			refund = refund - 0.1;
		}
		while (refund >= 0.05) {
			nickels = nickels + 1;
			refund = refund - 0.05;
		}
		while (refund >= 0.01) {
			pennies = pennies + 1;
			refund = refund - 0.01;
		}
		
		System.out.print("\nYour change is: ");
		System.out.print("\nToonies: " + toonies);
		System.out.print("\nLoonies: " + loonies);
		System.out.print("\nQuarters: " + quarters);
		System.out.print("\nDimes: " + dimes);
		System.out.print("\nNickels: " + nickels);
		System.out.print("\nPennies: " + pennies);
		
		
 	}

}
