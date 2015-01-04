/*PURPOSE:-THIS IS TO SUPPORT SCRIPTS IN SHELL.
	   IT SUPPORT BOTH WHILE AND IF LOOP.
*/
#include"script.h"

char **argv;		//SAME AS MAIN
int argc;		//SAME AS MAIN
/*---MAIN FUNCTION TO HANDLE SCRIPT EXECUTION.---*/
void run_script(char *filename)		
{

	FILE *fp;
	fp = fopen(filename,"r");
	if(fp == NULL)
	{
		puts("error:-can't open file");
		return;
	}
	struct line mbuf;
	/*---LOOP TO FINISH THE FILE COMMANDS.---*/
	while(1)
	{
		Initialize_struct_line_script(&mbuf,fp);
		/*---CHECK FOR FILE END---*/
		if(feof(fp))
			break;
		//TO TAKE LINE BY LINE INPUT FROM FILE.
		myreadline(&mbuf);
		clear_comment(&mbuf);	//REMOVE COMMENTS
		if(check_empty_line(mbuf.buf)==TRUE)	//CHECK  BLANK LINE
			continue;

		if(check_if(mbuf.buf)==1)	//CHECK FOR IF CONDITION
		{
			if_driver(fp,mbuf.buf);	//CALL IF_DRIVER
		}
		else if(check_while(mbuf.buf)==1)	//CHECK FOR WHILE
		{
			while_driver(fp,mbuf.buf);	//CALL WHILE_DRIVER
		}
		else if(check_var_eval(mbuf.buf)==1)	//CHECK FOR VARS.
                {
                        char *a;	//COPY BUFFER TO ARRAY A AND PASS IT
                        int l;
                        l = strlen(mbuf.buf);
                        a = calloc(l,1);
                        strcpy(a,mbuf.buf);
                        add_var(a,0);	//ADD_VAR,PASS VALUE IS 0 TO SAY THAT PRINT THE ANSWER ON TERMINAL
                }

		else
		{	//PARSE THE LINE
			parse_arg_script(&argc,&argv,mbuf.buf);
			if(check_wildcard(argc,argv)!=0)	//CHECK FOR WILDCARD
                        {
                                wildcard_exp(&argv,&argc);
                        }

			/*checking for built in command*/
			if(func_built_in_cmd(argv)==0)
	    		{
				if(check_backgrounding(argv))
				{
					background(argv);
				}
		
				else if(check_pipe(argv))
				{
					pipeline(argv);
				}
				else if(check_red(argv))
				{
					redirection(argv);
				}
				else
				{
					int status;
					pid_t pid = fork();
	
					switch(pid)
					{
						case -1:
							printf("\nfork error");
							break;
						case 0:
					
							execvp(argv[0],argv);
							printf("\nfailed to exit __can't run %s ",argv[0]);
							exit(100);
							break;
						default:
							while(pid!=wait(&status))
							/*DO NOTHING*/;
		//					pr_exit(status);
							break;
					}//switch
				}//else
	    		}//if
		
		}//else var
	

	   
		free(mbuf.buf);
		
	}//while
}//ADD_VAR

/*---FUNCTION TO REMOVE COMMENTS---*/
void clear_comment(struct line *ebuf)
{
	int i=0;
	while(ebuf->buf[i]!='\0' &&  ebuf->buf[i]!='#')
		i++;
	ebuf->buf[i]='\0';
}

/*---FUNCTION TO CHECK EMPTY LINE. RETURN 1 IF TRUE,ELSE 0---*/
int check_empty_line(char a[])
{
	int l;
	int i=0;
	
	l = strlen(a);
	while((a[i] == ' ' || a[i] == '\t') && a[i] != '\0')
		i++;
	if(i < l)
		return 0;
	return 1;
}

/*---THIS FUNCTION DOES THE JOB OF THE SHELL,IS WRITTEN FOR RECURSIVE USES WHICH IS CALLED UPON BY 
     IF DRIVERS,AND WHILE DRIVERS---*/
