/**
 * 
 * @author William Collins
 * Data Fields: char actorType: the display character for the elf
 * 				int strength: the strength of the character
 * 
 *
 */
public class Elf extends Actor{
	
	protected int strength;
	
	// constructors
	public Elf ( ){
		
	}
	
	public Elf(Actor actor ){
		super (actor);
	}
	
	public Elf(int strength, int magic) {
		super (strength * magic);
		
	}

	@Override public String toString(){
		return "e";
	}
}