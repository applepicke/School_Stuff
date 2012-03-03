import javax.swing.JOptionPane;
import java.lang.String;

public class Main {
	public static void main(String args[]) {
		
		String food = JOptionPane.showInputDialog("What are you going to eat?");
		String message;
		if (food.charAt(food.length()- 1) == 's') {
			 message = String.format("%s are gross", food);
		}
		else
			message = String.format("%s is gross", food);
		JOptionPane.showMessageDialog(null, message);
	}

}
