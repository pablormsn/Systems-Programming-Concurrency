#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDoble.h"

T_user * createUser(char *name, int uid, char *dir){
    T_user * user = malloc(sizeof(struct user));
    if(user == NULL){
        perror("No hay espacio");
        exit(-1);
    }
    (*user).userName_ = malloc(strlen(name) + 1);
    
    //(*user)->userName_ = malloc(strlen(name) + 1);
    strcpy(user->userName_, name);
     user->homeDirectory_ = malloc(strlen(dir) + 1);
    strcpy(user->homeDirectory_, dir);
    user->uid_ = uid;
    user->nextUser_ = NULL;
    user->previousUser_ = NULL;

}

T_userList createUserList(){
    T_userList lista;
    lista.head = NULL;
    lista.tail = NULL;
    return lista;
}

int esta(T_userList *userList, T_user *user){
    T_user *aux = userList->head;
    int esta = 0;
    while(aux != NULL){
        if((aux->uid_ == (*user).uid_)|| (strcmp((*user).userName_, (*aux).userName_) == 0) ){
            esta = 1;
        }

        aux = aux->previousUser_;
    }

    return esta;

}

int addUser(T_userList *userList, T_user *user){
    if(esta(userList, user) == 1){
        printf("El usuario ya está");
        return 0; // ya está en la lista
    }else{      //no está
        if((*userList).head == NULL){ //lista vacía
            (*user).nextUser_ = NULL;
            (*user).previousUser_ = NULL;
            (*userList).head = user;
            (*userList).tail = user;
        }else{  //lista con elementos
            T_user *uAux = userList->head;
            user->previousUser_ = uAux;
            user->nextUser_ = NULL;
            uAux->nextUser_ = user;
            userList->head = user;
            
        }

        return 1;
    }
}

int getUid(T_userList list, char *userName){
    T_user * user = createUser(userName, 1, " ");
    strcpy((*user).userName_, userName);
    if(esta(&list, user) == 0){
        printf("no esta");
    }else{
        user = list.head;
        while((strcmp(user->userName_, userName) != 0))user = user->previousUser_;
        return (user->uid_);
    }
}

int deleteUser(T_userList *list, char* userName){
    T_user * user = createUser(userName, 6773635636, " ");
    strcpy((*user).userName_, userName);
    if(esta(list, user) == 0){
        printf("\nno esta");
        return 0;
    }else{
        T_user *aux = list->head;
       if( (*list).head->uid_ == (*list).tail->uid_){ // 1 solo elem
            free(aux);
            list->head = NULL;
            list->tail = NULL;
       }else if(strcmp((*list).head->userName_, userName) == 0){ //cabeza
            (*list).head->previousUser_->nextUser_ = NULL;
            list->head = aux->previousUser_;
            free(aux);
       }else if(strcmp((*list).tail->userName_, userName) == 0){ //cola
            aux = (*list).tail;
            (*list).tail->nextUser_->previousUser_ = NULL;
            (*list).tail = aux->nextUser_;
            free(aux);
       }else{                                                    //en medio
            while(strcmp(aux->userName_, userName) != 0){
                aux = aux->previousUser_;
            }
            aux->nextUser_->previousUser_ = aux->previousUser_;
            aux->previousUser_->nextUser_ = aux->nextUser_;
            free(aux);
       }

    }
}


void printUserList(T_userList list, int reverse){
    if(reverse == 0){
    T_user *aux = list.head;
    while(aux != NULL){
        printf("\nUsuario %s con id %i y directorio %s", aux->userName_, aux->uid_, aux->homeDirectory_);
        aux = aux->previousUser_;
        }
    }else{
    T_user *aux = list.tail;
    while(aux != NULL){
        printf("\nUsuario %s con id %i y directorio %s", aux->userName_, aux->uid_, aux->homeDirectory_);
        aux = aux->nextUser_;
        }
    }
}
