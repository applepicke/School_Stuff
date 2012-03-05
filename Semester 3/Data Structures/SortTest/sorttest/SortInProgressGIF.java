/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package sorttest;

/**
 *
 * @author Rex
 */
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JPanel;

public class SortInProgressGIF implements Runnable {
	//private ImageIcon iiTestImage;
  private volatile boolean bRunning;
  JPanel jpSortInProgress;

  public void killAnimation() { bRunning = false; }

	public SortInProgressGIF(JPanel jpSortInProgress) { // throws InterruptedException required by Thread.sleep() method call
    this.jpSortInProgress = jpSortInProgress;
	}

  public void run() {
		//iiTestImage = new ImageIcon("boingdragon.gif");// other image files "smiley-peeking-1.gif", "smiley-peeking-2.gif", "smiley-peeking-3.gif", "SmileyAngel.gif", "SmileyAlien.gif"

		// standard GUI code to spawn the application frame (JFrame) and add a JPanel as a drawing surface.
		//jfApplication = new JFrame();
		//jfApplication.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//jfApplication.setTitle("GIF");
		//jfApplication.setSize(180, 100);
		//jfApplication.setVisible(true);

		// loop to force a repaint so that animation will be seen
    bRunning = true;
		while (bRunning) {
			jpSortInProgress.repaint();
      try {
        Thread.sleep(200);
      } catch (InterruptedException ex) {
        Logger.getLogger(SortInProgressGIF.class.getName()).log(Level.SEVERE, null, ex);
      }
		}
  }

  /*
	// standard CALLBACK method that is called as a consequence of the method call jfApplication.repaint()
	@SuppressWarnings("serial")
	public class Panel extends JPanel {
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			Graphics2D g2 = (Graphics2D) g;

			iiTestImage.paintIcon(null, g2, 20, 10);
		}
	}
   *
   */
}
