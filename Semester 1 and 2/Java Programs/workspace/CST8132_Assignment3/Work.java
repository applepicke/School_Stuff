import java.util.Scanner;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			inputFromKeyboard
 *			toString
 */

public class Work extends Event{
	private int length;
	Scanner input;
	
	public Work(){
		
	}
	
	public Work(int day, int month, int year, int hour, int minute){
		super(day, month, year, hour, minute);
	}
	
	public int getLength() {
		return length;
	}
	public void setLength(int length) {
		this.length = length; 
	}
	
	public String toString() {
		return "\tWork Event\n" + super.toString() + "Length: " + length + " hours" + "\n";
	}
	
	public void inputFromKeyboard(){
		input = new Scanner(System.in);
		super.inputFromKeyboard();
		System.out.print("Enter the length of your work shift in hours: ");
		length = input.nextInt();
		while (length < 1) {
			System.out.print("Invalid length, please reenter: ");
			length = input.nextInt();
		}
		
	}

}
