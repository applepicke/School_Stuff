/**
 * File name: CalculatorModel.java
 * Author: William Collins, 040652633
 * Course: CST8221 – JAP
 * Assignment: 1
 * Date: June 20, 2011
 * Professor: Svillen (the Villain) Ranev
 * Purpose: Perform all arithmetic operations for the calculator controller
 * 
 */


/**
 * The model performs arithmetic operations
 * @author William Collins (040652633)
 * @version 1.1
 * @see Calculator
 * @since 1.6
 */
public class CalculatorModel {
	
	//Static variables used in the logic of the program.
	public static final String FLOAT = "Float";
	public static final String INTEGER = "Integer";
	public static final String MODE_NOT_RECOGNIZED = "MODE NOT RECOGNIZED"; 
	public static final String ERROR = "--";
	public static enum Operation{ ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, SQUAREROOT, POWER, NONE }
	
	/**
	 * Holds the result of the calculations. It is a double because that is the largest datatype that will be returned
	 */
	private Double result;
	/**
	 * Holds the left operand of a calculation. Double precision will ensure proper calculations
	 */
	private Double leftOperand;
	/**
	 * Holds the right operand of a calculation. Double precision will ensure proper calculations
	 */
	private Double rightOperand;
	
	/**
	 * Is true when an error in a calculation has been detected. 
	 */
	private boolean error;
	/**
	 * Specifies the current mode of operation. Should be INTEGER or FLOAT.
	 */
	private String mode;
	/**
	 * The current arithmetical operation to be performed. One of the Operation enumerated datatype.
	 */
	private Operation currentOperation;
	/**
	 * A true value here signals that an operation has been performed, and we are ready for a new set of operands and operator.
	 */
	private boolean readyForNewNumberFlag;
	
	/**
	 * Default operating mode is FLOAT, and everything is set to zero, and will be ready for a new number.
	 * 
	 */
	public CalculatorModel(){
		mode = FLOAT;
		currentOperation = Operation.NONE;
		result = 0.0;
		leftOperand = 0.0;
		rightOperand = 0.0;
		readyForNewNumberFlag = true;
		
	}

	/**
	 * Sets the right operand to the specified value, while tranfering the previous right operand into the left operand.
	 * @param right: This string represents a number that will be parsed and assigned. No error checking is done in the 
	 * method, so the main program must make sure it doesn't allow invalid input to be passed in.
	 */
	public void setOperand(String right){
		leftOperand = rightOperand;
		rightOperand = Double.parseDouble(right);	
	}

	/**
	 * The operation will determine what arithmetic will be done.
	 * @param op: A String representing an operation to be performed. Simple strings represent the operations as an ad hoc solution.
	 */
	public void setOperation(String op){
		if (op.equals("+")){
			currentOperation = Operation.ADDITION;
		} else if (op.equals("-")){
			currentOperation = Operation.SUBTRACTION;
		} else if (op.equals("*")){
			currentOperation = Operation.MULTIPLICATION;
		} else if (op.equals("/")){
			currentOperation = Operation.DIVISION;
		} else if (op.equals("\u221A")){
			currentOperation = Operation.SQUAREROOT;
		} else if (op.equals("P")){
			currentOperation = Operation.POWER;
		} else if (op.equals("C")){
			currentOperation = Operation.NONE;
		}
		readyForNewNumberFlag = true;
	}
	
	/**
	 * Set the current mode of operation.
	 * NOTE: The behaviour is undefined for running in any mode other than the member constants declared above.
	 * @param mode: The mode to run in. Should be one of INTEGER or FLOAT
	 */
	public void setMode(String mode) {
		this.mode = mode;
	}
	
	/**
	 * Access to the mode
	 * @return The current operating mode
	 */
	public String getMode(){
		return mode;
	}
	
