package impresoras;



import impresoras.SalaImpresoras;

import java.lang.reflect.Array;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.*;

import javax.swing.table.TableModel;

public class SalaImpresorasML implements SalaImpresoras{

    ArrayList<Boolean> impresoras = new ArrayList<Boolean>();
   Queue<Integer> colaClientes = new ArrayDeque<Integer>();
    private int NI;
    private int impresorasLibres = 3;
    private int idImpresora;
    ReentrantLock l = new ReentrantLock();
    Condition usarImpresoras = l.newCondition();
    private boolean hayImpresoras = true;;

    public SalaImpresorasML(int tam){
        NI = tam;
        for(int i = 0; i < NI; ++i){
            impresoras.add(false);
        }
    }
       
    
    @Override
    public int quieroImpresora(int id) throws InterruptedException {
        l.lock();
        try{
        System.out.println("Cliente " + id + " quiere impresora.");
        colaClientes.add(id);
        while(!hayImpresoras || colaClientes.peek() != id){
            usarImpresoras.await();
        }
        --impresorasLibres;
        if(impresorasLibres == 0){
        hayImpresoras = false;
        }
        colaClientes.poll();
        if(colaClientes.size() > 0)usarImpresoras.signalAll();
        int idImpresora = 0;
        int i = 0;
        while(i< impresoras.size() && (impresoras.get(i) == true)){
          ++i;
        }
        idImpresora = i;
        impresoras.set(i, true);
        idImpresora = i;
        System.out.println("        Cliente " + id + " coge impresora " + idImpresora + ". Impresoras disponibles: " + impresorasLibres);
        return idImpresora;
        }finally{
            l.unlock();
        }
    }

    @Override
    public void devuelvoImpresora(int id, int n) throws InterruptedException {
        l.lock();
        try{
        ++impresorasLibres;
        hayImpresoras = true;
        System.out.println("    Cliente " + id + " devuelve impresora " + n + ". Impresoras disponibles: " + impresorasLibres);
        impresoras.set(n, false);
        if(impresorasLibres == 1)usarImpresoras.signalAll();    
        }finally{
            l.unlock();
        }
    }

    
}
