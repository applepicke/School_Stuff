class Programmer extends Employee {
	protected double hoursWorked;
        protected double rateOfPay;

	public Programmer() {
	}
	public Programmer (String name, Date startDate, Date dateOfBirth, double weeklyPayAmount, double weeklyTaxAmount, double hoursWorked, double rateOfPay) {
	 	super(name, startDate, dateOfBirth, weeklyPayAmount, weeklyTaxAmount);
		this.hoursWorked = hoursWorked;
		this.rateOfPay = rateOfPay;
	}

	public double getHoursWorked () {return hoursWorked; }
	public double getTateOfPay() { return rateOfPay; }

	public void setHoursWorked (double hoursWorked) {
		this.hoursWorked = hoursWorked; 
	}
	public void setTateOfPay (double rateOfPay) {
		this.rateOfPay = rateOfPay;
	}
	
	@Override
	public void calcWeeklyPayAmount() {
		if (hoursWorked < 40) 
			this.weeklyPayAmount = this.hoursWorked * this.rateOfPay;
		else    this.weeklyPayAmount = ((this.hoursWorked-40) *1.5 + 40)* this.rateOfPay;
	}
	
	@Override
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
    	
    	//Hours Worked
    	System.out.print("Enter hours worked: ");
    	hoursWorked = in.nextInt();
    	
    	//Rate of Pay
    	System.out.print("Enter hourly pay: ");
    	rateOfPay = in.nextDouble();
    }
		
}
