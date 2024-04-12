package recursos;

import java.util.LinkedList;
import java.util.List;



public class Control {
	private int NUM;// numero total de recursos
	private int numRec;
	private LinkedList<Integer> cola = new LinkedList<Integer>();


	public Control(int num) {
		this.NUM = num;
		this.numRec = num;
	}

	public synchronized void qRecursos(int id, int num) throws InterruptedException {
		cola.add(id);
		System.out.println("Proceso " + id + " pide " + num + " recursos. Quedan: " + numRec);
		while(num > numRec || cola.get(0) != id){
			System.out.println("					El proceso " + id + " está esperando en la cola");
			wait();
		}
		cola.removeFirst();
		numRec = numRec - num;
		System.out.println("El proceso " + id + " ha cogido " + num + " recursos. Quedan: " + numRec);

	}

	public synchronized void libRecursos(int id, int num) {
		numRec = numRec + num;
		System.out.println("		El proceso " + id + " ha liberado " + num + " recursos. Recursos totales: " + numRec);
		notifyAll();

	}
}
// CS-1: un proceso tiene que esperar su turno para coger los recursos
// CS-2: cuando es su turno el proceso debe esperar hasta haya recursos
// suficiente
// para él
