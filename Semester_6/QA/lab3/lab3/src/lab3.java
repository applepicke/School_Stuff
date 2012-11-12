import java.io.IOException;

import stack.stack;
import stackFunc.stackFunc;
import stringReverse.stringReverse;



class lab3 {
	
	static String input = "Java Source and Support";
    static String output,alt_out;
    static int answer;
    /*
     * The purpose of this routine is to calculate the data output requirements 
     * for the main section of the program 
     * 
     */
	public static  void calc_output ( int stkOpr,int stringOpr,char peekChr, int start, int stackSize) {
		stackFunc stackOpr = new stackFunc ();
		if (stkOpr == 0 ) {
     		stackOpr.stackAddition (start,stackSize);
		} else {
     		stackOpr.stackSubtraction (start,stackSize);
     	}
     	answer = stackOpr.ans;
     	
     	stringReverse theReverser =  new stringReverse (input);
     	
     	if (stringOpr == 0 ) {
    		output = theReverser.doRev(peekChr);
  		} else {
      		output = theReverser.doRevCap(peekChr);
      	}
	}
/*
 * This is the main routine that calls up the data routines
 */
	public static void main(String[] args)
		throws IOException {
    	int num = 40;
    	int stackSize = 1000;
       	int stkOpr = 0, strOpr=0;
       	char peekOpr=' ';    
    	
     	calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
    	
		System.out.println("Sum      : " + answer);
		
	    System.out.println("Normal   : " + input);
    	
      	System.out.println("Reversed : " + output);
      	
  
	}
}
