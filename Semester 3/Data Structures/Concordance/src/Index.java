import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;


public class Index {
	
	//Here I use both a HashSet and an ArrayList to optimize efficiency.
	//The hashset searches with O(1), and adds items with O(1)
	//The ArrayList adds items with O(1)
	
	HashSet<String> names;
	ArrayList<WordLocations> locations;
	ArrayList<String> tempList = new ArrayList<String>();
	WordLocations tempLocation = null;
	
	public Index(Collection<String> paragraphs){
		names = new HashSet<String>();//The hashset is used for searching for items
		locations = new ArrayList<WordLocations>(); //arraylist is used for storing items
	}
	
	//Returns an ArrayList of words in the paragraph
	public void fillIndex(String paragraph) {
		tempList.clear(); //Instead of wasting memory creating a new list
		String[] wordList;
		wordList = paragraph.split("[^a-zA-Z_0-9']+");
		for (String a: wordList){
			a = a.toLowerCase();
			tempList.add(a);
		}
		for (String s: tempList){
			//Search through the hashset for an item
			if (names.contains(s)){
				//If the item is in the hashset, add a location to it
				for (WordLocations loc: locations){
					if (s.compareTo(loc.getValue()) == 0 && !loc.doesLocExist(paragraph)){
						loc.addLocation(paragraph);
					}
				}
			}	
			else {
				//Otherwise add the item to both the arraylist and hashset
				tempLocation = new WordLocations(s, paragraph);
				names.add(s);
				locations.add(tempLocation);
			}
		}
	}
	
	public String displayIndex(){
		String temp = new String();
		for (String s: names)
			temp = temp.concat(s + "\n");
		return temp;
	}
	
	
	
}
