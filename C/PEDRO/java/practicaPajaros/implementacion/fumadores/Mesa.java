package fumadores;

import java.util.concurrent.*;

public class Mesa {

	// esta es una implementación pasiva para los fumadores
	// los van a despertar cuando tengan que fumar.

	public Mesa() {

	}

	public void qFumar(int id) {

		System.out.println("Fumador " + id + " coge los ingredientes");

	}

	public void finFumar(int id) {
		System.out.println("Fumador " + id + " ha terminado de fumar");

	}

	public void nuevosIng(int ing) { // se pasa el ingrediente que no se pone

		System.out.print("El agente ha puesto los ingredientes ");

	}

}

// CS-Fumador i: No puede fumar hasta que el fumador anterior no ha terminado
// de fumar y sus ingredientes están sobre la mesa
// CS-Agente: no puede poner nuevos ingredientes hasta que el fumador anterior
// no ha terminado de fumar
