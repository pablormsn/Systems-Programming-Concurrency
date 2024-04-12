package juego;

import java.util.concurrent.*;
public class Mesa {
    //0 - piedra, 1 - papel, 2 - tijeras
	int jugadores = 0;
	boolean empiezaJuego = false;
	int ganador = 0;

	int jugada0;
	int jugada1;
	int jugada2;
	int jugadaGanadora;

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
	public synchronized int nuevaJugada(int jug,int juego) throws InterruptedException{
		System.out.println("El jugador " + jug + " hace jugada " + juego );

		++jugadores;

		if(jug == 0){
			jugada0 = juego;
		}else if(jug == 1){
			jugada1 = juego;
		}else{
			jugada2 = juego;
		}

		if(jugadores == 3){
			empiezaJuego = true;
			notifyAll();
		}

		while(!empiezaJuego){
			wait();
		}
		--jugadores;
		if(jugadores == 0){
			empiezaJuego = false;
		}
		if((jugada0 == 1 && jugada1 == 0 && jugada2 == 0)||(jugada0 == 2 && jugada1 == 1 && jugada2 == 1)||(jugada0 == 0 && jugada1 == 2 && jugada2 == 2)){
			jugadaGanadora = jugada0;
		}else if((jugada1 == 1 && jugada0 == 0 && jugada2 == 0)||(jugada1 == 2 && jugada0 == 1 && jugada2 == 1)||(jugada1 == 0 && jugada0 == 2 && jugada2 == 2)){
			jugadaGanadora = jugada1;
		}else if((jugada2 == 1 && jugada0 == 0 && jugada1 == 0)||(jugada2 == 2 && jugada0 == 1 && jugada1 == 1)||(jugada2 == 0 && jugada0 == 2 && jugada1 == 2)){
			jugadaGanadora = jugada2;
		}else{
			jugadaGanadora = -1;
		}
		

		return jugadaGanadora;
	}
}	