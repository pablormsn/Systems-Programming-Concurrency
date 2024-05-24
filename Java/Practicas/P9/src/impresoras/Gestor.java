package impresoras;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Gestor {
	private int impADisponibles;
	private int impBDisponibles;

	ReentrantLock l = new ReentrantLock();
	Condition colaDocTipoA = l.newCondition();
	Condition colaDocTipoB = l.newCondition();
	Condition colaDocTipoAB = l.newCondition();
	


	
	public Gestor(int impA, int impB){
		impADisponibles = impA;
		impBDisponibles = impB;
		
	
	}
	public void imprimirA(int id) throws InterruptedException{
		l.lock();
		try {
			while(impADisponibles == 0) {
				colaDocTipoA.await();
			}
			System.out.println("Documento id "+id+" tipo A ha cogido la impresora "+impADisponibles);
			impADisponibles--;
			System.out.println("Quedan "+impADisponibles+" impresoras A disponibles");
		}finally {
			l.unlock();
		}
		
	}
	public void imprimirB(int id) throws InterruptedException {
		l.lock();
		try {
			while(impBDisponibles == 0) {
				colaDocTipoB.await();
			}
			System.out.println("Documento id "+id+" tipo B ha cogido la impresora "+impBDisponibles);
			impBDisponibles--;
			System.out.println("Quedan "+impBDisponibles+" impresoras B disponibles");
		}finally {
			l.unlock();
		}
		
	}
	public int imprimirAB(int id) throws InterruptedException {
		l.lock();
		int tipo = 0;
		try {
			while(impADisponibles == 0 && impBDisponibles == 0) {
				colaDocTipoAB.await();
			}

			if(impADisponibles > 0) {
				tipo = 0;
				System.out.println("Documento id "+id+" tipo AB ha cogido la impresora "+impADisponibles);
				impADisponibles--;
				System.out.println("Quedan "+impADisponibles+" impresoras A disponibles");
			}else {
				tipo = 1;
				System.out.println("Documento id "+id+" tipo AB ha cogido la impresora "+impBDisponibles);
				impBDisponibles--;
				System.out.println("Quedan "+impBDisponibles+" impresoras B disponibles");
			}
		}finally {
			l.unlock();
		}
		return tipo;
		
		
	}
	public void liberar(int id, int tipo) { //tipo 0 => imp A || tipo 1=> impB
		l.lock();
		try {
			if(tipo == 0) {
				impADisponibles++;
				System.out.println("Documento id "+id+" tipo A ha liberado la impresora "+impADisponibles);
				colaDocTipoA.signal();
			}else if(tipo == 1) {
				impBDisponibles++;
				System.out.println("Documento id "+id+" tipo B ha liberado la impresora "+impBDisponibles);
				colaDocTipoB.signal();
			}
			else {
				if(impADisponibles > 0) {
					impADisponibles++;
					System.out.println("Documento id "+id+" tipo AB ha liberado la impresora "+impADisponibles);
					colaDocTipoAB.signal();
				}else {
					impBDisponibles++;
					System.out.println("Documento id "+id+" tipo AB ha liberado la impresora "+impBDisponibles);
					colaDocTipoAB.signal();
				}
			}
		}finally {
			l.unlock();
		}
		
	}

}