void mainprg(struct line *mbuf,FILE *fp)
{
		/*---SAME AS MAIN PROGRAM ABOVE---*/
		clear_comment(mbuf);
		if(check_empty_line(mbuf->buf)==TRUE)
			return;
		if(check_if(mbuf->buf)==1)
		{
			if_driver(fp,mbuf->buf);
		}
		else if(check_while(mbuf->buf)==1)
		{
			while_driver(fp,mbuf->buf);
		}
		else if(check_var_eval(mbuf->buf)==1)
                {
                        char *a;
                        int l;
                        l = strlen(mbuf->buf);
                        a = calloc(l,1);
                        strcpy(a,mbuf->buf);
                        add_var(a,0);
                }

		else
		{
			parse_arg_script(&argc,&argv,mbuf->buf);
			if(check_wildcard(argc,argv)!=0)
                        {
                                wildcard_exp(&argv,&argc);
                        }

			/*checking for built in command*/
			if(func_built_in_cmd(argv)==0)
	    		{
				if(check_backgrounding(argv))
				{
					background(argv);
				}
		
				else if(check_pipe(argv))
				{
					pipeline(argv);
				}
				else if(check_red(argv))
				{
					redirection(argv);
				}
				else
				{
					int status;
					pid_t pid = fork();
	
					switch(pid)
					{
						case -1:
							printf("\nfork error");
							break;
						case 0:
					
							execvp(argv[0],argv);
							printf("\nfailed to exit __can't run %s ",argv[0]);
							exit(100);
							break;
						default:
							while(pid!=wait(&status))
							/*DO NOTHING*/;
		//					pr_exit(status);
							break;
					}//switch
				}//else
	    		}//if
		
		}//else var
	
}

