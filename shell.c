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

int main() {
    while (1) {
      char cwd[PATH_MAX];
      getcwd(cwd, sizeof(cwd));
      printf("ttmsh:%s$ ", cwd); // Shell prompt with current working directory.
      char buffer[100];
      fgets(buffer, sizeof(buffer), stdin); // Receives input from user.
      size_t len = strlen(buffer)-1;
      if (buffer[len]=='\n') buffer[len] = '\0'; // Removes the trailing newline from input.

      int f, status, t;
      char **commands = semi_sep(buffer, ";");
      int i;
      for (i = 0; commands[i]!=NULL; i++) {
        runcmd(commands[i]);
      }
    }
    return 0;
}
