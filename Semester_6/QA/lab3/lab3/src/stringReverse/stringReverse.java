package stringReverse;
import stack.stack;
import java.lang.Character;
/*
 * This class performs a number of string operations and reversals
 */
public class stringReverse {
   private String input; 
   private String output;
   
   public stringReverse (String in) {
      input = in;
   }
/*
 * This method reverses the order of a string or if the peekChr is given, 
 * it will reverse the order of a string but with the peekChr is removed  
 */
   public String doRev(int peekChr) {
      int stackSize = input.length(); 
      int ch = 0;
      stack theStack = new stack(stackSize); 
      for (int i = 0; i < input.length(); i++) {
         ch = input.charAt(i); 
         theStack.push(ch); 
      }
      
      output = "";
      if (peekChr == ' ') {
    	  while (!theStack.isEmpty()) {
    		   ch =  theStack.pop(); 
    		   output = output + (char)ch; 
    	  }
      } else {
    	  while (!theStack.isEmpty()) {
    		  if (peekChr != theStack.peek()){
    			  ch =  theStack.pop();
        		  output = output + (char)ch; 
    		  } else { 
    			  theStack.pop(); 
    		  }

    	  }
      }
      return output;
   }
   /*
    * This method captilizes and reverses the order of a string or if the peekChr is given, 
    * it will capitilize and reverse the order of a string but with the peekChr is removed  
    */
   public String doRevCap(char peekChr) {
	      int stackSize = input.length(); 
	      Character chr = new Character(' ');
	      stack theStack = new stack(stackSize); 
	      int ch=0;
	      for (int i = 0; i < input.length(); i++) {
	         ch = input.charAt(i); 
	         theStack.push(ch); 
	      }
    	  output = "";
	      if (peekChr == ' ') {
	    	  while (!theStack.isEmpty()) {
	    		  ch =  theStack.pop(); 
	    		  output = output + chr.toUpperCase((char)ch); 
	    	  }
	      } else {
	    	  while (!theStack.isEmpty()) {
	    		  if (peekChr != theStack.peek()){
	    			  ch =  theStack.pop(); 
	    			  output = output + chr.toUpperCase((char)ch);    
	    		  } else {
	    			  ch =  theStack.pop(); 
	    		  }
    			 
	    	  }
	    	  
	      }
	      return output;
	   }
}
