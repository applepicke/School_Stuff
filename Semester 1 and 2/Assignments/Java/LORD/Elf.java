
public class Elf extends Actor{
	
	protected char actorType = ' ';
	protected int strength;
	
	// constructors
	public Elf ( ){
		
	}
	
	public Elf(Actor actor ){
		super (actor);
	}
	
	public Elf(char actorType, int strength, int magic) {
		super (actorType, strength * magic);
	}


}