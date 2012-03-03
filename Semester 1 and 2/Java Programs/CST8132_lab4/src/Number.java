import java.lang.String;

public class Number {
	int dataInt;
	
	public Number(){}
	
	public int validateIntData(String input) {
		for (int i = 0; i < input.length(); i++ ){
			if (Character.isDigit(input.charAt(i)) == false){
				return  -1;
			}	
		}
		if (input == null || input.length() == 0 || input == "")
			return -1;
		dataInt = Integer.parseInt(input, 10);
		return 0;
	}
	
	public int getDataInt(){
		return dataInt;
	}

}
