package stack;
/*
 * This class does all of the stack based operations
 */
public class stack {
   private int maxSize;
   private int[] data;
   private int top;
   
   public stack (int s) {
      maxSize = s;
      data = new int[maxSize];
      top = -1;
   }
   public void push(int p) {
      data[++top] = p;
   }
   public int pop() {
      return data[top--];
   }
   public int peek() {
      return data[top];
   }
   public boolean isEmpty() {
      return (top == -1);
   }
}
