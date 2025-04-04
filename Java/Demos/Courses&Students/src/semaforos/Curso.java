package semaforos;

import java.util.concurrent.Semaphore;

public class Curso {

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;

	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	private volatile int nAlumnosIni = 0;//numero de alumnos en la parte de iniciacion
	private volatile int nAlumnosAv = 0;//numero de alumnos en la parte avanzada
	private Semaphore mutex1 = new Semaphore(1); //semaforo para controlar el acceso a nAlumnosIni
	private Semaphore mutex2 = new Semaphore(1); //semaforo para controlar el acceso a nAlumnosAv
	private Semaphore puedeRealizarIni = new Semaphore(1); //semaforo para controlar el acceso a la parte de iniciacion
	private Semaphore puedeEntrarAv = new Semaphore(1); //semaforo para controlar el acceso a la parte avanzada
	private Semaphore puedeRealizarAv = new Semaphore(0); //semaforo para controlar el acceso a la realizacion de la parte avanzada
	private Semaphore puedeSalirAv = new Semaphore(0); //semaforo para controlar la salida de la parte avanzada



	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		puedeRealizarIni.acquire(); //semaforo para controlar el acceso a la parte de iniciacion
		mutex1.acquire(); //semaforo para controlar el acceso a nAlumnosIni
			System.out.println("PARTE INICIACION: Alumno " + id + " espera a que haya plaza");
			nAlumnosIni++;
			System.out.println("Numero de alumnos en la parte de iniciacion: " + nAlumnosIni);
			if(nAlumnosIni < MAX_ALUMNOS_INI) { //Si no se ha llegado al maximo de alumnos
				puedeRealizarIni.release(); //Puede entrar otro alumno
			}
		mutex1.release(); //Libera el semaforo para controlar el acceso a nAlumnosIni

		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion");
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion");

		//Libera la conexion para que otro alumno pueda usarla
		mutex1.acquire(); //semaforo para controlar el acceso a nAlumnosIni
			nAlumnosIni--; //Decrementa el numero de alumnos en la parte de iniciacion
			System.out.println("Numero de alumnos en la parte de iniciacion: " + nAlumnosIni);
			if(nAlumnosIni == MAX_ALUMNOS_INI - 1) { //Si se ha liberado una plaza
				puedeRealizarIni.release(); //Puede entrar otro alumno
			}
		mutex1.release();
	}

	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		puedeEntrarAv.acquire();
		mutex2.acquire();
			System.out.println("PARTE AVANZADA: Alumno " + id + " espera a que haya plaza");
			nAlumnosAv++;
			System.out.println("Numero de alumnos en la parte avanzada: " + nAlumnosAv);
			if(nAlumnosAv < ALUMNOS_AV){
				puedeEntrarAv.release();
			}else{
				System.out.println("PARTE AVANZADA: Grupo formado, hay "+ ALUMNOS_AV + ". Alumno " + id + " empieza la parte avanzada");
				puedeRealizarAv.release();
			}
		mutex2.release();
	}

	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte
	 */
	public void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		puedeRealizarAv.acquire();
		mutex2.acquire();
			System.out.println("PARTE AVANZADA: Alumno " + id + " termina parte avanzada. Espera al resto");
			nAlumnosAv--;
		mutex2.release();
		System.out.println("Numero de alumnos en la parte avanzada: " + nAlumnosAv);
		if(nAlumnosAv > 0){
			puedeRealizarAv.release();
			puedeSalirAv.acquire();
		}else{
			System.out.println("PARTE AVANZADA: Los " + ALUMNOS_AV + " alumnos han terminado el curso.");
			puedeSalirAv.release();
			puedeEntrarAv.release();
		}
	}
}
