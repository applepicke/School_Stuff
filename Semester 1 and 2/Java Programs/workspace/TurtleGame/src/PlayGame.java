import java.lang.*;
import java.util.Scanner;
import java.lang.String;


public class PlayGame {
	public static void main (String args[]) {
	
	Game game;
	Scanner input = new Scanner(System.in);
	String anyKey = new String ();
	int menucontrol = 1;
	int rows = 0;
	int cols = 0;
	boolean penStartUp;
	
	
	System.out.print("\n                   Turtles With Penzzzz!!");
	System.out.print("\n                   **********************");
	
	System.out.print("\n\nWelcome to Turtlezz With Penzz!");
	System.out.print("\nPress Enter to continue: ");
	anyKey = input.nextLine();
	
	do {
	System.out.print("\nEnter the number of rows you would like in the game(3-20): ");
	rows = input.nextInt();
	}
	while (rows > 20 || rows < 3);
	
	do {
	System.out.print("\nEnter the number of columns you would like in the game(3-20): ");
	cols = input.nextInt();
	}
	while (cols > 20 || cols < 3);
	
	
	game = new Game (rows - 1, 1, false, rows, cols);
	
	while (menucontrol != 0) {
		
		do {
			game.display();
			if (game.isPenUp() == true)
			System.out.print("\n                   Pen Trail Status = ON");
			else
				System.out.print("\n                   Pen Trail Status = OFF");
			System.out.print("\n\n0 - Exit the Game");
			System.out.print("\n1 - Toggle Pen");
			System.out.print("\n2 - Move Right");
			System.out.print("\n3 - Move Left");
			System.out.print("\n4 - Move Up");
			System.out.print("\n5 - Move Down");
			menucontrol = input.nextInt();
		
			//0 - Exit the Menu
			if (menucontrol == 0)
				break;
		
			//1 - Toggle Pen
			if (menucontrol == 1) {
				game.togglePen();
			}
		
			//2 - Move Right
			else if (menucontrol == 2) {
				game.moveRight();
			}
		
			//3 - Move Left
			else if (menucontrol == 3) {
				game.moveLeft();
			}
		
			//4 - Move Up
			else if (menucontrol == 4) {
				game.moveUp();
			}
		
			//5 - Move Down
			else if (menucontrol == 5) {
				game.moveDown();
			}
		}
		while (menucontrol < 0 || menucontrol > 5);
	}
	
	System.out.print("\nToodles!!!");
	
	}
	

}
