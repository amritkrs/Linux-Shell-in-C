/*
PURPOSE: PROVIDE HELP FUNCTIONS
*/

#include"help.h"

void help(char a[])
{
	if(a==NULL)
	{
		printf("\nerror:need more arguments:please mention feature name also\n");
		return;
	}
	if(strcmp(a,"pipe")==0)
		help_pipe();
	else if(strcmp(a,"backgrounding")==0)
		help_background();
	else if(strcmp(a,"variable")==0)
		help_variable();
	else if(strcmp(a,"script")==0)
		help_script();
	else if(strcmp(a,"redirection")==0)
		help_redirection();
	else if(strcmp(a,"wildcard")==0)
		help_wildcard();
	else
	{
	 printf("\nsorry:no such feature help available\nplease refer to readme file for more help\n");
	}
}

void help_pipe(void)
{
	printf("\npipe is represented by '|'");
	printf("\nplease separate pipe with spaces");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}

void help_background(void)
{
	printf("\nplease put '&' at last separated by spaces from other parameters");
	printf("\ncheck out your program using ps command");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}

void help_variable(void)
{
	printf("\nfor mathematical evaluation of expression,please put a ' before expression");
	printf("\nexample:a='12\npr a will give 12");
	printf("\nexample:a=amrit\nthis will be treated as string variable.");
	printf("\nso say b=aditya,then\ncmp a b \nNOT MATCHING");
	printf("\nfor more help,see readme.txt");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}

void help_script(void)
{
	printf("\nwe provide u with if and while statement in scripts");
	printf("\nto see an example refer to readme.txt");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}

void help_redirection(void)
{
	printf("\n the support is given for only redirecting output to file or concatenating");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}

void help_wildcard(void)
{
	printf("\nit support tilda '~' expansion ,'*' expansion,and  $' expansion");
	printf("\nfor any problem contact amrit kumar at amritkrs@gmail.com\n");
}
