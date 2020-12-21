#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

// function for separating multiple commands on one line
char ** parse_commands(char *line, char *delimiter) {
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

void runcmd(char *command) { // Runs each respective command
    int status;
    char comm[100];
    strcpy(comm,command);
    char **args = parse_commands(command, " ");
    if (!strcmp(args[0], "exit")) exit(0);
    else if(strstr(comm,"|") != NULL){ 
      // example: cat ayy.txt| grep -v a |sort -r
      int f = fork();
      if(f) wait(&status);
      else{        
        FILE *fp, *fo;
        int i = 1;
        char buff[80];
        char **coms = parse_commands(comm, "|");
        if ((fp = popen(coms[0], "r")) == NULL){
                perror("popen");
                exit(0);
        }
        while(coms[i] != NULL){
          if ((fo = popen(coms[i], "w")) == NULL){
                perror("popen");
                exit(0);
          }
          while(fgets(buff, sizeof(buff), fp))
                fputs(buff, fo);
          i++;
        }
        pclose(fo);
        pclose(fp);
        exit(0);
        }
      }
    else if (!strcmp(args[0], "cd")) 
      if (chdir(args[1]) == -1) printf("Invalid directory.  MSG: %s\n", strerror(errno));
      else ;
    else {
        int f = fork();
        if (f)  wait(&status);
        else if (execvp(args[0], args) == -1) {
          printf("Invalid command.  MSG: %s\n", strerror(errno));
          exit(0);
        }
    }
}

// copies strings
void copy_str(char *target, char *source) {
  while (*source) {
    *target = *source;
    source++;
    target++;
  }
  *target = '\0';
}

// redirect function helper
void redirect2(char *command) {
    char *a = malloc(sizeof(char*)*100);
    char *b = malloc(sizeof(char*)*100);
    copy_str(a, command);
    copy_str(b, command);
    char **args = parse_commands(command, " ");

    int not_loop = 1;

    int i;
    for (i = 0; args[i]; i++) {
      if (!strcmp(args[i], "<")) {
        char **args1 = parse_commands(a, "<");
        char **filename = parse_commands(args1[1], " ");
        int fd1 = open(filename[0], O_RDONLY);
        if (fd1 == -1) printf("Error: %s\n", strerror(errno));
        else {
          int backup_stdout = dup(STDOUT_FILENO);
          dup2(fd1, STDIN_FILENO);
          runcmd(args1[0]);
          dup2(backup_stdout, STDIN_FILENO);
          close(fd1);
        }
        not_loop = 0;
        break;
      }
    }

    if (not_loop) runcmd(b);
}

// redirection and piping function
void redirect(char *command) {
    char *a = malloc(sizeof(char*)*100);
    char *b = malloc(sizeof(char*)*100);
    copy_str(a, command);
    copy_str(b, command);
    char **args = parse_commands(command, " ");

    int not_loop, not_loop2 = 1;
    int i;
    for (i = 0; args[i]; i++) {
      if (!strcmp(args[i], ">") || !strcmp(args[i], ">>")) {
        char **args1 = parse_commands(a, ">");
        char **filename = parse_commands(args1[1], " ");
        int fd = 0;
        if (!strcmp(args[i], ">")) fd = open(filename[0], O_WRONLY | O_CREAT | O_TRUNC);
        else fd = open(filename[0], O_APPEND | O_WRONLY | O_CREAT);
        if (fd == -1) printf("Error: %s\n", strerror(errno));
        else {
          int backup_stdout = dup(STDOUT_FILENO);
          dup2(fd, STDOUT_FILENO);
          redirect2(args1[0]);
          dup2(backup_stdout, STDOUT_FILENO);
          close(fd);
        }
        not_loop = 0;
      }
    }

    if (not_loop) redirect2(b);
}
