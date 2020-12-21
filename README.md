## TTMSH
by Jacky Chen, Vincent Jiang, and Cullen Ye\
TNPG: The Three Musketeers

### Features:
- Forks and executes commands.
- Parses multiple commands on one line, using ";".
- Redirection with >, <, >>.
- Piping with |.

---

### Attempted:
 * Tried to allow two redirections in the same command, as in: "tr a-z A-Z < file > another_file"
    * Doesn't work if another_file is already created.
---

### Bugs:
 
---

### Files & Function Headers:
#### main.c
  * Runs the shell.
  * Reads in commands.
  
#### shell.c
  * Interprets all the different commands and directly runs them.
  ```
  /*======== char ** parse_commands() ==========
  Inputs:  char *line, char *delimiter
  Returns: Array of commands, separated by delimeter.

  Uses strtok to separate the individual commands in a single line input.
  ====================*/

  /*======== void runcmd() ==========
  Inputs:  char *command
  Returns: N/A

  This actually interprets the given command. Forks and execvp's the command. This function specially accounts for "exit", redirection, piping, and cd.
  ====================*/

  /*======== void copy_str() ==========
  Inputs:  char *target, char *source
  Returns: N/A

  Copies string from source to target.
  ====================*/
  
  /*======== void redirect() ==========
  Inputs:  char *command
  Returns: N/A

  Directly handles redirection and piping.
  ====================*/
  
   /*======== void redirect2() ==========
  Inputs:  char *command
  Returns: N/A

  Just a helper function for redirect().
  ====================*/
  ```

#### shell.h
  * Header file for shell.c
