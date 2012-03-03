import java.lang.*; 		//all import statements must be first
import java.util.*;			//program uses class Scanner
/**   This class models a die - Linda Crane
 * 	  Data fields - value (int containing 1 through 6), colour (string)
 *    Methods - initial constructor, default constructor
 *    		  - rollDie - put random value in die value
 *    		  - inputValue, inputColour - input from keyboard
 *    		  - returnValue, returnColour - returns
 *    		  - display, displayGraphic - displays of data
  *   @version 1
  *   @see java.lang.String
  *   @see java.util.Scanner
  */
public class Die {
	private int value;
	private String colour;
	
	// default constructor
	public Die() {  value = 1;
	                colour = new String("white");
	}
	// initial constructor
	public Die(int v, String c) { value = v;
	                              colour = new String (c);
	}

	public void rollDie( ) {
		Random randomNumbers = new Random();
		value = randomNumbers.nextInt(6)+1;
	}

	public void inputValue() {
		Scanner input = new Scanner (System.in);
		
		System.out.println("Please enter your die value: ");
		value = input.nextInt();
		while (value < 1 || value > 6) {
			System.out.println("Invalid...Please enter your die value 1 - 6: ");
			value = input.nextInt();
		}	
	}

	public void inputColour() {
		Scanner input = new Scanner (System.in);
		
		System.out.println("Please enter your die colour: ");
		colour = input.nextLine();
	}

	public int returnValue ( ) {  return value;  }

	public String returnColour ( ){ return colour; }
	
	public void display () {
		System.out.println( "Your " + colour + " die has value " + value);
	}	
	public void displayGraphic () {
		if (value == 1){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|         |");
			System.out.println("|    *    |");
			System.out.println("|         |");
			System.out.println(" _________");
		}
		else if (value == 2){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *      |");
			System.out.println("|         |");
			System.out.println("|      *  |");
			System.out.println(" _________");
		}	
		else if (value == 3){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *      |");
			System.out.println("|    *    |");
			System.out.println("|      *  |");
			System.out.println(" _________");
		}	
		else if (value == 4){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println(" _________");
		}
		else if (value == 4){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println(" _________");
		}
		else if (value == 5){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println("|    *    |");
			System.out.println("|  *   *  |");
			System.out.println(" _________");
			
		}
		else if (value == 6){
			System.out.println(" _________");
			System.out.println("|         |");
			System.out.println("|  *   *  |");
			System.out.println("|  *   *  |");
			System.out.println("|  *   *  |");
			System.out.println(" _________");
			
		}
				
				
		
	}
	
	
}


