import java.lang.*;


public class Turtle {

	int row;
	int col;
	boolean penUp;
	
	
	public Turtle () {
		row = 19;
		col = 1;
		penUp = false;
	}
	
	
	public Turtle (int r, int c, boolean b) {
		row = r;
		col = c;
		penUp = b;
	}
	
	public int returnRow() {
		return row;
	}
	
	public int returnCol() {
		return col;
	}
	
	public boolean returnPenUp() {
		return penUp;
	}
	
	public void setRow(int r) {
		row = r;
	}
	
	public void setCol(int c) {
		col = c;
	}
	
	public void setPen(boolean b) {
		penUp = b;
	}
	
	public boolean isPenUp() {
		return penUp;
	}
	
	public void moveUp() {
		row -= 1;
	}
	
	public void moveDown() {
		row += 1;
	}
	
	public void moveLeft() {
		col -= 1;
	}
	
	public void moveRight() {
		col += 1;
	}
	
	public void movePenUp() {
		penUp = true;
	}
	
	public void movePenDown() {
		penUp = false;
	}
	
	
	
}
