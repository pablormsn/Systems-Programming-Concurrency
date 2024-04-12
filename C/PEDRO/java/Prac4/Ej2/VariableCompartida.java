
public class VariableCompartida {

	private int v;
	private boolean puedoEscribir = true;
	
	public void set(int valor) {
		while(!puedoEscribir) {
			Thread.yield();
		}
		v=valor;
		puedoEscribir = false;
	}
	
	public int get() {
		while(puedoEscribir) {
			Thread.yield();
		}
		puedoEscribir=true;
		return v;
	}
	
	public void inc() {
		v++;
	}
}
