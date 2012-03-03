@SuppressWarnings("serial")
public class EmptyListException extends RuntimeException {
	// no-argument constructor
	public EmptyListException() {
		this("List"); // call other EmptyListException constructor
	} // end EmptyListException no-argument constructor

	// one-argument constructor
	public EmptyListException(String name) {
		super(name + " is empty"); // call superclass constructor
	} // end EmptyListException one-argument constructor
} // end class EmptyListException