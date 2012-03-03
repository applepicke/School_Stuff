import java.util.Comparator;

// Part of List-Head project (no Tail)
// TODO Replace all references to String with something that works for EarthquakeRecord objects. There are two different solutions:
// TODO 1. Replace the data type String with the data type EarthquakeRecord. This works, but means your List can only ever be used with EarthquakeRecord objects.
// TODO 2. Convert your List and ListNode classes into a generic design.
public class List {
	private ListNode lnHead = null;
	private ListNode lnTail = null;
	private int nNumItems = 0; // specified in the List class but incremented in the 
	
	public List() { }

	public boolean isEmpty() { return lnHead == null; }

	/** insertAtFront has O(1) performance */
	public void insertAtFront(EarthquakeRecord newData) {
		lnHead = new ListNode(newData, lnHead);
		if (lnTail == null) // check to see if it is the first object
			lnTail = lnHead;
	} // end method insertAtFront

	/** insertAtFront has O(1) performance, because it has a tail reference; without a tail reference performance would be O(n) */
	public void insertAtBack(EarthquakeRecord newData) {
		ListNode lnNew = new ListNode(newData);
		if (isEmpty()) // firstNode and lastNode refer to same EarthquakeRecord
			lnTail = lnHead = lnNew;
		else
			lnTail = lnTail.lnNext = lnNew;
	} // end method insertAtBack

	/** insertInSequence has O(n) performance. */
	public void insertInSequence(EarthquakeRecord newData) {
		
		ListNode lnInsert = new ListNode( newData, lnHead );
		
		//If the list is empty, set the data to the head of the list
		if (isEmpty()) 
		{ 
			lnHead = lnInsert; 
		}
		
		//If the list only has a head, make the data the tail of the list
		else if (lnTail == null)
		{
			lnTail = lnInsert;
			if (CompareEpicenter.instance.compare(lnHead.data, lnTail.data) < 0)
			{
				lnHead.lnNext = lnTail;
				lnTail.lnNext = null;
			}
			else
			{
				lnTail.lnNext = lnHead;
				lnHead = lnTail;
				lnTail = lnHead.lnNext;
			}
		}

		//If the node passed in belongs in front, make it lnHead
		else if (CompareEpicenter.instance.compare(lnInsert.data, lnHead.data) < 0)
		{
			lnInsert.lnNext = lnHead;
			lnHead = lnInsert;
			lnInsert = lnHead.lnNext;
		}
		
		
		//If the list is populated with a head and tail, find where the data belongs
		else
		{
			ListNode lnAfter = lnInsert.lnNext;
			ListNode lnBefore = lnInsert;
			
			while (true)
			{
				//If the temporary link is null, make insert the tail
				if (lnAfter == null)
				{
					lnTail.lnNext = lnInsert;
					lnTail = lnInsert;
					lnInsert.lnNext = null;
					break;
				}
				//Compare values of data to be inserted. If data inserted is less than next data in line, insert before second piece
				else if (CompareEpicenter.instance.compare(lnInsert.data, lnAfter.data) > 0)
				{
					lnAfter = lnAfter.lnNext;
					lnBefore = lnBefore.lnNext;
				}
				else 
				{
					lnBefore.lnNext = lnInsert;
					lnInsert.lnNext = lnAfter;	
					break;
				}
			}
		}
	} // end method insertInSequence
	
	public EarthquakeRecord removeFromFront() throws EmptyListException {
		if (isEmpty()) // throw exception if List is empty
			throw new EmptyListException();

		EarthquakeRecord removedData = lnHead.data; // retrieve data being removed
		lnHead = lnHead.lnNext;
		if (isEmpty())
			lnTail = null;

		--nNumItems;
		return removedData; // return removed node data
	} // end method removeFromFront

	public EarthquakeRecord removeFromBack() throws EmptyListException {
		if (isEmpty()) // throw exception if List is empty
			throw new EmptyListException();

		EarthquakeRecord removedData = null;
		if (lnHead.lnNext == null){ // only one node
			removedData = lnHead.data;
			lnHead = null;
		}
		else { // Locate new last node. Even though we have a tail, we need access to the node one position away from the tail, so we have to start by walking from the head: O(n) performance
			ListNode lnCurr = lnHead.lnNext;
			ListNode lnPrev = lnHead;
			while (lnCurr.lnNext != null) {
				lnPrev = lnCurr;
				lnCurr = lnCurr.lnNext;
			}

			removedData = lnCurr.data; // retrieve data being removed

			lnPrev.lnNext = null;
		} // end else

		--nNumItems;
		return removedData; // return removed node data
	} // end method removeFromBack

	public void display() {
		if (isEmpty()) {
			System.out.println("Empty"); return;
		} // end if

		System.out.printf("%d %s: \n*********\n", nNumItems, nNumItems==1?"item":"items");
		ListNode lnCurrent = lnHead;
		while (lnCurrent != null) {
			System.out.print(lnCurrent.data + "\n");
			lnCurrent = lnCurrent.lnNext;
		} // end while

		System.out.println();
	} // end method print
	
	/** Inner class (non-static), therefore it has access to the parent class instance variables: <i>nNumItems</i> in this case. */
	private class ListNode {
		private EarthquakeRecord data;
		private ListNode lnNext;

		private ListNode(EarthquakeRecord object) { this(object, null); }
		private ListNode(EarthquakeRecord object, ListNode ln) { ++nNumItems; data = object; lnNext = ln; }
	} // end class ListNode
	
	/** Inner class (static), used to compare two strings. Singleton Style */
	private static class CompareEpicenter implements Comparator<EarthquakeRecord>{
		final public static CompareEpicenter instance = new CompareEpicenter(); 
		private CompareEpicenter(){}
		public int compare(EarthquakeRecord record1, EarthquakeRecord record2){
			return (record1.getEpicentre() - record2.getEpicentre());
		}
	}

} // end class List