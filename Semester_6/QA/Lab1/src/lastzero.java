
//
// HomeWork 01 - Question 01
//
class lastZero
{

	
public static int lastZero_correct (int[] x)
{
	   for (int i = x.length-1; i >= 0; i--)
	   {
	      if (x[i] == 0)
	      {
	         return i;
	      }
	   }
	   return -1;
}
	
public static int lastZero_defect (int[] x)
{  
   // Effects: if x==null throw NullPointerException 
   //   else return the index of the LAST 0 in x.
   //   Return -1 if 0 does not occur in x

   for (int i = 0; i < x.length; i++)
   {
      if (x[i] == 0)
      {
         return i;
      }
   }
   return -1;
}
   // test:  x=[0, 1, 0]              
   //        Expected = 2

public static void main (String []argv)
{  
   // Driver method for lastZero
   // Read an array from standard input, call lastZero()

   int []inArr = new int [argv.length];
   if (argv.length == 0)
   {
      System.out.println ("Usage: java lastZero v1 [v2] [v3] ... ");
      return;
   }

   for (int i = 0; i< argv.length; i++)
   {
      try
      {
         inArr [i] = Integer.parseInt (argv[i]);
      }
      catch (NumberFormatException e)
      {
         System.out.println ("Entry must be a integer, using 1.");
         inArr [i] = 1;
      }
   }
   
   System.out.println ("The DEFECTIVE last index of zero is: " + lastZero_defect(inArr));
   System.out.println ("The last index of zero is: " + lastZero_correct(inArr));

}

}
