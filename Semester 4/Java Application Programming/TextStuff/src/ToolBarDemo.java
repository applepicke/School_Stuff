import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
/**
 * Demonstrates toolbars and actions
 *	@author Cay Horstmann, modified by S. Ranev
 */
public class ToolBarDemo
{
   public static void main(String[] args)
   {
      EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
               ToolBarFrame frame = new ToolBarFrame();
               frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
               frame.setVisible(true);
            }
         });
   }
}

/**
 * A frame with a toolbar and menu for color changes.
 */
class ToolBarFrame extends JFrame
{
   public static final int DEFAULT_WIDTH = 300;
   public static final int DEFAULT_HEIGHT = 300;
   private JPanel panel;
   private Action exitAction;
  
   public ToolBarFrame()
   {
      setTitle("ToolBarTest");
      setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);

      // add a panel for color change

      panel = new JPanel();
      add(panel, BorderLayout.CENTER);

      // set up actions

      Action blueAction = new ColorAction("Blue", new ImageIcon("images/blue-ball.gif"),
                                          Color.BLUE, new Integer(KeyEvent.VK_B) );
      Action yellowAction = new ColorAction("Yellow", new ImageIcon("images/yellow-ball.gif"),
                                             Color.YELLOW,new Integer(KeyEvent.VK_Y));
      Action redAction = new ColorAction("Red", new ImageIcon("images/red-ball.gif"),
                                          Color.RED,new Integer(KeyEvent.VK_R));

      exitAction = new AbstractAction("Exit", new ImageIcon("images/exit.gif"))
         {
            public void actionPerformed(ActionEvent event)
            {
               System.exit(0);
            }
         };
      exitAction.putValue(Action.SHORT_DESCRIPTION, "Exit");

      // populate tool bar

      JToolBar bar = new JToolBar("Draggable");
      bar.setBorderPainted(true);
      bar.addSeparator();
      bar.add(blueAction);
      bar.add(new JToolBar.Separator(new Dimension(10,20)));     
      bar.add(yellowAction);
      bar.add(new JToolBar.Separator());
      bar.add(redAction);
      bar.addSeparator();
      bar.add(exitAction);
//      bar.setRollover(true);
//      bar.setFloatable(false);
//      bar.add(new JPanel().add(new JLabel("   Color Toolbar")));

//    bar.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.LOWERED));
//    add(bar, BorderLayout.SOUTH);
//    add(bar, BorderLayout.NORTH);
      add(bar, BorderLayout.PAGE_START);
      
      // populate menu

      JMenu menu = new JMenu("Color");
      menu.add(yellowAction);
      menu.add(blueAction);
      menu.add(redAction);
      menu.add(exitAction);
      JMenuBar menuBar = new JMenuBar();
      menuBar.setBorder(BorderFactory.createEtchedBorder(EtchedBorder.LOWERED));
      menuBar.add(menu);
      setJMenuBar(menuBar);
   }
  

   /**
    * The color action sets the background of the frame to a given color.
    * The background can be changed by choosing a menu item, clicking a toolbar button, or using mnemonics
    * if the color is red it disables simultaneously
    * the exit button in the tool bar end the Exit menu option
    */
   class ColorAction extends AbstractAction
   {
      public ColorAction(String name, Icon icon, Color c, Integer mnemonic)
      {
         putValue(Action.NAME, name);
         putValue(Action.ACTION_COMMAND_KEY,name);
         putValue(Action.SMALL_ICON, icon);
         putValue(Action.SHORT_DESCRIPTION,"Background "+ name);
         putValue(Action.MNEMONIC_KEY, mnemonic);
         putValue("Color", c);
      }

      public void actionPerformed(ActionEvent event)
      {
         String d = event.getActionCommand();
 //       d = (String)getValue(Action.SHORT_DESCRIPTION);
         if(d.equals("Red")) 
           exitAction.setEnabled(false);
         else
            exitAction.setEnabled(true);  
         Color c = (Color) getValue("Color");
         panel.setBackground(c);
      }
   }
}
