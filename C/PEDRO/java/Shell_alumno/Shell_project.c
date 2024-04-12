/**
UNIX Shell Project

Sistemas Operativos
Grados I. Informatica, Computadores & Software
Dept. Arquitectura de Computadores - UMA

Some code adapted from "Fundamentos de Sistemas Operativos", Silberschatz et al.

To compile and run the program:
   $ gcc Shell_project.c job_control.c -o Shell
   $ ./Shell
        (then type ^D to exit program)

**/

#include "job_control.h" // remember to compile with module job_control.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_LINE 256 /* 256 chars per line, per command, should be enough. */

// -----------------------------------------------------------------------
//                            MAIN
// -----------------------------------------------------------------------

job *tareas;

void manejador(int senal) {
  job *item;
  int status;
  int info;
  int pid_wait = 0;
  enum status status_res;

  for (int i = 1; i <= list_size(tareas); i++) {
    item = get_item_bypos(tareas, i);
    // Añadir la condición para que solo se ejecute en background
    pid_wait = waitpid(item->pgid, &status, WUNTRACED | WNOHANG | WCONTINUED);
    if (pid_wait == item->pgid) {
      status_res = analyze_status(status, &info);
      if (status_res == EXITED) {
        printf("Comando %s ejecutando en segundo plano con PID %d ha "
               "finalizado su ejecución \n",
               item->command, item->pgid);
        delete_job(tareas, item);
      } else if (status_res == SUSPENDED) {
        printf("Comando %s ejecutando en segundo plano con PID %d ha "
               "suspendido su ejecución \n",
               item->command, item->pgid);
        item->state = STOPPED;
      } else if (status_res == SIGNALED) {
        printf("Comando %s ejecutando en segundo plano con PID %d ha "
               "finalizado su ejecución \n",
               item->command, item->pgid);
        delete_job(tareas, item);
      }
    }
  }
}

int main(void) {
  char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
  int background;             /* equals 1 if a command is followed by '&' */
  char *args[MAX_LINE / 2]; /* command line (of 256) has max of 128 arguments */
  // probably useful variables:
  int pid_fork, pid_wait; /* pid for created and waited process */
  int status;             /* status returned by wait */
  enum status status_res; /* status processed by analyze_status() */
  int info;               /* info processed by analyze_status() */

  job *item;

  ignore_terminal_signals();
  signal(SIGCHLD, manejador);
  tareas = new_list("lista_jobs"); // Crear lista

  while (1) /* Program terminates normally inside get_command() after ^D is
               typed*/
  {
    printf("COMMAND->");
    fflush(stdout);
    get_command(inputBuffer, MAX_LINE, args,
                &background); /* get next command */

    if (args[0] == NULL)
      continue; // if empty command

    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
      int res = chdir(args[1]);
      if (res && args[1] != NULL) {
        printf("cd: no existe el fichero o el directorio: %s \n", args[1]);
      }
    } else if (strcmp(args[0], "jobs") == 0) {
      if (tareas->next != NULL)
        print_job_list(tareas);
      else
        printf("No hay tareas suspendidas o en background \n");
    } else if (strcmp(args[0], "fg") == 0) {
      int n;
      if (args[1] == NULL)
        n = 1;
      else {
        n = atoi(args[1]);
        if (n == 0 || n > list_size(tareas)) {
          printf("Error: Incorrect argument -> %s.\n", args[1]);
        }
      }
      job *elem = get_item_bypos(tareas, n);
      if (elem != NULL) {
        set_terminal(elem->pgid);
        if (elem->state == STOPPED) {
          killpg(elem->pgid, SIGCONT);
        }
        elem->state = FOREGROUND;
        waitpid(elem->pgid, &status, WUNTRACED);
        status_res = analyze_status(status, &info);
        set_terminal(getpid());
        printf("Foreground pid: %i, command: %s, status: %s, info: "
               "%i \n",
               elem->pgid, elem->command, status_strings[status_res], info);
        if (status_res == EXITED || status_res == SIGNALED)
          delete_job(tareas, elem);
        else if (status_res == SUSPENDED)
          elem->state = STOPPED;
      }

    } else if (strcmp(args[0], "bg") == 0) {
      int n;
      if (args[1] == NULL)
        n = 1;
      else {
        n = atoi(args[1]);
        if (n == 0 || n > list_size(tareas)) {
          printf(" Error: Incorrect argument -> %s \n", args[1]);
        }
      }
      job *elem = get_item_bypos(tareas, n);
      if (elem != NULL && elem->state == STOPPED) {
        elem->state = BACKGROUND;
        killpg(elem->pgid, SIGCONT);
        printf(" Background job running... pid: %i, command: %s "
               " \n",
               elem->pgid, elem->command);
      }
    } else {
      pid_fork = fork();
      if (pid_fork) {
        if (background == 0) {
          waitpid(pid_fork, &status, WUNTRACED);
          set_terminal(getpid());
          status_res = analyze_status(status, &info);
          if (strcmp(status_strings[status_res], "Suspended") == 0) {
            item = new_job(pid_fork, args[0], STOPPED);
            add_job(tareas, item);
          }
          printf("Foreground pid: %d, command: %s, %s, info: %d \n", pid_fork,
                 args[0], status_strings[status_res], info);
        } else {
          item = new_job(pid_fork, args[0], BACKGROUND);
          add_job(tareas, item);
          printf("Background job running... pid: %d, command: sleep \n",
                 pid_fork);
        }
      } else {
        new_process_group(getpid());
        if (background == 0) {
          set_terminal(getpid());
        }
        restore_terminal_signals();
        execvp(args[0], args);
        printf("Error, command not found: %s \n", args[0]);
        exit(-1);
      }
    }
    /* the steps are:
             (1) fork a child process using fork()
             (2) the child process will invoke execvp()
             (3) if background == 0, the parent will wait, otherwise continue
             (4) Shell shows a status message for processed command
             (5) loop returns to get_commnad() function
    */

  } // end while
}
