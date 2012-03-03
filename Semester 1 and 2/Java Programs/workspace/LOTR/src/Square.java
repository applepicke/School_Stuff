import java.lang.*;


public class Square {
	
	private char value;
	private int orcNum;
	private int elfNum;
	private boolean space;
	
	
	
	//Initializes value of the square
	public Square(char val) { 
		value = val; 
		space = true;
		
	}
	

	
	//Sets value
	public void setValue(char val) { value = val; }
	
	// Returns value
	public char getValue() { return value; }
	
	//Checks if this square is a mountain
	public boolean isMountain() {
		if (value == '^')
			return true;
		else return false;
	}
	
	
	//Checks if this square is an orc
	public boolean isOrc() {
		if (value == '@')
			return true;
		else return false;
	}
	
	//Checks if this square is an elf
	public boolean isElf() {
		if (value == '$')
			return true;
		else return false;
	}
	
	//set this square to an orc
	public void setOrc() {
		value = '@';
	}
	
	//set this square to an elf
	public void setElf() {
		value = '$';
	}
	
	//sets this square to a space
	public void setSpace() {
		value = ' ';
		space = true;
	}
	
	//sets space to false
	public void unSetSpace() {
		space = false;
	}
	
	//sets the elfNum
	public void setElfNum(int elf) {
		elfNum = elf;
	}
	
	//get elfnum
	public int getElfNum() {
		return elfNum;
	}
	
	//get orcNum
	public int getOrcNum() {
		return orcNum;
	}
	
	//sets the orcNum
	public void setOrcNum(int orc) {
		orcNum = orc;
	}
	
}
