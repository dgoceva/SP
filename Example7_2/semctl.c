/*
 * semctl.c:   Illustrate the semctl() function.
 *
 * This is a simple exerciser of the semctl() function. It lets you
 * perform one control operation on one semaphore set. It gives up
 * immediately if any control operation fails, so be careful not
to
 * set permissions to preclude read permission; you won't be able
to
 * reset the permissions with this code if you do.
 */

#include    <stdio.h>
#include    <sys/types.h>
#include    <sys/ipc.h>
#include    <sys/sem.h>
#include    <time.h>
#include    <stdlib.h>

union semun {
               int val;
               struct semid_ds *buf;
               ushort *array;
          };

struct semid_ds semid_ds;

static void   do_semctl();
static void   do_stat();

char    warning_message[] = "If you remove read permission\
    for yourself, this program will fail frequently!";

int main()
{
 union semun    arg;    /* union to pass to semctl() */
 int    cmd,    /* command to give to semctl() */
     i,    /* work area */
     semid,    /* semid to pass to semctl() */
     semnum;    /* semnum to pass to semctl() */

 (void) fprintf(stderr,
    "All numeric input must follow C conventions:\n");
 (void) fprintf(stderr,
    "\t0x... is interpreted as hexadecimal,\n");
 (void) fprintf(stderr, "\t0... is interpreted as octal,\n");
 (void) fprintf(stderr, "\totherwise, decimal.\n");
 (void) fprintf(stderr, "Enter semid value: ");
 (void) scanf("%i", &semid);

 (void) fprintf(stderr, "Valid semctl cmd values are:\n");
 (void) fprintf(stderr, "\tGETALL = %d\n", GETALL);
 (void) fprintf(stderr, "\tGETNCNT = %d\n", GETNCNT);
 (void) fprintf(stderr, "\tGETPID = %d\n", GETPID);
 (void) fprintf(stderr, "\tGETVAL = %d\n", GETVAL);
 (void) fprintf(stderr, "\tGETZCNT = %d\n", GETZCNT);
 (void) fprintf(stderr, "\tIPC_RMID = %d\n", IPC_RMID);
 (void) fprintf(stderr, "\tIPC_SET = %d\n", IPC_SET);
 (void) fprintf(stderr, "\tIPC_STAT = %d\n", IPC_STAT);
 (void) fprintf(stderr, "\tSETALL = %d\n", SETALL);
 (void) fprintf(stderr, "\tSETVAL = %d\n", SETVAL);
 (void) fprintf(stderr, "\nEnter cmd: ");
 (void) scanf("%i", &cmd);

 /* Do some setup operations needed by multiple commands. */
 switch (cmd) {
  case GETVAL:
  case SETVAL:
  case GETNCNT:
  case GETZCNT:
   /* Get the semaphore number for these commands. */
   (void) fprintf(stderr, "\nEnter semnum value: ");
   (void) scanf("%i", &semnum);
   break;
  case GETALL:
  case SETALL:
   /* Allocate a buffer for the semaphore values. */
   (void) fprintf(stderr,
    "Get number of semaphores in the set.\n");
   arg.buf = &semid_ds;
   do_semctl(semid, 0, IPC_STAT, arg);
   if (arg.array =
    (ushort *)malloc((unsigned)
     (semid_ds.sem_nsems * sizeof(ushort)))) {
    /* Break out if you got what you needed. */
    break;
   }
   (void) fprintf(stderr,
    "semctl: unable to allocate space for %d values\n",
    semid_ds.sem_nsems);
   exit(2);
 }

 /* Get the rest of the arguments needed for the specified
    command. */
 switch (cmd) {
  case SETVAL:
   /* Set value of one semaphore. */
   (void) fprintf(stderr, "\nEnter semaphore value: ");
   (void) scanf("%i", &arg.val);
   do_semctl(semid, semnum, SETVAL, arg);
   /* Fall through to verify the result. */
   (void) fprintf(stderr,
    "Do semctl GETVAL command to verify results.\n");
  case GETVAL:
   /* Get value of one semaphore. */
   arg.val = 0;
   do_semctl(semid, semnum, GETVAL, arg);
   break;
  case GETPID:
   /* Get PID of last process to successfully complete a
      semctl(SETVAL), semctl(SETALL), or semop() on the
      semaphore. */
   arg.val = 0;
   do_semctl(semid, 0, GETPID, arg);
   break;
  case GETNCNT:
   /* Get number of processes waiting for semaphore value to
      increase. */
   arg.val = 0;
   do_semctl(semid, semnum, GETNCNT, arg);
   break;
  case GETZCNT:
   /* Get number of processes waiting for semaphore value to
      become zero. */
   arg.val = 0;
   do_semctl(semid, semnum, GETZCNT, arg);
   break;
  case SETALL:
   /* Set the values of all semaphores in the set. */
   (void) fprintf(stderr,
       "There are %d semaphores in the set.\n",
       semid_ds.sem_nsems);
   (void) fprintf(stderr, "Enter semaphore values:\n");
   for (i = 0; i < semid_ds.sem_nsems; i++) {
    (void) fprintf(stderr, "Semaphore %d: ", i);
    (void) scanf("%hi", &arg.array[i]);
   }
   do_semctl(semid, 0, SETALL, arg);
   /* Fall through to verify the results. */
   (void) fprintf(stderr,
    "Do semctl GETALL command to verify results.\n");
  case GETALL:
   /* Get and print the values of all semaphores in the
      set.*/
   do_semctl(semid, 0, GETALL, arg);
   (void) fprintf(stderr,
       "The values of the %d semaphores are:\n",
       semid_ds.sem_nsems);
   for (i = 0; i < semid_ds.sem_nsems; i++)
    (void) fprintf(stderr, "%d ", arg.array[i]);
   (void) fprintf(stderr, "\n");
   break;
  case IPC_SET:
   /* Modify mode and/or ownership. */
   arg.buf = &semid_ds;
   do_semctl(semid, 0, IPC_STAT, arg);
   (void) fprintf(stderr, "Status before IPC_SET:\n");
   do_stat();
   (void) fprintf(stderr, "Enter sem_perm.uid value: ");
   (void) scanf("%hi", &semid_ds.sem_perm.uid);
   (void) fprintf(stderr, "Enter sem_perm.gid value: ");
   (void) scanf("%hi", &semid_ds.sem_perm.gid);
   (void) fprintf(stderr, "%s\n", warning_message);
   (void) fprintf(stderr, "Enter sem_perm.mode value: ");
   (void) scanf("%hi", &semid_ds.sem_perm.mode);
   do_semctl(semid, 0, IPC_SET, arg);
   /* Fall through to verify changes. */
   (void) fprintf(stderr, "Status after IPC_SET:\n");
  case IPC_STAT:
   /* Get and print current status. */
   arg.buf = &semid_ds;
   do_semctl(semid, 0, IPC_STAT, arg);
   do_stat();
   break;
  case IPC_RMID:
   /* Remove the semaphore set. */
   arg.val = 0;
   do_semctl(semid, 0, IPC_RMID, arg);
   break;
  default:
   /* Pass unknown command to semctl. */
   arg.val = 0;
   do_semctl(semid, 0, cmd, arg);
   break;
 }
 return (0);
}