	/**
	 * Performs calculations and returns the result to the caller. If there is an error, it will report with the constant ERROR.
	 * If the current operating mode is neither INTEGER or FLOAT, MODE_NOT_RECOGNIZED is returned.
	 * @return A string representation of the result of internal calculation based on the operator and the operands.
	 */
	public String getResult(){
		//When we return the result of a calculation, we know that we are expecting a new number to be entered
		readyForNewNumberFlag = true;
		
		//Now we shall perform our calculations
		performCalculations();
		
		//Check for errors and report an appropriate error string
		if (error){
			return ERROR;
		}
		
		//And return a value based on what mode we are in
		if (mode == INTEGER){
			return String.valueOf(result.intValue());
		}
		else if(mode == FLOAT){
			return String.valueOf(result.floatValue());
		} 
		//We will return an error string message if we can't recognize the mode
		return MODE_NOT_RECOGNIZED;
	}
	
	/**
	 * Everyone wants to know whether we messed up.
	 * @return boolean describing the error state
	 */
	public boolean isError() {
		return error;
	}

	/**
	 * Normally used for clearing the error, but freedom is nice. If the project were a little bigger I would reconsider leaving
	 * this access to my private data members, but for now I think it's okay. 
	 * @param error the error value you want to set.
	 */
	public void setError(boolean error) {
		this.error = error;
	}
	
	public void clear(){
		result = 0.0;
		leftOperand = 0.0;
		rightOperand = 0.0;
		currentOperation = Operation.NONE;
	}
	
	/**
	 * Somewhat obscurely named, will give a representation of zero for the appropriate mode we are running in.
	 * @return A string representation of zero.
	 */
	public String getZero(){
		if(mode == INTEGER){
			return "0";
		}
		else {
			return "0.0";
		}
	}
	
	/**
	 * The calculations do no special checks on the operands, simply performs the current operation of them. If the operation
	 * is undefined, however, zero is returned. How thoughtful right? Also, depending on our current operating mode, calculations will 
	 * be cast to appropriate data types to ensure precision and accuracy. 
	 * 
	 * Errors are handled by setting the error flag to true.
	 */
	private void performCalculations(){
		
		if (mode == INTEGER){	
			
			// Let's save ourself a whole bunch of method calls by just making one. 
			// Makes things look much cleaner and easier to read as well ;)
			float left = leftOperand.intValue();
			float right = rightOperand.intValue();
			
			
			//Casting the int results as double will still reflect proper integer values, 
			//only stored as double. Later, depending on the OpMode, we can retrieve accordingly
			switch(currentOperation){
			case ADDITION:
				result = (double) (left + right);
				break;
			case SUBTRACTION:
				result = (double) (left - right);
				break;
			case MULTIPLICATION:
				result = (double) (left * right);
				break;
			case DIVISION:
				result = (double) (left / right);
				break;
			case SQUAREROOT:
				result = Math.sqrt(right);
				break;
			case POWER:
				result = (double) Math.pow(left, right);
				break;
			default:
				result = 0.0;
				
			}
		}
		else if(mode == FLOAT){	
			
			//Same as above, just making things more efficient and easier to read.
			float left = leftOperand.floatValue();
			float right = rightOperand.floatValue();
			
			//We need to cast the values as double in order to fit them properly in the result
			switch(currentOperation){
			case ADDITION:
				result = (double) (left + right);
				break;
			case SUBTRACTION:
				result = (double) (left - right);
				break;
			case MULTIPLICATION:
				result = (double) (left * right);
				break;
			case DIVISION:
				result = (double) (left / right);
				break;
			case SQUAREROOT:
				result = Math.sqrt(right);
				break;
			case POWER:
				result = Math.pow(left, right);
				break;
			default:
				result = 0.0;
				
			}
		}	
		//Let's make sure we report the possible errors, and set the error value accordingly
		if (result.isInfinite() || result.isNaN()){
			error = true;
		}
		//This right operand will become the left operand if a new operand is introduced
		//rightOperand =  result;
	}
	
	/**
	 * Indicates to the outside world whether we are ready to accept a new number. Perhaps this is outside
	 * the functional scope of the class, but I'm in no hurry to plow through my code to change it, seeing
	 * as likely no one will ever read this code again. 
	 * @return A status indicating whether we are ready to start accepting a new number
	 */
	public boolean isReadyForNewNumber(){
		return readyForNewNumberFlag;
	}
	
	/**
	 * Tells the model whether or not it should be ready for a new number or not.
	 * @param ready self explanatory
	 */
	public void setReadyForNewNumber(boolean ready){
		readyForNewNumberFlag = ready;
	}
	
	
}
