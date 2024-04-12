package esqueletos;

import java.util.Random;

public class WorkerMontecarlo {
    int max;

    public WorkerMontecarlo(int max){
        this.max = max;
    }

    public Double procesar() {
        Random random = new Random();
        double x;
        double y;
        double radio = 0.5;
        int indice = 0;
        double dentro = 0.0;
        x = random.nextDouble(radio);
        y = random.nextDouble(radio);
        while(indice < this.max){
            if((radio * radio) >= (x * x + y * y))dentro++; //solo estará dentro del círculo si se cumple la fórmula
            ++indice;
        }
        double total = ((4.0*(dentro))/this.max); 
        return total;
    }


    

}
