package impresoras;



import impresoras.SalaImpresoras;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.concurrent.Semaphore;

import javax.swing.table.TableModel;

public class SalaImpresorasML implements SalaImpresoras{

    ArrayList<Boolean> impresoras = new ArrayList<Boolean>();
    private int NI;
    private int impresorasLibres = 3;
    private Semaphore mutex = new Semaphore(1, true);
    private Semaphore impresorasLlenas = new Semaphore(1, true);
    private Semaphore puedoLiberar = new Semaphore(0, true);
    private int idImpresora;
    public SalaImpresorasML(int tam){
        NI = tam;
        for(int i = 0; i < NI; ++i){
            impresoras.add(false);
        }
    }
       
    
    @Override
    public int quieroImpresora(int id) throws InterruptedException {
        System.out.println("Cliente " + id + " quiere impresora.");
        impresorasLlenas.acquire();
        mutex.acquire();
        --impresorasLibres;
        int i = 0;
        while(i< impresoras.size() && (impresoras.get(i) == true)){
          ++i;
        }
        idImpresora = i;
        impresoras.set(i, true);
       // puedoLiberar.release();
        System.out.println("        Cliente " + id + " coge impresora " + idImpresora + ". Impresoras disponibles: " + impresorasLibres);
        if(impresorasLibres > 0){
            impresorasLlenas.release();
        }
        mutex.release();
        return idImpresora;

    }

    @Override
    public void devuelvoImpresora(int id, int n) throws InterruptedException {
        //puedoLiberar.acquire();
        mutex.acquire();
        ++impresorasLibres;
        System.out.println("    Cliente " + id + " devuelve impresora " + n + ". Impresoras disponibles: " + impresorasLibres);
        impresoras.set(n, false);
        if(impresorasLibres == 1)impresorasLlenas.release();
        mutex.release();

    }

    
}
