import java.util.LinkedList;

public class WordLocations {
	private String value;
	private LinkedList<String> locationList;
	
	public WordLocations(String value){
		this.value = value;
		locationList = new LinkedList<String>();
	}
	
	//Initialize with value of word, and the first occurance of that word
	public WordLocations(String value, String initialLocation){
		this.value = value;
		locationList = new LinkedList<String>();
		locationList.add(initialLocation);
	}
	
	//Add a location of the word to the list
	public void addLocation(String location){
		locationList.add(location);
	}
	
	public boolean doesLocExist(String location){
		if (locationList.contains(location)){
			return true;
		}
		else return false;
	}
	
	public String getValue(){
		return value;
	}
	
	@Override
	public String toString(){
		return value + "\n";
	}
}
