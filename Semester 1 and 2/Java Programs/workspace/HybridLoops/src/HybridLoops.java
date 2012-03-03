import java.lang.*;
import java.util.Scanner;

public class HybridLoops {
	public static void main(String args[]) {
		
		Scanner input = new Scanner(System.in);
		
		int i = 0;
		int initValue = 0;
		int incValue = 0;
		
		System.out.println("Enter a number between 0 and 20: ");
		initValue = input.nextInt();
		
		while (initValue < 1 || initValue > 19) {
			System.out.println("Invalid value, please enter again: ");
			initValue = input.nextInt();
		}	
		
		System.out.println("Enter an increment less than 10: ");
		incValue = input.nextInt();
		
		while (incValue < 1 || incValue > 9) {
			System.out.println("Invalid value, please enter again: ");
			incValue = input.nextInt();
		}
		
		System.out.println("\n" + initValue);
		for (i = initValue; initValue + incValue < 21; i++) {
			System.out.println(initValue + incValue);
			initValue += incValue;
		}
		
	}

}
