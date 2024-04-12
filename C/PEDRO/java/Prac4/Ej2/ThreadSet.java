
public class ThreadSet extends Thread {

	private VariableCompartida var;
	
	public ThreadSet(VariableCompartida var) {
		this.var = var;
	}
	
	@Override
	public void run() {
		for(int i=0; i < 100; i++) {
			var.set(i);
		}
	}
}
