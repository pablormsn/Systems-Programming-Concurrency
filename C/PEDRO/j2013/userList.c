#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "userList.h"


T_user * createUser(char *name, int uid, char *dir){
    T_user newUser = malloc(sizeof( struct user));
    if(newUser == NULL){
        perror("No hay espacio");
        exit(-1);
    }else{
    newUser->nextUser_ = NULL;
    newUser->previousUser_ = NULL;
    newUser->uid_ = uid;
    newUser->userName_ = name;
    newUser->homeDirectory_ = dir;
    return newUser;
    }
}

T_userList createUserList(){
    T_userList lista = malloc(sizeof( struct userList));
    if(lista == NULL){
        perror("No hay espacio\n");
        exit(-1);
    }else{


    lista->head_ = NULL;
    lista->tail_ = NULL;
    lista->numberOfUsers_ = 0;
    }

}

int addUser(T_userList *list, T_user *user){
    T_user iter = (*list)->head_;
    if(iter == NULL){
        iter = user;
        (*list)->tail_ = iter;

    }else{
        ;
    } 


}
  



int getUid(T_userList list, char *userName){
    ;
}

int deleteUser(T_userList *list, char* userName){
    ;
}

void printUserList(T_userList list, int reverse){
    ;
}
