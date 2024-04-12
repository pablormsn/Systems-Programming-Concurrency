
public class Principal {

	public static void main(String[] args) {
		
		VariableCompartida var = new VariableCompartida();
		ThreadSet tSet = new ThreadSet(var);
		ThreadGet tGet = new ThreadGet(var);
		
		/*
		MiThread t1 = new MiThread(var);
		MiThread t2 = new MiThread(var);
		
		
		t1.start();
		t2.start();
		
		try {
			t1.join();
			t2.join();
			
			System.out.println("Valor variable compartida: " + var.get());
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
		tSet.start();
		tGet.start();
			
	}

}
