class SalesRep extends Employee {
	protected double salesAmount;
        protected double commissionRate;

	public SalesRep () {
	}
	public SalesRep (String name, Date startDate, Date dateOfBirth, double weeklyPayAmount, double weeklyTaxAmount, double salesAmount, double commissionRate) {
	 	super(name, startDate, dateOfBirth, weeklyPayAmount, weeklyTaxAmount);
		this.salesAmount = salesAmount;
		this.commissionRate = commissionRate;
	}
	
	public double getSalesAmount () {return salesAmount; }
	public double getCommissionRate() { return commissionRate; }

	public void setSalesAmount (double salesAmount) {
		this.salesAmount = salesAmount; 
	}
	public void setCommissionRate (double commissionRate) {
		this.commissionRate = commissionRate;
	}
	
	@Override
	public void calcWeeklyPayAmount() {
		this.weeklyPayAmount = this.salesAmount * this.commissionRate;
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
    	
    	//Sales Amount
    	System.out.print("Enter Sales Amount: ");
    	salesAmount = in.nextDouble();
    	
    	//Commision Rate
    	System.out.print("Enter your commision rate: ");
    	commissionRate = in.nextDouble();
    	
	}
}
