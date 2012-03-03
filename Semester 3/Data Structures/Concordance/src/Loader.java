import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.Scanner;
import javax.swing.JOptionPane;

public class Loader {
	
	private String sFileName; //The filename of the file to be loaded
	private Collection<String> paragraphs;
	private Index index;

	//This loader must be specified a filename in order to load the file
	public Loader(String sFileName) {
		this.sFileName = sFileName;
	}

	//Load in the text file, and separate it into paragraphs
	public void loadTextFile(Collection<String> paragraphs) throws FileNotFoundException{
		this.paragraphs = paragraphs;
		Scanner scanFile = new Scanner(new File(sFileName));
		while (scanFile.hasNext()){
			paragraphs.add(scanFile.nextLine());// Add next paragraph of file to collection
		}
		index = new Index(paragraphs);
	}
	
	//Fills the index with words and locations
	//CAUTION: shouldn't use before loading in a text file
	public void fillIndex(){
		for (String a: paragraphs){
			index.fillIndex(a);
		}
	}
	
	public void displayCollection(){
		//JOptionPane.showMessageDialog(null, index.displayIndex(), "Index", 1);
		System.out.print(index.displayIndex());
	}
}
