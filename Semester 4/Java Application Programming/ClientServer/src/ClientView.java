/**
 * File name: ClientView.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 2
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: The GUI for the client
 * 
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingWorker;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

/**
 * @author William Collins
 * @version 1
 * @see default package
 * @since 1.6
 * 
 */
public class ClientView extends JPanel{
	
	//The port numbers to be displayed in the combo selection box
	private String[] portList = { "", "8088", "9090", "65535" };
	
	/**
	 * hostField: The text field that holds the hostname to connect to
	 */
	private JTextField hostField;
	/**
	 * portSelectionBox: The selection box for the port
	 */
	private JComboBox portSelectionBox;
	/**
	 * commandField: The text field for sending commands to the server
	 */
	private JTextField commandField;
	/**
	 * commandDisplayArea: the area where responses are shown
	 */
	private JTextArea commandDisplayArea;
	/**
	 * connectButton: The button used to connect to the server
	 */
	private JButton connectButton;
	/**
	 * sendButton: the button to send a command
	 */
	private JButton sendButton;
	
	
	/**
	 * serverSocket: the socket of the server
	 */
	private Socket serverSocket;
	/**
	 * The input stream for the server socket
	 */
	private ObjectInputStream in;
	/**
	 * the output stream for the sever socket
	 */
	private ObjectOutputStream out;
	
	public static final String CLIENT_PROMPT = "CLIENT>";
	public static final String SERVER_PROMPT = "SERVER>";
	public static final String ERROR = "ERROR:";
	
	public ClientView(){
		
		//create the controller for our components
		ClientController controller = new ClientController();	
				
		//Make sure the socket exists
		serverSocket = new Socket();
		setLayout(new BorderLayout());
		
		//HOST PANEL
		JPanel hostPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		JLabel hostLabel = new JLabel("Host: ");
		hostField = new JTextField("localhost", 50);
		
		hostLabel.setDisplayedMnemonic('H');
		hostLabel.setPreferredSize(new Dimension(40, 40));
		hostLabel.setLabelFor(hostField);
		hostField.setBackground(Color.WHITE);
		
		hostPanel.add(hostLabel);
		hostPanel.add(hostField);
		
		
		//PORT PANEL
		JPanel portPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		JLabel portLabel = new JLabel("Port: ");	
		portSelectionBox = new JComboBox(portList);
		connectButton = new JButton("Connect");
		
		portLabel.setPreferredSize(new Dimension(40, 40));
		portLabel.setDisplayedMnemonic('P');
		portLabel.setLabelFor(portSelectionBox);
		portSelectionBox.setPreferredSize(new Dimension(100, 20));
		portSelectionBox.setBackground(Color.WHITE);
		portSelectionBox.setEditable(true);
		connectButton.setPreferredSize(new Dimension(100, 20));	
		connectButton.setMnemonic('C');
		
		portPanel.add(portLabel);
		portPanel.add(portSelectionBox);
		portPanel.add(connectButton);
	
		
		//CONNECTION SETUP PANEL
		JPanel connectionSetupPanel = new JPanel(new BorderLayout());
		Border redBorder = new LineBorder(Color.RED, 2, true);
		connectionSetupPanel.setBorder(BorderFactory.createTitledBorder(redBorder, "Connection Setup"));	
		connectionSetupPanel.add(hostPanel);
		connectionSetupPanel.add(portPanel, BorderLayout.SOUTH);	
	
		
		//COMMAND SEND PANEL
		JPanel commandSendPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		commandField = new JTextField("Type a Command Line Here", 48);
		sendButton = new JButton("Send");
		
		sendButton.setMnemonic('S');
		sendButton.setPreferredSize(new Dimension(80, 20));
		sendButton.setEnabled(false);
		
		commandField.setBackground(Color.WHITE);
		commandSendPanel.add(commandField);
		commandSendPanel.add(sendButton);	
		
		
		//COMMAND DISPLAY AREA
		commandDisplayArea = new JTextArea(30, 49);
		
		commandDisplayArea.setEditable(false);
		commandDisplayArea.setBackground(Color.WHITE);
		
		
		//COMMAND INTERFACE PANEL
		JPanel commandInterfacePanel = new JPanel(new BorderLayout());
		commandInterfacePanel.add(commandSendPanel, BorderLayout.NORTH);
		commandInterfacePanel.add(new JScrollPane(commandDisplayArea));
		
		
		//ADD THE MAIN PANELS
		add(connectionSetupPanel, BorderLayout.NORTH);
		add(commandInterfacePanel);
		
		//Add our controller
		connectButton.addActionListener(controller);
		sendButton.addActionListener(controller);
		
		//do final configuration on this panel
		setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));
		setVisible(true);
		
	}
	
	/**
	 * @author William Collins
	 * @version 1
	 * @see default package
	 * @since 1.6
	 * 
	 */
	private class ClientController implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			commandDisplayArea.setCaretPosition(commandDisplayArea.getDocument().getLength());
			Thread managerThread = new Thread(new ConnectionManagerThread(e.getActionCommand()));
			managerThread.start();			
		}	
	}
	
	/**
	 * @author William Collins
	 * @version 1
	 * @see default package
	 * @since 1.6
	 * 
	 */
	private class ConnectionManagerThread implements Runnable{

		String command;

		private ConnectionManagerThread(String command){
			this.command = command;
		}

		@Override
		public void run() {

			//We want to try to connect to the server
			if (command.equals("Connect")){
				try {			
					//Try creating a socket
					serverSocket = new Socket();
					InetSocketAddress address = new InetSocketAddress(hostField.getText(), Integer.parseInt((String) portSelectionBox.getSelectedItem()));
					serverSocket.connect(address, 1000);

					//Set up the streams
					out = new ObjectOutputStream(serverSocket.getOutputStream());
					in = new ObjectInputStream(serverSocket.getInputStream());		

					//success. Update the status of the buttons
					EventQueue.invokeLater(new Runnable(){
						@Override
						public void run() {
							connectButton.setEnabled(false);
							sendButton.setEnabled(true);		
						}				
					});
					commandDisplayArea.append("Connected to Socket" + serverSocket.toString() + "\n");

				} catch (UnknownHostException ex){
					commandDisplayArea.append(CLIENT_PROMPT + ERROR + " Unknown Host.\n");
				} catch (Exception ex){
					commandDisplayArea.append(CLIENT_PROMPT + ERROR + " Connection refused: server is not available. Check port or restart server.\n");
				}
			}

			//The rest of the commands require a connected socket
			try {

				//User sends a command
				if (command.equals("Send")){
					out.writeObject(commandField.getText());
					
					//Update the command field in the event queue
					EventQueue.invokeLater(new Runnable(){
						@Override
						public void run() {
							commandField.setText("");
							commandDisplayArea.setCaretPosition(commandDisplayArea.getDocument().getLength());
							commandField.requestFocusInWindow();			
						}
					});

					String response = (String)in.readObject();
					commandDisplayArea.append(SERVER_PROMPT + response + "\n");
					
					//Test for a close connection
					if (response.equals(ServerSocketRunnable.CONNECTION_CLOSED)){
						//If the connection has been closed, take action
						throw new Exception();
					}
					
				}		

			} catch (Exception ex) {
				
				//Edit the buttons in a thread safe way
				EventQueue.invokeLater(new Runnable(){
					@Override
					public void run() {
						connectButton.setEnabled(true);
						sendButton.setEnabled(false);
					}		
				});

				commandDisplayArea.append(CLIENT_PROMPT + "Connection closed.\n");
			} 		
		}
	}
}
