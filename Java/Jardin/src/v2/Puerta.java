package v2;

public class Puerta extends Thread {
	private Contador_Peterson visitantes;
	private int id;
	private int iter;
	
	public Puerta(int id, Contador_Peterson v, int iter) {
		visitantes = v;
		this.id = id;
		this.iter =iter;
	}
	public void run() {		
		for(int i = 0; i< iter; i++) {
			if(id == 0)
				visitantes.incP0(id);
			else
				visitantes.incP1(id);
		}
		
	}
}
