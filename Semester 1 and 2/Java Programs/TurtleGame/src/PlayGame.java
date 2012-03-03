import java.lang.*; 		//all import statements must be first
import java.util.*;	

public class PlayGame {
	public static void main (String[] argv) {
		Scanner in = new Scanner (System.in);

		int row;
		int col;

		do {
			System.out.print( "\nEnter the dimensions of the board, first the number of rows 20 max:  ");
			row = in.nextInt();
		} while (row < 0 || row > 20);

		do {
			System.out.print( "\nNow the number of cols 20 max:  ");
			col = in.nextInt();
		} while (col < 0 || col > 20);

		Game game = new Game(row,col, 0, 0);

		int choice = 1;
		while (choice !=0) {
			do {
				System.out.println("\nEnter direction to move - 1 for up, 2 for down, 3 for left, 4 for right..");
				System.out.print ("      or 5 to raise the pen, 6 to lower the pen, 7 to display, 8 to chamge symbol, 0 to quit:  "); 
				choice = in.nextInt();
			} while (choice < 0 || choice > 8);

			switch (choice) {
				case 0:  System.out.println ("Goodbye..."); break;
				case 1:  game.moveUp(); break;
				case 2:  game.moveDown(); break;
				case 3:  game.moveLeft(); break;
				case 4:  game.moveRight(); break;
				case 5:  game.raisePen(); break;
				case 6:  game.lowerPen(); break;
				case 7:  game.display( ); break;
				case 8:  game.changeTurtle(); break;
				
			} // end switch
		}// end while
	}// end main
}//end class

