import java.lang.*;
import java.util.Scanner;

public class WageProgram {
	public static void main(String args[]) {
		
		Scanner input = new Scanner(System.in);
		
		int hoursWorked = 0;
		float hourlyWage = 0.0f;
		float overTime = 0.0f;
		float wagePayed = 0.0f;
		float totalWage = 0.0f;
		float salesTax = 0.0f;
		float netWage = 0.0f;
		
		
		System.out.print("\nEnter amount of hours worked this week: ");
		hoursWorked = input.nextInt();
		
		while (hoursWorked < 0 || hoursWorked > 168) {
			System.out.print("\nThat input is unacceptable");
			hoursWorked = input.nextInt();
		}
		
		System.out.print("\nEnter your hourly wage: ");
		hourlyWage = input.nextFloat();
		
		while (hourlyWage <= 0){
			System.out.print("\nYou must be making at least some money!");
			hourlyWage = input.nextFloat();
		}
		
		if (hoursWorked <= 40){
			wagePayed = hoursWorked * hourlyWage;
			totalWage = wagePayed;
		}
			else {
				overTime = (float)((hoursWorked - 40.00f) * hourlyWage * 1.50f);
				wagePayed = hourlyWage * 40.0f;
				totalWage = overTime + wagePayed;
			}
		if (totalWage <= 1000)
			salesTax = 0;
			else if (totalWage > 1000 || totalWage <= 2000)
				salesTax = totalWage * 0.25f;
			else if (totalWage > 2000)
				salesTax = totalWage * 0.40f;
		
		netWage = totalWage - salesTax;
		
		System.out.printf("\nBase Pay is: $%.2f", wagePayed);
		System.out.printf("\nOvertime Pay is: $%.2f", overTime);
		System.out.printf("\nSales Tax is: $%.2f", salesTax);
		System.out.printf("\nNet Pay is: $%.2f", netWage);
	}

}
