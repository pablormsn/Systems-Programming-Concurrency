package v2;

public class Contador_Peterson {
	private int valor;
	private volatile boolean f0, f1;
	private int turno;

	Contador_Peterson() {
		f0 = false;
		f1 = false;
		turno = 1;
		valor = 0;
	}
	public void incP0(int pId) {
		//control de acceso a la seccion critica
		f0 = true;
		turno = 1;
		while (f1 && turno == 1) Thread.yield();;
		//SC P0
		valor++;		
		System.out.println("P0 incrementa contador "+valor);
		
		//post-seccion critica
		f0 = false;
	}
	public void incP1(int pId) {
		//control de acceso a la seccion critica
		f1 = true;
		turno = 0;
		while(f0 && turno == 0) Thread.yield();
		valor++;		
		System.out.println("P1 incrementa contador "+valor);
		
		//post-seccion critica
		f1 = false;

	}
	public int get() {
		return valor;
	}
}
