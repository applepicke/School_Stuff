import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;


public class LastZeroTest_correct {

	@Before
	public void setUp() {
		
	}
	
	@After
	public void tearDown() {
		
	}
	
	@Test
	public void testLastZeroWithNoZeros() {
		int[] testArray = { 1, 2, 3 };		
		int result = lastZero.lastZero_correct(testArray);
		assertTrue("No zero in list should return -1", result == -1);
		
	}
	
	@Test
	public void testLastZeroWithOneZero() {
		int[] testArray1 = { 2, 0, 8 };
		int[] testArray2 = { 0, 1, 2 };
		int[] testArray3 = { 1, 2, 0 };
		int result1 = lastZero.lastZero_correct(testArray1);
		int result2 = lastZero.lastZero_correct(testArray2);
		int result3 = lastZero.lastZero_correct(testArray3);
		assertTrue("Zero should be element 1", result1 == 1);
		assertTrue("Zero should be element 0", result2== -0);
		assertTrue("Zero should be element 2", result3 == 2);
	}
	
	@Test
	public void testLastZeroWithNull(){
		boolean thrown = false;
		try {
			lastZero.lastZero_correct(null);
		}
		catch (NullPointerException e) {
			thrown = true;
		}		
		assertTrue("Null pointer excpetion not thrown", thrown);
	}
	
	@Test
	public void testLastZeroWithMultipleZeros() {
		int[] testArray = { 0, 3, 0, 3 };
		int result = lastZero.lastZero_correct(testArray);
		assertTrue("Zero should be element 2", result == 2);
	}
	
	
	
	
}
