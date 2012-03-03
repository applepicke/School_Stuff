import java.lang.*; 		//all import statements must be first
import java.util.*;
import java.util.Scanner;
import java.lang.String;

public class Game {
	private Board board;
	private Turtle turtle;
	private String turtleString;
	private char  turtleChar;
	Scanner input = new Scanner(System.in);

	public Game ( ) {
		board = new Board();
		turtle = new Turtle();
		turtleString = new String();
		turtleChar = '*';
	}

	public Game (int r, int c, int startR, int startC) {
		board = new Board(r, c);
		turtle = new Turtle(startR, startC, true, turtleChar);
		turtleString = new String();
		turtleChar = '*';
	}
	
	public void changeTurtle () {
		System.out.print("\n Please enter a new symbol for the turtle: ");
		turtleString = input.nextLine(); 
		turtleChar = turtleString.charAt(0);
		
	}

	public void display ( ) {
		board.display (turtle.getRow(), turtle.getCol()) ;
	}

	public boolean moveUp ( ) {
		if (board.moveUpOK(turtle.getRow(), turtle.getCol())) {
			if ( ! turtle.isPenUp( )) 
				board.setSquare(turtle.getRow(), turtle.getCol(), true, turtleChar);
			turtle.setRow(turtle.getRow() + 1);
			return true;
		} else {
			System.out.println ("Invalid move...");
			return false;
		}
	}

	public boolean moveDown ( ) {
		if (board.moveDownOK(turtle.getRow(), turtle.getCol())){ 
			if ( ! turtle.isPenUp( )) 
				board.setSquare(turtle.getRow(), turtle.getCol(), true, turtleChar);
			turtle.setRow(turtle.getRow() - 1);
			return true;
		} else {
			System.out.println ("Invalid move...");
			return false;
		}
	}

	public boolean moveLeft ( ) {
		if (board.moveLeftOK(turtle.getRow(), turtle.getCol())){ 
			if ( ! turtle.isPenUp( )) 
				board.setSquare(turtle.getRow(), turtle.getCol(), true, turtleChar);
			turtle.setCol(turtle.getCol() - 1);
			return true;
		} else {
			System.out.println ("Invalid move...");
			return false;
		}
	}

	public boolean moveRight ( ) {
		if (board.moveRightOK(turtle.getRow(), turtle.getCol())) {
			if ( ! turtle.isPenUp( ))
				board.setSquare(turtle.getRow(), turtle.getCol(), true, turtleChar);
			turtle.setCol(turtle.getCol() + 1);
			return true;
		} else {
			System.out.println ("Invalid move...");
			return false;
		}
	}

	public void raisePen() {
		turtle.setPen (true);
	}

	public void lowerPen() {
		turtle.setPen (false);
	}

}

