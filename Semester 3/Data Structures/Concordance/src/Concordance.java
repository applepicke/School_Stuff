import java.io.FileNotFoundException;
import java.util.ArrayList;

import javax.swing.*;


public class Concordance {
	public static void main(String args[]){
		int flag = 0;
		Loader textLoader = null;
		
		//loop through until a correct file is entered, or cancel button is hit
		while(flag == 0){
			try{
				String sFileName = JOptionPane.showInputDialog("Book: ");
				textLoader = new Loader(sFileName);
				textLoader.loadTextFile(new ArrayList<String>());
				flag = 1;
			}catch(FileNotFoundException e){ //if the file isnt found, show a message and repeat
				JOptionPane.showMessageDialog(null, "Invalid Filename!");
			}catch(Exception e){
				return;
			}
		}
		textLoader.fillIndex();
		textLoader.displayCollection();
		
	}
}
