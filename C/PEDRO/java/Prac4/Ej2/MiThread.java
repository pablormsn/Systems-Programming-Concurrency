
public class MiThread extends Thread {

	private VariableCompartida var;
	
	public MiThread(VariableCompartida var) {
		this.var = var;
	}
	
	@Override
	public void run() {
		for(int i=0; i < 1000; i++) {
			var.inc();
		}
	}
}
