import java.lang.*;
import java.util.Random;



// The purpose of the actor is to move around the board. This class will contain the type of actor,
// and also its strength, position, assignment of random move number. 
public class Actor {
	
	private char actorType;
	private int colPosition;
	private int rowPosition;
	private int actorStrength;
	
	Random move;
	Random strength;
	
	// Default Constructor
	public Actor() {
		actorType = ' ';
		actorStrength = 0;
		colPosition = 0;
		rowPosition = 0;
		
	}
	
	// Initialize Actor's Type, Strength, and Position
	public Actor(char type){
		actorType = type;
	}
	
	// Randomize a move number for each move
	public int setRandomMove() {
		move = new Random ();
		return move.nextInt(4);
	}
	
	// Randomize a Strength
	public int setRandomStrength() {
		strength = new Random();
		return strength.nextInt(9)+1;
	}
	
	// Sets a character type
	public void setActorType(char type){
		actorType = type;
	}
	
	// Returns character type
	public int getActorType() {
		return actorType;
	}
	
	// Edits the character's position
	public void editPosition(int row, int col) {
		rowPosition = row;
		colPosition = col;
	}
	
	// Returns the character's row
	public int getRow() { return rowPosition; }
	
	// Returns the character's column
	public int getCol() { return colPosition; }
	
	// Move actor to the right
	public void moveRight() { colPosition += 1; }	
	
	// Move actor to the left
	public void moveLeft() { colPosition -= 1; }
	
	// move actor down
	public void moveDown() { rowPosition += 1; }
	
	// move actor up
	public void moveUp() { rowPosition -= 1; }
	
}
