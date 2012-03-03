/**
 * File name: Client.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 2
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: To interact with our server
 * 
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */

import java.awt.EventQueue;
import javax.swing.JFrame;

/**
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
public class Client {

	public static final String TITLE = "#V's Client";
	
	public static void main(String args[]) {
		
		EventQueue.invokeLater(new Runnable() {

			@Override
			public void run() {
				
				//Let's initialize our frame and main panel
				JFrame clientFrame = new JFrame(TITLE); 
				ClientView clientView = new ClientView();
				
				//Now Make the frame sea-worthy
				clientFrame.setContentPane(clientView);
				clientFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				clientFrame.setSize(635, 400);
				clientFrame.setResizable(false);
				clientFrame.setVisible(true);
				
			}		
		});
	}
}
