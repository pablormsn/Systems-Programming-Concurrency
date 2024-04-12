package ascensores;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;


public class EdificioS implements Edificio{
    private Semaphore subir = new Semaphore(1, true);  
    private Semaphore mutex = new Semaphore(1, true); 
    private List<Boolean> ascensores = new ArrayList<Boolean>();
    private List<Integer> usos = new ArrayList<Integer>();
    private int libres;
    private int Usos0 = 0;
    private int Usos1 = 0;
    private int Usos2 = 0;
    private int veces20 = 0;


    public  EdificioS(int n){
        libres = n;
        for(int i = 0; i < n; ++i){
            ascensores.add(false);
        }

        for(int i = 0; i < n; ++i){
            usos.add(0);

        }


    }
    @Override
    public int boardOnLift(int id) throws InterruptedException {
        
        subir.acquire();
        mutex.acquire();
        --libres;
        int idAscensor;
        int i = 0;
        while((i < ascensores.size()) && (ascensores.get(i) != false)){
            ++i;
        }
        idAscensor = i;
        ascensores.set(i, true);
        if(i == 0){
            ++Usos0;
            usos.set(i, Usos0 );
        }else if(i == 1){
            ++Usos1;
            usos.set(i, Usos1 );
        }else if(i == 2){
            ++Usos2;
            usos.set(i, Usos2 );
        }
        System.out.println("Persona " + id + " coge el ascensor " + idAscensor );
        if(libres > 0){
            subir.release();
        }
        mutex.release();
        
        return idAscensor;
    }

    @Override
    public void boardOffLift(int id, int liftId) throws InterruptedException {
        mutex.acquire();
        ++libres;
        ascensores.set(liftId, false);
        System.out.println("Persona " + id + " sale del ascensor " + liftId);
       
        if(libres == 1){
            subir.release();
        }
        if( (Usos0 + Usos1 + Usos2) == 20)veces20++;
        if(veces20 == 3){
            showUsage();
        }
        mutex.release();

        
    }

    @Override
    public void showUsage() {
        
        for(int i = 0; i < usos.size(); ++i){
            System.out.println("Ascensor " + i + " usado " + usos.get(i) + " veces");
        }
        
    }
    
}
