package mesaLocks;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
public class Mesa {
    //0 - piedra, 1 - papel, 2 - tijeras

	private ReentrantLock l = new ReentrantLock();
	private Condition esperaJugadas = l.newCondition();
	private Condition finalizar = l.newCondition();
	private List<Integer> lista = new ArrayList<>();
	private int ganador = -1;
	private boolean finalizado = false;

	public Mesa(){
		for (int i = 0; i < 3; i++) {
			lista.add(-1);
		}
	}
	
	/**
	 * 
	 * @param jug jugador que llama al m�todo (0,1,2)
	 * @param juego jugada del jugador (0-piedra,1-papel, 2-tijeras)
	 * @return  si ha habido un ganador en esta jugada se devuelve 
	 *          la jugada ganadora
	 *         o -1, si no ha habido ganador
	 * @throws InterruptedException
	 * 
	 * El jugador que llama a este m�todo muestra su jugada, y espera a que 
	 * est�n la de los otros dos. 
	 * Hay dos condiciones de sincronizaci�n
	 * CS1- Un jugador espera en el m�todo hasta que est�n las tres jugadas
	 * CS2- Un jugador tiene que esperar a que finalice la jugada anterior para
	 *     empezar la siguiente
	 * 
	 */
	public int nuevaJugada(int jug,int juego) throws InterruptedException{
		
		l.lock();

		try{

			while(lista.get(jug) != -1){
				esperaJugadas.await();
			}

			if(finalizado){
				finalizado = false;
			}

			lista.set(jug, juego);

			System.out.println("Jugador " + jug + " pone " + juego);

			if (!lista.contains(-1)) {
				if (lista.get(0) == 0 && lista.get(1) == 2 && lista.get(2) == 2 || 
				lista.get(0) == 1 && lista.get(1) == 0 && lista.get(2) == 0 ||
				lista.get(0) == 2 && lista.get(1) == 1 && lista.get(2) == 1) {
					ganador = 0;	
				}else if (lista.get(1) == 0 && lista.get(0) == 2 && lista.get(2) == 2 || 
				lista.get(1) == 1 && lista.get(0) == 0 && lista.get(2) == 0 ||
				lista.get(1) == 2 && lista.get(0) == 1 && lista.get(2) == 1) {
					ganador = 1;
				}else if(lista.get(2) == 0 && lista.get(1) == 2 && lista.get(0) == 2 || 
				lista.get(2) == 1 && lista.get(1) == 0 && lista.get(0) == 0 ||
				lista.get(2) == 2 && lista.get(1) == 1 && lista.get(0) == 1){
					ganador = 2;
				}else{
					for (int i = 0; i < 3; i++) {
						lista.set(i, -1);
					}
					esperaJugadas.signalAll();
				}
				finalizado = true;
				finalizar.signalAll();
				System.out.println("fin partida.");
			}

			while(!finalizado){
				finalizar.await();
			}


		}finally{
			l.unlock();
		}
		return ganador;
	}
}
