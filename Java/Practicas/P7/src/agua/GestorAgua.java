package agua;

import java.util.concurrent.Semaphore;

/*
* CS
* -Solo entra 1 atomo de oxigeno (Oxigeno)
* -Solo entran 2 atomos de hidrogeno (Hidrogeno)
* -Los atomos esperan hasta que se forme la molecula (GestorAgua)
* -Cuando se forma la molecula, salen los atomos y pueden volver(GestorAgua)
* */

public class GestorAgua {
	private int atomosH;
	private int atomosO;
	private int atomos;

	private Semaphore puedeEntrarH, puedeEntrarO, moleculaFormada, mutex;
	
	
	public GestorAgua() {
		//TODO
		atomosH = 0;
		atomosO = 0;
		atomos = 0;
		puedeEntrarH = new Semaphore(1);
		puedeEntrarO = new Semaphore(1);
		moleculaFormada = new Semaphore(0);
		mutex = new Semaphore(1);

	}
	
	
	public void hListo(int id) throws InterruptedException {
		//TODO
		puedeEntrarH.acquire();
			mutex.acquire();
				System.out.println("Atomo de Hidrogeno con id " + id + " ha entrado al gestor");
				atomosH++;
				System.out.println("atomoH: " + atomosH);
				atomos++;
				System.out.println("atomos: " + atomos);
				if (atomos<3){
					if(atomosH < 2){
						puedeEntrarH.release();
					}
					mutex.release();
					moleculaFormada.acquire();
				}

	}
	
	public void oListo(int id) throws InterruptedException {
		//TODO			
	}
	
	public static void main(String[] args) {
		GestorAgua gestor = new GestorAgua();
		Oxigeno oxigenos[] = new Oxigeno[5];
		Hidrogeno hidrogenos[] = new Hidrogeno[5];
		for(int i = 0 ; i < 5; i++) {
			oxigenos[i] = new Oxigeno(i, gestor);
			hidrogenos[i] = new Hidrogeno(i, gestor);
		}

		for(int i = 0 ; i < 5; i++) {
			oxigenos[i].start();
			hidrogenos[i].start();
		}
	}

}
