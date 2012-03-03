/**
 * 
 * @author William Collins
 *
 */
public class Wizard extends Orc {

	protected int strength;
	
	// constructors
	public Wizard() {
		
	}
	
	public Wizard(Actor actor ){
		super(actor);
	}
	
	public Wizard(int strength, int weapon){
		super(strength, weapon);
	}

	@Override public String toString(){
		return "w";
	}
}
