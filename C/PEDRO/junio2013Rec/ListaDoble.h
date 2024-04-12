#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct user {
    int   uid_           ;
    char *userName_      ;
    char *homeDirectory_ ;
    
    struct user * nextUser_ ;
    struct user * previousUser_ ;
} T_user ;


typedef struct list {
   T_user * head;
   T_user * tail;
} T_userList ;

T_user * createUser(char *name, int uid, char *dir) ;
T_userList createUserList() ;
int addUser(T_userList *userList, T_user *user) ;
int getUid(T_userList list, char *userName) ;
int deleteUser(T_userList *list, char* userName) ;
void printUserList(T_userList list, int reverse) ;
