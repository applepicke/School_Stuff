import java.util.Scanner;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			toString
 */

public class Assignment extends Event{
	
	Scanner input;
	
	public Assignment() {
		
	}
	
	public Assignment(int day, int month, int year, int hour, int minute) {
		super(day, month, year, hour, minute);
	}
	
	public String toString() {
		return "\n\tAssignment\n" + super.toString();
	}
	
}
