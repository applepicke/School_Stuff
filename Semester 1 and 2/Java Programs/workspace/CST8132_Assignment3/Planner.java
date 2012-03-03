import java.util.Scanner;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			addEventInput - add event info from user
 *			addEvent - add specific events
 *			removeEvent - delete an event
 *			display - display events
 *			displaySeven - displays for seven days
 *			setUserDate - gets date info from user
 *			setUserTime - gets time info from user
 *			toString
 */

public class Planner {
	private Event events[] = new Event[1000];
	private Scanner input;
	private int maxIndex;
	
	// For the user input of year, month and day
	int year;
	int month;
	int day;
	int hour;
	int minute;
	
	public Planner(){
		events[0] = new Event();
	}
	
	//Get and Sets
	public void setMaxIndex(int maxIndex){
		this.maxIndex = maxIndex;
	}
	
	public Event getEvent(int i) {
		return events[i];
	}
	
	public int getMaxIndex() {
		return maxIndex;
	}
	
	public int getIndex() throws Exception {
		for (int i = 0; i < maxIndex; i++) {
			if(day == events[i].getDate().getDay() && month == events[i].getDate().getMonth() &&
					year == events[i].getDate().getYear())
				return i;
		}
		throw new Exception();
	}
	//Different input for each event
	public void addEventInput(int i) throws Exception{
		events[i].inputFromKeyboard();
		for (int j = 0; j < i; j++) {
			if (events[i].getDate().getYear() == events[j].getDate().getYear() && events[i].getDate().getMonth() == events[j].getDate().getMonth() && 
					events[i].getDate().getDay() == events[j].getDate().getDay() && events[i].getTime().getHour() == events[j].getTime().getHour() && 
					events[i].getTime().getMinute() == events[j].getTime().getMinute()) 
			{
				throw new Exception();
			}
		}
		System.out.print("\nEvent Added!");
		maxIndex++;
		
	}
	
	//Add different types of Events
	public void addEvent(int i) throws Exception {
		events[i] = new Event();
		this.addEventInput(i);
	}
	
	public void addMeeting(int i) throws Exception{
		events[i] = new Meeting();
		this.addEventInput(i);
	}
	
	public void addWork(int i) throws Exception {
		events[i] = new Work();
		this.addEventInput(i);
	}
	
	public void addSocial(int i) throws Exception{
		events[i] = new Social();
		this.addEventInput(i);
	}
	
	public void addAssignment(int i) throws Exception {
		events[i] = new Assignment();
		this.addEventInput(i);
	}
	
	//Remove Events
	public void removeEvent(int index) {
		for ( ; index < maxIndex; index++) {
			events[index] = events[index + 1];
		}
		maxIndex--;
	}
	
	//Display one event
	public void display() throws Exception{
		boolean isNone = true;
		input = new Scanner(System.in);
		for (int i = 0; i < maxIndex; i++) {
			if (events[i].getDate().getYear() == year && events[i].getDate().getMonth() == month && events[i].getDate().getDay() == day) {
				System.out.print("\n" + events[i]);
				isNone = false;
			}
		}
		if (isNone)
			throw new Exception();
	}
	
	//Display seven days of events
	public void displaySeven() throws Exception{
		for (int i = 0; i < 7; i++){
			System.out.print("\n\tDay " + (i+1) );
			System.out.print("\n\t*****");
			this.display();
			day++;
		}
		
	}
	
	//Set the input of Year Month and Day from user
	public void setUserDate() {
		
		input = new Scanner(System.in);
		System.out.print("\nEnter Year of the event: ");
		year = input.nextInt();
		System.out.print("Enter Month of the event: ");
		month = input.nextInt();
		System.out.print("Enter Day of the event: ");
		day = input.nextInt();
	}
	
	//Set the input of Hour and minute from user
	public void setUserTime() {
		input = new Scanner(System.in);
		System.out.print("\nEnter Hour of the event: ");
		hour = input.nextInt();
		System.out.print("Enter minute of the event: ");
		minute = input.nextInt();
	}
}
