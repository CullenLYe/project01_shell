#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

// function for separating multiple commands on one line
char ** semi_sep(char *line, char *delimiter) {
  char **commands = malloc(sizeof(char*)*100);
  char *p;
  p = strtok(line, delimiter);
  int i = 0;
  while (p!=NULL) {
    commands[i] = p;
    p = strtok(NULL, delimiter);
    i++;
  }
  return commands;
}

void runcmd(char *command) { // Runs each respective command.
    int status;
    char **args = semi_sep(command, " ");
    if (!strcmp(args[0], "exit")) exit(0);
    if (!strcmp(args[0], "exit")) exit(0);
    else if(strstr(command,"|") != NULL){ 
      // anything with spaces won't work 
      // ls|wc does work
      // example: cat ayy.txt| grep -v a |sort -r
      int f = fork();
      if(f) wait(&status);
      else{
      FILE *fp;
      char buff[80];
      fp = popen(command, "r");
      fgets( buff, sizeof(buff), fp);
      printf("%s", buff);
      pclose(fp);
      exit(0);}
    }
    else if (!strcmp(args[0], "cd")) 
      if (chdir(args[1]) == -1) printf("Invalid directory.  MSG: %s\n", strerror(errno));
      else ;
    else {
        int f = fork();
        if (f)  wait(&status);
        else if (execvp(args[0], args) == -1) {
          printf("Invalid command.  MSG: %s\n", strerror(errno));
          exit(0);}
    }
}

