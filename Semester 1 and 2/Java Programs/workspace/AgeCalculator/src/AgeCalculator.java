import java.lang.*;
import java.util.Scanner;
/** This program calculates your age in years, months, or both years
 * and months
 * @version 1.0
 * @author Willy
 *
 */
public class AgeCalculator {
	public static void main(String args[]) {
		
		Scanner input = new Scanner(System.in);
		
		int todayYear = 0;
		int todayMonth = 0;
		int birthYear = 0;
		int birthMonth = 0;
		int yearFactor = 0;
		int ageYear = 0;
		int ageMonth = 0;
		int displayNumber = 0;
		
		
		
		
			System.out.print("\n\nHello, it is time to find out how old you are!");
			System.out.print("\n\n**Please note, that all years are entered in a four digit format (2000, 1876),\n**and all months are entered numerically (1=Jan, 2=Feb, etc)");
			System.out.print("\n\nEnter the year we are currently in: ");
			todayYear = input.nextInt();
		
			System.out.print("Enter the current month we are in: ");
			todayMonth = input.nextInt();
		
			while (todayMonth > 12 || todayMonth < 1) {
				System.out.print("Incorrect month, please enter the current month: ");
				todayMonth = input.nextInt();
			}
		
			System.out.print("Enter your birth year: ");
			birthYear = input.nextInt();
		
			while (birthYear > todayYear) {
				System.out.print("You cannot be born in the future, that is just nonsense!");
				System.out.print("\nPlease enter the year you were born: ");
				birthYear = input.nextInt();
			}
		
			System.out.print("Enter your birth month: ");
			birthMonth = input.nextInt();
		
			while (birthMonth > 12 || birthMonth < 1) {
				System.out.print("Not a valid month, please enter your birth month: ");
				birthMonth = input.nextInt();
			}
		
			if (todayMonth < birthMonth) 
				yearFactor = 1;
			else 
				yearFactor = 0;
		
			ageYear = (todayYear - birthYear) - yearFactor;
		
			if (yearFactor == 1)
				ageMonth = (12 - birthMonth) + todayMonth;
			else 
				ageMonth = (todayMonth - birthMonth);
		
			System.out.print("\n**Enter a 1 to calculate your age in years only");
			System.out.print("\n**Enter a 2 to calculate your age in months only");
			System.out.print("\n**Enter a 3 to calculate your age in both years and months");
			System.out.print("\nNow is the time to decide, will it be a 1, a 2, or a 3: ");
		
			displayNumber = input.nextInt();
		
			while (displayNumber > 3 || displayNumber < 1) {
				System.out.print("That is definately not a valid response");
				System.out.print("\nYou only have to enter a number between 1 and 3: ");
				displayNumber = input.nextInt();
			}
		
			if (displayNumber == 1)
				System.out.print("\nYou are " + ageYear + " years old\n");
			else if (displayNumber == 2)
				System.out.print("\nYou are " + (ageYear * 12 + ageMonth) + " months old\n");
			else if (displayNumber == 3)
				System.out.print("\nYou are " + ageYear + " years, and " + ageMonth + " months old\n");
		
	
		
	}

}
