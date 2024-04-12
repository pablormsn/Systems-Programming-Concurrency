package prPractica4PSYCej5;

public class Principal {

	public static void main(String[] args) {
		int num = 10;
		NodoFib n = new NodoFib(num);
		Thread t = new Thread(n);
		t.start();
		try {
			t.join();
			System.out.print("El fibonacci de " + num + " es: " +n.getRes());
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

}
