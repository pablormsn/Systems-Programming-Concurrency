package monitores;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Curso {


	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	private int nAlumnosIni = 0;//numero de alumnos en la parte de iniciacion
	private int nAlumnosAv = 0;//numero de alumnos en la parte avanzada
	private boolean cursandoAv = false;

	ReentrantLock l = new ReentrantLock();
	Condition puedeRealizarIni = l.newCondition();
	Condition puedeEntrarAv = l.newCondition();
	Condition puedeRealizarAv = l.newCondition();
	Condition puedeSalirAv = l.newCondition();
	
	
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		l.lock();
		try{
			while(nAlumnosIni == MAX_ALUMNOS_INI){
				puedeRealizarIni.await();
			}
			System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");
			nAlumnosIni++;
			System.out.println("Numero de alumnos en la parte de iniciacion: " + nAlumnosIni);
			if(nAlumnosIni < MAX_ALUMNOS_INI) { //Si no se ha llegado al maximo de alumnos
				puedeRealizarIni.signalAll(); //Puede entrar otro alumno
			}
		}finally{
			l.unlock();
		}
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		l.lock();
		try{
			System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");
			nAlumnosIni--; //Decrementa el numero de alumnos en la parte de iniciacion
			System.out.println("Numero de alumnos en la parte de iniciacion: " + nAlumnosIni);
			if(nAlumnosIni == MAX_ALUMNOS_INI - 1) { //Si se ha liberado una plaza
				puedeRealizarIni.signalAll(); //Puede entrar otro alumno
			}
		}finally{
			l.unlock();
		}
		//Libera la conexion para que otro alumno pueda usarla
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		l.lock();
		try{
			while(cursandoAv){
				puedeEntrarAv.await();
			}
			nAlumnosAv++;
			if(nAlumnosAv < ALUMNOS_AV){
				System.out.println("PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
				System.out.println("Numero de alumnos en la parte avanzada: " + nAlumnosAv);
				while (!cursandoAv){
					puedeRealizarAv.await();
				}
				System.out.println("PARTE AVANZADA: Grupo formado, hay "+ ALUMNOS_AV + ". Alumno " + id + " empieza la parte avanzada");
			}else{
				cursandoAv = true;
				System.out.println("PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
				System.out.println("PARTE AVANZADA: Grupo formado, hay "+ ALUMNOS_AV + ". Alumno " + id + " empieza la parte avanzada");
				puedeRealizarAv.signalAll();
			}
		}finally{
			l.unlock();
		}
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		l.lock();
		try{
			nAlumnosAv--;
			if(nAlumnosAv > 0){
				System.out.println("PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
				System.out.println("Numero de alumnos en la parte avanzada: " + nAlumnosAv);
				while(nAlumnosAv > 0){
					puedeSalirAv.await();
				}
			}else{
				cursandoAv = false;
				System.out.println("PARTE AVANZADA: Alumno " + id + " termina su parte del proyecto.");
				System.out.println("Numero de alumnos en la parte avanzada: " + nAlumnosAv);
				System.out.println("PARTE AVANZADA: Los " + ALUMNOS_AV + " alumnos han terminado el curso.");
				puedeSalirAv.signalAll();
				puedeEntrarAv.signalAll();
			}
		}finally{
			l.unlock();
		}
	}
}
