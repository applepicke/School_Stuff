import java.util.Scanner;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			inputFromKeyboard
 *			toString
 */

public class Meeting extends Event{
	private String place;
	Scanner input;
	
	public Meeting () {
		place = new String();
	}
	
	public Meeting (int day, int month, int year, int hour, int minute) {
		super(day, month, year, hour, minute);	
	}
	
	public void setPlace(String place) {
		this.place = new String(place);
	}
	
	public String getPlace() {
		return place;
	}
	
	public String toString() {
		return "\tMeeting\n" + super.toString() + "Place - " + place + "\n";
	}
	
	public void inputFromKeyboard() {
		input = new Scanner(System.in);
		super.inputFromKeyboard();
		System.out.print("Where is the meeting to take place?");
		place = new String(input.nextLine());
	}

}
