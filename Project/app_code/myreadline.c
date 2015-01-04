/*THIS PROGRAM READS AN ARBITRARY LENGTH LINE

  AUTHOR:- AMRIT
*/
/*THERE IS ALREADY GNU GETLINE AND GETDELIM FUNCTIONS BUT TO WRITE MY OWN SIMPLE READLINE FUNCTION I AM WRITING IT */

// STRUCTURE TO BE USED FOR READLINE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include"myreadline.h"
//#include"parsing.c"

/* struct line
{
	size_t buflen;
	char *buf;
	FILE *fp;
};*/

//struct line ebuf;

/*FUNCTION TO INITIALIZE THE BUFFER*/

void Initialize_struct_line(struct line *ebuf)
{

	ebuf->buflen = 0;
	ebuf->fp = stdin;
}

/*FUNCTION TO INITIALIZE BUFFER FOR SCRIPT PROGRAMS*/

void Initialize_struct_line_script(struct line *ebuf,FILE *fp)
{
	ebuf->buflen = 0;
	ebuf->fp = fp;
}
/* IF USER GIVE BUFLEN ZERO ,PROGRAM PUT ITS OWN BUFLEN*/

#define myown_buflen 80;


long myreadline(struct line *ebuf)
{
	char *p;
	char *end;
	char *start;
	
	/*INITIALIZING THE BUFFER LENGTH IF IT IS ZERO */


	if(ebuf->buflen == 0)
	{
		ebuf->buflen = myown_buflen;
	}

	/*ALLOCATE FIRST CHUNK OF MEMORY*/

	p = start = malloc(ebuf->buflen);

	end = p + ebuf->buflen;

	*p = '\0';
	/*START READING FROM FILE USING FGETS FUNCTION*/
	while(fgets(p,end-p,ebuf->fp) != 0)
	{
	
		unsigned long len;
		len = strlen(p);
		if(len == 0)
		{
			/*This only happens when 1st thing on line is a '\0'*/
		
			printf("\n WARNING : NUL CHARACTER SEEN; REST OF LINE IGNORED");
			
			p[0] = '\n' ;
			len = 1;
		}

		/*jump past the line just read */

		p += len;

		/*if the last character isn't a newline,the whole line didn't fit into buffer,
		  get some more buffer and try again*/

		/*this p[-1] though looks unusual,if you see from pointer perspective,it is correct.*/
		if(p[-1]!='\n')
		{
			/*THIS ASSIGNS MORE BUFFER*/
			unsigned long offset;

			offset = p - start;		//calculate offset.
			ebuf->buflen += myown_buflen; //increase buffer length of struct line structure.

			/*---realloc is a very useful function,please learn it thoroughly,else it may
			     cause lots of trouble---*/
			start = (char*)realloc(start,ebuf->buflen);

			p = start + offset;
			end = start + ebuf->buflen;
			*p = '\0';
		}
		else
		{
			/*remove newline*/
			p[-1]= '\0'; 
			break;
		}
	}
	/*ASSIGN TO BUF THE READ LINE*/
	ebuf->buf = start;
	//return value can be used if needed.
	return strlen(ebuf->buf);
}






/*THIS FUNCTION USES SPACES AS DELIMITER TO SEPARATE ARGUMENTS AND ASSIGN IT TO ARGV.
  THERE IS NO LIMIT PUT ON NO. OF ARGUMENTS.*/


void parse_arg(int *argc,char ***argv,char *line)
{
	/*we need to free the argv used previously and set argc to zero before we start filling it up*/

	char ** tmpargv;
	int tmpargc;

	/*we need to free it only if it have been called more than once in the program,so we keep a 
	  static variable to count number of call*/
	
	static int call_count=0;
	
	if(call_count!=0)
	{
		tmpargc = *argc;
		tmpargv = *argv;

		int i;
		for(i = 0;i < tmpargc; i++)	//free each argument by looping over.
		{
			free(tmpargv[i]);
			(*argv)[i]=NULL;
		}

		free(tmpargv);		//free the double array.
		(*argv)=NULL;
	}
	call_count++;

	/*Initialize argc to 0*/
	*argc = 0;
	/*REMOVE LEADING WHITESPACES*/
	while(*line == ' ' || *line == '\t')
		line++;
	/*since we are using dynamic allocation,we need to know how much memory to 
	  allocate.so,first we run through the line to find number of arguments.also
	  we dont want to lose track of line we assign it to one more pointer to do it.*/
	
	char *tmpline;
	tmpline = line;
	/*check if tmpline is not null,then the argument count is at least one,therefore 	   increment argc.*/
	if(*tmpline!='\0')
		(*argc)++;
	
	while(*tmpline!='\0')
	{
	 /*as soon as we encounter any whitespace character,we remove all the consecutive
	   whitespace chars,then check if we reached the end,if not then increment argc.
	 */
		if(*tmpline == ' ' || *tmpline == '\t')
		{
			while(*tmpline == ' ' || *tmpline == '\t')
				tmpline++;
			if(*tmpline!='\0')
				(*argc)++;
		}
		
		if(*tmpline!='\0')
			tmpline++;
	}
	/*Now,we know no. of arguments,we allocate to argv these many numbers of arrays*/
	(*argv) = calloc((*argc+1),sizeof(char*));
	/*Now we can read the variables to track the length of each argument,so that we 
	  can allocate array size for each individuAL ARRAYS*/
	int length=0;
	char *tmp;

	/*WE REINITIALIZE TMPLINE TO LINE,SO THAT WE CAN RUN THROUGH THE LINE ONCE AGAIN
	*/
	tmpline = line;

	int count = 0;
	int charcount=0;

	while(*tmpline != '\0')
	{
		while(*tmpline == ' ' || *tmpline == '\t')
			tmpline++;
		tmp = tmpline;

		//remove whitespaces.
		while((*tmpline!=' ' && *tmpline != '\t') && (*tmpline != '\0'))
		{
			tmpline++;
			length++;
		}

		tmpline = tmp;/*To get back to starting position so that we can save the
				chars of arguments in the array.*/

		(*argv)[count] = calloc(length+1 , sizeof(char));

		count++;


		while((*tmpline!=' ' && *tmpline != '\t')&& (*tmpline!='\0'))
		{


			(*argv)[count-1][charcount] = *tmpline;


			charcount++;
			tmpline++;
		}
		(*argv)[count-1][charcount] = '\0';
		/*we need to reinitialize length to 0 to be used again*/
		length = 0;
		charcount = 0;

	}
	/*the last argument in execvp must be null*/
	(*argv)[*argc] = NULL;

}

