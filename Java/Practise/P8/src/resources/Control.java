package Recursos;
import java.util.ArrayList;
import java.util.List;

public class Control {

	private int recursos;
	//TODO
	ArrayList<Integer> turnos = new ArrayList<>();
	public Control(int recursos) {
		//TODO
		this.recursos = recursos;
	}
	
	public synchronized void quieroRecursos(int id, int num) throws InterruptedException{
		//TODO
		System.out.println("El proceso " + id + "quiere usar "+num+ " recursos");

		turnos.add(id);

		System.out.println("Cola de turnos: ");
		System.out.println(turnos);

		while (id!=turnos.get(0) || num>recursos){
			wait();
		}
		System.out.println("El proceso " + id + " coge "+num+ " recursos");

		turnos.remove(0);
		recursos -= num;
		System.out.println("Recursos restantes: "+recursos);

		if(recursos>0){
			notifyAll();
		}
	}
	
	public synchronized void liberoRecursos(int id, int num) {
		//TODO
		System.out.println("El proceso " + id + "libera "+num+ " recursos");
		recursos += num;
		System.out.println("Recursos restantes: "+recursos);

		notifyAll();
	}
	
	public static void main(String[] args) {
		Control c = new Control(10);
		Proceso procesos[] = new Proceso[6];
		for(int i = 0; i < 6 ; i++)
			procesos[i] = new Proceso(i, c, 10);
		for(int i = 0; i < 6 ; i++)
			procesos[i].start();

	}

}
