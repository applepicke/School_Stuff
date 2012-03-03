import java.lang.*; 		//all import statements must be first
import java.util.*;			//program uses class Scanner
/**  Displays an int number between 0 and 255 (inclusive) in its binary format
  *   @version 1
  *   @see java.lang.String
  *   @see java.util.Scanner
  */
public class HA7BinaryErr {
	public static void main (String[] argv) {

		Scanner input = new Scanner (System.in);
		
		
		int number = 0;
		int factorOfTwo = 0;

//		get number to convert from user
		do {
			System.out.println("Enter the number to convert (0-255): ");
			number = input.nextInt();
		}  while (number< 0 || number > 255);

		System.out.println("The number " + number + " converted to binary is : ");
//		convert to binary by successively dividing by larger factors of 2		
		for (factorOfTwo = 128; factorOfTwo > 0; factorOfTwo /= 2) {
			if (number / factorOfTwo >= 1){
				System.out.print("1");
				number -= factorOfTwo;
			}
			else System.out.print ("0");
		}

	} // end of main
}// end of class

