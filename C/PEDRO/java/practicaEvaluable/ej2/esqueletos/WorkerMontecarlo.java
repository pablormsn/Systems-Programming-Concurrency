package esqueletos;

import java.util.List;
import java.util.Random;

import javax.swing.SwingWorker;

public class WorkerMontecarlo extends SwingWorker<Object, Double>{
    int iteraciones;
    Panel panel;
    double res;
    
    public WorkerMontecarlo(int it, Panel panel){
        iteraciones = it;
        this.panel = panel;
    }

    public Double procesar() {             
        double dentro = 0.0;             
        Random random = new Random();             
        double radio = 0.5;             
        double x;             
        double y;             
        int indice = 1;   
        x = random.nextDouble(radio);          
        y = random.nextDouble(radio);           
        while( indice <= iteraciones){                 
            if((radio * radio) >= (x * x + y * y))dentro++; //solo estará dentro del círculo si se cumple la fórmula
            publish((4.0 *(dentro))/(double)iteraciones);
            setProgress(((indice)*100 / iteraciones));
            try {
                Thread.sleep(90);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            ++indice;
        }
        res = (( 4.0 * (dentro))/(double)iteraciones);
        return res;
    }

    protected void process(List<Double> list){
        panel.escribePI1(list.get(list.size()-1));
    }

    @Override
    protected Object doInBackground() throws Exception {
        // TODO Auto-generated method stub
        return procesar();
    }

    public void done(){
        this.setProgress(100);
        panel.escribePI1(res);
    }

    
    

}
