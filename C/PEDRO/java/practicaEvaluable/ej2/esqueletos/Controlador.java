package esqueletos;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Controlador implements ActionListener, PropertyChangeListener{
	WorkerSeries workerS;
	WorkerMontecarlo workerM;
	private Panel panel;

	public Controlador(Panel panel) {
		this.panel = panel;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		workerS = new WorkerSeries( panel.getIteraciones(), panel);
		workerM = new WorkerMontecarlo( panel.getIteraciones(), panel);
		workerS.addPropertyChangeListener(this);
        workerM.addPropertyChangeListener(this);
		workerM.execute();
		workerS.execute();
		
	}

	@Override
	public void propertyChange(PropertyChangeEvent evento) {
	   if(evento.getPropertyName().equals("progress")){
        if(evento.getSource()==workerS){
            panel.setProgresoLeibniz((int)evento.getNewValue());
        }else{
        	panel.setProgresoMonteCarlo((int)evento.getNewValue());
        }
      }
    }

}
