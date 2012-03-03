class Executive extends Employee {
	protected double yearlySalary;

	public Executive () {
	}
	public Executive (String name, Date startDate, Date dateOfBirth, double weeklyPayAmount, double weeklyTaxAmount, double yearlySalary) {
	 	super(name, startDate, dateOfBirth, weeklyPayAmount, weeklyTaxAmount);
		this.yearlySalary = yearlySalary;
	}

	public double getYearlySalary () {return yearlySalary; }
	public void setYearlySalary (double yearlySalary) {
		this.yearlySalary = yearlySalary; 
	}
	
	@Override
	public void calcWeeklyPayAmount() {
		this.weeklyPayAmount = yearlySalary / 52.0;
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
    	
    	//Yearly Salary
    	System.out.print("Enter yearly salary: ");
    	yearlySalary = in.nextDouble();
    }
		
}
