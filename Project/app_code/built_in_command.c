/*
PURPOSE :- BUILT_IN_COMMAND PROVIDED BY THE SHELL ARE ALL DEFINED HERE.
AUTHOR :- AMRIT
*/


/*FUNCTION TO PROVIDE cd COMMAND AS FLEXIBLY AS POSSIBLE*/
/*SUPPORT (.),  (..), AND RELATIVE PATHNAMES*/

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
#include"variable.h"
#include"script.h"



#define PATH_MAX 100
/*---function to change directory.---*/
void cd(char *path)
{
//	char path[PATH_MAX];
	/*if no argument is given then it assumes path to be home directory*/
	if(path == NULL)
	{
		chdir("/home/amrit/Project/app_code");
	}
	//"." is treated as current directory.
	else if(!(strcmp(path,".")))
	{
		/*DONT DO ANYTHING*/
		;
	}
	//".." is treated as parent dirctory.
	else if(!(strcmp(path,"..")))
	{
		chdir("..");
	}
	// if command start with "/" then path is assumed to be absolute.
	else if(*path == '/')
	{
		chdir(path);
	}
	else
	{
		/*code for relative pathname*/
		char *buf;
		buf = calloc(PATH_MAX,sizeof(char));
	
		/*get current directory using getcwd,and add to it the relative pathname*/
		if(getcwd(buf,PATH_MAX) == NULL)
		{
			fprintf(stderr,"\nprogram cd failed : %s",strerror(errno));
			exit(100);
		}
		strcat(buf,"/");
		strcat(buf,path);
		chdir(buf);
	}

}

extern int g_red_var;
extern Lexicon;

/*list of built_in_functions*/
int func_built_in_cmd(char *argv[])
{
	/*ret is value used for return.*/
	/*return 0 if argv doesn't have builtin cmd,else rerturn 1 and execute the command*/
	int ret=0;
	char *tmp;

	if(argv[0]==NULL)
	{
		/*this var is explained in pipe.c*/
		if(g_red_var==1)
		{
			while(getchar() != '\n');
			g_red_var=0;
		}
		ret=1;
	}
	/*bye to exit*/
	else if(strcmp(argv[0],"bye")==0 || strcmp(argv[0],"exit")==0 || strcmp(argv[0],"logout")==0)
	{
		ret = 1;
		exit(100);
	}
	/*cd to change directory*/
	else if(strcmp(argv[0],"cd")==0)
	{
		ret=1;
	
		cd(argv[1]);
	}
	/*$ as starting letter to print env vars.*/
	else if(argv[0][0]=='$')
	{
		ret=1;
		tmp=getenv(argv[0]+1);
		if(tmp==NULL)
		{
			printf("\nerror--:no such variable\n");
		}
		else
			puts(tmp);
	}
		
	/*set to set env variable.*/
	else if(strcmp(argv[0],"set")==0)
	{
		ret=1;
		if(argv[2]==NULL)
		{
			if(putenv(argv[1])!=0)
				perror("set failure");
		}
		else
			{
				if(setenv(argv[1],argv[3],1)!=0)
					puts("error setting env var");
			}
		
	}
	//to remove environment variable.
	else if(strcmp(argv[0],"unset")==0)
	{
		ret=1;
		unsetenv(argv[1]);
	}
	//print the variable value.
	else if(strcmp(argv[0],"pr")==0)
	{
		ret=1;
		Print_var_value(argv[1]);
	}
	//compare b/n 2 string variable and print appropriate message.
	else if(strcmp(argv[0],"cmp")==0)
	{
		ret = 1;
		if(argv[1] == NULL ||argv[2] == NULL)
		{
			puts("error:- invalid no. of arguments");
		}
		else
		{
			cmp_str(argv[1],argv[2]);
		}
	}
	//to return 1/0 just like strcmp in string.h
	else if(strcmp(argv[0],"strcmp")==0)
	{
		int a;
		ret = 1;
                if(argv[1] == NULL ||argv[2] == NULL)
                {
                        puts("error:- invalid no. of arguments");
                }
                else
                {
			a = str_cmp(argv[1],argv[2]);
                        if(a==0)
				return 1;
			else 
				return -1;
                }
		
        }
	//to run the script.
	else if(strcmp(argv[0],"run")==0)
	{
		ret = 1;
		if(argv[1]==NULL)
		{
			puts("error:- invalid no. of arguments");
		}
		else
		run_script(argv[1]);
	}
	//read the variable ,used mainly for script;support only numerical values.
	else if(strcmp(argv[0],"read")==0)
	{
		ret = 1;
		float f;
		scanf("%f",&f);
		if(argv[1] == NULL)
		{
			printf("\nerror:-number of argument is improper\n");
		}
		else
		{
			add_lexicon(argv[1],0,f,NULL);
		}
	}
	else if(strcmp(argv[0],"help")==0)
	{
		ret = 1;
		help(argv[1]);
	}

	return ret;
}

