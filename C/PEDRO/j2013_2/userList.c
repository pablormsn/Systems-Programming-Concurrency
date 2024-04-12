#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "userList1.h"


T_user * createUser(char *name, int uid, char *dir){
    T_user *newUser = malloc(sizeof(T_user));
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
    T_userList *lista = malloc(sizeof(T_userList));
    if(lista == NULL){
        perror("No hay espacio\n");
        exit(-1);
    }else{


    lista->head_ = NULL;
    lista->tail_ = NULL;
    //lista->tail_->previousUser_ = NULL;
    //lista->tail_->nextUser_ = NULL;
    lista->numberOfUsers_ = 0;
    }
}


int addUser(T_userList *list, T_user *user){
    int ok = 1;
    if((*list).tail_ == NULL){
        ++list->numberOfUsers_; 
        (*list).head_ = user;
        (*list).tail_ = user;
        ok = 0;

    }else if((*list).numberOfUsers_ == 1){
        if(((*list).head_->userName_ == user->userName_) && ((*list).head_->uid_ == user->uid_)){
            ok = 1;
        }else{

            //(*user).nextUser_ = (*list).head_;
            //(*list).tail_ = user;
            //++(*list).numberOfUsers_;
            //ok = 0;
        }
    }else{
        ; //mas de 1 usuario
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