import java.util.Scanner;
import java.util.Random;
/**   Battlefield simulator
 *	  Author:  Linda Crane
 */
public class LordOfTheRings {

	
	public static void main(String[] args) {
		Scanner in = new Scanner (System.in);
		final  int NUMROWS = 4;
		final  int NUMCOLS = 4;
		Battlefield game = new Battlefield (NUMROWS, NUMCOLS);  // start with 4 x 4 battlefield
		
		// initialization of mountains terrain
																  // parameters are for Square constructor'm' for mountain terrain, ' ' for default actor type, 0 for default actor strength
		game.setSquare(1, 2, new Square('m', new Actor(' ', 0))); // parameters are 1 for row, 2 for col, temp for Square
		game.setSquare(2, 2, new Square('m', new Actor(' ', 0)));
		
			
		// initialization of actors

		game.setSquare(0, 3, new Square('n', new Elf('e', 7, 2)));
		game.setSquare(1, 0, new Square('n', new Orc('o', 5, 12)));
		game.setSquare(3, 2, new Square('n', new Elf('h', 9, 5)));
		game.setSquare(3, 1, new Square('n', new Elf('e', 5, 5)));
		game.setSquare(0, 2, new Square('n', new Orc('w', 3, 14)));
		
		
		// display battlefield
		game.display();
		
		Random move = new Random();
		int cont = 0;
		while (game.getNumElves()>0 && game.getNumOrcs()>0 && cont == 0){
			// move each actor in the board
			System.out.println ("Move each actor: ");
			for (int i = 0 ; i < NUMROWS; i++)
				for (int j= 0; j < NUMCOLS; j++) {
					game.moveActor(move.nextInt(4), i, j);

				}
			game.display();
			System.out.print ("Enter 0 to continue, 1 to quit:");
			cont = in.nextInt();
		} // end while
		if (game.getNumOrcs() > 0)  System.out.println ("Orcs won...with " + game.getNumOrcs()  );
		else System.out.println ("Elves won...with " + game.getNumElves()  );

	}// end main
	
} // end of class
