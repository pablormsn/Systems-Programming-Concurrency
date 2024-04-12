package impresoras;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.*;

import impresoras.SalaImpresoras;

public class SalaImpresorasML implements SalaImpresoras{
    private int numImpresoras;
    List<Boolean> impresoras = new LinkedList<Boolean>(Arrays.asList(false, false, false));
    List<Integer> clientes = new LinkedList<Integer>();
    private int impresorasDisponibles;
    boolean hayImpresoras = true;

    public SalaImpresorasML(int n){
        this.numImpresoras = n;
        impresorasDisponibles = n;
    }

    @Override
    public synchronized int quieroImpresora(int id) throws InterruptedException {
        clientes.add(id);
        System.out.println("El cliente " + id + " quiere impresora");
        while(!hayImpresoras || (clientes.get(0) != id))wait();
        --impresorasDisponibles;
        if(impresorasDisponibles == 0){
            hayImpresoras = false;
        }
        clientes.remove(0);
        if(clientes.size() > 0 )notifyAll();
        int i = 0;
        int idImpresora;
        while(i < impresoras.size() && impresoras.get(i) == true){
            ++i;
        }
        idImpresora = i;
        impresoras.set(i,true );
        System.out.println("El cliente " + id + " coge impresora " + idImpresora + ". Quedan " + impresorasDisponibles);


        return idImpresora;
    }

    @Override
    public synchronized void devuelvoImpresora(int id, int n) throws InterruptedException {
        ++impresorasDisponibles;
        hayImpresoras = true;
        System.out.println("El cliente " + id + " devuelve la impresora " + n + ". Impresoras disponibles: " + impresorasDisponibles);
        impresoras.set(n, false);
        if(impresorasDisponibles == 1){
            notifyAll();
        }
    }


}
