/**
 * File name: ServerSocketRunnable.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 2
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: Handles an individual client connection
 * 
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
public class ServerSocketRunnable implements Runnable{
	
	private Socket socket;
	
	//The array of commands. To expand the list, simply add the command and
	//assign it an index 
	public static final String COMMAND[] = { "END", "ECHO", "TIME", "DATE", "?" };
	
	public static final int END = 0;
	public static final int ECHO = 1;
	public static final int TIME = 2;
	public static final int DATE = 3;
	public static final int HELP = 4;
	
	public static final String PROMPT = ">";
	public static final String NEWPROMPT = ": ";
	public static final String HELP_RESPONSE = "AVAILABLE SERVICES";
	public static final String ERROR = "ERROR";
	public static final String CONNECTION_CLOSED = "Connection closed";
	
	
	public ServerSocketRunnable(Socket socket){	
		this.socket = socket;
	}
	
	@Override
	public void run(){
		
		ObjectInputStream in;
		ObjectOutputStream out;
		String command;			//Stores the command sent by the client
		
		//Try to open the Input and Output stream of the socket for use
		try {
			in = new ObjectInputStream(socket.getInputStream());
			out = new ObjectOutputStream(socket.getOutputStream());	

			//Continue receiving commands until the user decides to quit
			while(true) {

				//Get the command from the client
				command = (String)in.readObject();

				//Client wants to end the session
				if (command.startsWith(COMMAND[END] + PROMPT)){
					break;
				}

				//Client wants to echo
				else if (command.startsWith(COMMAND[ECHO] + PROMPT)){
					out.writeObject(COMMAND[ECHO] + NEWPROMPT + command.substring(COMMAND[ECHO].length() + 1));
				}

				//Client wants to know the time
				else if (command.startsWith(COMMAND[TIME] + PROMPT)){
					out.writeObject(COMMAND[TIME] + NEWPROMPT + new SimpleDateFormat("hh:mm:ss a").format(new Date()));
				}

				//Client wants to know the date
				else if (command.startsWith(COMMAND[DATE] + PROMPT)){
					out.writeObject(COMMAND[DATE] + NEWPROMPT + new SimpleDateFormat("dd MMMM yyyy").format(new Date()));
				}

				//Client wants help
				else if (command.startsWith(COMMAND[HELP] + PROMPT)){
					StringBuilder help = new StringBuilder();
					help.append(HELP_RESPONSE + NEWPROMPT + '\n');

					for (String s: COMMAND){
						help.append(s);
						help.append("\n");
					}

					out.writeObject(help.toString());
				}

				//Command not recognized
				else {
					out.writeObject(ERROR + NEWPROMPT + "Unrecognized Command.");
				}

				//Sleep for 100 milliseconds
				Thread.sleep(100);

			}

			out.writeObject(CONNECTION_CLOSED);
			out.close();
			in.close();
			socket.close();
			
			System.out.println("Server Socket: Closing client connection...");

		} catch (Exception cnfe) {
			//The thread will exit when no connection is detected, and the Executor will re-use it next time
		}
	}
}
