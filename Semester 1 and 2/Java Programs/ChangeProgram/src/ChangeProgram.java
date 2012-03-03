import java.lang.*;
import java.util.Scanner;
/** takes an amount from 0.00 to 5.00 and gives back change
 * @version 1
 * @author William Collins
 *
 */

public class ChangeProgram {
	public static void main(String args[]) {
		Scanner input = new Scanner (System.in);
		
		int toonie = 0;
		int loonie = 0;
		int quarter = 0;
		int dime = 0;
		int nickel = 0;
		int penny = 0;
		double amount = 0.00;
		double change = 0.00;
		int pizza = 0;
		
		while (pizza < 3) {
		
		System.out.print("\nEnter an amount of money between $0.00 and $100.00: ");
		amount = input.nextDouble();
		
		while ( amount > 100.00 || amount < 0.0 )  {
			System.out.print("Invalid input \n\nEnter an amount of money between $0.00 and $100.00: ");
			amount = input.nextDouble();
		}
			change = (double) (100.00 - amount);
			
			
			while (change >= 2.00) {
				toonie = (toonie + 1);
				change = (change - 2.00);
			}
			while (change >= 1.00) {
				loonie = (loonie + 1);
				change = (change - 1.00);
			}
			while (change >= 0.25) {
				quarter = (quarter + 1);
				change = (change - 0.25);
			}
			while (change >= 0.10) {
				dime = (dime + 1);
				change = (change - 0.10);
			}
			while (change >= 0.05) {
				nickel = (nickel + 1);
				change = (change - 0.05);
			}
			while (change >= 0.01f) {
				penny = (penny + 1);
				change = (change - 0.01);
			}
			
			System.out.print("\nYour change is: ");
			System.out.print("\nToonies: " + toonie);
			System.out.print("\nLoonies: " + loonie);
			System.out.print("\nQuarters: " + quarter);
			System.out.print("\nDimes: " + dime);
			System.out.print("\nNickels: " + nickel);
			System.out.print("\nPennies: " + penny);
			System.out.print("\n ");
			
			toonie = 0;
			loonie = 0;
			quarter = 0;
			dime = 0;
			nickel = 0;
			penny = 0;
			
			pizza ++;
			
			}
		}
	}