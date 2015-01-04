/*THIS FILE CONTAIN ALL THE FUNCTIONS FOR REDIRECTION*/

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


/*r_argv is used for redirection args*/
char **r_argv;
/*function to tell main that user has asked for redirection*/
int check_red(char **argv)
{
	int i=0;
	while(argv[i]!=NULL)
	{
		if(strcmp(argv[i],">")==0 || strcmp(argv[i],">>")==0)
			return 1;
		i++;
	}
	return 0;
}
/*we provide two types of redirection
  1:- write to file ---">".
  2:- append ---------">>".

  so this function let the program know the type of redirection asked*/
int check_type_red(char **argv)
{
	int i=0;
	
	while(argv[i]!=NULL)
        {
                if(strcmp(argv[i],">")==0)
                        return 1;
		else if(strcmp(argv[i],">>")==0)
			return 2;
                i++;    
        }       
        return 0;
}       
/*same as others*/
void parse_r_argv(char ***r_argv,char **argv,int *t_argc)
{
	static int cal_count=0;
	int len;
	int i=0;
	if(cal_count!=0)
	{
		char **tmp_argv;
		tmp_argv = (*r_argv);
		for(i = 0;i < *t_argc ; i++)
			free(tmp_argv[i]);
		free(tmp_argv);
	}
	cal_count++;
	*t_argc=0;

	if(strcmp(argv[0],">")==0 || strcmp(argv[0],">>")==0)
	{
		printf("\nerror :__  1st char can't be redirection\n");
		exit(50);
	}

	for(i=0; ;i++)
	{
		if(strcmp(argv[i],">")==0 || strcmp(argv[i],">>")==0)
			break;

		*t_argc += 1;
	}

	(*r_argv) = calloc(*t_argc + 1,sizeof(char*));

	for(i=0;i < *t_argc ;i++)
	{
		len = strlen(argv[i]);
		(*r_argv)[i] = calloc(len + 1,1);
		strcpy((*r_argv)[i],argv[i]);
	}

	(*r_argv)[i]=NULL;
}

/*return the filename of file where result is to be redirected*/
char* get_file(char **argv)
{
	char *filename;
	int i=0;
	int len;
	/*last arg is filename*/
	while(argv[i]!=NULL)
	{
		if(strcmp(argv[i],">")==0 || strcmp(argv[i],">>")==0)
		{
			i++;
			len = strlen(argv[i]);
			filename = calloc(len+1,1);
			strcpy(filename,argv[i]);
			return filename;
			
		}
		i++;
	}
	
}

/*create the asked file and then close stdout and exec*/
void re_execute(char **r_argv,char *filename,char **argv)
{
	int fd;
	mode_t mode;
	mode = S_IRWXU;

	if(check_type_red(argv)==1)
	{
		fd = open(filename,O_CREAT|O_WRONLY|O_TRUNC,mode);
	}
	
	else
	{
		fd = open(filename,O_CREAT|O_WRONLY|O_APPEND,mode);
	}
	
	close(1);
	dup(fd);
	close(fd);
	execvp(r_argv[0],r_argv);

}
/*fork process and calls re_execute to exec the args*/
void redirection(char **argv)
{
	char *filename;
	int status;	
	int t_argc=0;
	pid_t pid;
	parse_r_argv(&r_argv,argv,&t_argc);
	filename = get_file(argv);
	
	pid = fork();
	switch (pid)
	{
		case -1:printf("\nswitch error\n");
			exit(20);
			break;
		case 0:	
			re_execute(r_argv,filename,argv);
			break;
		default:
			while(pid!=wait(&status));
			pr_exit(status);
			break;
	}

	free(filename);

}


