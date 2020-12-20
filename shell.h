#ifndef SHELL_H
#define SHELL_H

// separates a string input using a char delimeter; returns a string array  
char ** parse_commands(char *line, char *delimiter);

// copies string 
void copy_str(char *target, char *source);

// runs a command based on string input 
void runcmd(char *command);

// redirect function helper
void redirect2(char *command, char *f_name);

// implements redirection 
void redirect(char *command);

#endif

