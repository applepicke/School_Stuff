import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 * The class manages a set of <i>EarthquakeRecord</i> objects. One set of <i>EarthquakeRecord</i> objects will be loaded into memory, but there may be multiple indexes to those objects. The sequence of each index is based on a sort order which is defined by <i>Comparator</i> objects built in the <i>EarthquakeRecord</i> class.
 * @author Rex.Woollard@AlgonquinCollege.com
 * @author Updated by: coll0300@algonquinlive.com 
 */
public class EarthquakeDataSet {
	/** Tracks number of records actually stored in array container. The primary array may have unused elements if it is larger than this value. */
	private int nNumRecordsLoaded;
	/** Reference to the primary array which will be allocated when processing the file; it may be oversized if the user specifies a size which is greater than the number of records. */
	private EarthquakeRecord[] aeqrOriginalOrder; 

	public EarthquakeDataSet() { }


	

	/**
	 * Accepts filename as argument; opens file; creates array of references (the container); builds <i>EarthquakeRecord</i> objects and adds to container.
	 * 
	 * @param sFileName
	 * @return long value that represents the time taken to complete file processing (in milliseconds)
	 * @throws Exception   1:File open error 2:Read record error 3:Parse field error
	 */
	public long loadDataFromFile(File file) throws FileNotFoundException, Exception {
		Scanner scanInput = new Scanner(file); // can throw FileNotFoundException which is caught in main()
		int nMaxNumRecords;
		do { // guard against negative or 0 value from user, since those would be meaningless entries
			nMaxNumRecords = Integer.parseInt(JOptionPane.showInputDialog("Maximum Number of Records: "));
		} while (nMaxNumRecords <= 0);

		nNumRecordsLoaded = 0; // nNumRecordsProcessed may be less then nMaxNumRecords if the array is larger than needed
		long lStartTime = System.currentTimeMillis(); // used to track the timing of each significant activity
		aeqrOriginalOrder = new EarthquakeRecord[nMaxNumRecords]; // first array may be oversized, if fewer records exist than nMaxNumRecords, then subsequent arrays will be smaller
		try { // EarthquakeRecord file parsing manages exception handling and accounts for significant variability in field formats, this try block catches residual unhandled exceptions
			while (nNumRecordsLoaded < nMaxNumRecords && scanInput.hasNext()) {
				String sRawRecord = scanInput.nextLine(); // sRawRecord references a String object with the raw, unparsed data for one earthquake record
				aeqrOriginalOrder[nNumRecordsLoaded++] = new EarthquakeRecord(sRawRecord); // EarthquakeRecord constructor will parse raw String into specific instance variables
			}
		} catch (Exception e) {
			throw new Exception("Input failure at record: " + nNumRecordsLoaded);
		}
		System.out.printf("Number Records Loaded: %d", nNumRecordsLoaded);
		return System.currentTimeMillis() - lStartTime; // calculate the elapse time to load the data from disk into memory
	}
	public long copyOriginalArray() {
		// There will only ever be a single set of EarthquakeRecord objects, but there will be 4 big arrays of references to manage 4 different views of that common set of objects.
		// Create parallel arrays of references, which will act as indexes; Populate with the identical sequence of reference values using <i>copyOf()</i>.
		// Before sorting the three arrays will contain identical sets of values in the identical sequence.
		// After sorting the three arrays will contain identical sets of values but in different sequences (to reflect the different sort order).

		long copyStartTime = System.currentTimeMillis(); // Capture the start time of the copy
		
		return System.currentTimeMillis() - copyStartTime; // Return the elapse time
	}

	/**
	 * Allows user to select index which will be used to display, and thus determine an alternate sequence.
	 */
	public void display() {
		String[] asSortKeys = { "Original" };
		String sReturnValue = (String) JOptionPane.showInputDialog(null, "Select array to sequence display:", "Key Sequence", JOptionPane.INFORMATION_MESSAGE, null, asSortKeys, asSortKeys[0]);
		if (sReturnValue == asSortKeys[0])
			display("Original Sequence", aeqrOriginalOrder);

	}

	/**
	 * Displays data set based on selected view. Shows only a subset of data; enough to survey for the correctness of sorting.
	 * @param rsLabel <i>String</i> is shown to provide the user with context.
	 * @param raeqrDataSet reference to the array that contains references to the <i>EarthquakeRecord</i> objects, but in the desired viewing sequence.
	 */
	private void display(String rsLabel, EarthquakeRecord[] raeqrDataSet) {
		System.out.println(rsLabel);
		if (nNumRecordsLoaded < 30)
			for (int i = 0; i < nNumRecordsLoaded; ++i)
				System.out.println(raeqrDataSet[i]);
		else {
			System.out.println("First 10 records:");
			for (int i = 0; i < 10; ++i)
				System.out.println(raeqrDataSet[i]);

			System.out.println("Middle 10 records:");
			int nStart = nNumRecordsLoaded / 2 - 5;
			int nEnd = nStart + 10;
			for (int i = nStart; i < nEnd; ++i)
				System.out.println(raeqrDataSet[i]);

			System.out.println("Last 10 records:");
			for (int i = nNumRecordsLoaded - 10; i < nNumRecordsLoaded; ++i)
				System.out.println(raeqrDataSet[i]);
		}
	}
	public void linkList(EarthquakeRecord [] array, List list)
	{
		for (int i = nNumRecordsLoaded; i > 0; i--)
		{
			list.insertInSequence(array[i-1]);
		}
	}
	
	public EarthquakeRecord[] getAeqrOriginalOrder() {
		return aeqrOriginalOrder;
	}
	/**
	 * Data sets are potentially huge, thus <i>toString</i> is not used to generate a representation of all data, only a count of the number of <i>EarthquakeRecord</i> objects captured in the data set.
	 */
	public String toString() { return "Number of Records: " + nNumRecordsLoaded; }
}