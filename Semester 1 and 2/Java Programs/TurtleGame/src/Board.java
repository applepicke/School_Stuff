import java.lang.*; 		//all import statements must be first
import java.util.*;	

public class Board {
	private int nRow;
	private int nCol;
	private char board [][];

	public Board( ) {
		nRow = 20;
		nCol = 20;
		board = new char[nRow][nCol];
	}

	public Board (int r, int c) {
		nRow = r;
		nCol = c;
		board = new char[nRow][nCol];
		for (int j = nRow-1; j >= 0; j--){
			for (int i = 0; i < nCol; i++) {
				board [j][i]=' ';
			}
		}	
	}	
	
	
	public boolean setSquare (int r, int c, boolean b, char s) {
		if (r < nRow && r >= 0 && c <nCol && c >= 0) {
			board [r][c]= s;
			return true;
		} else {
			return false;
		}
	}
	
	public boolean moveUpOK ( int r, int c) {
		if (r+1 >= nRow) return false;
		else return true;
	}

	public boolean moveDownOK ( int r, int c) {
		if (r-1 < 0) return false;
		else return true;
	}

	public boolean moveLeftOK ( int r, int c) {
		if (c-1 < 0) return false;
		else return true;
	}

	public boolean moveRightOK ( int r, int c) {
		if (c+1 >= nCol) return false;
		else return true;
	}

	public void display (int r, int c ) {
		// display top row of ---
		for (int i = 0; i < nCol+2; i++)
			System.out.print ("-");
		// display rows - note I display row 0 at bottom instead of top!
		for (int i = nRow-1; i >= 0 ; i--) {
			System.out.print ("\n|");
			for (int j = 0; j < nCol; j++) {
				if (r == i && c == j) 
					System.out.print (":");
				else System.out.print (board[i][j]);
			
			}
			System.out.print ("|");
		}
		System.out.println();
		// display bottom row of ---
		for (int i = 0; i < nCol+2; i++)
			System.out.print ("-");
	}
}


