public class ListTest {
	public static void main(String args[]) {
		List list = new List(); // create the List container

		// insert Strings in list
		list.insertInSequence("Adams"); list.display();
		list.insertInSequence("Cobby"); list.display();
		list.insertInSequence("Bones"); list.display();
	
		list.insertInSequence("Abamith");  list.display();
		list.insertInSequence("Bilson"); list.display();

		// remove objects from list; print after each removal
		try {
			Object removedObject = list.removeFromFront();
			System.out.printf("%s removed\n", removedObject);
			list.display();

			removedObject = list.removeFromFront();
			System.out.printf("%s removed\n", removedObject);
			list.display();

			removedObject = list.removeFromFront();
			System.out.printf("%s removed\n", removedObject);
			list.display();

			removedObject = list.removeFromFront();
			System.out.printf("%s removed\n", removedObject);
			list.display();
		} // end try
		catch (EmptyListException emptyListException) {
			emptyListException.printStackTrace();
		} // end catch
	} // end main
} // end class ListTest