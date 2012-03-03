import javax.swing.JApplet;


public class CalculatorApplet extends JApplet{
	
	@Override
	public void init(){
		super.init();
		CalculatorView view = new CalculatorView();
		setContentPane(view);
	}
	
}
