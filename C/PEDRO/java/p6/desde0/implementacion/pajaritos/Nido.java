package pajaritos;

import java.util.concurrent.*;

public class Nido {
	private int B = 10; // Número máximo de bichos
	private int bichitos; // puede tener de 0 a B bichitos

	public void come(int id) {

		System.out.println("El bebé " + id + " ha comido un bichito. Quedan " + bichitos);

	}

	public void nuevoBichito(int id) {
		// el papa/mama id deja un nuevo bichito en el nido

		System.out.println("El papá " + id + " ha añadido un bichito. Hay " + bichitos);

	}
}

// CS-Bebe-i: No puede comer del nido si está vacío
// CS-Papa/Mama: No puede poner un bichito en el nido si está lleno
