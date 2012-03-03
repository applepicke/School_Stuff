

public class ModelTest {

	public static void main(String args[]){
		
		String op = "\u221A";
		String num1 = "2.9";
		String num2 = "4";
		
		CalculatorModel model = new CalculatorModel();
		model.setOperand(num1);
		model.setOperation(op);
		model.setOperand(num2);
		System.out.print(num1 + " " + op + " " + num2 + " = " + model.getResult() + "\n");
		
		model.setMode(CalculatorModel.INTEGER);
		model.setOperand(num1);
		model.setOperation(op);
		model.setOperand(num2);
		System.out.print(num1 + " " + op + " " + num2 + " = " + model.getResult() + "\n");
		
	}
	
}
