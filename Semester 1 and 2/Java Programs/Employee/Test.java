import java.util.Scanner;
class Test {
	public static void main (String [] args) {
		
		Scanner in = new Scanner(System.in);
		Employee[] company = new Employee[100];
		int employees = 0;
		int menu1 = 0;
		int menu2 = 0;
		
		System.out.print("\n********************************** ");
		System.out.print("\n   Super Awesome Stuff Program ");
		System.out.print("\n********************************** ");
		
		
		while (employees < 100){
			
			System.out.print("\n\n1 - Add new employee");
			System.out.print("\n2 - Do weekly payroll");
			System.out.print("\n3 - Quit");
			
			menu1 = in.nextInt();
			//Add employee
			if (menu1 == 1) {
				System.out.print("\n1 - Executive");
				System.out.print("\n2 - SalesRep ");
				System.out.print("\n3 - Programmer ");
				
				menu2 = in.nextInt();
				
				if (menu2 == 1) {
					company[employees] = new Executive();
					company[employees].setFromKeyboard();
				}	
				if (menu2 == 2) {
					company[employees] = new SalesRep();
					company[employees].setFromKeyboard();
				}
				if (menu2 == 3) {
					company[employees] = new Programmer();
					company[employees].setFromKeyboard();
				}
				employees++;
			}
			
			//Calculate Weekly Pay
			if (menu1 == 2) {
				for (int i=0; i < employees; i++){
					company[i].calcWeeklyPayAmount();
					company[i].calcWeeklyTaxAmount();
					System.out.print("\n" + company[i]);
				}
				
			}
			
			//Exit
			if (menu1 == 3) {
				break;
			}
			
			
			
		}
		System.out.print("\nToodles!!");
		
		
	}
		
}
