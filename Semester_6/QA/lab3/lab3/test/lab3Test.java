import java.io.IOException;

import junit.framework.Assert;

import org.junit.Test;


public class lab3Test {

	@Test
	public void testCalcOutputAdditiveStack() {
		
		int num = 40;
    	int stackSize = 10000;
       	int stkOpr = 0, strOpr=0;
       	char peekOpr=' ';    
    	
     	lab3.calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
     	Assert.assertTrue(lab3.answer == 820);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("troppuS dna ecruoS avaJ"));
		
	}
	
	@Test
	public void testCalcOutputSubtractiveStack() {
		
		int num = 40;
    	int stackSize = 10000;
       	int stkOpr = 1, strOpr=0;
       	char peekOpr=' ';    
    	
     	lab3.calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
     	Assert.assertTrue(lab3.answer == -820);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("troppuS dna ecruoS avaJ"));
		
	}
	
	@Test
	public void testCalcOutputReverseCapitalize() {
		
		int num = 40;
    	int stackSize = 10000;
       	int stkOpr = 0, strOpr=1;
       	char peekOpr=' ';    
    	
     	lab3.calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("TROPPUS DNA ECRUOS AVAJ"));
		
	}
	
	@Test
	public void testCalcOutputPeekReg() {
		
		int num = 40;
    	int stackSize = 10000;
       	int stkOpr = 0, strOpr=0;
       	char peekOpr='S';    
    	
     	lab3.calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("troppu dna ecruo avaJ"));
		
	}
	
	@Test
	public void testCalcOutputPeekCap() {
		
		int num = 40;
    	int stackSize = 10000;
       	int stkOpr = 0, strOpr=1;
       	char peekOpr='S';    
    	
     	lab3.calc_output (stkOpr,strOpr,peekOpr,num, stackSize);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("troppu dna ecruo avaJ"));
		
	}
	
	@Test
	public void testLab3Main() throws IOException {
		lab3.main(null);
     	Assert.assertTrue(lab3.input.equalsIgnoreCase("Java Source and Support"));
     	Assert.assertTrue(lab3.output.equalsIgnoreCase("troppuS dna ecruoS avaJ"));
	}
	
}
