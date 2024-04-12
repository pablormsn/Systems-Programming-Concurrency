public class Principal {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MiThread t1 = new MiThread(10, 'a');
		MiThread t2 = new MiThread(10, 'z');
		MiThread t3 = new MiThread(10, 'm');
		
		t1.start();
		t2.start();
		t3.start();

	}

}
