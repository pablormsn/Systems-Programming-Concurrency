#include<stdio.h>
#include<stdlib.h>


void decrypt(unsigned * v, unsigned * k){
    unsigned delta = 0x9e3779b9;
    unsigned sum = 0xC6EF3720;
    for(int i = 0; i < 32; ++i){
    v[1] = v[1] - ((v[0]<<4)+k[2])^(v[0]+sum)^((v[0]>>5)+k[3]);
    v[0] = v[0] - ((v[1]<<4)+k[0])^(v[1]+sum)^((v[1]>>5)+k[1]);
    sum = sum - delta;
    }
}




int main(int argc, char const *argv[])
{
    unsigned k[4]={128, 129, 130, 131}; 
    FILE * ptr_entrada;
    FILE * ptr_salida;
    if(arghc != 3){
        perror("Error, se esperaba un fichero de entrada y uno de salida");
        exit(-1);
    }

    

    
    return 0;
}
