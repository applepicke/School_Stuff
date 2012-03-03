import java.lang.*;
import java.lang.String;
public class Practice {
	public static void main(String args[]) {
		
		Class1Practice pizza = new Class1Practice("bill", "washington");
		System.out.print(pizza);
		
		Class1Practice pie = new Class1Practice("boob", "mag");
		System.out.print(pie);
		
		pizza = pie;
		
		pie.edit("beebles", "clue");
		System.out.print(pie);
		System.out.print(pizza);
	}

}
