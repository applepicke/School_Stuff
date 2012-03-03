import java.lang.*;
/* created by *CurtisOfTheDark*
 * variables - mountainRow
 * 			 - mountainCol
 * 			 - mountainSymbol
 * methods  - initialize position constructor
 * 			- return position
 */

public class Mountain {
	
	private int mountainRow;
	private int mountainCol;
	private int mountainSymbol;
	
	// Initialize position of mountain
	public Mountain(int row, int col) {
		mountainRow = row;
		mountainCol = col;
		mountainSymbol = '^';
	}
	
	// Set the position of the mountain
	public void setMountain(int row, int col) {
		mountainRow = row;
		mountainCol = col;
	}
	
	// Returns row of mountain
	public int getRow() { return mountainRow; }
	
	// Returns col of mountain
	public int getCol() { return mountainCol; }
	
	
	

}
