#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char ** parse_args(char *line) {
  char **args = malloc(sizeof(char*)*100);
  char *p = line;
  int i;
  for (i=0; p!=NULL; i++) {
    args[i] = strsep(&p, " ");
  }
  args[i] = NULL;
  return args;
}

// function for separating multiple commands on one line 
char ** semi_sep(char *line) {
  char **commands = malloc(sizeof(char*)*100);
  char *p;
  p = strtok(line, ";");
  int i = 0;
  while (p!=NULL) {
    commands[i] = p;
    p = strtok(NULL, ";");
    i++;
  }
  return commands;
}

// removes " " from front and end of string
char * str_trim(char *line) {
}

int main() {
    while (1) {
      printf("$: "); // Shell prompt.
      char buffer[100];
      fgets(buffer, sizeof(buffer), stdin); // Receives input from user.
      size_t len = strlen(buffer)-1;
      if (buffer[len]=='\n') buffer[len] = '\0'; // Removes the trailing newline from input.
      if (!strcmp(buffer, "exit")) exit(0); // If input is "exit", then exit program.

      int f, status;
      char **commands = semi_sep(buffer);
      int i;
      for (i = 0; commands[i]!=NULL; i++) {
        f = fork();
        if (!f) { // Child Process [This execvp's the user's input.]
          char **args = parse_args(commands[i]);
          //char *str = str_trim(args[0]);
          //execvp(str, args); 
          execvp(args[0], args);
        }
        else {// Parent Process [Waits until the child process is finished.]
          int childpid = waitpid(f, &status, 0);
        }
      }
    }
    return 0;
}


