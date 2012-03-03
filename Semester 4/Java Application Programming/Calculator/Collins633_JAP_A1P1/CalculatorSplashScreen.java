/**
 * File name: CalculatorSplashScreen.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 1
 * Date: June 1, 2011
 * Professor: Svillen (the Villain) Ranev
 * Purpose: The standard splash screen for the calculator program
 * 
 * @author William Collins
 * @version 1
 * @see Calculator
 * @since 1.6
 * 
 */
package Calculator;

import java.awt.*;
import javax.swing.*;


public class CalculatorSplashScreen extends JWindow {

	/**
	 * The duration the splash screen will stay on the screen
	 */
	int duration;
	
	/** 
	 * @param duration: The duration the splash screen will be displayed
	 */
	public CalculatorSplashScreen(int duration){
		this.duration = duration;
	}
	
	//Creates and shows the super awesome splash window
	public void showSplashWindow(){
		
		//Create our content pane
		JPanel content = new JPanel(new BorderLayout()); //The content pane that will contain the splash screen
		content.setBackground(Color.BLACK);
		
		//Center the window on the screen
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		int width = 500;
		int height = 250;
		int x = (screenSize.width-width) / 2;
		int y = (screenSize.height - height) / 2;
		setBounds(x , y, width, height);
		
		//Set the image and text
		JLabel image = new JLabel(new ImageIcon("calc.jpg"));
		JLabel author = new JLabel("William Collins (040652633) #V");
		author.setHorizontalAlignment(JLabel.CENTER);
		author.setFont(new Font(Font.MONOSPACED, Font.BOLD, 14));
		author.setForeground(new Color(255, 255, 255));
		
		//Make a nice little border and add the items to the panel
		content.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
		content.add(image, BorderLayout.CENTER);
		content.add(author, BorderLayout.SOUTH);
		
		//Show the splash screen
		add(content);
		setVisible(true);
		
		//Wait a certain amount of time, then close
		try{
			Thread.sleep(duration);
		} 
		catch(Exception e){
			e.printStackTrace();
		}
		
		setVisible(false);
		dispose();
	}
	
}
