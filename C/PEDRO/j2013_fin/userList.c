#include <stdio.h>
#include "userList.h"
#include <stdlib.h>
#include <string.h>

T_user * createUser(char *name, int uid, char *dir){
    T_user *usuario = malloc(sizeof(struct user));
    if(usuario == NULL){
        perror("No hay espacio\n");
        exit(-1);
    }else{
        usuario->userName_ = name;
        usuario->uid_ = uid;
        usuario->homeDirectory_ = dir;
        usuario->nextUser_ = NULL;
        usuario->previousUser_ = NULL;

    }
}



T_userList createUserList(){
   T_userList *Lista = malloc(sizeof(struct userList));
   if(Lista == NULL){
       perror("No hay espacio\n");
        exit(-1);
   }else{
       Lista->head_ = NULL;
       Lista->tail_ = NULL;
      Lista->numberOfUsers_ = 0;
      return *Lista;
   }

}

int esta(T_userList *userList, T_user *user){
     T_user *it = malloc(sizeof(struct user));
     it = userList->head_;
     int esta = 0; //0 no esta y 1 si esta
     for(int i = 0; i < userList->numberOfUsers_; ++i){
         if((user->uid_ == it->uid_) || (user->userName_ == it->userName_)){
             esta = 1;
         }

         it = it->nextUser_;
     }

     return esta;
    
}

int addUser(T_userList *userList , T_user *user){
    int ok = 0;
    if(userList->head_ == NULL){
        userList->head_ = user;
        userList->tail_ = user;
        userList->numberOfUsers_ = 1;
        ok = 1;
    }else if(userList->numberOfUsers_ == 1){
        int incluido = esta(userList, user);
        if(incluido == 0){
            userList->head_ = user;
            user->nextUser_ = userList->tail_;
            userList->tail_->previousUser_ = user;
            ok = 1;
            userList->numberOfUsers_ = 2;
        }
    }else{
        int incluido = esta(userList, user);
        if(incluido == 0){
            user->nextUser_ = userList->head_;
            userList->head_ = user;
            ok = 1;
            ++userList->numberOfUsers_;
        }
    }
}

int getUid(T_userList list, char *userName) {
    T_user *aux = malloc(sizeof(struct user));
    aux->userName_ = userName;
    int incluido = esta(&list, aux);
    int uid = 0;
    if(incluido == 1){
        T_user *it = malloc(sizeof(struct user));
        it = list.head_;
        for(int i = 0; i< list.numberOfUsers_; ++i){
            if(it->userName_ == userName){
                uid = it->uid_;
            }

            it = it->nextUser_;
        }

    }else{
        perror("No está\n");
        exit(-1);
    }

    return uid;
}
int deleteUser(T_userList *list, char* userName){
   int ok = -1;
   if(list->numberOfUsers_ == 0){
       perror("No hay usuarios");
       exit(-1);
   }else{
       T_user *eliminar = malloc(sizeof(struct user));
        if(eliminar != NULL){
            eliminar->userName_ = userName;
            int incluido = esta(&list, eliminar);
            if(incluido == 1){
                if(list->numberOfUsers_ == 1){
                    list->head_ = NULL;
                    list->tail_ = NULL;
                    list->numberOfUsers_ = 0;
                    ok = 0;
                }else{
                    if(eliminar->userName_ == list->head_->userName_){
                        
                        T_user *aux = malloc(sizeof(struct user));
                        aux = list->head_;
                        list->head_ = list->head_->nextUser_;
                        free(aux);
                        --list->numberOfUsers_;
                        

                    }else if(eliminar->userName_ == list->tail_->userName_){
                        T_user *aux = malloc(sizeof(struct user));
                        aux = list->tail_;
                        list->tail_ = list->tail_->previousUser_;
                        free(aux);
                        --list->numberOfUsers_;
                    }else{
                        T_user *iter = malloc(sizeof(struct user));
                        iter = list->head_;
                        while(iter->userName_ != eliminar->userName_){
                            iter = iter->nextUser_;
                        }

                        T_user *aux = malloc(sizeof(struct user));
                        aux = iter;
                        iter->previousUser_->nextUser_ = iter->nextUser_;
                        iter->nextUser_->previousUser_ = iter->previousUser_;
                        free(aux);

                    }
                    ok = 0;
                }
            }else{
                perror("No está el usuario");
                exit(-1);
            }
        }
   }

   return ok;
}



void printUserList(T_userList list, int reverse){
  
   
    if(reverse == 0){
        T_user *it = malloc(sizeof(struct user));
        it = list.head_;
       while(it != NULL){
           printf("Nombre %s UID %i direccion %s", it->userName_, it->uid_, it->homeDirectory_);
           it = it->nextUser_;
           printf("\n");
       }
    }else{
        T_user *it = malloc(sizeof(struct user));
        it = list.tail_;
        while(it != NULL){
            printf("Nombre %s UID %i direccion %s", it->userName_, it->uid_, it->homeDirectory_);
            it = it->previousUser_;
            printf("\n");
        }


    }
    
}

