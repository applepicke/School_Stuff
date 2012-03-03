import java.util.Scanner;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			inputFromKeyboard
 *			toString
 */

public class Event {
	private OurDate date;
	private Time time;
	private String event;
	private Scanner input;

	
	public Event () {
		date = new OurDate();
		time = new Time();
	}
	
	public Event(int day, int month, int year, int hour, int minute) {
		date = new OurDate(day, month, year);
		time = new Time(hour, minute);		
	}
	
	public void setDate(OurDate date) {
		this.date = new OurDate(date);
	}
	
	public void setDate(int day, int month, int year) {
		this.date.setDay(day);
		this.date.setMonth(month);
		this.date.setYear(year);
	}
	
	public void setTime(Time time) {
		this.time = new Time(time);
	}
	
	public void setTime(int hour, int minute) {
		this.time.setHour(hour);
		this.time.setMinute(minute);
	}
	
	public void setEvent(String event) {
		this.event = new String(event);
	}
	
	public String getEvent() {
		return event;
	}
	
	public OurDate getDate() {
		return date;
	}
	
	public Time getTime() {
		return time;
	}
	
	public void inputFromKeyboard() {
		date.inputFromKeyboard();
		time.inputFromKeyboard();
		input = new Scanner(System.in);
		System.out.print("\nEnter new event description: ");
		event = new String(input.nextLine());
	}
	
	public String toString() {
		return date + " - " + time + " - " + event + "\n";
	}

	
}
