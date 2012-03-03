/**  class Square models a square on the battlefield
 *   Author:  Linda Crane(Extended by William Collins)
 *   Data Fields:  terrain: char - holds 'n' (normal) or 'm'(mountain)
 *				   actor: Actor - holds actor on the square
 *	 Methods:  default constructor
 *             initial constructor- with parameters char and Actor 
 *			   copy constructor
 *             getTerrain: returns terrain
 *             getActor:  returns actor
 *             setTerrain: sets based on parameter terrain
 *             setActor: sets based on parameter actor
 *             toString:  returns M if there's a mountain, otherwise value of actor
 */
public class Square {
	private char terrain = 'n';
	private Actor actor;
	
	public Square () {
		actor = new Actor();
	}
	public Square (Square square) {
		if (square.getTerrain() == 'n' || square.getTerrain() == 'm')
			this.terrain = square.getTerrain();
		else this.terrain = 'n';
		
		this.setActor(square.getActor());

	}
	public Square(char terrain, Actor actor){
		if (terrain == 'n' || terrain == 'm')
			this.terrain = terrain;
		else this.terrain = 'n'; 
		
		this.setActor(actor);
			
	}
	
	// get methods
	public char getTerrain ( ){ return terrain; }
	public Actor getActor() { return actor; }
	
	// set methods
	public void setTerrain (char terrain){
		if (terrain == 'n' || terrain == 'm')
			this.terrain = terrain;
		else this.terrain = 'n';
	}
	/************Updated*****************/
	public void setActor (Actor actor) {
		if(actor instanceof Hobbit)
			this.actor = new Hobbit(actor);
		else if(actor instanceof Wizard)
			this.actor = new Wizard(actor);
		else if (actor instanceof Elf) 
			this.actor = new Elf(actor);
		else if(actor instanceof Orc)
			this.actor = new Orc(actor);
		else
			this.actor = new Actor(actor);
	}
	
	/************Update*****************/

	/************Update*****************/
	
	public String toString() {
		if (terrain == 'm') {
			if (actor.toString() == "e" || actor.toString() == "h" || actor.toString() == "o" || actor.toString() == "w")
				return actor.toString();
			else return "M";
		}
		else  return actor.toString();
	
	}
	
	/***********************************/
}
