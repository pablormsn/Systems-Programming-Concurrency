import java.util.List;
import java.util.ArrayList;

public class Nodo extends Thread {
	
	private List<Integer> lista;
	
	public Nodo(List<Integer> l) {
		lista=l;
	}
	
	private void añade(List<Integer> l, int desde, int hasta) {
		
		l.addAll(lista.subList(desde, hasta));
		
	}
	
	private void mezcla(List<Integer> l1, List<Integer> l2) {
		
		while(l1.size() > 0 && l2.size() > 0) {
			if(l1.get(0) <= l2.get(0)) {
				lista.add(l1.get(0));
				l1.remove(l1.get(0));
			} else {
				lista.add(l2.get(0));
				l2.remove(l2.get(0));
			}
		}
		
		lista.addAll(l1);
		lista.addAll(l2);
	}
	
	@Override
	public void run() {
		if(lista.size() > 1) {
			List<Integer> l1 = new ArrayList<Integer>();
			List<Integer> l2 = new ArrayList<Integer>();
			
			añade(l1, 0, lista.size()/2);
			añade(l2, lista.size()/2, lista.size());
			
			Nodo n1 = new Nodo(l1);
			Nodo n2 = new Nodo(l2);
			
			n1.start();
			n2.start();
			
			try {
				n1.join();
				n2.join();
				
				lista.clear();
				mezcla(l1, l2);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
