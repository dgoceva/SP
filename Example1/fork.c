/* fork.c - example of a fork in a program */
/* The program asks for UNIX commands to be typed and inputted to a string*/
/* The string is then "parsed" by locating blanks etc. */
/* Each command and sorresponding arguments are put in a args array */
/* execvp is called to execute these commands in child process */
/* spawned by fork() */

/* cc -o fork fork.c */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
 * parse--split the command in buf into
 *         individual arguments.
 */
int parse(char* buf, char** args)
{
    while (*buf != '\0') {
        /*
         * Strip whitespace.  Use nulls, so
         * that the previous argument is terminated
         * automatically.
         */
        while ((*buf == ' ') || (*buf == '\t'))
            *buf++ = '\0';

        /*
         * Save the argument.
         */
        *args++ = buf;

        /*
         * Skip over the argument.
         */
        while ((*buf != '\0') && (*buf != ' ') && (*buf != '\t'))
            buf++;
    }

    *args = NULL;
    return 0;
}

/*
 * execute--spawn a child process and execute
 *           the program.
 */
void execute(char **args)
{
    int pid, status;

    /*
     * Get a child process.
     */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);

	/* NOTE: perror() produces a short  error  message  on  the  standard
           error describing the last error encountered during a call to
           a system or library function.
       */
    }

    /*
     * The child executes the code inside the if.
     */
    if (pid == 0) {
        execvp(*args, args);
        perror(*args);
        exit(1);

       /* NOTE: The execv() vnd execvp versions of execl() are useful when the
          number  of  arguments is unknown in advance;
          The arguments to execv() and execvp()  are the name
          of the file to be executed and a vector of strings  contain-
          ing  the  arguments.   The last argument string must be fol-
          lowed by a 0 pointer.

          execlp() and execvp() are called with the same arguments  as
          execl()  and  execv(),  but duplicate the shell's actions in
          searching for an executable file in a list  of  directories.
          The directory list is obtained from the environment.
        */
    }

    /*
     * The parent executes the wait.
     */
    while (wait(&status) != pid)
        /* empty */ ;
}
int main()
{
    char buf[1024];
    char *args[64];

    for (;;) {
        /*
         * Prompt for and read a command.
         */
        printf("Command: ");

        if (gets(buf) == NULL) {
            printf("\n");
            exit(0);
        }

        /*
         * Split the string into arguments.
         */
        parse(buf, args);

        /*
         * Execute the command.
         */
        execute(args);

    }
}

