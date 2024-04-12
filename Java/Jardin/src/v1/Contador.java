package v1;

public class Contador {
	private int valor;
	
	public Contador() {
		valor = 0;
	}
	public void inc(int pId) {
		valor++;		
		//System.out.println("P"+pId+" incrementa contador "+valor);
	}
	public int get() {
		return valor;
	}
}
