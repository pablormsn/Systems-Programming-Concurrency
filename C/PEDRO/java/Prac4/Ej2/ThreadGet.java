
public class ThreadGet extends Thread {

private VariableCompartida var;
	
	public ThreadGet(VariableCompartida var) {
		this.var = var;
	}
	
	@Override
	public void run() {
		for(int i=0; i < 100; i++) {
			System.out.println(var.get());
		}
	}
}
