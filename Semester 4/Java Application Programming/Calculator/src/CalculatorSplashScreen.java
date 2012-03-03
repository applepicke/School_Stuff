/**
 * File name: CalculatorSplashScreen.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 1
 * Date: June 20, 2011
 * Professor: Svillen (the Villain) Ranev
 * Purpose: The standard splash screen for the calculator program
 */

import java.awt.*;
import javax.swing.*;

/**
 * Shows a nice little splash screen with a loading bar.
 * @author William Collins (040652633)
 * @version 1.1
 * @see Calculator
 * @since 1.6
 */
public class CalculatorSplashScreen extends JWindow {

	/**
	 * The duration the splash screen will stay on the screen
	 */
	private int duration;
	
	/** 
	 * @param duration: The duration the splash screen will be displayed
	 */
	public CalculatorSplashScreen(int duration){
		this.duration = duration;
	}
	
	/**
	 * Creates and shows the splash window
	 */
	public void showSplashWindow(){
		
		//used for the progress bar
		long referenceTime = System.currentTimeMillis();
		long newTime;
		
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
		JLabel image = new JLabel(new ImageIcon(getClass().getResource("calc.jpg")));
		JLabel author = new JLabel("William Collins (040652633) #V");
		author.setHorizontalAlignment(JLabel.CENTER);
		author.setFont(new Font(Font.MONOSPACED, Font.BOLD, 14));
		author.setForeground(new Color(255, 255, 255));
		
		//Make a progress bar to show how things are coming along
		JProgressBar progress = new JProgressBar(0, duration);
		progress.setString("Loading Calculator. Please wait...");
		progress.setStringPainted(true);
		progress.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		progress.setForeground(Color.RED);
		
		//Make a nice little border and add the items to the panel
		content.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
		content.add(progress, BorderLayout.NORTH);
		content.add(image, BorderLayout.CENTER);
		content.add(author, BorderLayout.SOUTH);
		
		
		//Show the splash screen
		add(content);
		setVisible(true);
		
		//This replaces Thread.sleep and waits a "duration" amount of time accurately
		while ( (newTime = System.currentTimeMillis() - referenceTime) < duration){
			progress.setValue((int)newTime);
		}
		
		setVisible(false);
		dispose();
	}
	
}