/*THIS PARSE FUNCTION IS NEEDED SEPARATELY THOUGH WITHOUT ANY CHANGE IN CODE BECAUSE WE NEED TO FREE THE MEMORY FOR ARGC
  AND ARGV AND SO IT MUST FREE IT SEPARATELY OR ELSE SEGMENTATION FAULT WILL HAPPEN AS EACH ARGV AND ARGC ARE LOCAL VAR-
  IABLES OF THEIR OWN SET OF FUNCTIONS*/
 
void parse_arg_script(int *argc,char ***argv,char *line)
{
	/*we need to free the argv used previously and set argc to zero before we start filling it up*/

	char ** tmpargv;
	int tmpargc;

	/*we need to free it only if it have been called more than once in the program,so we keep a 
	  static variable to count number of call*/
	
	static int call_count=0;
	
	if(call_count!=0)
	{
		tmpargc = *argc;
		tmpargv = *argv;

		int i;
		for(i = 0;i < tmpargc; i++)
		{
			free(tmpargv[i]);
			(*argv)[i]=NULL;
		}

		free(tmpargv);
		(*argv)=NULL;
	}
	call_count++;

	/*Initialize argc to 0*/
	*argc = 0;
	/*REMOVE LEADING WHITESPACES*/
	while(*line == ' ' || *line == '\t')
		line++;
	/*since we are using dynamic allocation,we need to know how much memory to 
	  allocate.so,first we run through the line to find number of arguments.also
	  we dont want to lose track of line we assign it to one more pointer to do it.*/
	
	char *tmpline;
	tmpline = line;
	/*check if tmpline is not null,then the argument count is at least one,therefore 	   increment argc.*/
	if(*tmpline!='\0')
		(*argc)++;
	
	while(*tmpline!='\0')
	{
	 /*as soon as we encounter any whitespace character,we remove all the consecutive
	   whitespace chars,then check if we reached the end,if not then increment argc.
	 */
		if(*tmpline == ' ' || *tmpline == '\t')
		{
			while(*tmpline == ' ' || *tmpline == '\t')
				tmpline++;
			if(*tmpline!='\0')
				(*argc)++;
		}
		
		if(*tmpline!='\0')
			tmpline++;
	}
	/*Now,we know no. of arguments,we allocate to argv these many numbers of arrays*/
	(*argv) = calloc((*argc+1),sizeof(char*));
	/*Now we can read the variables to track the length of each argument,so that we 
	  can allocate array size for each individuAL ARRAYS*/
	int length=0;
	char *tmp;

	/*WE REINITIALIZE TMPLINE TO LINE,SO THAT WE CAN RUN THROUGH THE LINE ONCE AGAIN
	*/
	tmpline = line;

	int count = 0;
	int charcount = 0;

	while(*tmpline != '\0')
	{
		while(*tmpline == ' ' || *tmpline == '\t')
			tmpline++;
		tmp = tmpline;

		while((*tmpline!=' ' && *tmpline != '\t') && (*tmpline != '\0'))
		{
			tmpline++;
			length++;
		}

		tmpline = tmp;/*To get back to starting position so that we can save the
				chars of arguments in the array.*/

		(*argv)[count] = calloc(length+1 , sizeof(char));

		count++;


		while((*tmpline!=' ' && *tmpline != '\t')&& (*tmpline!='\0'))
		{


			(*argv)[count-1][charcount] = *tmpline;


			charcount++;
			tmpline++;
		}
		(*argv)[count-1][charcount] = '\0';
		/*we need to reinitialize length to 0 to be used again*/
		length = 0;
		charcount = 0;

	}
	/*the last argument in execvp must be null*/
	(*argv)[*argc] = NULL;

}


/*to check the working of this file independently.*/
/*int main()
{
	puts("hi");
	FILE *f1;
	struct line line;
//	line.buflen = 0;
//	puts("ks");
//	if(f1 = fopen(stdin,"r")==NULL);
//	line.fp = stdin;
//	puts("failed");
	unsigned long i;
	char **argv;
	int argc;
	while(4)
	{

		Initialize_struct_line(&line);
//		puts("1");
	i = readline(&line);
//	puts(line.buf)char **argv;int argc;
	

	parse_arg(&argc,&argv,line.buf);
	puts("here");
	for(i = 0;i<argc;i++)
		puts(argv[i]);
	free(line.buf);
	line.buf = NULL;
	}
}*/
