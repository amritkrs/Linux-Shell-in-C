/*	THIS FILE CONTAINS ALL THE FUNCTIONS ONE NEED TO PERFORM PIPE OPERATION .
 	IT SUPPORT MULTIPLE PIPES WHOSE NUMBER IS LIMITED ONLY BY MACHINE INABILITY
	TO HANDLE .

	AUTHOR :- AMRIT
	DATE:-  28-01-13 TO 01-02-13
*/

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


/*	LOGIC:- TO IMPLEMENT MULTIPLE PIPES THE LOGIC USED HERE IS VERY SIMPLE.
		Consider the command ; ls | cat | wc | cat .
		now i keep count of how many instructions i already have finished
		and my parser tracks whether we have reached the last instuction 
		or not.
		now i use even and odd count to perform piping.

		for ls : count = 1 .so input is stdin.output - pipefd[1].
		for cat: count = 2(even).so input is pipefd[0] and output
			 is pipefd2[1];
		for wc : count = 3(odd).so 1st i close pipefd in parent and
			 call pipe function again to re-use it.
			 here input is pipefd2[0] and output is pipefd[1].
		for cat: count = 4(even and last).so no need to refresh pipefd2
			 here but if one more inst. would have been there then 
			 we ought to have refreshed pipefd2.
			 input - pipefd[0]
			 output - stdout.

*/

	       
/*This is a global variable to be used when redirection is mixed with pipe.*/
/*i have assumed that there wont arise a case where redirection is needed 
  before pipes so i have supplied the possibility of redirection only for 
  last command. */

/*g_red_var is put to 1 when redirection is encountered ,which in turn is 
  put to 0 by built_in_command.*/

int g_red_var=0;

/*this is used for parsing pipe arguments repeatedly*/
/*example:- ls | wc | cat
  here the 1st time argv is called it contain ls
  next time it contain wc and then cat
*/

char **l_argv;
/*the next two array are used for file descriptors to contain pipe fds.*/
	
int pipefd[2];
int pipefd2[2];

/*this function is to provide whether the argv in main is having pipe or not*/
int check_pipe(char *argv[]);

/*parse the argument repeatedly as shown in above example*/
void parse_pipe(char **argv,char ***l_argv,int *last);

/*this function is called to execute the different commands and pass their output 
  to pipes.*/
void left_child(char **argv,int last,int count);

/*code for check_pipe*/
/*return 1 if true else false*/
int check_pipe(char *argv[])
{
	int c=0;

	/*ans is used to avoid two return in this program*/
	int ans=0;

	while(argv[c]!=NULL)
	{
		if(strcmp(argv[c],"|")==0)
			ans = 1;
		c++;
	}
	return ans;
}

/*main function for pipe implementation.it is called by main and it handles all 
  the other functions to finish the pipe implementation*/
void pipeline(char **argv)
{
	/*ret is for parent and l_pid is for child*/
	pid_t ret;
	pid_t l_pid;

	/*status to be used if u want the child termination status*/
	int status;
	
	/*this variable is aptly named because it tells me that the pipes are over 
	  and therefore the result should be placed on terminal or redirected if required*/
	int last = 0;
	
	/*this static variable is used to keep track of number of times pipes is encountered*/
	/*its use is already told in logic section above*/
	
	static int count=1;

	/*creat pipe and check for errors*/
	if(pipe(pipefd)<0)
	{
		perror("pipe");
		exit(1);
	}

	if(pipe(pipefd2)<0)
	{
		perror("pipe");
		exit(2);
	}

	/*loop to continue till last command*/
	while(!last)
	{
		/*refresh pipefd to use it again as explained in logic*/
		if((count > 2) && (count % 2)!=0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			if(pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(7);
			}
		}
		/*refresh pipefd2 for even continuation as exp. in logic*/
		else if((count > 2)&&(count % 2)==0)
		{
			close(pipefd2[0]);
			close(pipefd2[1]);
			if(pipe(pipefd2) < 0)
                        {
                                perror("pipe");
                                exit(7);
                        }
		}

		/*parse_pipe separates the arguments for pipe*/
		parse_pipe(argv,&l_argv,&last);

		/*create child process*/
		l_pid = fork();

		/*check for pipe error*/
		if(l_pid < 0)
		{
			perror("fork");
			exit(3);
		}

		/*in child call left child*/
		else if(l_pid == 0)
		{
			left_child(l_argv,last,count);
		
		}
		else
		/*in parent increase the count*/
		count++;
		        
	}
	/*once we r done,we reset count to 1, and close all the open file
	  descriptors in parent*/
	count = 1;
	close(pipefd[0]);
	close(pipefd[1]);
	close(pipefd2[0]);
	close(pipefd2[1]);
}