/*---MAIN FUNCTION THAT HANDLES IF/ELSE AND ALSO NESTED ONES USING RECURSION---*/
int if_driver(FILE *fp,char *p)
{
	struct line ebuf;
	int b_cnt=0;		//COUNT FOR BRACES.
	int ret_val=1;		//RETURN VALUE
	
	p = remove_if(p);	//REMOVE IF FROM LINE SO THAT EXPRESSION CAN BE PASSED TO ADD_VAR
	
	if(add_var(p,1)!=0)	//THE ARGUMENT TO ADD_VAR IS 1,BECAUSE WE NEED IT TO RETURN THE ANSWER
	{
		Initialize_struct_line_script(&ebuf,fp);
		myreadline(&ebuf);
		//HERE BRACES ARE ENFORCED AS TOLD IN README.TXT,TO DEVELOP GOOD PROGRAMMING PRACTISE.
		if(check_brace(ebuf.buf)!=1)	
		{
			ret_val=0;
			printf("\nerror:-format for if is not correct\n");
			free(ebuf.buf);
			return ret_val;
		}
		else
		{
			b_cnt++;
			free(ebuf.buf);
		}
	    //LOOP RUNS TILL THE IF BLOCK DOESN'T GET OVER,WHICH IS KNOWN BY BRACE COUNT GOING TO ZERO
		while(b_cnt!=0)
		{
			if(feof(fp))
			      break;

			Initialize_struct_line_script(&ebuf,fp);
			myreadline(&ebuf);
			
			if(check_brace(ebuf.buf)==1)	//CHECK FOR OPENING BRACE
			{
				b_cnt++;		//INCREASE BRACE COUNT
				free(ebuf.buf);
			}
			else if(check_brace(ebuf.buf)==2)	//CHECK FOR CLOSING BRACE
			{
				b_cnt--;		//DECREMENT BRACE COUNT.
				free(ebuf.buf);
			}
			else			//ELSE CALL MAINPRG TO DO USUAL ACTIVITY
			{
				mainprg(&ebuf,fp);
				free(ebuf.buf);
			}
		}//while
		
		Initialize_struct_line_script(&ebuf,fp);
		myreadline(&ebuf);

		while(check_empty_line(ebuf.buf)==1)	//REMOVE EMPTY LINE AFTER IF
		{
			if(feof(fp)==1)
				break;
			free(ebuf.buf);
			Initialize_struct_line_script(&ebuf,fp);
			myreadline(&ebuf);
		}

		/*---SINCE IF HAS BEEN EXECUTED,REMAINING ALL THE OTHER ELSE BLOCKS MUST BE LEFT.---*/
		/*---SO,WE JUST READ THE FILE,AND DONT DO ANYTHING.---*/
		/*---HERE ALSO PHILOSOPHY,IS SAME,CHECK FOR BRACE COUNT.---*/
		while(check_else(ebuf.buf)==1)		//CHECK FOR ELSE STATEMENT
		{
			
			Initialize_struct_line_script(&ebuf,fp);	
			myreadline(&ebuf);
			if(check_brace(ebuf.buf)!=1)	
			{
				ret_val=0;
				printf("\nerror:-format for if is not correct\n");
				free(ebuf.buf);
				return ret_val;
			}
			else
			{
				b_cnt++;
				free(ebuf.buf);
			}

			while(b_cnt!=0)
			{
				if(feof(fp))
				      break;

				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
				
				if(check_brace(ebuf.buf)==1)
				{
					b_cnt++;
					free(ebuf.buf);
				}
				else if(check_brace(ebuf.buf)==2)
				{
					b_cnt--;
					free(ebuf.buf);
				}
				else
				{
					free(ebuf.buf);
				}
			}

			Initialize_struct_line_script(&ebuf,fp);
			myreadline(&ebuf);

			while(check_empty_line(ebuf.buf)==1)
			{
				if(feof(fp))
					break;
				free(ebuf.buf);
				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
			}
		}//while(check_else)
	}//if(add_var...)
	else
	{
		/*--THIS MEANS THAT IF HAS FAILED,SO WE MUST FIRST READ OF IF BLOCK,WITHOUT
		    EXECUTING IT,AND THEN CHECK FOR ELSE STATEMENT,ALSO NESTED IF STATEMENTS--*/
		Initialize_struct_line_script(&ebuf,fp);
		myreadline(&ebuf);
		if(check_brace(ebuf.buf)!=1)
		{
			ret_val=0;
			printf("\nerror:-format for if is not correct\n");
			free(ebuf.buf);
			return ret_val;
		}
		else
		{
			b_cnt++;
			free(ebuf.buf);
		}

		while(b_cnt!=0)
		{
			if(feof(fp))
			      break;

			Initialize_struct_line_script(&ebuf,fp);
			myreadline(&ebuf);
			
			if(check_brace(ebuf.buf)==1)
			{
				b_cnt++;
				free(ebuf.buf);
			}
			else if(check_brace(ebuf.buf)==2)
			{
				b_cnt--;
				free(ebuf.buf);
			}
			else
			{
				/*DO-NOTHING*/
				free(ebuf.buf);
			}
		}//while
		

		Initialize_struct_line_script(&ebuf,fp);
		myreadline(&ebuf);

		while(check_empty_line(ebuf.buf)==1)
		{
				if(feof(fp))
					break;
				free(ebuf.buf);
				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
		}
		
		//CHECK FOR ELSE STATEMENT IN THE BUFFER
		if(check_else(ebuf.buf)==1)
		{
			ebuf.buf = remove_else(ebuf.buf); //REMOVE ELSE FROM BUFFER.
			if(check_if(ebuf.buf)==1)		//CHECK FOR NESTED IF
			{
				if_driver(fp,ebuf.buf);		//CALL IF DRIVER.
			}
			else
			{
				//ONLY ELSE IS THERE,SO JUST EXECUTE IT.
				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
				if(check_brace(ebuf.buf)!=1)
				{
					ret_val=0;
					printf("\nerror:-format for if is not correct\n");
					free(ebuf.buf);
					return ret_val;
				}
				else
				{
					b_cnt++;
					free(ebuf.buf);
				}

				while(b_cnt!=0)
				{
					if(feof(fp))
					      break;
	
					Initialize_struct_line_script(&ebuf,fp);
					myreadline(&ebuf);
				
					if(check_brace(ebuf.buf)==1)
					{
						b_cnt++;
						free(ebuf.buf);
					}
					else if(check_brace(ebuf.buf)==2)
					{
						b_cnt--;
						free(ebuf.buf);
					}
					else
					{
						mainprg(&ebuf,fp);
						free(ebuf.buf);
					}	
				}//while

			}
		}
	}
}	

/*---REMOVE IF FROM THE ARRAY.---*/
char* remove_if(char *p)
{
	while(*p == ' ' || *p == '\t')
	{
		p++;
	}
	
	p++;		//CALL TWO TIMES P++ TO REMOVE IF.
	p++;

	return p;
}

