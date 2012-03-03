/**   This class models an actor
 *	  Author:  Linda Crane
 *	  Data fields:   actorType:  char - holds 'e', 'o' or default ' '
 *                   strength: int - must be between 0 and 10
 *    Methods:  default constructor
 *              initial constructor - using paramters actorType and strength
 *              copy constructor
 *              getActorType:  returns actorType
 *				getStrength : returns strength
 *				setActorType:  sets based on parameter ActorType
 *			    setStrength : sets based on parameter Strength
 *			    toString: returns actorType as a String
 */
public class Actor {
	private char actorType = ' ';
	private int strength;
	
	// constructors
	public Actor(Actor actor ){
		if (actor.actorType == 'e' || actor.actorType == 'o' || actor.actorType == 'w' || actor.actorType == 'h')
			this.actorType = actor.actorType;
		else this.actorType = ' ';

		this.strength = actor.strength;

	}
	public Actor(char actorType, int strength){
		if (actorType == 'e' || actorType == 'o' || actorType == 'w' || actorType == 'h')
			this.actorType = actorType;
		else this.actorType = ' ';

	
		this.strength = strength;
		
	}
	public Actor ( ){
		
	}
	// get methods
	public char getActorType() { return actorType; }
	public int getStrength() { return strength; } 
	
	// set methods
	public void setActorType(char actorType) {
		if (actorType == 'e' || actorType == 'o' || actorType == 'w' || actorType == 'h')
			this.actorType = actorType;
		else this.actorType = ' ';
	}
	public void setStrength (int strength) {
			this.strength = strength;

	}

	public char getActorTeam(){
		if (actorType == 'e' || actorType == 'h')
			return 'e';
		else 
			return 'o';
	}

	public String toString(){
		return "" + actorType;
	}

}
