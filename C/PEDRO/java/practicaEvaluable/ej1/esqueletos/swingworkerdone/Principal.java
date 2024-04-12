package swingworkerdone;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import java.awt.EventQueue;

public class Principal {
    public static void crearGUI(){
        JFrame frame = new JFrame("MonteCarlo");
        Panel panel = new Panel();
        Controlador ctr = new Controlador(panel);
        panel.setControlador(ctr);
        frame.setContentPane(panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.pack();
		frame.setVisible(true);
    }

    public static void main(String[] args) {
        // Hebra dispacher...
        EventQueue.invokeLater(new Runnable() {
			public void run() {
				crearGUI();
			}
		});
    }

}


