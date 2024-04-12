package esqueleto;

import java.util.concurrent.Semaphore;

import javax.print.attribute.standard.MediaSize.NA;

public class Curso {

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	Semaphore mutex1 = new Semaphore(1, true);
	Semaphore mutex2 = new Semaphore(1, true);
	Semaphore esperaLleno1 = new Semaphore(1, true);
	Semaphore puedeSalir1 = new Semaphore(0, true);
	Semaphore puedeSalir2 = new Semaphore(0, true);
	Semaphore puedenEntrarAv = new Semaphore(0, true);
	Semaphore esperaLLeno2 = new Semaphore(1, true);
	private int liberarAvanzados = 0;
	private int nIni = 0;
	private int nAva = 0;
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		esperaLleno1.acquire();
		mutex1.acquire();
		nIni++;
		if(nIni < 10){
			esperaLleno1.release();
		}
		puedeSalir1.release();
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion, " + nIni);
		mutex1.release();
	}

	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		puedeSalir1.acquire();
		mutex1.acquire();
		nIni--;
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion, " + nIni);
		if(nIni > 0){
			puedeSalir1.release();
		}
		if(nIni == MAX_ALUMNOS_INI-1){
			esperaLleno1.release();
		}
		mutex1.release();
		//Libera la conexion para que otro alumno pueda usarla
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		esperaLLeno2.acquire();
		mutex2.acquire();
		nAva++;
		System.out.println("					PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos, hay " + nAva);
		if(nAva == ALUMNOS_AV){
			puedenEntrarAv.release();
			System.out.println("					PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
		} else{
			esperaLLeno2.release();
		}
		mutex2.release();
		puedenEntrarAv.acquire();

		//Espera a que haya tres alumnos conectados

		//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo

		//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		mutex2.acquire();
		nAva--;
		System.out.println("					PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto, hay " + nAva);
		if(nAva > 0){
			puedenEntrarAv.release();
			liberarAvanzados++;
		} else{
			puedeSalir2.release();
		}
		mutex2.release();
		puedeSalir2.acquire();
		if(liberarAvanzados > 0){
			mutex2.acquire();
			liberarAvanzados--;
			mutex2.release();
			puedeSalir2.release();
		}else{
			esperaLLeno2.release();
			System.out.println("					PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
		}
		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen

		//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
	}
}
