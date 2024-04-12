package blectoresescritoresjusto;

import java.util.concurrent.Semaphore;

public class GestorBD {

	private int nLectores = 0;
	private boolean hayEscritor = false;
	private int EscritorEntrar = 0;

	public synchronized void entraLector(int id) throws InterruptedException {

		while ( hayEscritor ||EscritorEntrar > 0) {
			wait();
		}
		nLectores++;
		System.out.println("Entra lector " + id + ", hay " + nLectores + " lectores");

	}

	public synchronized void saleLector(int id) throws InterruptedException {

		nLectores--;

		System.out.println("Sale lector " + id + ", hay " + nLectores + " lectores");

		if (nLectores == 0)
			notify();

	}

	public synchronized void entraEscritor(int id) throws InterruptedException {
		++EscritorEntrar;
		System.out.println("Quiero entrar, escritores en cola: " + EscritorEntrar);
		while (nLectores > 0 || EscritorEntrar > 0) {
			wait();
		}
		hayEscritor = true;
		System.out.println("                    Entra escritor " + id);
	}

	public synchronized void saleEscritor(int id) throws InterruptedException {

		hayEscritor = false;
		System.out.println("                    Sale escritor " + id);
		if(EscritorEntrar == 0){
			notifyAll();
		}
	}

}