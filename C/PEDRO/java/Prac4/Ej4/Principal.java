import java.util.List;
import java.util.ArrayList;
import java.util.Random;

public class Principal {

	public static void main(String[] args) {
		Random random = new Random();
		List<Integer> lista = new ArrayList<Integer>();
		for(int i=0; i < 100; i++) {
			lista.add(random.nextInt(100));
		}
		System.out.print("Lista sin ordenar: "+lista+ "\n");
		
		
		Nodo raiz= new Nodo(lista);
		raiz.start();
		
		try {
			raiz.join();
			System.out.println("Lista ordenada: "+lista);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
