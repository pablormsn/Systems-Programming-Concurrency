package agua;


import java.util.concurrent.*;

public class GestorAgua {
	int agua=0;
	int oTotal=0;
	int hTotal=0;
	int contH=2;
	int contO=1;
	
	Semaphore oxigeno=new Semaphore(1,true); 
	Semaphore hidrogeno=new Semaphore(1,true); 
	Semaphore h2o=new Semaphore(0,true);
	
	Semaphore mutex1=new Semaphore(1,true); 
	Semaphore mutex2=new Semaphore(1,true);
	Semaphore mutex3=new Semaphore(1,true);
	Semaphore mutex4=new Semaphore(1,true);
	
	public void hListo(int id) throws InterruptedException{ 
		mutex1.acquire();
		hTotal++;
		System.out.println("H = "+hTotal); 
		mutex1.release();
		
		hidrogeno.acquire(); 
		
		mutex2.acquire();
		contH--;
		if(contH>0) { //si todavia falta otra, lo liberamos
			hidrogeno.release();
		} 
		mutex2.release();
		
		System.out.println("H ACEPTADO");
		if(contH==0 && contO==0) {
			h2o.release();
		}
		
	}
	
	public void oListo(int id) throws InterruptedException{ 
		mutex3.acquire();
		oTotal++;
		System.out.println("O = "+oTotal); 
		mutex3.release();
		
		oxigeno.acquire();
		
		mutex4.acquire();
		contO--;
		mutex4.release();
		System.out.println("O ACEPTADO");
		if(contH==0 && contO==0) {
			h2o.release();
		}

	}
	
	public void molecLista() throws InterruptedException {
		h2o.acquire();
		mutex1.acquire();
		oTotal--;
		hTotal-=2;
		System.out.println("H2O GENERADO O = "+oTotal+" // H = "+hTotal); agua++;
		contO=1;
		contH=2; 
		mutex1.release();
		oxigeno.release();
        hidrogeno.release();
	}
}