void left_child(char **argv,int last,int count)
{

	/*first time close only stdout and take the input from stdin.*/
	if(count == 1)
	{
		
		close(pipefd2[0]);


                close(pipefd2[1]);
                close(pipefd[0]);
                close(1);
                dup(pipefd[1]);
                close(pipefd[1]);
	
	
                execvp(argv[0],argv);
                printf("\nexec error\n");
                exit(4);
	}
	/*this one is even call and so from our prior Logic section here
	  we take input from pipefd[0] and output to pipefd[1].*/
	else if((count % 2)==0 && (!last))
	{
		
		
                close(pipefd[1]);
                close(pipefd2[0]);
                close(0);
                dup(pipefd[0]);
                close(pipefd[0]);
		close(1);
		dup(pipefd2[1]);
		close(pipefd2[1]);
                execvp(argv[0],argv);
                printf("\nexec error\n");
                exit(4);
	}
	/*odd:-
		input - pipefd2[0].
		output - pipefd[1].
	*/
	else if((count % 2)!=0 && (!last))
        {


                close(pipefd2[1]);
                close(pipefd[0]);
                close(0);
                dup(pipefd2[0]);
                close(pipefd2[0]);
                close(1);
                dup(pipefd[1]);
                close(pipefd[1]);
                execvp(argv[0],argv);
                printf("\nexec error\n");
                exit(4);
        }
	/*last.
	  	output - stdout.
	*/
	else if(last)
        {
		/*count - even
			input - pipefd[0].
		*/
		if(count % 2 == 0)
		{
	
			
                	close(pipefd2[0]);
                	close(pipefd2[1]);
			close(pipefd[1]);
                	close(0);
                	dup(pipefd[0]);
                	close(pipefd[0]);
			if(check_type_red(argv))
			{
				g_red_var=1;
				redirection(argv);
			}
			else
			{
           			execvp(argv[0],argv);
                		printf("\nexec error\n");
                		exit(4);
        		}
		}	
		

		else
		{
			/*count - odd
				input - pipefd2[0].
			*/
			close(pipefd[0]);
                        close(pipefd[1]);
                        close(pipefd2[1]);
                        close(0);
                        dup(pipefd2[0]);
                        close(pipefd2[0]);
			if(check_type_red(argv))
			{
				g_red_var=1;
				redirection(argv);
			}
			else
			{
                        	execvp(argv[0],argv);
                        	printf("\nexec error\n");
                        	exit(4);
			}
		}
	}

	

}

/*parse args for pipe*/
void parse_pipe(char **argv,char ***l_argv,int *last)
{
	/*unlike other parsing,here parse is called repeatedly to parse the arguments.
	  therefore it must keep track till where in argv it has parsed ,and also count
	  of no. of arguments each time it parse,so that we can free the memory..*/

	/*i tracks till where we finished parsing, so that next call will start from there itself.
	  tmpargc is used to free and allocate memory dynamically for l_argv.*/

	static int i = 0;
	static int tmpargc=0;

	int len;
	int k=0,j=0;
	char **tmpargv;
	tmpargv = *l_argv;
	/*free*/
	if(tmpargc!=0)
	{
		for(j=0;j<tmpargc;j++)
		{
			free(tmpargv[j]);
		}
		free(tmpargv);
	}

	/*reset tmpargc*/
	tmpargc = 0;
	
	/*start from last time left over args.*/
	for(j=i; ;j++)
	{	/*check whether there are no more pipes in argv*/
		if(argv[j]==NULL)
		{
			*last = 1;
			break;
		}
		
		/*encounter pipe,break;*/
		if(strcmp(argv[j],"|")==0)
			break;
		/*inc. tmpargc*/
		tmpargc++;
	}
	
	(*l_argv) = calloc(tmpargc + 1,sizeof(char*));
	
	/*copy args to l_argv*/
	for(j=i,k=0; ;j++,k++)
        {
		/*recheck for last,not needed but still kept for clarity*/
                if(argv[j]==NULL)
                {
                        *last = 1;
                        break;
                }

                if(strcmp(argv[j],"|")==0)
                        break;


		len = strlen(argv[j]);

		(*l_argv)[k] = calloc(len + 1,sizeof(char));
		strcpy((*l_argv)[k],argv[j]);
	}
	
	(*l_argv)[k]=NULL;
	/*inc. i beyond pipe symbol*/
	i = j+1;
	/*if this is last time pipe is enc. make static i to be zero so that it can be used again*/
	if(*last == 1)
	{
		i = 0;
	}
}

/*--------------------------------THANK YOU-------------------------------*/
