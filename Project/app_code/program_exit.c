/*	TO WRITE A PROGRAM THAT WILL PRINT APPROPRIATE MESSAGE FOR PROGRAM TERMINATION

	AUTHOR :- AMRIT
	DATE :- 23-01-13
*/
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
/*-----print the exit message for the process whosw status is passed-----*/
void pr_exit(int status)
{

	if(WIFEXITED(status))
		printf("\nnormal termination,exit status = %d \n",WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("\nabnormal termination,signal number = %d %s",WTERMSIG(status),
		#ifdef WCOREDUMP
			WCOREDUMP(status)?"core file generated!":"");
		#else
			"" );
		#endif

	else if(WIFSTOPPED(status))
		printf("\nchild stopped,signal no. = %d\n",WSTOPSIG(status));
}


