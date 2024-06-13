package practicaGUI_A;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;

public class Worker extends SwingWorker<List<Primos>, Void>{
    private int n;
    private int tipo;
    private Panel panel;

    public Worker(int n, int tipo, Panel panel) {
        this.n = n;
        this.tipo = tipo;
        this.panel = panel;
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
    protected List<Primos> doInBackground() throws Exception {
        List<Primos> primos = new ArrayList<>();
        long i = 2;
        long primoA = 0;
        long primoB = 0;
        int pos = 0;
        while (primos.size() < n) {
            if (esPrimo(i)) {
                if (tipo == 1) {
                    if (esPrimo(i + 2)) {
                        primoA = i;
                        primoB = i + 2;
                        primos.add(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeTwin("Calculando primos twin.." + "\n");
                    }
                } else if (tipo == 2) {
                    if (esPrimo(i + 4) || esPrimo(i - 4)) {
                        primoA = i;
                        primoB = i + 4;
                        primos.add(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeCousin("Calculando primos cousin.." + "\n");
                    }
                } else if (tipo == 3) {
                    if (esPrimo(i + 6) || esPrimo(i - 6)) {
                        primoA = i;
                        primoB = i + 6;
                        primos.add(new Primos(primoA, primoB, pos));
                        pos++;
                        panel.mensajeSexy("Calculando primos sexy.." + "\n");
                    }
                }
            }
            i++;
        }
        return primos;
    }

    public void done(){
        try{
            if(tipo == 1){
                panel.limpiaAreaTwin();
                panel.escribePrimosTwin(get());
                panel.mensaje("GUI creada\n");
            }else if(tipo == 2){
                panel.limpiaAreaCousin();
                panel.escribePrimosCousin(get());
                panel.mensaje("GUI creada\n");
            }else if(tipo == 3){
                panel.limpiaAreaSexy();
                panel.escribePrimosSexy(get());
                panel.mensaje("GUI creada\n");
            }
        }catch (InterruptedException e){
            System.out.println("Tarea interrumpida");
            e.printStackTrace();
        }catch (ExecutionException | CancellationException e) {
            System.out.println("Tarea cancelada");
            e.printStackTrace();
        }

    }


}
