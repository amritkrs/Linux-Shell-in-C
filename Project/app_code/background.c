#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<time.h>
#include<errno.h>
#include <readline/readline.h>
#include <readline/history.h>
/*b_argv wll be used to contain arguments to be run as background command and b_tmp_argc for its count*/
/*b_tmp_argc also used to free memory and reuse it*/

char **b_argv;
int b_tmp_argc;

/*this function used in main to check if user has asked the process to be put in background*/
int check_backgrounding(char **argv)
{
	int i=0;
	while(argv[i]!=NULL)
	{
		i++;
	}
	i--;
	if(strcmp(argv[i],"&")==0)
		return 1;

	return 0;
}
/*parses the arguments for bg*/
/*same as other parser*/
/*see myreadline.c to understand it*/
void parse_background(char ***b_argv,char **argv,int *tmp_argc)
{
	static int call_count=0;
	int i;
	int len;
	if(call_count!=0)
	{
		char **tmp_argv;

		tmp_argv = (*b_argv);

		for(i=0;i< *tmp_argc;i++)
		{
			free(tmp_argv[i]);
		}

		free(tmp_argv);
	}

	call_count++;
	i=0;
	
	while(strcmp(argv[i],"&")!=0)
		i++;
	
	*tmp_argc=0;
	*tmp_argc = i;

	(*b_argv) = calloc(*tmp_argc + 1,sizeof(char*));
	
	for(i=0;i < *tmp_argc ;i++)
	{
		len = strlen(argv[i]);
		(*b_argv)[i] = calloc(len + 1,1);
		strcpy((*b_argv)[i],argv[i]);

	}

	(*b_argv)[i]=NULL;

}

/*main function which create new process group and thus make the job to run in bg*/
void background(char **argv)
{

	pid_t pid;	//used by fork
	pid_t ret;	//process id used for return check from many system calls
	int status;
	parse_background(&b_argv,argv,&b_tmp_argc);	//parse the input.
	
	/*---create child process---*/
	pid = fork();

	switch (pid)
	{
		case -1: printf("\nfork error\n");	//error
			 exit(20);
			 break;
		
		/*setpgid used to change child process group to separate pgrp whose leader is child*/
		case 0:  if(setpgid(getpid(),0) < 0)
			 {
			 	puts("setpgid error");
				exit(21);
			 }
			/*check for pipe implemetation if any*/
			 if(check_pipe(b_argv))
			 {
				pipeline(b_argv);
			 }
			 else
			 {
			 	execvp(b_argv[0],b_argv);
			 	printf("\nbackground exec failed\n");
			 	exit(22);
			 }
			 break;
		default: /*both parent and child try to make child to change its pgid
			   as the order of fork is unknown*/
			 if(setpgid(pid,0)<0)
			 {
			 //	puts("setpgid error");
			//	exit(23);
			 };
			 ret = waitpid(pid,&status,WNOHANG|WUNTRACED);
			 if(ret < 0)
			 {
				printf("\nwaitpid error\n");
				exit(26);
			 }
			 else if(ret > 0)
			 {
			 	pr_exit(status);
			 }


	                 return;
			 break;
	}
}


