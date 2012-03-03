/**
 * File name: Calculator.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 1
 * Date: June 1, 2011
 * Professor: Svillen (the Villain) Ranev
 * Purpose: Runs the calculator program
 * 
 * @author William Collins
 * @version 1
 * @see Calculator
 * @since 1.6
 * 
 */
package Calculator;

import java.awt.EventQueue;
import javax.swing.JFrame;

public class Calculator {
	
	/**
	 * @param args: the main program arguments.
	 */
	public static void main(String args[]){
			
		//Show the Splash Screen
		CalculatorSplashScreen splash = new CalculatorSplashScreen(5000);
		splash.showSplashWindow();
		
		EventQueue.invokeLater(new Runnable() {

			@Override
			public void run() {
				
				//Show the Calculator
				JFrame calcFrame = new JFrame("Calculator");
				calcFrame.setSize(260, 260);
				calcFrame.setResizable(false);
				calcFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				calcFrame.setContentPane(new CalculatorView());
				calcFrame.setLocation(50, 50);
				calcFrame.setVisible(true);
			
			}	
		});
		
		
	}	
}
