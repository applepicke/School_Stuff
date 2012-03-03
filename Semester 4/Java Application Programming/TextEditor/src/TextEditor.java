/* CST8221 � JAP, Midterm Test, Part 1
* Student Name: William Collins (#V) 040652633
* Date: Tuesday July 5 Time: 1:50
* Development platform: Win XP
* Development tool: Eclipse
*/

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;

public class TextEditor extends JFrame{
	
	private JPanel mainPanel;
	private JTextArea textArea;
	private JMenuItem newItem, open, save, exit;
	private JMenuItem cut, copy, paste;
	private JMenuItem about;
	private JFileChooser chooser;
	private JTextField infoBar;
	
	private static String TITLE = "#V's Midterm Test - S11";
	private static String STATUS = "Status: ";
	
	public TextEditor(){		
		
		//Set up text Area
		textArea = new JTextArea(30, 50);
		textArea.setLineWrap(false);
		textArea.setBackground(Color.WHITE);
		
		//Set up the infoBar
		infoBar = new JTextField();
		infoBar.setEditable(false);
		infoBar.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 12));
		infoBar.setBorder(BorderFactory.createEmptyBorder());
		infoBar.setVisible(false);
		
		//Set up the menu items
		MenuController handler = new MenuController();
		JMenuBar menuBar = new JMenuBar();
		
		JMenu fileMenu = new JMenu("File");
		JMenu editMenu = new JMenu("Edit");
		JMenu helpMenu = new JMenu("Help");
		
		//Set up the mnemonics
		fileMenu.setMnemonic('f');
		editMenu.setMnemonic('e');
		helpMenu.setMnemonic('h');
		
		//File menu items
		newItem = new JMenuItem("New");
		open = new JMenuItem("Open");
		save = new JMenuItem("Save");
		exit = new JMenuItem("Exit");	
		
		//Edit menu items
		cut = new JMenuItem("Cut");
		copy = new JMenuItem("Copy");
		paste = new JMenuItem("Paste");
		
		//Help menu items
		about = new JMenuItem("About");
		about.setMnemonic('a');
		
		//Set the accelerators
		newItem.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_DOWN_MASK));
		open.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_DOWN_MASK ));
		save.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_DOWN_MASK ));
		exit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F4, KeyEvent.ALT_DOWN_MASK));
		
		//Add the handlers for the menu items
		newItem.addActionListener(handler);
		open.addActionListener(handler);
		save.addActionListener(handler);
		exit.addActionListener(handler);
		cut.addActionListener(handler);
		copy.addActionListener(handler);
		paste.addActionListener(handler);
		about.addActionListener(handler);
		
		//Add the file menu items to the file menu and to the menubar
		fileMenu.add(newItem);
		fileMenu.addSeparator();
		fileMenu.add(open);
		fileMenu.add(save);
		fileMenu.addSeparator();
		fileMenu.add(exit);
		menuBar.add(fileMenu);	
		
		//Add the edit menu items
		editMenu.add(cut);
		editMenu.add(copy);
		editMenu.add(paste);
		menuBar.add(editMenu);
		
		//Add the help menu items
		helpMenu.add(about);
		menuBar.add(helpMenu);
		
		// Set up the initial panel
		mainPanel = new JPanel(new BorderLayout());
		mainPanel.add(new JScrollPane(textArea));
		mainPanel.add(infoBar, BorderLayout.SOUTH);
		
		//Set up the file chooser
		chooser = new JFileChooser(".");
		FileFilter filter = new FileNameExtensionFilter("Java source files (.java)","java");
		filter = new FileNameExtensionFilter("Text Files (.txt)","txt");
		chooser.addChoosableFileFilter(filter);
		filter = new FileNameExtensionFilter("Java Files (.class)","class");
		chooser.addChoosableFileFilter(filter);
		filter = new FileNameExtensionFilter("Java Files (.java)","java");
		chooser.addChoosableFileFilter(filter);
		chooser.setAcceptAllFileFilterUsed(false);
	
		//Do the last minute frame setup
		setTitle(TITLE);
		setJMenuBar(menuBar);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(mainPanel);
		//DisplayMode displayMode = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode();
		setSize(555, 355);
		setVisible(true);
		
		
	}
	
	/**
	 * Opens the file and displays it in the text field
	 * @param file
	 * @return
	 */
	private String openFile(File file){
		StringBuilder builder = new StringBuilder();
		try {
			Scanner fileReader = new Scanner(new FileReader(file));
			while (fileReader.hasNextLine()){
				builder.append(fileReader.nextLine() + "\n");
			}	
		} catch (FileNotFoundException e) {
			infoBar.setText(STATUS + "File Does Not Exist");
			return null;
		}
		return builder.toString();
	}
	
	/**
	 * Saves the specified file
	 * @param file
	 */
	private void saveFile(File file) {
		try {
			FileWriter writer = new FileWriter(file);
			writer.write(textArea.getText());
			writer.close();
		} catch (IOException e){
			JOptionPane.showMessageDialog(this, "Cannot save file");
		}
	}
	
	private class MenuController extends AbstractAction {

		@Override
		public void actionPerformed(ActionEvent e) {
			int option = 0;
			
			Object source = e.getSource();
			
			//Handle a new file event
			if (source == newItem){
				textArea.setText("");
				infoBar.setText(STATUS + "New empty file.");
			}
			
			//Handle the open file event
			if (source == open){
				option = chooser.showOpenDialog(mainPanel);
				if (option == JFileChooser.APPROVE_OPTION){
					String newText = openFile(chooser.getSelectedFile());
					
					//Make sure the file can be opened
					if (newText != null) {
						textArea.setText(openFile(chooser.getSelectedFile()));
						infoBar.setText("File " + chooser.getSelectedFile().getName() + " is open.");
						textArea.setCaretPosition(0);
					}

				}
				if (option == JFileChooser.CANCEL_OPTION){
					infoBar.setText(STATUS + "Open operation is cancelled.");
				}
			}
			//Handle the save file event
			if (source == save){
				option = chooser.showSaveDialog(mainPanel);
				if (option == JFileChooser.APPROVE_OPTION){
					saveFile(chooser.getSelectedFile());
					infoBar.setText("File " + chooser.getSelectedFile().getName() + " is saved.");
				}
				if (option == JFileChooser.CANCEL_OPTION){
					infoBar.setText(STATUS + "Save operation is cancelled.");
				}
			}
			
			//Handle the exit event
			if (source == exit){
				System.exit(0);
			}
			
			//Handle cut, copy and paste
			if (source == cut || source == copy || source == paste){
				infoBar.setText(STATUS + ((JMenuItem)source).getActionCommand() + " menu item has been selected.");
			}
			
			//Handle the About button
			if (source == about){
				JOptionPane.showMessageDialog(mainPanel, "#V's Program Awesomer\nVersion 1.0, Summer 2011");
				return;
			}
			
			//Trick the frame into showing the updated infoBar
			infoBar.setVisible(true);
			setVisible(false);
			setVisible(true);
			
		}
	}
	
	public static void main(String args[]){
		SwingUtilities.invokeLater(new Runnable() {

			@Override
			public void run() {
				TextEditor editor = new TextEditor();
			}
		});
	}
}
