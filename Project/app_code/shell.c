#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<time.h>
#include<errno.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<wordexp.h>
#include"myreadline.h"
#include"program_exit.h"
#include"redirection.h"
#include"pipe.h"
#include"background.h"
#include"built_in_command.h"
#include"variable.h"
#include"wildcard_expansion.h"

#define PATH_MAX 100

void print_prompt(void);	//print_prompt function.

/*----action to be taken if ctrl-c is pressed.------*/
void ouch(int sig)
{
	printf("OUCH! - I GOT A SIGNAL %d\n",sig);
}


main()
{
	char **argv;			//same use as mains
	int argc;			//same use as mains
	struct line ebuf;		//to store the input.
	struct sigaction act;		//for signal handling.
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	sigaction(SIGINT,&act,0);

	setup_lexicon();		//to initialize variables at start of program.
		
	/*----the loop for shell---*/
	while(1)
	{
		Initialize_struct_line(&ebuf);	
		print_prompt();
		myreadline(&ebuf);		//to read user input.

		if(check_var_eval(ebuf.buf)==1)	//check for variable manipulation.
                {
                        char *a;		//copy the input line to array a and pass it.
                        int l;
                        l = strlen(ebuf.buf);
                        a = calloc(l,1);
                        strcpy(a,ebuf.buf);
                        add_var(a,0);		//call add_var to do variable manipulation.
                }
		else
		{
			parse_arg(&argc,&argv,ebuf.buf);   //parse the input
			if(check_wildcard(argc,argv)!=0)   //check if metacharacter expansion is needed
			{
				wildcard_exp(&argv,&argc);
			}

	    		if(func_built_in_cmd(argv)==0)	 	//check for built_in_commands
	    		{
				if(check_backgrounding(argv))	//check if user has asked for bg job.
				{
					background(argv);	//call background function.
				}
		
				else if(check_pipe(argv))	//check for pipe.
				{
					pipeline(argv);		//call pipeline to execute pipe.
					
					/*-as pipe processes takelittle time and for such process i 
					   am not waiting in parent to finish,so what happens is that 
					   parent process continue,and print its prompt before pipe 
					   finishes,so i have made parent to wait just a little.
					   this should in general not be done as system call is not 
					   portable.
					*/
					system("sleep 0.05");	
				}
				else if(check_red(argv))	//to check for redirection.
				{
					redirection(argv);	//call redirection fn. to take care.
				}
				else
				{
					int status;	   
					//create a child process,and run the command
					pid_t pid = fork();

					switch(pid)
					{
						case -1:	//error
							printf("\nfork error");
							break;
						case 0:		//child process
				
							execvp(argv[0],argv);
							printf("\nfailed to exit __can't run %s ",argv[0]);
							exit(999);
							break;
						default:	//parent process
							//parent wait for child to finish.
							while(pid!=wait(&status))
								/*DO NOTHING*/;
							//to print exit status of child process.
					//			pr_exit(status); 
								break;
					}//switch
				}//else
	    		}//if
		
		}//else var
		free(ebuf.buf);		//free the allocated memory for input line.
	   
	}//while
	return;
}//main

/*----------print the prompt----------*/
void print_prompt(void)
{
	char buf[PATH_MAX];

                /*get current directory using getcwd,and add to it the relative pathname*/
                if(getcwd(buf,PATH_MAX) == NULL)
                {
                        fprintf(stderr,"\nprogram cd failed : %s",strerror(errno));
                        exit(100);
                }


	printf("[AM-SHELL:%s]$ ",buf);
}

