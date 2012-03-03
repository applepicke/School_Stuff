import java.util.Scanner;
import java.lang.String;

public class Class1Practice {
	
	private String nName;
	private String nPlace;
	
	public Class1Practice(String nope, String mope) {
		nName = nope;
		nPlace = mope;
	}
	public void edit(String nope, String mope) {
		nName = nope;
		nPlace = mope;
	}
	
	public String toString() {
		return "Name: " + nName + "\nPlace: " + nPlace + "\n";
	}
	
}
