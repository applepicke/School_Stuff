import java.lang.*;
import java.lang.String;
import java.util.Scanner;

public class LOTR {
	public static void main(String args[]) {
		
		
		String anyKey = new String();
		Scanner input = new Scanner(System.in);
		
		int columns = 0;
		int rows = 0;
		int orcs = 0;
		int elves = 0;
		int mountains = 0;
		
		int tempRow;
		int tempCol;
		
		int control = 0;
		
		char orc = '@';
		char elf = '$';
		char mountain = '^';

		
		//initialize a blank board 20 x 20, just to call the menu statements

Battlefield tempbattle = new Battlefield();
		
		//Set the board size
		rows = tempbattle.getRows();
		columns = tempbattle.getCols();
		tempbattle.printLine();
		
		//Initialize the board with specified settings
		Battlefield battle = new Battlefield(rows, columns);
		
		//Show the battlefield
		System.out.print("Here is your Battlefield\n");
		battle.display();
		battle.printLine();
		battle.printLine();
		System.out.print("Press enter to continue...");
		anyKey = input.nextLine();
		battle.printLine();
		                                       
			
		//Set and place Orcs
		orcs = tempbattle.getOrc();
		battle.initOrc(orcs);
		for (int i=0; i<orcs; i++){
			tempRow = battle.setRandomRow();
			tempCol = battle.setRandomCol();
			while (battle.isSpaceFree(tempRow,tempCol) != true) {
				tempRow = battle.setRandomRow();
				tempCol = battle.setRandomCol();
			}			
				battle.initOrcActor(tempRow, tempCol, i);
				battle.placeActor(tempRow, tempCol, orc);
		}
		
		
		//Set and place Elves
		elves = tempbattle.getElf();
		battle.initElf(elves);
		for (int i=0; i<elves; i++){
			tempRow = battle.setRandomRow();
			tempCol = battle.setRandomCol();
			while (battle.isSpaceFree(tempRow,tempCol) != true) {
				tempRow = battle.setRandomRow();
				tempCol = battle.setRandomCol();
			}		
				battle.initElfActor(tempRow, tempCol, i);
				battle.placeActor(tempRow, tempCol, elf);
		}
		
		
		//Set orcs and elves variables
		battle.setActors(orcs, elves);
		
		//Set and place mountains
		mountains = tempbattle.getMountain();
		tempbattle.printLine();
		for (int i=0; i<mountains; i++){
			tempRow = battle.setRandomRow();
			tempCol = battle.setRandomCol();
			while (battle.isSpaceFree(tempRow,tempCol) != true) {
				tempRow = battle.setRandomRow();
				tempCol = battle.setRandomCol();
			}			
				battle.placeActor(tempRow, tempCol, mountain);
		}

		
		
		//Begin battle
		do {
			battle.display();
			battle.showActors();
			
			do {
				System.out.print("\n\n0-Surrender");
				System.out.print("\n1-Continue Battle");
				System.out.print("\n2-Show Legend");
				System.out.print("\nWhat would you like to do: ");
			
				control = input.nextInt();
				if (control == 2) {
					battle.showLegend();
				}
			}
			while (control == 2);
			battle.moveAll();
		}
		
		while (control == 1);
		
		if (battle.whoWon() ==1)
			System.out.print("\nElves are Victorious!!\n");
		else if (battle.whoWon() ==2)
			System.out.print("\nOrcs are Victorious!!\n");
		else
			System.out.print("\nDraw!!!\n");
	}
	
	
}
