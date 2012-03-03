import java.lang.*;


public class Board {
	
	int nRow;
	int nCol;
	boolean board [] [];
	
	
	
	
	public Board () {
		nRow = 20;
		nCol = 20;
		board = new boolean [20][20];
		for (int j=0 ; j < 20; j++){
			for (int i=0 ; i < 20; i++){
				board[j][i] = false;
			}
		}
	}
	
	
	
	
	
	public Board (int r, int c) {
		nRow = r;
		nCol = c;
		board = new boolean [r][c];
		for (int j=0 ; j < nRow; j++){
			for (int i=0 ; i < nCol; i++){
				board[j][i] = false;
			}
		}
	}
	
	
	
	public boolean setSquare (int r, int c, boolean b) {
		if (r <= 0 || r >= nRow || c <= 0 || c >= nCol) 
			return false;
		else
			board[r][c] = b;
			return true;
	}
	
	
	
	public boolean checkSquare (int r, int c) {
		if (r <= 0 || r >= nRow || c <= 0 || c >= nCol) 
			return false;
		else  
			return board[r][c];
	
		
		
	}
	
	
	
	public boolean moveUpOkay (int r, int c) {
		if (r-1 > 0) {
			return true;
		}
		else
			return false;
	}
	
	
	
	
	public boolean moveDownOkay (int r, int c) {
		if (r+1 < nRow) {
			return true;
		}
		else
			return false;
	}
	
	
	
	public boolean moveLeftOkay (int r, int c) {
		if (c-1 > 0) {
			return true;
		}	
		else 
			return false;
	}
	
	
	
	public boolean moveRightOkay (int r, int c) {
		if (c+1 < nCol - 1) {
			return true;
		}	
		else
			return false;
	}
	
	
	
	public void display(int r, int c) {
		System.out.print("\n                   ");
		for (int e = 0; e <= nCol; e++)
			if (e == nCol) {
				System.out.print("_");
			}
			else
				System.out.print("_");
		for (int j = 0; j < nRow; j++) {
			System.out.print("\n                   |");
			for (int i = 0; i < nCol; i++) {
				if (j == r && i == c) 
					System.out.print("@");
				else if (board[j][i] == true)
					System.out.print("*");
				else if (i == nCol - 1)
					System.out.print("|");
				else
					System.out.print(" ");
				
			}
		}
		System.out.print("\n                   ");
		for (int f = 0; f <= nCol; f++) {
			System.out.print("_");
		}
		
		
	}
	
	

}
