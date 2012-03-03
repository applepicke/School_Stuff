import java.lang.*;
import java.util.Scanner;

/** This is a dice game, enjoy!
 * @version 1.0
 * @author Willy (William Collins)
 *
 */
public class DiceGame {
	public static void main (String args[]) {
		
		Scanner input = new Scanner(System.in);
		Die die1 = new Die();
		Die die2 = new Die();
		
		
		int potAmount = 100;
		int betAmount = 10;
		
		System.out.print("\n*****************************************");
		System.out.print("\n   The rule of this game are simple!   ");
		System.out.print("\nYou make a bet, and two dice are rolled");
		System.out.print("\n           Doubles = 2x Bet            ");
		System.out.print("\n       Total of 7 or 11 = Bet         ");
		System.out.print("\n   Total of under 6, or over 9 = Even  ");
		System.out.print("\n        Anything else = Lose!         ");
		System.out.print("\n*****************************************\n");
		
		while (potAmount > 0 && betAmount != 0) {
					
		
			die1.rollDie();
			die2.rollDie();
			
			
			
			
			do {
			System.out.print("\nCurrent pot is $" + potAmount);
			System.out.print("\nEnter your bet amount(0 to quit): ");
			betAmount = input.nextInt();
			}
			while (betAmount < 0 || betAmount > potAmount);
			
			if (betAmount != 0) { 
				
			
				die1.display();
				die1.displayGraphic();
				die2.display();
				die2.displayGraphic();
			
				if (die1.returnValue() == die2.returnValue()) {
					System.out.print("\nYou win double!!\n");
					potAmount += betAmount * 2;
				}
				else if (die1.returnValue() + die2.returnValue() == 7 || die1.returnValue() + die2.returnValue() == 11) {
					System.out.print("\nYou win!!\n");
					potAmount += betAmount;
				}
				else if (die1.returnValue() + die2.returnValue() <= 5 || die1.returnValue() + die2.returnValue() > 10) {
					System.out.print("\nYou stay even!!\n");
				}
				else {
					System.out.print("\nYou lose!!\n");
					potAmount -= betAmount; 
				}	
			
			}
			
		}
		
		System.out.println("\nToodles!");
	}

}
