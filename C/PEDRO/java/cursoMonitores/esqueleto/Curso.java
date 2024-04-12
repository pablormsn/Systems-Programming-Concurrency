package esqueleto;

import java.util.ArrayList;
import java.util.List;

public class Curso {

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	List<Integer> colaIni = new ArrayList<>();
	List<Integer> colaAva = new ArrayList<>();

	private int nIni = 0;
	private int nAva = 0;
	boolean llenoIni = false;
	boolean puedoSalirIni = false;
	boolean hayGrupo = false;
	boolean llenoAva = false;
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public synchronized void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		System.out.println("PARTE INICIACION: Alumno " + id + " espera en cola");
		colaIni.add(id);
		while(llenoIni ||colaIni.get(0) != id) wait();
		colaIni.remove(0);
		nIni++;
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion, hay " + nIni);
		puedoSalirIni = true;
		if(nIni == MAX_ALUMNOS_INI){
			llenoIni = true;
		}
		if(colaIni.size() > 0){
			notifyAll();
		}
		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public synchronized void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		while(!puedoSalirIni) wait();
		nIni--;
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion, hay " + nIni);
		if(nIni == 9){
			llenoIni = false;
			notifyAll();
		}
		if(nIni == 0){
			puedoSalirIni = false;
		}
		//Libera la conexion para que otro alumno pueda usarla
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public synchronized void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		colaAva.add(id);
		System.out.println("				PARTE AVANZADA: Alumno " + id + " espera en la cola");
		while(llenoAva || colaAva.get(0) != id) wait();
		colaAva.remove(0);
		nAva++;
		System.out.println("				PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos, hay " + nAva);
		if(nAva == ALUMNOS_AV){
			llenoAva = true;
			hayGrupo = true;
			System.out.println("				PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
			notifyAll();
		} else if(colaAva.size() > 0){
			notifyAll();
		} 
		
		//Espera a que haya tres alumnos conectados

		//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo

		//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public synchronized void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		while(!hayGrupo) wait();
		nAva--;
		System.out.println("				PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto, hay " + nAva);
		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen

		//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
		if(nAva == 0){
			System.out.println("				PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
			llenoAva = false;
			notifyAll();
		}
	}
}
