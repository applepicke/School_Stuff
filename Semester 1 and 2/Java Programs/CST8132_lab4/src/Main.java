import java.util.Scanner;
import java.lang.String;

public class Main {
	public static void main(String args[]){
		Number inputNum = new Number();
		Scanner in = new Scanner(System.in);
		String inputStr;
		
		
		System.out.print("Please enter a number between 1 and 100 inclusive:\n");
		inputStr = new String(in.nextLine());
		inputNum.validateIntData(inputStr);
			
		while (inputNum.getDataInt() > 100 || inputNum.getDataInt() < 1 || inputNum.validateIntData(inputStr) == -1){
			System.out.print("invalid number\n");
			System.out.print("Please enter a number between 1 and 100 inclusive:\n");
			inputStr = new String(in.nextLine());	
			inputNum.validateIntData(inputStr);
		}
		System.out.print("\nYour number is: " + inputNum.getDataInt());
		System.out.print("\nYour number + 1 is: " + (inputNum.getDataInt() + 1));
		System.out.print("\nYour number times 3 is: " + (inputNum.getDataInt() * 3));
		
	}
}
