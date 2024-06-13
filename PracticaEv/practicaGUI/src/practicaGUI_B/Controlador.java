package practicaGUI_B;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Controlador implements ActionListener {
    private Panel panel;
    private Worker worker1;
    private Worker worker2;
    private Worker worker3;

    public Controlador(Panel panel) {
        this.panel = panel;
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(e.getActionCommand().equals("NUMERO1")){
            int n = panel.numero1();
            worker1 = new Worker(n, 1, panel);
            worker1.execute();
        } else if(e.getActionCommand().equals("NUMERO2")){
            int n = panel.numero2();
            worker2 = new Worker(n, 2, panel);
            worker2.execute();
        } else if(e.getActionCommand().equals("NUMERO3")){
            int n = panel.numero3();
            worker3 = new Worker(n, 3, panel);
            worker3.execute();
        } else if(e.getActionCommand().equals("FIN")){
            if(worker1 != null) worker1.cancel(true);
            if(worker2 != null) worker2.cancel(true);
            if(worker3 != null) worker3.cancel(true);
        }
    }

}
