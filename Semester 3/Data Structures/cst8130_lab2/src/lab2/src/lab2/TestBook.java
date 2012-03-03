package lab2;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TestBook {
	public static void main(String[] args) {
		// Uses the builder-pattern to create new Book objects. Only selected values need be initialized.
		// Unknown values are skipped.
		Book bookLordOfTheRings = new Book.Builder("Lord of the Rings")
		.author("Tolkein, J.R.R.").pages(1178).isbn(123456789012L).price(123.45).build();
		Book bookTheBelgariad = new Book.Builder("The Belgariad")
		.author("Eddings, David").pages(1823).isbn(144056789000L).price(99.99).build();
		Book bookTheChamberOfSecrets = new Book.Builder("The Chamber of Secrets")
		.author("Rowlings, J.K.").price(37.95).build();
		Book bookMasterCPlusPlus = new Book.Builder("Master C++").author("Woollard, Rex").build();
		Book bookWebstersDictionary = new Book.Builder("Webster's Dictionary").build();
		Book bookTheBible = new Book.Builder("The Bible").isbn(1).build();
		// Uses the constructor-style to create new Book objects. All arguments must be present, whether or
		// not they are needed. The Book constructor has been annotated with @Deprecated as a
		// mechanism to discourage its use, but retain the functionality.
		Book bookTheHobbit = new Book("The Hobbit", "Tolkein, J.R.R.", 0, 100056789000L, 98.76);
		Book bookTheMallorean = new Book("The Mallorean", "Eddings, David", 1940, 146758906640L, 88.88);
		Book bookTheGobletOfFire = new Book("Goblet of Fire", "Rowlings, J.K.", 986, 488484848333L, 77.77);
		// store all books in a List Collection which can be sorted.
		// The Book objects could have been created directly using the listBooks.add() method call,
		// but were created independently for greater clarity in this example
		List<Book> listBooks = new ArrayList<Book>();
		listBooks.add(bookLordOfTheRings);
		listBooks.add(bookTheBelgariad);
		listBooks.add(bookTheChamberOfSecrets);
		listBooks.add(bookMasterCPlusPlus);
		listBooks.add(bookWebstersDictionary);
		listBooks.add(bookTheBible);
		listBooks.add(bookTheHobbit);
		listBooks.add(bookTheMallorean);
		listBooks.add(bookTheGobletOfFire);
		System.out.println("Original Order");
		for (Book book : listBooks)
			System.out.println(book);
		// Sort using Title as the key
		// sort() is a static method in the Collections class; encapsulates a high-performance sorting algorithm.
		Collections.sort(listBooks, Book.CompareTitle.instance);
		System.out.println("\nSorted Order: Title");
		for (Book book : listBooks)
			System.out.println(book);
		// Sort using Author as the key
		Collections.sort(listBooks, Book.CompareAuthor.instance);
		System.out.println("\nSorted Order: Author");
		for (Book book : listBooks)
			System.out.println(book);
		// Sort using ISBN as the key
		Collections.sort(listBooks, Book.CompareISBN.instance);
		System.out.println("\nSorted Order: ISBN");
		for (Book book : listBooks)
			System.out.println(book);
		// Sort using Price as the key
		Collections.sort(listBooks, Book.ComparePrice.instance);
		System.out.println("\nSorted Order: Price");
		for (Book book : listBooks)
			System.out.println(book);
		// Sort using Pages as the key
		Collections.sort(listBooks, Book.ComparePages.instance);
		System.out.println("\nSorted Order: Pages");
		for (Book book : listBooks)
			System.out.println(book);
	} // end main()
} // end class TestBook
