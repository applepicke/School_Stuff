import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class ListTest {
	public static void main(String args[]) {
		List list = new List(); // create the List container
		EarthquakeDataSet eqds = new EarthquakeDataSet(); // create object that will manage the collection of <i>EarthquakeRecord</i> objects, currently empty
		String sFileName = null;
		try {
			File file;
			JFileChooser fc = new JFileChooser(".");
			fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
			int returnVal = fc.showOpenDialog(null);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
				file = fc.getSelectedFile();

				long lElapseTime = eqds.loadDataFromFile(file);// open file and parse all data into <i>EarthquakeRecord</i> objects
				eqds.display(); // allows the user to display contents of any sequence array before data is sorted.
				System.out.println("File Loading / Parsing: Elapsed time: " + ((float) lElapseTime) / 1000.0);
			}
		} catch (FileNotFoundException fnfe) {
			JOptionPane.showMessageDialog(null, "File not found: " + sFileName);
		} catch (IOException ioe) {
			JOptionPane.showMessageDialog(null, "IO Exception: " + sFileName);
		} catch (Exception e) {
			JOptionPane.showMessageDialog(null, "ERROR: General Exception");
			e.printStackTrace();
		}
		
		//Get original Array
		EarthquakeRecord[] array = eqds.getAeqrOriginalOrder();
		
		// insert Strings in list
		eqds.linkList(array, list);

		//display what is in the list
		list.display();
	} // end main
} // end class ListTest