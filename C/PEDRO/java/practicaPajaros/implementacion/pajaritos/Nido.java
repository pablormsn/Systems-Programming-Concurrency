package pajaritos;

import java.util.concurrent.*;

import javax.script.ScriptEngineManager;

public class Nido {
	private int B = 10; // Número máximo de bichos
	private int bichitos; // puede tener de 0 a B bichitos
	private Semaphore añadeBichito = new Semaphore(1, true);
	private Semaphore come = new Semaphore(0, true);
	private Semaphore mutex = new Semaphore(1, true);

	public void come(int id) throws InterruptedException {
		come.acquire();
		mutex.acquire();
		--bichitos;
		System.out.println("El bebé " + id + " ha comido un bichito. Quedan " + bichitos);
		if(bichitos == B - 1)añadeBichito.release();
		if(bichitos > 0)come.release();
		mutex.release();
	}

	public void nuevoBichito(int id) throws InterruptedException {
		// el papa/mama id deja un nuevo bichito en el nido
		añadeBichito.acquire();
		mutex.acquire();
		++bichitos;
		System.out.println("El papá " + id + " ha añadido un bichito. Hay " + bichitos);
		if(bichitos < B)añadeBichito.release();
		if(bichitos == 1)come.release();
		mutex.release();
	}
}

// CS-Bebe-i: No puede comer del nido si está vacío
// CS-Papa/Mama: No puede poner un bichito en el nido si está lleno
