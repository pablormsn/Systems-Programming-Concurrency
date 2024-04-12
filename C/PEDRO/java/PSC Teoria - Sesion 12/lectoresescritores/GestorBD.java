package lectoresescritores;

import java.util.concurrent.*;

public class GestorBD {

	public synchronized void entraLector(int id) {

		while(hayEscritor){
			wait();
		}
		System.out.println("Entra lector " + id + " Hay " + nLectores);

	}

	public void saleLector(int id) {
		nLectores--;
		System.out.println("Sale lector " + id + " Hay " + nLectores);

	}

	public void entraEscritor(int id) {
		while(hayEscritor || nLectores){
			wait();
		}
		System.out.println("                    Entra escritor " + id);
	}

	public void saleEscritor(int id) {
		hayEscritor = false;
		System.out.println("             Sale escritor " + id);
		notifyAll();
	}

}
// CS-Escritores: exclusion mutua
// CS-Lectores: puede haber varios pero nunca con un escritor