/*---REMOVE ELSE FROM THE ARRAY.---*/
char* remove_else(char *p)
{
	while(*p == ' ' || *p == '\t')
		p++;
	
	p++;		//CALL P++ 4 TIMES,CAN ALSO USE LOOP,BUT IT WILL ADD TO SYSTEM BURDEN.
	p++;
	p++;
	p++;
	
	return p;
}

/*---FUNCTION TO CHECK BRACKETS AND ITS TYPE,
	RETURN 	1: OPENING BRACE
		2: CLOSING BRACE
		0: FOR NO BRACE
---*/
int check_brace(char a[])
{
	int i=0;
	while((a[i] == ' ' || a[i] == '\t') && (a[i] != '\0'))
		i++;
	
	if(a[i] == '{')
		return 1;
	else if(a[i] == '}')
		return 2;
	else
		return 0;
}
//CHECK IF IF CONDITION IS THERE ON LINE
int check_if(char a[])
{
	int i=0;
	if(check_empty_line(a)==1)
		return 0;
	while(a[i] == ' ' || a[i] == '\t')
		i++;

	if((a[i] == 'i') && (a[i+1] == 'f'))
		return 1;
	return 0;
}
//CHECK FOR ELSE CONDITION ON LINE
int check_else(char a[])
{
	int i=0;
	if(check_empty_line(a)==1)
		return 0;
	
	while(a[i] == ' ' || a[i] == '\t')
		i++;
	
	if((a[i] == 'e') && (a[i+1] == 'l') && (a[i+2] == 's') && (a[i+3] == 'e'))
		return 1;
	return 0;
}

/*---THIS ROUTINE IS FOR PERFORMING WHILE LOOP.---*/
/*---IT ALLOWS FOR BRACE EXEMPTION,JUST TO SHOW HOW CAN WE WRITE CODE FOR SUCH PRACTISE.---*/
void while_driver(FILE *fp,char *p)
{
	int ret=1;
	int b_cnt=0;
	struct line ebuf;
	int len;

	p = remove_while(p);		//REMOVE WHILE FROM BUFFER.
	//SINCE WE MUST LOOP BACK TO START OF WHILE BLOCK,WE USE FTELL FN. FOR IT.
	len = ftell(fp);		
	// DO-WHILE LOOP IS USED TO IMPLEMENT BRACELESS BLOCKS AS WELL.
	do
	{
		// EVERY TIME IT COMES TO SAME POSITION IF WHILE CONDITION IS TRUE.
		fseek(fp,len,SEEK_SET);
		
		if(add_var(p,1)!=0)	//IF LOOP CONDITION FAILS,THEN JUST READ THE BLOCK.
		{
			do
			{
				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
				if(check_brace(ebuf.buf)==1)
					b_cnt++;
				else if(check_brace(ebuf.buf)==2)
					b_cnt--;
				else
				{
					mainprg(&ebuf,fp);
				}
			}while(b_cnt!=0);
		}//if(add_var...)
		else
		{
			//EXECUTE THE BLOCK,USE BRACE COUNT FOR KEEPING TRACK OF BLOCK.
			ret = 0;
			do
			{
				Initialize_struct_line_script(&ebuf,fp);
				myreadline(&ebuf);
				if(check_brace(ebuf.buf)==1)
                                b_cnt++;
                        	else if(check_brace(ebuf.buf)==2)
                                b_cnt--;
			}while(b_cnt!=0);
		}
	}while(ret!=0);

}

//REMOVE WHILE FROM BUFFER
char* remove_while(char *p)
{
	int i;
	while(*p == ' ' || *p == '\t')
		p++;
	//HERE WE USE FOR LOOP INSTEAD OF P++ 5 TIMES TO MAKE CODE MORE READABLE.
	for(i=0;i<5;i++)
		p++;
	return p;
}
//CHECK FOR WHILE IN BUFFER.
int check_while(char p[])
{
	int i=0;
	if(check_empty_line(p)==1)
		return 0;
	while(p[i] == ' ' || p[i] == '\t')
		i++;
	if(p[i] == 'w' && p[i+1] == 'h' && p[i+2] == 'i' && p[i+3] == 'l' && p[i+4] == 'e')
		return 1;
	return 0;
}
