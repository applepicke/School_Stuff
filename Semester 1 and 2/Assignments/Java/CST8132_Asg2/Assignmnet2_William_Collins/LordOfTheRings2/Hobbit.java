/**
 * This is an extension of the Elf class. A hobbit is an elf,
 * just representing 'h' on the field.
 * @author William Collins
 *
 */

public class Hobbit extends Elf{
	
	protected int strength;
	
	// constructors
	public Hobbit ( ){
		
	}
	
	public Hobbit(Actor actor ){
		super (actor);
	}
	
	public Hobbit(int strength, int magic) {
		super (strength, magic);
		
	}

	@Override public String toString(){
		return "h";
	}
}


