package esqueletos;
import javax.swing.JFrame;
import javax.swing.SwingUtilit1ies;
import java.awt.EventQueue;

public class Principal {


    public static void crearGUI(){
        Panel panel = new Panel();
        Controlador control = new Controlador(panel);
        panel.setControlador(control);
        JFrame ventana = new JFrame("MonteCarlo");
        ventana.setContentPane(panel);
        ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.pack();
		ventana.setVisible(true);
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


