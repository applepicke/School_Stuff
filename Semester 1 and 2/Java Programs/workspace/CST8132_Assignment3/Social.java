/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			toString
 */
public class Social extends Event{
	public Social() {
		
	}
	
	public Social(int day, int month, int year, int hour, int minute) {
		super(day, month, year, hour, minute);
	}
	
	public String toString() {
		return "\n\tSocial Event\n" + super.toString();
	}
	
	
}
