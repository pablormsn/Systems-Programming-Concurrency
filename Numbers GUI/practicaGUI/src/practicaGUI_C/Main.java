package practicaGUI_C;

import javax.swing.*;

public class Main {
    public static void crearGUI(){
        if(SwingUtilities.isEventDispatchThread()){
            System.out.println("Es una hebra dispatcher");
        }

        JFrame ventana = new JFrame("Numeros primos");

        Panel panel = new Panel();
        ControladorBarraTwin controladorBarraTwin = new ControladorBarraTwin(panel);
        ControladorBarraCousin controladorBarraCousin = new ControladorBarraCousin(panel);
        ControladorBarraSexy controladorBarraSexy = new ControladorBarraSexy(panel);
        Controlador controlador = new Controlador(panel, controladorBarraTwin, controladorBarraCousin, controladorBarraSexy);
        panel.controlador(controlador);
        ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        ventana.setContentPane(panel);
        ventana.pack();
        ventana.setVisible(true);
    }

    public static void main(String[] args){
        SwingUtilities.invokeLater(new Runnable(){
            @Override
            public void run(){
                crearGUI();
            }
        });
    }
}
