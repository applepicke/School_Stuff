/**   This class extends an actor as an orc
 *	  Author:  Linda Crane (Updated by William Collins)
 *	  Data fields:   actorType:  char - holds 'e', 'o' or default ' '
 *                   strength: int - must be between 0 and 10
 *    Methods: setStrength: 
 */
public class Orc extends Actor{
	
	protected char actorType = ' ';
	protected int strength;
	
	// constructors
	public Orc() {
		
	}
	
	public Orc(Actor actor ){
		super(actor);
	}
	
	public Orc(char actorType, int strength, int weapon){
		super(actorType, strength + weapon);
	}

	

}