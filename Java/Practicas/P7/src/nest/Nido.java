package nido;
import java.util.concurrent.Semaphore;

public class Nido {
	private final int maxBichos;
	private volatile int bichitos;
	private Semaphore puedeComer, puedePoner, mutex;
	
	
	public Nido(int max) {
		//TODO
		maxBichos = max;
		puedePoner = new Semaphore(1);
		puedeComer = new Semaphore(0);
		mutex = new Semaphore(1);
		bichitos = 0;


	}
	
	public void depositarBicho(int id) throws InterruptedException {
		//TODO
		puedePoner.acquire();//Pone el semáforo en 0 para que nadie más pueda poner mientras se pone el bicho
		mutex.acquire(); //Pone el semáforo en 0 para que nadie más pueda acceder a la variable bichitos
		System.out.println("Padre "+id+ " ha depositado un bichito");
		bichitos++;
		System.out.println("Bichitos en el nido: "+bichitos);
		if(bichitos<maxBichos){
			puedePoner.release();//si no esta lleno, puede poner. Release pone el semaforo en 1
		}
		if(bichitos == 1){
			puedeComer.release();//si no esta vacio, puede comer. Release pone el semaforo en 1
		}
		mutex.release(); //Libera el semáforo para que otro pueda acceder a la variable bichitos
	}
	public void comerBicho(int id) throws InterruptedException {
		//TODO
		puedeComer.acquire();//Pone el semáforo en 0 para que nadie más pueda comer mientras se come el bicho
		mutex.acquire(); //Pone el semáforo en 0 para que nadie más pueda acceder a la variable bichitos
		System.out.println("Polluelo "+id+ " ha comido un bichito");
		bichitos--;
		System.out.println("Bichitos en el nido: "+bichitos);
		if(bichitos>0){
			puedeComer.release();//si no esta vacio, puede comer. Release pone el semaforo en 1
		}
		if(bichitos == (maxBichos-1)){
			puedePoner.release();//si no esta lleno, puede poner. Release pone el semaforo en 1
		}
		mutex.release(); //Libera el semáforo para que otro pueda acceder a la variable bichitos
	}
	
	public static void main(String[] args) {
		Nido nido = new Nido(7);
		Pajaro p0 = new Pajaro(0,nido);
		Pajaro p1 = new Pajaro(1, nido);
		Polluelo polluelos[] = new Polluelo[5];
		for(int i = 0; i < 5; i++)
			polluelos[i] = new Polluelo(i, nido);
		p0.start();
		p1.start();
		for(int i = 0; i < 5; i++)
			polluelos[i] .start();
		
		
		try {
			Thread.sleep(2000);
			p0.interrupt();
			p1.interrupt();
			for(int i = 0; i < 5; i++)
				polluelos[i].interrupt();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	

}

