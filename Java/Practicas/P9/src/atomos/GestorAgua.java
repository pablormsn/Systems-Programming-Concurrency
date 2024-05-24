package atomos;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/*
* CS: Solo pueden entrar 2 atomos de hidrogeno y 1 de oxigeno
* CS: Hasta qque no se forme molecula (H20) => ningun atomo sale
* l: lock
* CONDICIONES: -puedenEntrarH
* 				-puedenEntrarO
* 				-moleculaFormada
* */

public class GestorAgua {
	private int atomosH = 0;
	private boolean atomosO = false;

	ReentrantLock l = new ReentrantLock();
	Condition puedenEntrarH = l.newCondition();
	Condition puedenEntrarO = l.newCondition();
	Condition moleculaFormada = l.newCondition();

	public void hListo(int id) throws InterruptedException {
		//ENTRA UN ATOMO DE HIDROGENO
		l.lock();
		try{
			while (atomosH == 2){
				puedenEntrarH.await();
			}
			System.out.println("Atomo de hidrogeno " + id + " ha entrado");
			atomosH++;
			if (atomosH == 2 && atomosO){
				moleculaFormada.signalAll();
				System.out.println("Molecula de agua formada");
			}

			if(atomosH<2 || !atomosO){
				moleculaFormada.await();
			}
			System.out.println("Atomo de hidrogeno " + id + " ha salido");
			atomosH--;

			if (atomosH == 0){
				puedenEntrarH.signalAll();
			}
		}
		finally {
			l.unlock();
		}
	}
	
	public void oListo(int id) throws InterruptedException { 
		//ENTRA UN ATOMO DE OXIGENO
		l.lock();
		try{
			while (atomosO){
				puedenEntrarO.await();
			}
			System.out.println("Atomo de oxigeno " + id + " ha entrado");
			atomosO = true;
			if (atomosH == 2){
				moleculaFormada.signalAll();
				System.out.println("Molecula de agua formada");
			}
			if(atomosH<2){
				moleculaFormada.await();
			}
			System.out.println("Atomo de oxigeno " + id + " ha salido");
			atomosO = false;
			puedenEntrarO.signalAll();
		}
		finally {
			l.unlock();
		}

	}
}