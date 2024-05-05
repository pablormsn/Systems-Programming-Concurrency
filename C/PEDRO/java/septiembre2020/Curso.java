package semaforos;

import java.util.concurrent.Semaphore;

public class Curso {

	//Numero maximo de alumnos cursando simultaneamente la parte de iniciacion
	private final int MAX_ALUMNOS_INI = 10;
	
	//Numero de alumnos por grupo en la parte avanzada
	private final int ALUMNOS_AV = 3;
	
	int numAlumnosIni = 0;
	int numAvan = 0;
	private Semaphore empiezaIni = new Semaphore(1, true);
	private Semaphore mutex1 = new Semaphore(1, true);
	private Semaphore mutex2 = new Semaphore(1, true);
	private Semaphore saleAvan = new Semaphore(0, true);
	private Semaphore entraAvan = new Semaphore(1, true);
	private Semaphore empiezaAvan = new Semaphore(0, true);

	
	//El alumno tendra que esperar si ya hay 10 alumnos cursando la parte de iniciacion
	public void esperaPlazaIniciacion(int id) throws InterruptedException{
		//Espera si ya hay 10 alumnos cursando esta parte
		empiezaIni.acquire();
		mutex1.acquire();
		++numAlumnosIni;
		//Mensaje a mostrar cuando el alumno pueda conectarse y cursar la parte de iniciacion
		System.out.println("PARTE INICIACION: Alumno " + id + " cursa parte iniciacion. Alumnos en inicializacion: " + numAlumnosIni);
		if(numAlumnosIni < 10)empiezaIni.release();
		mutex1.release();
	}


	//El alumno informa que ya ha terminado de cursar la parte de iniciacion
	public void finIniciacion(int id) throws InterruptedException{
		//Mensaje a mostrar para indicar que el alumno ha terminado la parte de principiantes
		mutex1.acquire();
		--numAlumnosIni;
		System.out.println("PARTE INICIACION: Alumno " + id + " termina parte iniciacion. Alumnos en inicializacion: " + numAlumnosIni);
		if(numAlumnosIni == 9)empiezaIni.release();
		mutex1.release();

		//Libera la conexion para que otro alumno pueda usarla
	}
	
	/* El alumno tendra que esperar:
	 *   - si ya hay un grupo realizando la parte avanzada
	 *   - si todavia no estan los tres miembros del grupo conectados
	 */
	public void esperaPlazaAvanzado(int id) throws InterruptedException{
		//Espera a que no haya otro grupo realizando esta parte
		//Espera a que haya tres alumnos conectados

		entraAvan.acquire();
		mutex2.acquire();
		++numAvan;
		//Mensaje a mostrar si el alumno tiene que esperar al resto de miembros en el grupo
		System.out.println("	PARTE AVANZADA: Alumno " + id + " espera a que haya " + ALUMNOS_AV + " alumnos");
		if(numAvan < 3){
			entraAvan.release();
		}else{
			System.out.println("		PARTE AVANZADA: Hay " + ALUMNOS_AV + " alumnos. Alumno " + id + " empieza el proyecto");
			empiezaAvan.release();
		}
		mutex2.release();
		//Mensaje a mostrar cuando el alumno pueda empezar a cursar la parte avanzada
		
	}
	
	/* El alumno:
	 *   - informa que ya ha terminado de cursar la parte avanzada 
	 *   - espera hasta que los tres miembros del grupo hayan terminado su parte 
	 */ 
	public void finAvanzado(int id) throws InterruptedException{
		//Espera a que los 3 alumnos terminen su parte avanzada
		//Mensaje a mostrar si el alumno tiene que esperar a que los otros miembros del grupo terminen
		
		empiezaAvan.acquire();
		mutex2.acquire();
		System.out.println(				"PARTE AVANZADA: Alumno " +  id + " termina su parte del proyecto. Espera al resto");
		--numAvan;
		mutex2.release();
		if(numAvan > 0){
			empiezaAvan.release();
			saleAvan.acquire();
		}else{
			System.out.println("				PARTE AVANZADA: LOS " + ALUMNOS_AV + " ALUMNOS HAN TERMINADO EL CURSO");
			saleAvan.release();
			entraAvan.release();
		}
		//Mensaje a mostrar cuando los tres alumnos del grupo han terminado su parte
		
	}
}
