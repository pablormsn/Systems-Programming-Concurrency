package ascensores;

public class Principal {
	public static final int NUM_LIFTS = 3;
	public static final int NUM_PERSONS = 20;

	public static void main(String[] args) throws InterruptedException {
		EdificioS b = new EdificioS(NUM_LIFTS); // EdificioML b = new EdificioML(NUM_LIFTS);
		Thread[] p = new Thread[NUM_PERSONS];
		for (int i = 0; i < NUM_PERSONS; i++) {
			p[i] = new Thread(new Persona(i, b));
			p[i].start();
		}
		
		// FALTA. Escribe el código para mostrar el uso de los ascensores.

	}
}
