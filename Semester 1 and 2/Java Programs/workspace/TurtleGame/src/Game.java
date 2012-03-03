import java.lang.*;


public class Game {

	Turtle turtle;
	Board board;
	
	public Game() {
		turtle = new Turtle();
		board = new Board();
	}
	
	public Game(int r, int c, boolean b, int startR, int startC) {
		turtle = new Turtle(r, c, b);
		board = new Board(startR, startC);
	}
	
	public void display() {
		board.display(turtle.returnRow(),turtle.returnCol());
	}
	
	public boolean moveUp() {
		if (board.moveUpOkay(turtle.returnRow(), turtle.returnCol()) == true) {
			board.setSquare(turtle.returnRow(), turtle.returnCol(), turtle.isPenUp());
			turtle.moveUp();
			return true;
		}
		else
			return false;
			
	}
	
	public boolean moveDown() {
		if (board.moveDownOkay(turtle.returnRow(), turtle.returnCol()) == true) {
			board.setSquare(turtle.returnRow(), turtle.returnCol(), turtle.isPenUp());
			turtle.moveDown();
			return true;
		}
		else
			return false;
		
	}
	
	public boolean moveLeft() {
		if (board.moveLeftOkay(turtle.returnRow(), turtle.returnCol()) == true) {
			board.setSquare(turtle.returnRow(), turtle.returnCol(), turtle.isPenUp());
			turtle.moveLeft();
			return true;
		}
		else
			return false;
	}
	
	public boolean moveRight() {
		if (board.moveRightOkay(turtle.returnRow(), turtle.returnCol()) == true) {
			board.setSquare(turtle.returnRow(), turtle.returnCol(), turtle.isPenUp());
			turtle.moveRight();
			return true;
		}
		else 
			return false;
	}
	
	public void togglePen() {
		if (turtle.isPenUp() == true)
		turtle.movePenDown();
		else if (turtle.isPenUp() == false)
		turtle.movePenUp();
	}
	
	public boolean isPenUp () {
		if (turtle.isPenUp() == true)
			return true;
		else 
			return false;
	}
	
}
