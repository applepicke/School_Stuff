import java.lang.*;
import java.util.Scanner;
import java.lang.String;

public class HA3 {
	public static void main(String args[]){
		
		Scanner input = new Scanner(System.in);
		String string = new String();
		int tally = 0;
		
		System.out.print("\nPlease enter a word or sentence: ");
		string = input.nextLine();
		
		System.out.print("Your word or sentence was " + string.length() + " characters long.");
		string.toLowerCase();
		
		for (char i = 'a'; i <= 'z'; i++){
			for (int j = 0; j < string.length();j++) {
				if (string.charAt(j) == i)
					tally += 1;
			}
			if (tally != 0) 
				System.out.print("\n" + i + "= " + tally);
			tally = 0;
		}	
		
	}

}
