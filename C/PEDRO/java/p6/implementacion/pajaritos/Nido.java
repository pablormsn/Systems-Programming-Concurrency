package pajaritos;

import java.util.concurrent.*;

public class Nido {
	private int B = 10; // Número máximo de bichos
	private int numBichitos; // puede tener de 0 a B bichitos
	private Semaphore mutex = new Semaphore(1);
	private Semaphore hayHueco = new Semaphore(1);
	private Semaphore hayBichitos = new Semaphore(0);

	public void come(int id) throws InterruptedException {
		hayBichitos.acquire();
		mutex.acquire();
		numBichitos--;
		System.out.println("El bebé " + id + " ha comido un bichito. Quedan " + numBichitos);
		if(numBichitos>0)hayBichitos.release();
		if(numBichitos == B - 1)hayHueco.release();
		mutex.release();
	}

	public void nuevoBichito(int id) throws InterruptedException {
		// el papa/mama id deja un nuevo bichito en el nido
		hayHueco.acquire();
		mutex.acquire();
		numBichitos++;
		System.out.println("El papá " + id + " ha añadido un bichito. Hay " + numBichitos);
		if(numBichitos<B)hayHueco.acquire();
		if(numBichitos == 1)hayBichitos.release();
		mutex.release();
	}
}

// CS-Bebe-i: No puede comer del nido si está vacío
// CS-Papa/Mama: No puede poner un bichito en el nido si está lleno
