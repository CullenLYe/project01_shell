#ifndef SHELL_H
#define SHELL_H

// separates a string input using a char delimeter; returns a string array  
char ** semi_sep(char *line, char *delimiter);

//
void runcmd(char *command);

#endif

