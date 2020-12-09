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

int main() {
    while (1) {
      printf("$: "); // Shell prompt.
      char buffer[100];
      fgets(buffer, sizeof(buffer), stdin); // Receives input from user.
      size_t len = strlen(buffer)-1;
      if (buffer[len]=='\n') buffer[len] = '\0'; // Removes the trailing newline from input.
      if (!strcmp(buffer, "exit")) exit(0); // If input is "exit", then exit program.

      int f, status;
      f = fork();
      if (!f) { // Child Process [This execvp's the user's input.]
        if (!strncmp(buffer, "cd", 2)) { // Checks to see if the user used "cd".
          char *dir = buffer+3; // Takes out the directory after the command "cd".
          if (chdir(dir)) { // Changes directory.
            printf("No such directory: '%s'\n", dir);
          };
        }
        else {
          char **args = parse_args(buffer);
          execvp(args[0], args);
        }
      }
      else { // Parent Process [Waits until the child process is finished.]
        int childpid = waitpid(f, &status, 0);
      }

    }
    return 0;
}
