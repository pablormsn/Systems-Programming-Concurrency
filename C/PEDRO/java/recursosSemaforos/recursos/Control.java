package recursos;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;


public class Control {
	private int NUM;// numero total de recursos
	private int numRec;
	private int numAct;
	private Semaphore mutex = new Semaphore(1, true);
	private Semaphore hayRecursoSuf = new Semaphore(1, true);
	

	public Control(int num) {
		this.NUM = num;
		this.numRec = num;
	}

	public void qRecursos(int id, int num) throws InterruptedException {
		hayRecursoSuf.acquire();
		mutex.acquire();
		numRec-=num;
		System.out.println("Proceso " + id + " pide " + num + " recursos. Quedan: " + numRec);
		mutex.release();
	}
	
	public void libRecursos(int id, int num) throws InterruptedException{
		mutex.acquire();
		numRec += num;
		System.out.println("El proceso " + id + " ha liberado " + num + " recursos. Recursos totales: " + numRec);
		if(numAct < numRec) {
			hayRecursoSuf.release();
		}
		mutex.release();
	}
}	
// CS-1: un proceso tiene que esperar su turno para coger los recursos
// CS-2: cuando es su turno el proceso debe esperar hasta haya recursos
// suficiente
// para él
