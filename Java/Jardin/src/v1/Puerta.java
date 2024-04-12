package v1;

public class Puerta extends Thread {
	private Contador visitantes;
	private int id;
	private int iter;
	
	public Puerta(int id, Contador v, int iter) {
		visitantes = v;
		this.id = id;
		this.iter =iter;
	}
	public void run() {		
		for(int i = 0; i< iter; i++) {				
			visitantes.inc(id);					
		}
		
	}
}
