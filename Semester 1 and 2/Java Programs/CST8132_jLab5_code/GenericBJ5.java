import java.util.ArrayList;
/**
 * This class demonstrates how to use the Java 4 and earlier
 * ArrayList container class.
 * If compiled with Java 5 or later,
 * it will compile and work the same way it works in Java 5 and later,
 * but will produce the following warning:
 * GenericBJ5.java uses unchecked or unsafe operations.
 * Note: Recompile with -Xlint:unchecked for details.
 *
 * If compiled with javac -Xlint:unchecked GenericBJ5.java
 * it will produce 7 warnings. The first two read
 *
 * GenericBJ5.java:47: warning: [unchecked] unchecked call to add(E) as a member of
 * the raw type java.util.ArrayList
 * this.add(date[0]);
 *         ^
 *  GenericBJ5.java:48: warning: [unchecked] unchecked call to add(E) as a member of
 *  the raw type java.util.ArrayList
 *  activity.add(whatToDo[0]);
 *              ^
 * The other warning are similar to the ones above.
 *  
 * if you want to keep compatibility with Java 4,
 * you can ignore the warnings and the code will work as expected or
 * as an alternative, you can compile the client code using
 * the source 1.4 flag (javac -source 1.4), ensuring that no warnings are generated.
 * However, in that case you won�t be able to use any
 * of the new language features introduced in Java 5.0.
 * @author Svillen Ranev
 * @version 1.4
 * @see Java.util.ArrayList
 */
public class GenericBJ5 extends ArrayList{
  private ArrayList activity; 
  private String [] date = {"29-06-09","01-07-09"};
  private String [] whatToDo = {"Learn Java!","Enjoy Java!"};
  public GenericBJ5(){
    activity = new ArrayList();	
  }
  public static void main (String[]args){
   GenericBJ5 g = new GenericBJ5();
   g.runGenericBJ5();
  }
  public void runGenericBJ5(){
//Add dates and activities to an empty ArrayList   
   this.add(date[0]);
   activity.add(whatToDo[0]);
   this.add(1,date[1]);
   activity.add(1,whatToDo[1]);
//Repalce existing activities
   activity.set(0,whatToDo[0]);
   activity.set(1,whatToDo[1]);

   /*The line below compiles - ArrayList can add any object*/
   this.add(new String("pizza"));
   
   Object o1 = this.get(0);
   Object o2 = activity.get(0);
   /*Safe code */
   if(o1 instanceof String & o2 instanceof String)
     System.out.println((String)this.get(0) + " " + (String)activity.get(0));
   
   /*Unsafe code but it will work because the cast is correct */
   System.out.println((String)this.get(1) + " " + (String) activity.get(1));
   
   o1 = get(2);
   /*Unsafe code.Compiles but it will crash in runtime because the cast is wrong.*/
   String s1 = new String();
   if (o1 instanceof String) s1 = (String)o1; 
   
   System.out.print(s1);
 }
}