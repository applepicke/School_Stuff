/**
 * MenuDemo.java
 *
 * Demonstrates howto bild  main menu and popup menu.
 */
import java.awt.EventQueue;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class MenuDemo extends JFrame
   implements ActionListener, MenuListener {

       private JMenuItem saveItem;
       private JMenuItem saveAsItem;
       private JMenuItem exitItem;
       private JCheckBoxMenuItem readonlyItem;
       private JPopupMenu popup;

       public MenuDemo() {
           setTitle("Menu Demo");

           JMenuBar mbar = new JMenuBar();
           setJMenuBar( mbar );

           // demonstrate enabled/disabled items
           JMenu fileMenu = new JMenu("File");
           fileMenu.setMnemonic('F');
           fileMenu.addMenuListener(this);
           

           // demonstrate accelerators
           JMenuItem openItem = new JMenuItem("Open");
           openItem.setAccelerator(
               KeyStroke.getKeyStroke(KeyEvent.VK_O,
               InputEvent.CTRL_MASK));
            saveItem = new JMenuItem("Save");
            saveItem.setAccelerator
                (KeyStroke.getKeyStroke(KeyEvent.VK_S,
                InputEvent.CTRL_DOWN_MASK));
            saveAsItem = new JMenuItem("Save As");
            saveAsItem.setAccelerator
                (KeyStroke.getKeyStroke(KeyEvent.VK_S,
                InputEvent.CTRL_DOWN_MASK+InputEvent.ALT_DOWN_MASK));
            exitItem = new JMenuItem("Exit");
            exitItem.setAccelerator
                (KeyStroke.getKeyStroke(KeyEvent.VK_F4,InputEvent.ALT_DOWN_MASK));
            mbar.add(makeMenu(fileMenu,
                new Object[]
                    {  "New",
                        openItem,
                        null,
                        saveItem,
                        saveAsItem,
                        null,
                        exitItem,
                    }, this));

      // demonstrate check box and radio button menus

      readonlyItem = new JCheckBoxMenuItem("Read-only");
      ButtonGroup group = new ButtonGroup();
      JRadioButtonMenuItem insertItem
         = new JRadioButtonMenuItem("Insert");
      insertItem.setSelected(true);
      JRadioButtonMenuItem overtypeItem
         = new JRadioButtonMenuItem("Overtype");
      group.add(insertItem);
      group.add(overtypeItem);

      // buid submenu
      JMenu optionMenu = new JMenu("Options");
      optionMenu.add(readonlyItem);
      optionMenu.addSeparator();
      optionMenu.add(insertItem);
      optionMenu.add(overtypeItem);
      // demonstrate icons and nested menus

      mbar.add(makeMenu("Edit",
         new Object[]
         {  new JMenuItem("Cut",
               new ImageIcon("images/cut.gif")),
            new JMenuItem("Copy",
               new ImageIcon("images/copy.gif")),
            new JMenuItem("Paste",
               new ImageIcon("images/paste.gif")),
            null,
            optionMenu,
/*            
            makeMenu("Options",
               new Object[]
               {  readonlyItem,
                  null,
                  insertItem,
                  overtypeItem
               },
               this)
*/               
         },
         this));

      // demonstrate mnemonics

      JMenu helpMenu = new JMenu("Help");
      helpMenu.setMnemonic('H');
      mbar.add(Box.createHorizontalGlue());   
      mbar.add(makeMenu(helpMenu,
         new Object[]
         {  new JMenuItem("Index", 'I'),
            new JMenuItem("About", 'A')
         },
         this));

      // demonstrate pop-ups

      popup = makePopupMenu(
         new Object[]
         {  "Cut",
            "Copy",
            "Paste"
         },
         this);

      getContentPane().addMouseListener(new MouseAdapter()
         {  
            @Override
            public void mouseReleased(MouseEvent evt)
            {  if (evt.isPopupTrigger())//In Windows the pop-up triger is right moudse button
                  popup.show(evt.getComponent(),
                     evt.getX(), evt.getY());
            }
         });
   }

   @Override
   public void actionPerformed(ActionEvent evt)
   {  String arg = evt.getActionCommand();
      System.out.println(arg);
      if(arg.equals("Exit")) {
         this.dispose();
         System.exit(0);
     }
   }

   @Override
   public void menuSelected(MenuEvent evt)
   {  saveItem.setEnabled(!readonlyItem.isSelected());
      saveAsItem.setEnabled(!readonlyItem.isSelected());
   }

   @Override
   public void menuDeselected(MenuEvent evt) {
   	System.out.println("File menu item is deselected");
   }

   @Override
   public void menuCanceled(MenuEvent evt) {
   	System.out.println("File menu is canceled");
   }

   public static JMenu makeMenu(Object parent,
      Object[] items, Object target)
   {  JMenu m = null;
      if (parent instanceof JMenu)
         m = (JMenu)parent;
      else if (parent instanceof String)
         m = new JMenu((String)parent);
      else
         return null;

      for (int i = 0; i < items.length; i++)
      {  if (items[i] == null)
            m.addSeparator();
         else
            m.add(makeMenuItem(items[i], target));
      }

      return m;
   }

   public static JMenuItem makeMenuItem(Object item,
      Object target)
   {  JMenuItem r = null;
      if (item instanceof String)
         r = new JMenuItem((String)item);
      else if (item instanceof JMenuItem)
         r = (JMenuItem)item;
      else return null;

      if (target instanceof ActionListener)
         r.addActionListener((ActionListener)target);
      return r;
   }

   public static JPopupMenu makePopupMenu
      (Object[] items, Object target)
   {  JPopupMenu m = new JPopupMenu();

      for (int i = 0; i < items.length; i++)
      {  if (items[i] == null)
            m.addSeparator();
         else
            m.add(makeMenuItem(items[i], target));
      }

      return m;
   }

   public static void main(String[] args) {
       
    EventQueue.invokeLater(new Runnable() {
       public void run(){
         JFrame frame = new MenuDemo();
         frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         frame.setSize( 300, 200 );
         frame.setVisible( true );
       }
    });
   }//end main
}//end class
