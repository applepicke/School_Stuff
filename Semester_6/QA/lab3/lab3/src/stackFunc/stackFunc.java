package stackFunc;
import stack.stack;
/*
 * This class has a number of stack based functions for addition and subtraction
 */
public class stackFunc {
   	static int num;
   	public static int ans;
  /*
   * This method performs an addition of all of the numbers from 0 to the start on the stack
   */
    public static void stackAddition(int start,int stackSize) {
    	stack theStack = new stack(stackSize); 
    	ans = 0; 
    	num = start;
      	while (num > 0) {
        	 theStack.push(num); 
         	--num; 
      	}
      	while (!theStack.isEmpty()) {
        	 int newN = theStack.pop(); 
         	ans += newN; 
      	}
    	
   	}
    /*
     * This method performs a subtraction of all of the numbers from 0 to the start on the stack
     */
    public static void stackSubtraction(int start,int stackSize) {
    	stack theStack = new stack(stackSize); 
    	ans = 0; 
    	num = start;
      	while (num > 0) {
        	 theStack.push(num); 
         	--num; 
      	}
      	while (!theStack.isEmpty()) {
        	 int newN = theStack.pop(); 
         	ans += newN; 
      	}
    	
   	}
}
