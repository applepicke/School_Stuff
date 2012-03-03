/**
 * File name: Server.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 2
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: To get random information from the client and send it back for no reason
 * 
*/
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
public class Server {
	
	public static final int DEFAULT_PORT = 8088;	
	
	public static void main(String args[]){
			
		ServerSocket serverSocket;
		int port = DEFAULT_PORT;
		
		//Try parsing a port from the given argument
		if (args.length > 0){			
			try {
				port = Integer.parseInt(args[0]);
				
			} catch(NumberFormatException e){
				port = 8088;
			}	
		}
		
		if (port == 8088){
			System.out.println("Using default port: " + String.valueOf(DEFAULT_PORT));
		}
		else {
			System.out.println("Using port: " + port);
		}
		
		//Setup the Execcutor service
		ExecutorService executor = Executors.newCachedThreadPool();
		
		try {
			serverSocket = new ServerSocket(port);
			//Continually accept connections
			while(true){
				Socket clientSocket = serverSocket.accept();
				
				//Now serve the client in a new thread
				ServerSocketRunnable serverRunnable = new ServerSocketRunnable(clientSocket);
				executor.execute(serverRunnable);
				
				System.out.println("Connecting to a client Socket" + clientSocket.toString());
			}

		} catch (IOException e){
			System.out.println("Unable to create server socket. Exiting.");
		}
	}
}
