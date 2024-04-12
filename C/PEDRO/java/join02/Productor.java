package join02;

public class Productor {
    RecursoCompartido recurso;
    public Productor(RecursoCompartido rec){
        recurso = rec;
    }
    
    public void run(){
        for(int i = 0; i<10; ++i){
            recurso.escribir(i);
        }
    }



}
