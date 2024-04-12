#include "ADN.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void emptyChain(Chain *chain){
    *chain = NULL;
}

void showChain(Chain chain){
    Chain c = chain;
    int fcount = 0;
    while(c!=NULL){
        if(fcount == c->id){        
            printf("%s",c->fragment);
            c = c->next;
        }else{
            printf("????");            
        }
        fcount++;
    }
    printf("\n");
}

void destroyChain(Chain *chain){
    Chain aux = *chain;
    while(*chain != NULL){
        *chain = (*chain)->next;
        free(aux);
        aux = *chain;
    }
}


int addFragment(Chain *chain, char *frag, int id){
    
    if(id < 0){        
        return 0;   
    } else {
        Chain curr = *chain, ant = NULL;
        while(curr!=NULL && curr->id < id){
            ant = curr;
            curr = curr->next;
        }
        if(curr!=NULL && curr->id == id){
            strcpy(curr->fragment, frag);
        } else {
            Chain newN = (Chain) malloc(sizeof(Node));      
            if(newN == NULL){
                perror("Insuficient memory");
                exit(-1);
            }            
            newN->prev = ant;
            newN->id = id;   
            strcpy(newN->fragment, frag);
            if(ant ==NULL){ //insert first position
                *chain = newN;
                newN-> next = curr;
            } else{ //insert intermediate or final
                ant->next = newN;
                newN->next = curr;
            }
        }       
    }
     return 1;
        
}



void loadFromFile(char *filename, Chain *chain){
    FILE * f = fopen(filename, "rb");
    if(f == NULL){
        perror("Error loading from file");
        exit(-1);
    }
    int id, r = 1;
    char fg[5];
    destroyChain(chain); 
    while (fread(&id,sizeof(int), 1, f) && r){
        fread(fg, sizeof(char), 4, f);
        fg[4] = '\0';
        r = addFragment(chain, fg,id);
    }

    fclose(f);
}

void saveToFile(char *filename, Chain chain){
    FILE * f = fopen(filename, "wb");
    if(f == NULL){
        perror("Error loading from file");
        exit(-1);
    }
    Chain aux = chain;
    while(aux!=NULL){
        fwrite(&(aux->id), sizeof(int), 1, f);
        fwrite(aux->fragment, sizeof(char), 4, f);
        aux = aux->next;
    }
    fclose(f);
}


int cut(Chain *chain, char *frag){
    Chain curr = *chain, prev = NULL;
    int count = 0;
    while(curr!=NULL){
        if(strcmp(curr->fragment,frag)==0){
            count++;
            if(prev == NULL){
                *chain = curr->next;
                free(curr);
                curr = *chain;
                (*chain) ->prev = NULL;
            }else{
                prev->next = curr->next;
                if(curr->next!= NULL)
                curr->next->prev = prev;
                free(curr);
                curr = prev->next;
            }            
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
    return count;
}

int extract(Chain *chain, int id){
    Chain curr = *chain;
    int cont = 0;
    while(curr != NULL && curr->id < id){
        curr = curr->next;
    }
        
    while(curr != NULL && curr->id == id){
        Chain aux = curr;
        curr= curr->prev; 
        if(curr == NULL){
            *chain = aux->next;
        }else{
            curr->next = aux->next;
        }               
        free(aux);
        cont++;
        id--;
    }
    return cont;
}