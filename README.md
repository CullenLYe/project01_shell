## TTMSH
by Jacky Chen, Vincent Jiang, and Cullen Ye\
TNPG: The Three Musketeers

### Features:
- Shell prompt shows your current directory.
- Forks and executes commands.
   - Specifically accounts for "exit", cd, redirection, and piping.
- Parses multiple commands on one line, using ";".
- Redirection with >, <, >>.
- Piping with |.

---

### Attempted:
 * Tried to allow two redirections in the same command, as in: "tr a-z A-Z < file > another_file"
    * Doesn't work if another_file is already created.
---

### Bugs:
 * Limited to 100 characters per line of command.
---

### Files & Function Headers:
#### main.c
  * Runs the shell.
  * Displays current directory in the prompt.
  * Allows the user to type into stdin.
  * Reads in commands & sends them off to be interpreted.
  
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

  Directly handles redirection.
  ====================*/
  
   /*======== void redirect2() ==========
  Inputs:  char *command
  Returns: N/A

  Just a helper function for redirect().
  ====================*/
  ```

#### shell.h
  * Header file for shell.c.
