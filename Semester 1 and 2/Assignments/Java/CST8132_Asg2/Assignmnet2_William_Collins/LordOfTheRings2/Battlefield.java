/**  Battlefield - models a two-dimensional array of Square objects
 *   Author:  Linda Crane (Extended by William Collins)
 *	 Data Fields:  numRows: int - number of rows in array
 *				   numCols: int - number of cols in array
 *				   battlefield:  Square[][]
 *                 numElves:  int - number of elves in array
 *                 numOrcs: int - number of orcs in array
 *   Methods:  initial constructor - using parameters of numRows and numCols
 *             getNumRows - returns numRows
 *             getNumCols - returns numCols
 *			   getNumElves - returns numElves
 *			   getNumOrcs - returns numOrcs
 *			   setSquare: sets value of square based on parameters row, col and Square object, increments numElves and numOrcs
 *			   display:  displays the battlefield array
 *			   moveActor: moves current actor at position indicated by parameters row and col, in direction indicated by parameter direction
 */
public class Battlefield {
	private int numRows;
	private int numCols;
	private Square [] [] battlefield;
	private int numElves;
	private int numOrcs;
	
	public Battlefield (int numRows, int numCols) {
		this.numRows = numRows;
		this.numCols = numCols;
		battlefield = new Square[numRows][numCols];
		for (int i = 0; i < numRows; i++)
			for (int j = 0; j < numCols; j++) 
				battlefield[i][j] = new Square();
	}
	
	// get methods
	public int getNumRows() { return numRows; }
	public int getNumCols() { return numCols; }
	public Square getSquare (int row, int col) {
		return battlefield[row][col];
	}
	public int getNumElves() { return numElves; }
	public int getNumOrcs() { return numOrcs; }
	
	// set methods
	public void setSquare(int row, int col, Square square) {
		battlefield[row][col] = new Square(square);
		if (square.getActor().toString() == "o" || square.getActor().toString() == "w") numOrcs++;
		else if (square.getActor().toString() == "e" || square.getActor().toString() == "h") numElves++;
	}

	// other methods
	public void display () {
		// display top border
		for (int i = 0; i < numCols+2; i++)
			System.out.print("-");
		System.out.println();
		
		// display board
		for (int i = 0; i < numRows; i++){
			System.out.print ("|");
			for (int j = 0; j < numCols; j++) {
				System.out.print(battlefield[i][j]);	
			}
			System.out.println ("|");
		}
		// display bottom border
		for (int i = 0; i < numCols+2; i++)
			System.out.print("-");
		System.out.println();
		System.out.println ("Current army count - Elves: " + numElves + " Orcs: " + numOrcs);
	} // end of display
	
	public void moveActor (int direction, int row, int col){
		int newRow = 0;
		int newCol = 0;
		if (battlefield[row][col].getActor().toString() == " ")
			System.out.println ("No actor to move at row " + row + " col " + col);
		
		else if (direction == 0 && row == 0) 			// move up not allowed
				 System.out.println ("Actor at row " + row + " col " + col + " cannot move up");
		else if (direction == 1 && row == numRows-1)	 // move down not allowed	
				 System.out.println ("Actor at row " + row + " col " + col + " cannot move down");
		else if (direction == 2 && col == 0) 			// move left not allowed
			 	 System.out.println ("Actor at row " + row + " col " + col + " cannot move left");
		else if (direction == 3 && col == numCols-1)	 // move right not allowed	
				System.out.println ("Actor at row " + row + " col " + col + " cannot move right");
		else  {
				if (direction == 0){  		// move up
					newRow = row-1;
					newCol = col;
				} else if (direction == 1) {  // move down
					newRow = row + 1;
					newCol = col;
				} else if (direction == 2) {  // move left	
					newRow = row;
					newCol = col-1;
				} else { 					  // move right
					newRow = row;
					newCol = col+1;
				}
				
				/*******************Additions to Mountain checking********************/
				
				if (battlefield[newRow][newCol].getTerrain() == 'm' && battlefield[row][col].getActor().getStrength() < 20) // cannot move onto a mountain 
					System.out.println ("Cannot move onto a mountain from row " + row + " and col " + col);
				else if (battlefield[newRow][newCol].getTerrain() == 'm' && battlefield[row][col].getActor().getStrength() >= 20){
					System.out.println ("Move onto Mountain with strength greater than 20");
					battlefield[newRow][newCol].setActor (battlefield[row][col].getActor());	
					battlefield[row][col].setActor (new Actor(0));
				}	
				
				/********************************************************************/
				
				else if (battlefield[newRow][newCol].getActor().getClass() == battlefield[row][col].getActor().getClass() )
					System.out.println ("Cannot move onto a space occupied by your own team player");
				else if (battlefield[newRow][newCol].getActor().toString() == " " ) {
					System.out.println ("Move onto normal terrain to position row " + newRow + " and col" + newCol);
					battlefield[newRow][newCol].setActor (battlefield[row][col].getActor());	
					battlefield[row][col].setActor (new Actor(0));
				}else //  fight
					if (battlefield[newRow][newCol].getActor().getStrength() == battlefield[row][col].getActor().getStrength() )
						System.out.println ("Battle resulted in draw at row "+ row + "and col" + col );
					else if (battlefield[newRow][newCol].getActor().getStrength() > battlefield[row][col].getActor().getStrength() ){
						System.out.println ("Lost the battle.... die at row " + row + " col " + col);
						if (battlefield[row][col].getActor().toString() == "e" || battlefield[row][col].getActor().toString() == "h") numElves --;
						else numOrcs--;
						battlefield[row][col].setActor(new Actor(0));
					}
					else {  System.out.println ("Won the battle...move to row " + row + " col " + col );
						if (battlefield[row][col].getActor().toString() == "e" || battlefield[row][col].getActor().toString() == "h") numOrcs --;
						else numElves--;
						battlefield[newRow][newCol].setActor (battlefield[row][col].getActor());	
						battlefield[row][col].setActor (new Actor(0));
					} 
			} // end else
		} // end moveActor method
		
		
	
}// end class Battlefield
