#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDoble.h"

int main(){
    T_user * user = createUser("Amparo", 0, "/home/amparo");
    T_user * user2 = createUser("Amparo", 999, "/home/amparo");
    T_user * user3 = createUser("Chema", 1, "/home/chema");
    T_user * user4 = createUser("Benjumea", 2, "/home/benjumea");
    T_userList list = createUserList();
    addUser(&list, user);
    addUser(&list, user2); 
    addUser(&list, user3); 
    addUser(&list, user4); 
    int a = getUid(list,"Amparo"); 
    int b = getUid(list,"Chema"); 
    int c = getUid(list,"Benjumea"); 
    printUserList(list, 0);
    printUserList(list, 1);
    deleteUser(&list, "Amparo"); 
    deleteUser(&list, "Jdjd"); 
    deleteUser(&list, "Chema"); 
    deleteUser(&list, "Benjumea"); 

}