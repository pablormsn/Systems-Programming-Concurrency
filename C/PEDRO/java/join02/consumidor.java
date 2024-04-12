package join02;

public class consumidor {
    RecursoCompartido recurso;
    public consumidor(RecursoCompartido rec){
        recurso = rec;
    }
    
    public void run(){
        for(int i = 0; i<10; ++i){
            recurso.leer();
        }
    }
}
