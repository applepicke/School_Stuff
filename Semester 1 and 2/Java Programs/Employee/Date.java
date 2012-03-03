import java.util.*;

class Date {
	private int year;
	private int month;
	private int day;

	public Date () {
	}
	public Date (int year, int month, int day) {
		this.year = year;
		this.month = month;
		this.day = day;
	}
	public Date (Date date) {
		this.year = date.year;
		this.month = date.month;
		this.day = date.day;
	}

	public int getYear () { return year; }
	public int getMonth() { return month; }
	public int getDay()   { return day;  }

	public void setYear (int year) {
		this.year = year;
	}
	public void setMonth (int month) {
		this.month = month;
	}
	public void setDay (int day) {
		this.day = day;
	}

	public String toString () {
		return " " + year + "/" + month + "/" + day;
	}
}