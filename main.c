#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

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
      char **commands = parse_commands(buffer, ";");
      int i;
      for (i = 0; commands[i]!=NULL; i++) {
        redirect(commands[i]);
      }
    }
    return 0;
}