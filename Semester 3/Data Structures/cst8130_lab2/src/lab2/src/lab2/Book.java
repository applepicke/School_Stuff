package lab2;

import java.util.Comparator;
public class Book {
	private String sTitle;
	private String sAuthor;
	private int nPages;
	private long lISBN;
	private double dPrice;
	private Book(Builder builder) {
		sTitle = builder.sTitle;
		sAuthor = builder.sAuthor;
		nPages = builder.nPages;
		lISBN = builder.lISBN;
		dPrice = builder.dPrice;
	}
	@Deprecated // @Deprecated annotation discourages use of the method, but still allows it to function.
	public Book(String sTitle, String sAuthor, int nPages, long lISBN, double dPrice) {
		this.sTitle = sTitle;
		this.sAuthor = sAuthor;
		this.nPages = nPages;
		this.lISBN = lISBN;
		this.dPrice = dPrice;
	}
	@Override // @Override annotation checks spelling and argument matching with superclass version
	public String toString() {
		return String.format("Title:%-25s Author:%-15s Pages:%4d ISBN:%013d Price:%6.2f",
				sTitle, sAuthor, nPages, lISBN, dPrice);
	}
	// BUILDER DESIGN PATTERN
	// inner static class
	public static class Builder {
		// Required Parameter
		private final String sTitle;
		// Optional Parameters
		private String sAuthor = "";
		private int nPages;
		private long lISBN;
		private double dPrice;

		// Constructor arguments force the required fields to be specified
		public Builder(String sTitle) { this.sTitle = sTitle; }
		// Named methods provide optional initialization. Returning "this" allows for cascading initialization calls.
		public Builder author(String sAuthor) { this.sAuthor = sAuthor; return this; }
		public Builder pages(int nPages) { this.nPages = nPages; return this; }
		public Builder isbn(long lISBN) { this.lISBN = lISBN; return this; }
		public Builder price(double dPrice) { this.dPrice = dPrice; return this; }
		// Builder.build() creates a Book object, populates it with values already initialized by Builder.
		// Builder object is sent to a newly created Book() object.
		// The Builder has already fully organized initialization.
		public Book build() { return new Book(this); }
	} // end class Builder
	// SINGLETON DESIGN PATTERN
	// Comparator interface ensures that each inner static class implements a compare() method.
	// The Collections.sort() method needs access to the specific compare() method.
	// Java won't allow sending a reference to a method, but it will allow a reference to an object.
	// Create an object that has access to a compare() method; capture object location as a static final reference.
	// Use the static final reference when calling Collections.sort().
	// The Colletions.sort() algorithm can access the compare() method using the object reference.
	
	
	public static class CompareTitle implements Comparator<Book> {
		// No CompareTitle object will be created if instance variable never used.
		public final static CompareTitle instance = new CompareTitle();
		private CompareTitle() { } // private keyword prevents creation of CompareTitle objects outside the class
		@Override // Comparator interface enforces requirement that a compare() method be implemented.
		public int compare(Book book1, Book book2) { return book1.sTitle.compareTo(book2.sTitle); }
	} // end class CompareTitle
	
	public static class CompareAuthor implements Comparator<Book> {
		// TODO Comparator class to compare based on sAuthor
		public final static CompareAuthor instance = new CompareAuthor();
		private CompareAuthor() { } 
		@Override 
		public int compare(Book book1, Book book2) { return book1.sAuthor.compareTo(book2.sAuthor); }
	} // end class CompareAuthor
	
	public static class ComparePages implements Comparator<Book> {
		// TODO Comparator class to compare based on nPages
		public final static ComparePages instance = new ComparePages();
		private ComparePages() { } 
		@Override 
		public int compare(Book book1, Book book2) { return (book1.nPages - book2.nPages);}
		
	} // end class ComparePages
	
	public static class CompareISBN implements Comparator<Book> {
		// TODO Comparator class to compare based on lISBN
		public final static CompareISBN instance = new CompareISBN();
		private CompareISBN() { } 
		@Override 
		public int compare(Book book1, Book book2){  
			if (book1.lISBN > book2.lISBN) return 1;
			else if (book1.lISBN == book2.lISBN) return 0;
			else return -1;
		}
	} // end class CompareISBN
	
	public static class ComparePrice implements Comparator<Book> {
		// TODO Comparator class to compare based on dPrice
		public final static ComparePrice instance = new ComparePrice();
		private ComparePrice() { } 
		@Override 
		public int compare(Book book1, Book book2) { return Double.compare(book1.dPrice, book2.dPrice);}
	} // end class ComparePrice
	
	
} // end class Book