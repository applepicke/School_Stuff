

import junit.framework.*;


public class TestMath extends TestCase { 

  protected void setUp() { 
    	
  	// put common setup code in here
   }
   
  protected void tearDown() {
  	
  	// put common cleanup code in here
  }
    
  public void testAdd() {
  	int num1 = 3;
  	int num2 = 2;
  	int total = 5;
  	int sum = 0;
  	sum = Math.add(num1, num2);
  	assertEquals(sum, total);
  }
  
  public void testMulitply() {
  	
  	int num1 = 2; 
  	int num2 = 7; 
  	int total = 14;
  	int sum = 0;
  	sum = Math.multiply(num1, num2);
  	assertEquals("Problem with multiply", sum, total);
  	
  	
  	num1 = 5;
  	num2 = 4;
  	total = 20;
  	sum = Math.multiply(num1, num2);
  	assertEquals("Problem with multiply", sum, total);
  	
  }
    
}