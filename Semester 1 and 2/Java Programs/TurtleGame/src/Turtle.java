import java.lang.*; 		//all import statements must be first
import java.util.*;	
public class Turtle {
	
	private char turtleSymbol;
	private int row;
	private int col;
	private boolean penUp;

	public Turtle ( ) {
		row = 0;
		col = 0;
		penUp = true;
		turtleSymbol = '*';
	}

	public Turtle (int r, int c, boolean b, char s) { 
		row = r;
		col = c;
		penUp = b;
		turtleSymbol = s;
	}
	public void setSymbol (char s){ turtleSymbol = s; }
	public char getSymbol () { return turtleSymbol; }
	public int getRow() {  return row; }
	public int getCol( ) { return col; }
	public boolean getPenUp ( ) { return penUp; }

	public void setRow (int r) { row = r;    }
	public void setCol (int c) { col = c;    }
            public void setPen (boolean b) { penUp = b; }

	public boolean isPenUp ( ) { return penUp; }

	public void  moveUp( ) { row ++;  }
	public void  moveDown( ) { row --;  }
	public void moveLeft( ) { col--;  }
	public void moveRight( ) { col++; }

	public void movePenUp( ) { penUp = true; }
	public void movePenDown( ) { penUp = false; }
}