/*
 * Print indication of arguments being passed to semctl(), call
 * semctl(), and report the results. If semctl() fails, do not
 * return; this example doesn't deal with errors, it just reports
 * them.
 */
static void
do_semctl(semid, semnum, cmd, arg)
union semun  arg;
int  cmd,
  semid,
  semnum;
{
 register int      i;   /* work area */

 (void) fprintf(stderr, "\nsemctl: Calling semctl(%d, %d, %d, ", semid, semnum, cmd);
 switch (cmd) {
  case GETALL:
   (void) fprintf(stderr, "arg.array = %p)\n",
       arg.array);
   break;
  case IPC_STAT:
  case IPC_SET:
   (void) fprintf(stderr, "arg.buf = %p)\n", arg.buf);
   break;
  case SETALL:
   (void) fprintf(stderr, "arg.array = [");
   for (i = 0;i < semid_ds.sem_nsems;) {
    (void) fprintf(stderr, "%d", arg.array[i++]);
    if (i < semid_ds.sem_nsems)
      (void) fprintf(stderr, ", ");
   }
   (void) fprintf(stderr, "])\n");
   break;
  case SETVAL:
  default:
   (void) fprintf(stderr, "arg.val = %d)\n", arg.val);
   break;
 }
 i = semctl(semid, semnum, cmd, arg);
 if (i == -1) {
  perror("semctl: semctl failed");
  exit(1);
 }
 (void) fprintf(stderr, "semctl: semctl returned %d\n", i);
 return;
}

/*
 * Display contents of commonly used pieces of the status
structure.
 */
static void
do_stat()
{
 (void) fprintf(stderr, "sem_perm.uid = %d\n",
       semid_ds.sem_perm.uid);
 (void) fprintf(stderr, "sem_perm.gid = %d\n",
       semid_ds.sem_perm.gid);
 (void) fprintf(stderr, "sem_perm.cuid = %d\n",
       semid_ds.sem_perm.cuid);
 (void) fprintf(stderr, "sem_perm.cgid = %d\n",
       semid_ds.sem_perm.cgid);
 (void) fprintf(stderr, "sem_perm.mode = %#o, ",
       semid_ds.sem_perm.mode);
 (void) fprintf(stderr, "access permissions = %#o\n",
       semid_ds.sem_perm.mode & 0777);
 (void) fprintf(stderr, "sem_nsems = %ld\n",
semid_ds.sem_nsems);
 (void) fprintf(stderr, "sem_otime = %s", semid_ds.sem_otime ?
      ctime(&semid_ds.sem_otime) : "Not Set\n");
 (void) fprintf(stderr, "sem_ctime = %s",
       ctime(&semid_ds.sem_ctime));
}
