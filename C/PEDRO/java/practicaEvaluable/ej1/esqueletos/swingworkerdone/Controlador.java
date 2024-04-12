package swingworkerdone;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Controlador implements ActionListener {

	private Panel panel;

	public Controlador(Panel panel) {
		this.panel = panel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		int it = panel.getIteraciones();
		 WorkerMontecarlo workerM = new WorkerMontecarlo(it);
		 WorkerSeries workerS = new WorkerSeries(it);
		 panel.escribePI1(workerM.procesar());
         panel.escribePI2(workerS.procesar());
	}

}
