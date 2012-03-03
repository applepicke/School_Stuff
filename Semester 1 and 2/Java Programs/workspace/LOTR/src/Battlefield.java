import java.lang.*;
import java.util.Scanner;
import java.util.Random;

public class Battlefield {
	
	Scanner input = new Scanner(System.in);
	Random random = new Random();
	
	
	private Actor orcActor[];
	private Actor elfActor[];
	private Square board[][];
	private int boardRows;
	private int boardCols;
	
	private int orcs;
	private int elves;
	private int mountains;
	
	private int maxOrcs;
	private int maxElves;
	
	private char orc = '@';
	private char elf = '$';
	private char mountain = '^';
	private char space = ' ';
	
	
	// Initialize Battlefield rows and columns as a space and set to 20
	public Battlefield () {
		board = new Square[10][20];	
		boardRows = 10;
		boardCols = 20;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				board[i][j] = new Square(' ');
			}
		}

	}
	//Set orcs and elves
	public void setActors(int o, int e){
		orcs = o;
		elves = e;
	}
	
	//Initialize rows and columns as input from user
	public Battlefield (int rows, int cols) {
		board = new Square [rows][cols];
		boardRows = rows;
		boardCols = cols;
		for (int i = 0; i < boardRows; i++) {
			for (int j = 0; j < boardCols; j++) {
				board[i][j] = new Square(' ');
			}
		}
	}
	
	//Specify Rows
	public int getRows () {
		int rows;
		do {
		System.out.print("\nPlease enter the number of rows for your battlefield (5-10); ");
		rows = input.nextInt();
		}
		while (rows < 5 || rows > 10); 
		return rows;
	}
	
	//Specify Columns
	public int getCols() {
		int cols;
		do {
		System.out.print("\nPlease enter the number of columns for your battlefield (10-20); ");
		cols = input.nextInt();
		}
		while (cols < 10 || cols > 20); 
		return cols;
	}	
	
	//Specify Number of Orcs
	public int getOrc() {
		do {
		System.out.print("\nPlease enter the number of orcs in the battle(5-10): ");
		orcs = input.nextInt();
		maxOrcs = orcs;
		maxElves = elves;
		}
		while (orcs < 5 || orcs > 10);
		for (int i=0; i<boardRows; i++){
			for (int j=0; j<boardCols; j++){
				board[i][j].setElfNum(orcs);
			}
		}
		return orcs;
		
	}
	
	//Specify Number of Elves
	public int getElf() {
		do {
		System.out.print("\nPlease enter the number of elves in the battle(5-10): ");
		elves = input.nextInt();
		}
		while (elves < 5 || elves > 10);
		for (int i=0; i<boardRows; i++){
			for (int j=0; j<boardCols; j++){
				board[i][j].setElfNum(elves);
			}
		}
		return elves;
	}
	
	//Specify number of mountains
	public int getMountain() {
		do {
			System.out.print("\nPlease enter the number of mountains you wish to place on the field(5-10): ");
			mountains = input.nextInt();
		}
		while (mountains < 5 || mountains > 10);
		return mountains;
		
	}
	
	//Initialize Orc Actors
	public void initOrcActor(int row, int col, int orcNum) {
		
		orcActor[orcNum] = new Actor(orc);
		orcActor[orcNum].editPosition(row, col);
		board[row][col].setOrcNum(orcNum);
	}
	
	//Initialize orc actor class
	public void initOrc(int o) {
		orcActor = new Actor [o+1];
		orcActor[o] = new Actor(elf);
	}
	
	//Initialize elf actor class
	public void initElf(int o) {
		elfActor = new Actor [o+1];
		elfActor[o] = new Actor(elf);
	}
	
	//Initialize  Elf Actors
	public void initElfActor(int row, int col, int elfNum) {
		
		elfActor[elfNum] = new Actor(elf);
		elfActor[elfNum].editPosition(row, col);
		board[row][col].setElfNum(elfNum);
	}
	
	//Print a blank line
	public void printLine() {
		System.out.print("\n");
	}
		
	//Place actor on the board
	public void placeActor(int row, int col, char actor) {
		board[row][col].setValue(actor);
	}
	
	//Who is to the left
	public char whoIsLeft(int row, int col) {
		if (board[row][col-1].getValue() == orc)
			return orc;
		else if (board[row][col-1].getValue() == elf)
			return elf;
		else if (board[row][col-1].getValue() == mountain)
			return mountain;
		else return ' ';
	}
	
	//Who is to the right
	public char whoIsRight(int row, int col) {
		if (board[row][col+1].getValue() == orc)
			return orc;
		else if (board[row][col+1].getValue() == elf)
			return elf;
		else if (board[row][col+1].getValue() == mountain)
			return mountain;
		else return ' ';
	}
	
	//Who is Up
	public char whoIsUp(int row, int col) {
		if (board[row-1][col].getValue() == orc)
			return orc;
		else if (board[row-1][col].getValue() == elf)
			return elf;
		else if (board[row-1][col].getValue() == mountain)
			return mountain;
		else return ' ';
	}
	
	//Who is down
	public char whoIsDown(int row, int col) {
		if (board[row+1][col].getValue() == orc)
			return orc;
		else if (board[row+1][col].getValue() == elf)
			return elf;
		else if (board[row+1][col].getValue() == mountain)
			return mountain;
		else return ' ';
	}
	     
	
	//Set Orc to new space
	public void setOrcSpace(int orcNum, int row, int col) {
		orcActor[orcNum].editPosition(row, col);
	}
	
	//Set Elf to new space
	public void setElfSpace(int elfNum, int row, int col) {
		elfActor[elfNum].editPosition(row, col);
	}
	
	//Move actor to the left
	public void moveLeft(int row, int col, char actor) { 
			if (board[row][col].getValue() == orc) {
				board[row][col].setSpace();
				board[row][col-1].setOrc();
				board[row][col-1].setOrcNum(board[row][col].getOrcNum());
				board[row][col].setOrcNum(orcs);
	
				
				
			}
			else if (board[row][col].getValue() == elf) {
				board[row][col].setSpace();
				board[row][col-1].setElf();
				board[row][col-1].setElfNum(board[row][col].getElfNum());
				board[row][col].setElfNum(elves);
			}
		}
	
	
	//Move actor to the right
	public void moveRight(int row, int col, int actorNum) {
		if (board[row][col].getValue() == orc) {
			board[row][col].setSpace();
			board[row][col+1].setOrc();
			board[row][col+1].setOrcNum(board[row][col].getOrcNum());
			board[row][col].setOrcNum(maxOrcs);
			
		}
		else if (board[row][col].getValue() == elf) {
			board[row][col].setSpace();
			board[row][col+1].setElf();
			board[row][col+1].setElfNum(board[row][col].getElfNum());
			board[row][col].setElfNum(maxElves);
		}
	}
	
	//Move actor up
	public void moveUp(int row, int col, int actorNum) {
		if (board[row][col].getValue() == orc) {
			board[row][col].setSpace();
			board[row+1][col].setOrc();
			board[row+1][col].setOrcNum(board[row][col].getOrcNum());
			board[row][col].setOrcNum(maxOrcs);
		}
		else if (board[row][col].getValue() == elf) {
			board[row][col].setSpace();
			board[row+1][col].setElf();
			board[row+1][col].setElfNum(board[row][col].getElfNum());
			board[row][col].setElfNum(maxElves);
		}
	}
	
	//Move actor down
	public void moveDown(int row, int col, int actorNum) {
		if (board[row][col].getValue() == orc) {
			board[row][col].setSpace();
			board[row-1][col].setOrc();
			board[row-1][col].setOrcNum(board[row][col].getOrcNum());
			board[row][col].setOrcNum(maxOrcs);
		}
		else if (board[row][col].getValue() == elf) {
			board[row][col].setSpace();
			board[row-1][col].setElf();
			board[row-1][col].setElfNum(board[row][col].getElfNum());
			board[row][col].setElfNum(maxElves);
		}
	}
	
	//Is a mountain left
	public boolean isMountainLeft(int row, int col) {
		if (col != 0) {
		if (board[row][col-1].getValue() == mountain)
			return true;
		else return false;
		}
		else return true;
	}
	
	//Is a mountain right
	public boolean isMountainRight(int row, int col) {
		if (col != boardCols - 1) {
		if (board[row][col+1].getValue() == mountain)
			return true;
		else return false;
		}
		else return true;
	}
	
	//Is a mountain up
	public boolean isMountainUp(int row, int col) {
		if (row != boardRows-1){
			if (board[row+1][col].getValue() == mountain)
				return true;
			else return false;
		}
		else return true;
	}
	
	//Is a mountain down
	public boolean isMountainDown(int row, int col) {
		if (row != 0){
		if (board[row-1][col].getValue() == mountain)
			return true;
		else return false;
		}
		else return true;
	}
	
	
	//Display the battlefield
	public void display() {
		System.out.print(" ");
		for (int i=0; i<boardCols; i++) {
			System.out.print("_");
		}	
		System.out.print("\n");
		for (int rows = boardRows-1; rows >= 0; rows--) {
			System.out.print("|");
			for (int cols = 0; cols < boardCols; cols++) {
				System.out.print(board[rows][cols].getValue());
			}
			System.out.print("|");
			System.out.print("\n");
		}
		System.out.print(" ");
		for (int j=0; j<boardCols; j++) {
			System.out.print("_");
		}
	}

	//checks to see if a space is occupied
	public boolean isSpaceFree(int row, int col) {
		if (board[row][col].getValue() == ' ')
			return true;
		else return false;
	}
	
	//Assign a random number to row
	public int setRandomRow() {
		int randomRow = random.nextInt(boardRows);
		return randomRow;	
	}
	
	//Assign a random number to col
	public int setRandomCol() {
		int randomCol = random.nextInt(boardCols);
		return randomCol;
	}
	
	
	//Move all characters randomly
	public void moveAll() {
		//For every square, determine what is in it
		for (int row=0; row < boardRows; row++) {
			for (int col=0; col < boardCols; col++) {
				//Check to see if its an orc or an elf
				if (board[row][col].getOrcNum()!=5 || board[row][col].getElfNum() !=5) {
				//***********************************************************
				//               Beginning of Orc Move
				//***********************************************************
				if (board[row][col].getValue() == orc){
					int randomMove = orcActor[board[row][col].getOrcNum()].setRandomMove();
					int randomStrength = orcActor[board[row][col].getOrcNum()].setRandomStrength();	
					
					//*****************************Move Left
					if (randomMove == 0) {
						//Check if a mountain is in the way
						if (isMountainLeft(row, col) != true) {
							//Check if there is a space
							if (board[row][col-1].getValue() == ' ') {
								moveLeft(row, col, orc);
								setOrcSpace(board[row][col].getOrcNum(), row, col-1);
							}
							//There is an elf next to the orc
							else if (board[row][col-1].getValue() != orc){
								//Check strength of each actor
								//If strength is greater 
								int random1 = orcActor[board[row][col].getOrcNum()].setRandomStrength();
								int random2 = elfActor[board[row][col-1].getElfNum()].setRandomStrength();
								if (random1 > random2) {
									moveLeft(row, col, orc);
									setOrcSpace(board[row][col].getOrcNum(), row, col-1);
									elves -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setOrcNum(maxOrcs);
									orcs -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//end of move left
					
					//***************************************Move right
					else if (randomMove == 1) {
						//Check if a mountain is in the way
						if (isMountainRight(row, col) != true) {
							//Check if there is a space
							if (board[row][col+1].getValue() == ' ') {
								moveRight(row, col, orc);
								setOrcSpace(board[row][col].getOrcNum(), row, col+1);
							}
							//There is an elf next to the orc
							else if (board[row][col+1].getValue() != orc){
								//Check strength of each actor
								//If strength is greater 
								int random1 = orcActor[board[row][col].getOrcNum()].setRandomStrength();
								int random2 = elfActor[board[row][col+1].getElfNum()].setRandomStrength();
								if (random1 > random2) {
									moveRight(row, col, orc);
									setOrcSpace(board[row][col].getOrcNum(), row, col+1);
									elves -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setOrcNum(maxOrcs);
									orcs -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Right
							
					//***************************************Move Up
					else if (randomMove == 2) {
						//Check if a mountain is in the way
						if (isMountainUp(row, col) != true) {
							//Check if there is a space
							if (board[row+1][col].getValue() == ' ') {
								moveUp(row, col, orc);
								setOrcSpace(board[row][col].getOrcNum(), row+1, col);
							}
							//There is an elf next to the orc
							else if (board[row+1][col].getValue() != orc){
								//Check strength of each actor
								//If strength is greater 
								int random1 = orcActor[board[row][col].getOrcNum()].setRandomStrength();
								int random2 = elfActor[board[row+1][col].getElfNum()].setRandomStrength();
								if (random1 > random2) {
									moveUp(row, col, orc);
									setOrcSpace(board[row][col].getOrcNum(), row+1, col);
									elves -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setOrcNum(maxOrcs);
									orcs -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Up
					
					//***************************************Move Down
					else if (randomMove == 3) {
						//Check if a mountain is in the way
						if (isMountainDown(row, col) != true) {
							//Check if there is a space
							if (board[row-1][col].getValue() == ' ') {
								moveDown(row, col, orc);
								setOrcSpace(board[row][col].getOrcNum(), row-1, col);
							}
							//There is an elf next to the orc
							else if (board[row-1][col].getValue() != orc){
								//Check strength of each actor
								//If strength is greater 
								int random1 = orcActor[board[row][col].getOrcNum()].setRandomStrength();
								int random2 = elfActor[board[row-1][col].getElfNum()].setRandomStrength();
								if (random1 > random2) {
									moveDown(row, col, orc);
									setOrcSpace(board[row][col].getOrcNum(), row-1, col);
									elves -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setOrcNum(maxOrcs);
									orcs -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Down
				}//End of Orc move
				
				//***********************************************************
				//               Beginning of Elf Move
				//***********************************************************
				
				if (board[row][col].getValue() == elf){
					int randomMove = elfActor[board[row][col].getElfNum()].setRandomMove();
					int randomStrength = elfActor[board[row][col].getElfNum()].setRandomStrength();	
					
					//*****************************Move Left
					if (randomMove == 0) {
						//Check if a mountain is in the way
						if (isMountainLeft(row, col) != true) {
							//Check if there is a space
							if (board[row][col-1].getValue() == ' ') {
								moveLeft(row, col, elf);
								setElfSpace(board[row][col].getElfNum(), row, col-1);
							}
							//There is an orc next to the elf
							else if (board[row][col-1].getValue() != elf){
								//Check strength of each actor
								//If strength is greater 
								int random1 = elfActor[board[row][col].getElfNum()].setRandomStrength();
								int random2 = orcActor[board[row][col-1].getOrcNum()].setRandomStrength();
								if (random1 > random2) {
									moveLeft(row, col, elf);
									setElfSpace(board[row][col].getElfNum(), row, col-1);
									orcs -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setElfNum(maxElves);
									elves -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//end of move left
					
					//***************************************Move right
					else if (randomMove == 1) {
						//Check if a mountain is in the way
						if (isMountainRight(row, col) != true) {
							//Check if there is a space
							if (board[row][col+1].getValue() == ' ') {
								moveRight(row, col, elf);
								setElfSpace(board[row][col].getElfNum(), row, col+1);
							}
							//There is an orc next to the elf
							else if (board[row][col+1].getValue() != elf){
								//Check strength of each actor
								//If strength is greater 
								int random1 = elfActor[board[row][col].getElfNum()].setRandomStrength();
								int random2 = orcActor[board[row][col+1].getOrcNum()].setRandomStrength();
								if (random1 > random2) {
									moveRight(row, col, elf);
									setElfSpace(board[row][col].getElfNum(), row, col+1);
									orcs -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setElfNum(maxElves);
									elves -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Right
							
					//***************************************Move Up
					else if (randomMove == 2) {
						//Check if a mountain is in the way
						if (isMountainUp(row, col) != true) {
							//Check if there is a space
							if (board[row+1][col].getValue() == ' ') {
								moveUp(row, col, elf);
								setElfSpace(board[row][col].getElfNum(), row+1, col);
							}
							//There is an orc next to the elf
							else if (board[row+1][col].getValue() != elf){
								//Check strength of each actor
								//If strength is greater 
								int random1 = elfActor[board[row][col].getElfNum()].setRandomStrength();
								int random2 = orcActor[board[row+1][col].getOrcNum()].setRandomStrength();
								if (random1 > random2) {
									moveUp(row, col, elf);
									setElfSpace(board[row][col].getElfNum(), row+1, col);
									orcs -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setElfNum(maxElves);
									elves -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Up
					
					//***************************************Move Down
					else if (randomMove == 3) {
						//Check if a mountain is in the way
						if (isMountainDown(row, col) != true) {
							//Check if there is a space
							if (board[row-1][col].getValue() == ' ') {
								moveDown(row, col, elf);
								setElfSpace(board[row][col].getElfNum(), row-1, col);
							}
							//There is an orc next to the elf
							else if (board[row-1][col].getValue() != elf){
								//Check strength of each actor
								//If strength is greater 
								int random1 = elfActor[board[row][col].getElfNum()].setRandomStrength();
								int random2 = orcActor[board[row-1][col].getOrcNum()].setRandomStrength();
								if (random1 > random2) {
									moveDown(row, col, elf);
									setElfSpace(board[row][col].getElfNum(), row-1, col);
									orcs -= 1;
								}
								//If strength is less
								if (random1 < random2) {
									board[row][col].setValue(' ');
									board[row][col].setElfNum(maxElves);
									elves -= 1;
								}
								//If strength is equal do nothing
								
							}//end of else						
						}//end of mountain check	
					}//End of move Down
				}//End of Elf move
				}
			}// End of For statement
		}//End of for statement
	}
	
	//Show number of orcs and elves
	public void showActors(){
		System.out.print("\nNumber of Orcs: " + orcs + "\nNumber of Elves: " + elves);
	}
	
	//Show the legend
	public void showLegend(){
		System.out.print("\n\n********************");
		System.out.print("\n      Orcs: @       ");
		System.out.print("\n      Elves: $      ");
		System.out.print("\n      Mountains: ^  ");
		System.out.print("\n********************");
	}
	
	//Who won? 1 is elves, 2 is orcs, 0 is draw
	public int whoWon(){
		if (elves > orcs) {
			return 1;
		}
		else if (elves < orcs) {
			return 2;
		}
		else return 0;
	}
	
}
