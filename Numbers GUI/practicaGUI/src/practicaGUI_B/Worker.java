package practicaGUI_B;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;

public class Worker extends SwingWorker<Void,Primos>{
    private int n;
    private int tipo;
    private Panel panel;

    public Worker(int n, int tipo, Panel panel) {
        this.n = n;
        this.tipo = tipo;
        this.panel = panel;
        if(tipo == 1){
            panel.limpiaAreaTwin();
        }else if(tipo == 2){
            panel.limpiaAreaCousin();
        }else if(tipo == 3){
            panel.limpiaAreaSexy();
        }
    }

    //Calcula si un número es primo
    private boolean esPrimo(long n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    protected Void doInBackground() throws Exception {
        long i = 2;
        long primoA = 0;
        long primoB = 0;
        int pos = 0;
        while (pos < n && !isCancelled()) {
            if (esPrimo(i)) {
                if (tipo == 1) {
                    if (esPrimo(i + 2)) {
                        primoA = i;
                        primoB = i + 2;
                        publish(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeTwin("Calculando primos twin.." + "\n");
                    }
                } else if (tipo == 2) {
                    if (esPrimo(i + 4) || esPrimo(i - 4)) {
                        primoA = i;
                        primoB = i + 4;
                        publish(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeCousin("Calculando primos cousin.." + "\n");
                    }
                } else if (tipo == 3) {
                    if (esPrimo(i + 6) || esPrimo(i - 6)) {
                        primoA = i;
                        primoB = i + 6;
                        publish(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeSexy("Calculando primos sexy.." + "\n");
                    }
                }
            }
            i++;
        }
        return null;
    }

    public void done(){
        try{
            get();
            panel.mensaje("GUI creada\n");
        }catch (ExecutionException e){
            System.out.println("Error en la tarea");
            e.printStackTrace();
        }catch (CancellationException e){
            System.out.println("Tarea cancelada");
            e.printStackTrace();
        }catch (InterruptedException e){
            System.out.println("Tarea interrumpida");
            e.printStackTrace();
        }
    }


    @Override
    protected void process(List<Primos> lista) {
        try{
            if (tipo == 1) {
                panel.escribePrimosTwin(lista);
            } else if (tipo == 2) {
                panel.escribePrimosCousin(lista);
            } else if (tipo == 3) {
                panel.escribePrimosSexy(lista);
            }
        }catch (CancellationException e) {
            System.out.println("Tarea cancelada");
            e.printStackTrace();
        }

    }
}
