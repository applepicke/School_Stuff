/**
 * 
 * @author William Collins
 * Data Fields: char actorType: the display character for the orc
 * 				int strength: the strength of the character
 * 
 *
 */
public class Orc extends Actor{
	
	protected int strength;
	
	// constructors
	public Orc() {
		
	}
	
	public Orc(Actor actor ){
		super(actor);
	}
	
	public Orc(int strength, int weapon){
		super(strength + weapon);
	}

	@Override public String toString(){
		return "o";
	}

}