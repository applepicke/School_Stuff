import java.util.*;
/**
 * @author William Collins / 040652633
 *  CST8132 Section 313
 *	Methods: Set and Get methods
 *			inputFromKeyboard
 *			toString
 */
public class OurDate {
	private int day = 1;
	private int month = 1;
	private int year = 2010;
	
	public OurDate() {
	
	}
	public OurDate (int day, int month, int year){
		setDay(day);
		setMonth (month);
		setYear (year);
	}
	public OurDate (OurDate date){
		this.day = date.day;
		this.month = date.month;
		this.year = date.year;
	}
	
	// get methods
	public int getDay () { return day; }
	public int getMonth() { return month;}
	public int getYear() { return year; }
	
	// set methods
	public void setDay (int day){
		if (day <= 0 || day > 31) 
			this.day = 1;
		else if (this.month == 2 && day > 29) 
			this.day = 1;
		else if (this.day > 30 && (this.month == 9 ||this.month == 4 ||this.month == 6 ||this.month == 11) )
			this.day = 1;
		else this.day = day;
	}
	public void setMonth (int month){
		if (month < 0 || month > 12 )
			this.month = 1;
		else this.month = month;
	}
	public void setYear (int year){
		if (year < 0)
			this.year = 2010;
		else this.year = year;
	}
	
	// accessors and mutators
	public boolean isSame (OurDate date){
		if (this.year == date.year && this.month == date.month && this.day == date.day)
			return true;
		else return false;
	}
	public String toString() {   return new String ("" + day + "/" + month + "/" + year);
	}
	public int subtract (OurDate date) {
		int [] daysInMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // note first entry of 0 is so that January (month 1) can be used as first array index 
		int thisJulianDate = (this.year-1)*365;
		for (int i = 1; i < this.month; i++)
			thisJulianDate += daysInMonth[i];
		thisJulianDate += this.day;
		
		int paramJulianDate = (date.year-1)*365;
		for (int i = 1; i < date.month; i++)
			paramJulianDate += daysInMonth[i];
		paramJulianDate += date.day;
		
		return paramJulianDate - thisJulianDate;
	}
	public void inputFromKeyboard() {
		Scanner in = new Scanner (System.in);
		
		System.out.print ("\nEnter year: ");
		this.year = in.nextInt();
		while (this.year <= 0) {
			System.out.print ("Invalid year...reenter positive number: ");
			this.year = in.nextInt();
		}
		System.out.print ("Enter month: ");
		this.month = in.nextInt();
		while (this.month <= 0 || this.month > 12) {
			System.out.print ("Invalid month...reenter between 1 and 12: ");
			this.month = in.nextInt();
		}
		System.out.print ("Enter day: ");
		this.day = in.nextInt();
		while (this.day <= 0 || this.day > 31 || (this.month == 2 && this.day > 29) || (this.day > 30 && (this.month == 9 ||this.month == 4 ||this.month == 6 ||this.month == 11) ) ){
			System.out.print ("Invalid day for month...reenter between 1 and 31: ");
			this.day = in.nextInt();
		}
		
	}
	public void addOne (){
		this.day++;
		if (this.day > 31 || (this.month == 2 && this.day > 29) || (this.day > 30 && (this.month == 9 ||this.month == 4 ||this.month == 6 ||this.month == 11) ) ){ 
			this.day = 1;
			this.month ++;
			if (this.month > 12) {
				this.month = 1;
				this.year++;
			}
		}
	}

}
