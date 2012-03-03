// Fig. 14.9: TextFieldFrame.java
// Demonstrating the JTextField and JPasswordField classes.
// Modified by S. Ranev
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import javax.swing.border.*;

public class TextFieldPanel extends JPanel
{
   private JTextField textField1; // text field with set size
   private JTextField textField2; // text field constructed with text
   private JTextField textField3; // text field with text and size
   private JPasswordField passwordField; // password field with text

   // TextFieldFrame constructor adds JTextFields to JFrame
   public TextFieldPanel()
   {
//      super( "Testing JTextField and JPasswordField" );
      // change the default layout of the main panel
      setLayout( new BorderLayout());
      // create a panel to hold the editable text fields
      JPanel pane1 = new JPanel();
      pane1.setLayout( new BorderLayout() ); // change panel layout
      pane1.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));//set borders
      // construct empty textfield with 25 columns
      textField1 = new JTextField( 25 ); 
      pane1.add(textField1,BorderLayout.NORTH);//add textField1 to pane1
      

      // construct textfield with default text
      textField2 = new JTextField(25);
      textField2.setHorizontalAlignment(JTextField.RIGHT);
      textField2.setText("Enter text here and press Enter");
      pane1.add(textField2,BorderLayout.SOUTH); //add textField2 to pane1
      // add first panel to frame
      add(pane1, BorderLayout.NORTH);   

      // create a panel to hold non-editable text field and password field
      JPanel pane2 = new JPanel();// default layout
      // construct textfield with default text and 21 columns
      textField3 = new JTextField( "Uneditable text field", 21 );
      textField3.setEditable( false ); // disable editing
      textField3.setBackground(Color.WHITE);
      pane2.add( textField3 ); // add textField3 to JFrame

      // construct passwordfield with default text
      passwordField = new JPasswordField( "Hidden text" );
      pane2.add( passwordField ); // add passwordField to JFrame
      // add second panel to frame
      add(pane2,BorderLayout.SOUTH);
      // register event handlers
      TextFieldHandler handler = new TextFieldHandler();
      textField1.addActionListener( handler );
      textField2.addActionListener( handler );
      textField3.addActionListener( handler );
      passwordField.addActionListener( handler );
   } // end TextFieldFrame constructor

   // private inner class for event handling
   private class TextFieldHandler implements ActionListener 
   {
      // process textfield events
      public void actionPerformed( ActionEvent event )
      {
         String string = ""; // declare string to display

         // user pressed Enter in JTextField textField1
         if ( event.getSource() == textField1 )
            string = String.format( "textField1: %s",
               textField1.getText() );

         // user pressed Enter in JTextField textField2
         else if ( event.getSource() == textField2 )
            string = String.format( "textField2: %s",
               textField2.getText() );

         // user pressed Enter in JTextField textField3
         else if ( event.getSource() == textField3 )
            string = String.format( "textField3: %s", 
               textField3.getText() );

         // user pressed Enter in JPasswordField passwordField
         else if ( event.getSource() == passwordField ){
            string = String.format( "passwordField: %s", 
              new String(passwordField.getPassword()));
          //display password in non-editable field - textField3 
            textField3.setText("Display "+ string);
         }
         // display JTextField content
         JOptionPane.showMessageDialog( null, string ); 
      } // end method actionPerformed
   } // end private inner class TextFieldHandler
} // end class TextFieldFrame

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
