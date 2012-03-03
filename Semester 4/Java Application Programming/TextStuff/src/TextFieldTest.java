// Fig. 14.10: TextFieldTest.java
// Testing TextFieldFrame.
// Modified by S. Ranev
import javax.swing.JFrame;
import java.awt.*;

public class TextFieldTest
{
   public static void main( String[] args )
   { 
     //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
      javax.swing.SwingUtilities.invokeLater(new Runnable() {
      @Override
        public void run() {                

      // create the application frame
        JFrame frame = new JFrame("Testing JTextField and JPasswordField");
        TextFieldPanel textFieldPanel = new TextFieldPanel(); 
        Container contentPane = frame.getContentPane();
        contentPane.add(textFieldPanel,BorderLayout.CENTER);
        frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        frame.setSize( 350, 130 ); // set frame size
        frame.setResizable(false);
        frame.setVisible( true ); // display frame
       } 
    });
   } // end main
} // end class TextFieldTest

/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
