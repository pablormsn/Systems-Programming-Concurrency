#include "userList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_user *createUser(char *name, int uid, char *dir) {
  T_user *newUser = malloc(sizeof(Tuser));

  if (newUser == NULL) {
    perror("Error. No hay memoria suficiente");
    exit(-1);
  } else {
    // newUser->userName = name;
    strcpy(newUser->userName, name);
    newUser->uid = uid;
    // newUser->homeDirectory = dir;
    strcpy(newUser->homeDirectory, dir);
    newUser->nextUser = NULL;
    newUser->previousUser = NULL;
    return newUser;
  }
}

T_userList createUserList() {
  TuserList *newList;
  newList->head = NULL;
  newList->tail = NULL;
  newList->numberOfUsers = 0;
  return *newList;
}

int addUser(T_userList *list, T_user *user) {
  int ok = 1;
  Tuser *aux = list->head;

  while (aux->previousUser != NULL &&
         (aux->userName != user->userName && aux->uid != user->uid)) {
    aux = aux->previousUser;
  }

  if (aux->uid == user->uid || aux->userName == user->userName) {
    ok = 0;
  } else {
    if (list->numberOfUsers == 0) {
      list->head = user;
      list->tail = user;
      list->numberOfUsers++;
    } else {
      list->head->nextUser = user;
      aux->previousUser = list->head;
      list->head = user;
      list->numberOfUsers++;
    }
  }

  return ok;
}

int getUid(T_userList list, char *userName);

