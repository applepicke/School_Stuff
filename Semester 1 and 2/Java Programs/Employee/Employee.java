import java.util.*;
import java.util.Scanner;

class Employee {
    protected String name = new String();
    protected Date startDate= new Date();
    protected Date dateOfBirth = new Date();
    protected double weeklyPayAmount;
    protected double weeklyTaxAmount;
    protected Scanner in = new Scanner(System.in);

    public Employee () {
    }
    public Employee (String name, Date startDate, Date dateOfBirth, double weeklyPayAmount, double weeklyTaxAmount) {
	this.name = new String (name);
        this.startDate = new Date (startDate);
	this.dateOfBirth = new Date (dateOfBirth);
	this.weeklyPayAmount = weeklyPayAmount;
	this.weeklyTaxAmount = weeklyTaxAmount;
    }
    public Employee (Employee employee) {
	this.name = new String (employee.name);
        this.startDate = new Date (employee.startDate);
	this.dateOfBirth = new Date (employee.dateOfBirth);
	this.weeklyPayAmount = employee.weeklyPayAmount;
	this.weeklyTaxAmount = employee.weeklyTaxAmount;
    }

    public String getName () { return name; }
    public Date getStartDate() { return startDate; }
    public Date dateOfBirth() { return dateOfBirth; }
    public double getWeeklyPayAmount() { return weeklyPayAmount; }
    public double getWeeklyTaxAmount() { return weeklyTaxAmount; }

    public void setName (String name) {
	this.name = new String (name);
    }
    public void setStartDate (Date startDate) {
	this.startDate = new Date (startDate);
    }
    public void setDateOfBirth (Date dateOfBirth) {
	this.dateOfBirth = new Date (dateOfBirth);
    }
    public void setWeeklyPayAmount (double weeklyPayAmount) {
	this.weeklyPayAmount = weeklyPayAmount;
    }
    public void setWeeklyTaxAmount (double weeklyTaxAmount) {
	this.weeklyTaxAmount = weeklyTaxAmount;
    }


    public void calcWeeklyPayAmount() {
    }
    public void calcWeeklyTaxAmount() {
	if (weeklyPayAmount > 2000)
		weeklyTaxAmount = weeklyPayAmount * 0.3;
	else if (weeklyPayAmount < 1000)
		weeklyTaxAmount = 0;
	else    weeklyTaxAmount = weeklyPayAmount * 0.2;
    }

    public String toString () {
	return name + " Pay: $" + weeklyPayAmount + " Tax $" + weeklyTaxAmount;
    }
    
    public void setFromKeyboard() {
    	weeklyPayAmount = 0;
    	weeklyTaxAmount = 0;
    	
    	//Name
    	System.out.print("\nPlease enter your name: ");
    	name = in.nextLine();
    	
    	
    	//Enter Birth Date
    	System.out.print("\nEnter birth date: \nYear: ");
    	dateOfBirth.setYear(in.nextInt());
    	do {
    	System.out.print("Month: ");
    	dateOfBirth.setMonth(in.nextInt());
    	}while (dateOfBirth.getMonth() < 1  || dateOfBirth.getMonth() > 12);
    	do {
    	System.out.print("Day: ");
    	dateOfBirth.setDay(in.nextInt());
    	}while (dateOfBirth.getDay() < 1  || dateOfBirth.getDay() > 31);
    	
    	//Start Date
    	
    	do {
    	System.out.print("\nEnter start date: \nYear: ");
    	startDate.setYear(in.nextInt());
    	}while (startDate.getYear() < dateOfBirth.getYear());
    	do {
    	System.out.print("Month: ");
    	startDate.setMonth(in.nextInt());
    	}while (startDate.getMonth() < 1  || startDate.getMonth() > 12);
    	do {
    	System.out.print("Day: ");
    	startDate.setDay(in.nextInt());
    	}while (startDate.getDay() < 1  || startDate.getDay() > 31);
    	
    	
    	
    }
}
