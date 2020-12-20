#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

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

// function for trimming string input
char * trim(char *line) {
  int size;
  int j = 0;
  for (size = 0; line[size]!=0; size++);
  if (line[size-1] == ' ') size--; 
  if (line[0] == ' ') {j=1; size--;} 
  char *ret = malloc(sizeof(char*)*size);
  int i;
  for (i = 0; i < size; i++) {
    ret[i] = line[i+j];
  }
  return ret;
}

int main() {
    while (1) {
      char cwd[PATH_MAX];
      getcwd(cwd, sizeof(cwd));
      printf("~%s$ ", cwd); // Shell prompt with current working directory.
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
          if (!strncmp(buffer, "cd", 2)) { // Checks to see if the user used "cd".
          char *dir = buffer+3; // Takes out the directory after the command "cd".
          if (chdir(dir))// Changes directory.
            printf("No such directory: '%s'\n", dir);
          }
          else {
            char *str = trim(commands[i]);
            char **args = parse_args(str); 
            execvp(args[0], args);
          }
        }
        // Parent Process [Waits until the child process is finished.]
        else {int childpid = waitpid(f, &status, 0);}
        
      }
    }
    return 0;
}

