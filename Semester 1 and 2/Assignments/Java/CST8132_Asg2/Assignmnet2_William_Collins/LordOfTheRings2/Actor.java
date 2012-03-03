/**   This class models an actor
 *	  Author:  Linda Crane (Extended by William Collins)
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
	private int strength;
	
	// constructors
	public Actor(Actor actor){
		this.strength = actor.strength;

	}
	public Actor(int strength){
		this.strength = strength;
		
	}
	public Actor ( ){
		
	}
	// get methods
	public int getStrength() { return strength; } 
	
	// set methods
	public void setStrength (int strength) {
			this.strength = strength;

	}

	public String toString(){
		return " ";
	}

}
