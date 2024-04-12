package recursos;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;


public class Control {
	private ReentrantLock l = new ReentrantLock();
	private int NUM;// numero total de recursos
	private int numRec;
	private LinkedList<Integer> cola = new LinkedList<Integer>();
	

	Condition colaSigue = l.newCondition(); 

	public Control(int num) {
		this.NUM = num;
		this.numRec = num;
	}

	public void qRecursos(int id, int num) throws InterruptedException {
		l.lock();
		try{
		cola.add(id);
		System.out.println("Proceso " + id + " pide " + num + " recursos. Quedan: " + numRec);
		while(num > numRec || cola.get(0) != id){
				System.out.println("Proceso " + id + " esperando en cola");
				colaSigue.await();

			}
			cola.removeFirst();
			numRec -= num;
			System.out.println("El proceso " + id + " ha cogido " + num + " recursos. Quedan: " + numRec);
			}finally{
			l.unlock();
		}
	}

	public void libRecursos(int id, int num) {
		l.lock();
		try{
		numRec = numRec + num;
		System.out.println("El proceso " + id + " ha liberado " + num + " recursos. Recursos totales: " + numRec);
		colaSigue.signalAll();
		}finally{
			l.unlock();
		}
	}
}
// CS-1: un proceso tiene que esperar su turno para coger los recursos
// CS-2: cuando es su turno el proceso debe esperar hasta haya recursos
// suficiente
// para él
