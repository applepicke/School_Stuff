import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import javax.xml.crypto.KeySelector.Purpose;


public class TextEditor extends JFrame{
	
	private JPanel mainPanel;
	private JTextArea textArea;
	private JMenuItem open, save, exit;
	private JFileChooser chooser;
	private JTextField infoBar;
	private File currentFile;
	private boolean isModified;
	
	private Map<String, Color> keywordMap;
	
	private static String TITLE = "Willy's Text Editor";
	private static String JAVA_KEYWORD_MAP = "jkeywords.lst";
	
	public TextEditor(){		
		
		//Set up text Area
		//TextAreaController textHandler = new TextAreaController();
		textArea = new JTextArea();
		textArea.setLineWrap(false);
		textArea.setBackground(Color.WHITE);
		textArea.setTabSize(4);
		//textArea.addKeyListener(textHandler);
		
		//Set up the map holding the keywords and colors
		keywordMap = loadKeywordMapping(new File(JAVA_KEYWORD_MAP));
		
		//Set up the default open file and the isModified flag
		currentFile = null;
		isModified = false;
		
		//Set up the inforBar
		infoBar = new JTextField();
		infoBar.setEditable(false);
		infoBar.setFont(new Font(Font.SANS_SERIF, Font.ITALIC, 10));
		
		//Set up the menu items
		MenuController handler = new MenuController();
		JMenuBar menuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		fileMenu.setMnemonic('f');
		open = new JMenuItem("Open");
		save = new JMenuItem("Save");
		exit = new JMenuItem("Exit");	
		//Set the accelerators
		open.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_DOWN_MASK ));
		save.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_DOWN_MASK ));
		//Add the handlers for the menu items
		open.addActionListener(handler);
		save.addActionListener(handler);
		exit.addActionListener(handler);
		fileMenu.add(save);
		fileMenu.add(open);
		fileMenu.add(exit);
		menuBar.add(fileMenu);	
		
		// Set up the initial panel
		mainPanel = new JPanel(new BorderLayout());
		mainPanel.add(new JScrollPane(textArea));
		mainPanel.add(infoBar, BorderLayout.SOUTH);
		mainPanel.setBorder(BorderFactory.createLineBorder(Color.LIGHT_GRAY));
		
		//Set up the file chooser
		chooser = new JFileChooser(".");
		
		
		//Do the last minute frame setup
		setTitle(TITLE);
		setJMenuBar(menuBar);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setContentPane(mainPanel);
		DisplayMode displayMode = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode();
		setSize(displayMode.getWidth()/2, displayMode.getHeight()/2);
		setLocation(200, 200);
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
			setFile(file);
		} catch (FileNotFoundException e) {
			JOptionPane.showMessageDialog(this, "Cannot open file");
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
			setFile(file);
		} catch (IOException e){
			JOptionPane.showMessageDialog(this, "Cannot save file");
		}
	}
	
	private void tryExit(){
		int option = 0;
		if (isModified){
			option = JOptionPane.showConfirmDialog(this, "Do you want to save " + currentFile.getName() + " before exiting?");
			if (option == JOptionPane.YES_OPTION){
				saveFile(currentFile);
			}
			else {
				System.exit(0);
			}
		}
	}
	
	private void setFile(File file){
		currentFile = file;
		setTitle(TITLE + " (" + file.getName() + ")");	
		isModified = false;
	}
	
	private HashMap<String, Color> loadKeywordMapping(File mapFile){
		HashMap<String, Color> map = new HashMap<String, Color>();
		Scanner fileScan;
		Color currentColor = Color.MAGENTA;
		String nextKeyword;
		
		//Try to open the keyword mapping file
		try {
			fileScan = new Scanner(new FileReader(mapFile));
		} catch (FileNotFoundException e){
			infoBar.setText("ERROR: Could not load keyword mappings.");
			return map;
		}
		
		//Scan the file for keywords and color tags
		while (fileScan.hasNextLine()){
			nextKeyword = fileScan.nextLine();
			
			//Check to see if the keyword is a color tag
			if (nextKeyword.equals(":BLUE")){
				currentColor = Color.BLUE;
			}
			else {
				map.put(nextKeyword, currentColor);
			}
		}
		
		return map;
	}
	
	private class MenuController extends AbstractAction {

		@Override
		public void actionPerformed(ActionEvent e) {
			int option = 0;
			
			//Handle the open file event
			if (e.getSource() == open){
				option = chooser.showOpenDialog(mainPanel);
				if (option == JFileChooser.APPROVE_OPTION){
					textArea.setText(openFile(chooser.getSelectedFile()));
					infoBar.setText(chooser.getSelectedFile().getName() + " has been opened successfully.");
				}
			}
			//Handle the save file event
			if (e.getSource() == save){
				option = chooser.showSaveDialog(mainPanel);
				if (option == JFileChooser.APPROVE_OPTION){
					saveFile(chooser.getSelectedFile());
					infoBar.setText(chooser.getSelectedFile().getName() + " has been saved.");

				}
			}
			
			//Handle the exit event
			if (e.getSource() == exit){
				tryExit();
			}
			
		}
		
	}
	
	private class TextAreaController extends KeyAdapter{
		
		@Override
		public void keyTyped(KeyEvent e) {
			
			Scanner textScanner = new Scanner(textArea.getText());
			String currentWord;
			
			if (e.getSource() != textArea){
				return;
			}
			
			while(textScanner.hasNext()){
				currentWord = textScanner.next();
				
			}
			
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
