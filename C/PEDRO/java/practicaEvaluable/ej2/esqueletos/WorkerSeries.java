package esqueletos;

import java.util.List;

import javax.swing.SwingWorker;

public class WorkerSeries extends SwingWorker<Object, Double>{
    double max;
    Panel panel;
    int div = 1;
    double total = 0.0;
    
    public WorkerSeries(int max, Panel panel){
        this.max = max;
        this.panel = panel;
    }

    public double procesar() throws InterruptedException{
        int cont = 0;
        while(cont < max){
            if(cont % 2 == 0){
                total = total + (4.0/div); //cuando es par se añade como valor positivo al sumatorio
            }else if(cont % 2 == 1){
                total = total - (4.0/div); // es impar, añadimos como valor negativo al sumatorio
            }
            setProgress((int) (((div)/max)* 100));
            div = div + 2;
            publish(total);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            ++cont;
        }
        return total;
    }

    protected void process(List<Double> list){
        panel.escribePI2(list.get(list.size()-1));
    }   


    @Override
    protected Object doInBackground() throws Exception {
        // TODO Auto-generated method stub
        return procesar();
    }
    

    public void done(){
        this.setProgress(100);
        panel.escribePI2(total);
    }
}
