package semaforos;

import java.util.concurrent.Semaphore;

public class Tiovivo {
	private final int N = 5;
	private volatile int nPasajeros = 0;
	private Semaphore puedeSubir = new Semaphore(1);
	private Semaphore puedeBajar = new Semaphore(0);
	private Semaphore puedeEmpezar = new Semaphore(0);
	private Semaphore mutex = new Semaphore(1);

	public void subir(int id) throws InterruptedException
	{	
	//TODO
		puedeSubir.acquire();
		mutex.acquire();
			System.out.println("El pasajero " + id + " sube al tiovivo");
			nPasajeros++;
			System.out.println("Hay " + nPasajeros + " pasajeros en el tiovivo");
			if(nPasajeros < N)
			{
				puedeSubir.release();
			}
			else
			{
				puedeEmpezar.release();
			}
		mutex.release();
	}
	
	public void bajar(int id) throws InterruptedException
	{
		//TODO
		puedeBajar.acquire();
		mutex.acquire();
			System.out.println("El pasajero " + id + " baja del tiovivo");
			nPasajeros--;
			System.out.println("Hay " + nPasajeros + " pasajeros en el tiovivo");
			if (nPasajeros > 0)
			{
				puedeBajar.release();
			}
			else
			{
				puedeSubir.release();
			}
		mutex.release();
	}
	
	public void esperaLleno () throws InterruptedException
	{
		//TODO
		puedeEmpezar.acquire();
		System.out.println("***Tiovivo lleno. Empieza el viaje!!***");

	}
	
	public void finViaje () 
	{
		//TODO
		System.out.println("El tiovivo ha terminado de girar");
		puedeBajar.release();
	}
}
