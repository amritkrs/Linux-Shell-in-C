/*PURPOSE:TO WRITE FUNCTION TO DO WILDCARD EXPNSION*/
#include"wildcard_expansion.h"
//MAIN FUNCTION TO HANDLE WILDCARD EXPANSION.
//SUPPORT *,~,$ ALL THREE EXPANSION.
//TYPE echo $(cd;pwd) and see the result.
//type ~amrit and see the expansion.

/*---THIS FUNCTION PERFORMS THE METACHARACTER EXPANSION FOR THE SHELL.---*/
void wildcard_exp(char ***argv,int *argc)
{
        int max_size = 5000;	//MAXIMUM NUMBER OF ARGUMENTS ALLOWED,CAN BE CHANGED IF USED REALLOC.
        int cnt=0;		//COUNT TO KEEP TRACK OF NUMBER OF ARGUMENTS THAT HAS GOT EXPANDED.
        int i=0;		//TEMPORARY VARIABLE.
        int flags=0;		//FLAG IS USED BY WORDEXP FUNCTION.
        int ret;		//RET IS USED FOR ERROR CHECK FROM WORDEXP
        char **tmpargv,**targv;	//TEMPORARY VARIABLES,USED FOR RECEIVING ARGS,AND THEN COPYING TO ARGV.
        int tmpargc,targc;	//SIMILAR AS ABOVE.
        int len;		//LEN IS USED TO FIND STRLEN,USED IN DYNAMIC ALLOCATION.
        int j=0;		//TEMPORARY VARIABLE.
	wordexp_t results;	//STRUCTURE VARIABLE OF WORDEXP_T DEFINED IN WORDEXP.H

        tmpargv = calloc(max_size,sizeof(char*));   //ALLOCATE MEMORY FOR HAVING AT MOST MAX_SIZE ARGS.
	//LOOP FOR COPYING ARGUMENTS TO TMPARGV.
        for(i=0;i<*argc;i++)
        {
                if(check_wild((*argv)[i])==1)	//CHECK IF WILDCARD EXPANSION IS ASKED FOR.
                {
			//CALL WORDEXP AND LET THE RESULTS BE APPENDED.
                        ret = wordexp((*argv)[i],&results,flags);
			//WORDEXP RETURNS 0 IF EVERYTHING WENT FINE,IF NOT PRINT ERROR.
                        if(ret!=0)	
                        {
                                printf("\nerror:_");
                                return;
                        }
			//ALLOCATE MEMORY FOR EACH ARGUMENT BY FINDING ITS SIZE,AND COPY IT TO TMPARGV.
                        for(j=0;j<results.we_wordc;j++)
			{
                                len = strlen(results.we_wordv[j]);
                                if(cnt == max_size)	//NO. EXCEED MAX_SIZE.
                                {
                                        printf("\nerror:- too many arguments");
                                        return;
                                }
                                tmpargv[cnt] = calloc(len+1,sizeof(char));
                                strcpy(tmpargv[cnt],results.we_wordv[j]);
                                cnt++;
                        }
                }
                else
                {
			//JUST COPY ARGV TO TMPARGV.
                        len=strlen((*argv)[i]);
                        if(cnt == max_size)
                        {
                                printf("\nerror:- too many arguments");
                                return;
                        }

                        tmpargv[cnt]=calloc(len+1,sizeof(char));
                        strcpy(tmpargv[cnt],(*argv)[i]);
                        cnt++;
                }
        }
	//NOW ONWARD,WE FIRST FREE ARGV,THEN REALLOCATE MEMORY FOR THEM,THEN COPY FROM TMPARGV.
	tmpargc = cnt;	//CNT HAS KEPT TRACK OF THE NUMBER OF ARGUMENT,SO ASSIGN IT TO TMPARGC.

        targc = *argc;	
        targv = *argv;	//TO FREE ARGV.

	for(i = 0;i < targc; i++)
        {
		free(targv[i]);	//FREE EACH ARGS SEPARATELY.
        }
        free(targv);	//FREE DOUBLE ARRAY.
        (*argv)=NULL;	//JUST TO MAKE SURE NO REUSE.

        (*argv) = calloc(tmpargc+1,sizeof(char*));	//REALLOCATE MEMORY.
	
        for(i=0;i<tmpargc;i++)	//COPY ONE BY ONE,BY ALLOCATING MEMORY.
        {
                len = strlen(tmpargv[i]);
                (*argv)[i] = calloc(len+1,sizeof(char));
                strcpy((*argv)[i],tmpargv[i]);
        }

        (*argv)[tmpargc]=NULL;
        *argc = tmpargc;

        for(i=0;i<tmpargc;i++)	
	{
                free(tmpargv[i]);	//FREE TMPARGV ARGS.
        }
        free(tmpargv);		//FREE TMPARGV.
}

/*--THIS FUNCTION RETURNS 1 IF WILDCARD EXPANSION IS ASKED FOR IN THE WORD PASSED,ELSE RETURN ZERO.--*/
/*---THIS FUNCTION IS CALLED BY MAIN SHELL PROGRAM TO CHECK FOR WILDCARD EXPANSION IF ASKED.---*/
int check_wildcard(int argc,char **argv)
{
        int ret=0;	//RETURN VALUE.
        int i,j;	//TEMPORARY VARIABLES TO BE USED IN LOOPS.
        int len;	//FOR STRLEN.
        for(i=0;i<argc;i++)
        {
                len = strlen(argv[i]);
                for(j=0;j<len;j++)
                {
                        if(argv[i][j]=='*' || argv[i][j]=='$' || argv[i][j]=='~')
                                ret=i+1;
                        break;
                }
                if(ret != 0)
                        break;
        }
        return ret;
}

/*-----THIS FUNCTION IS USED BY WILDCARD_EXP FUNCTION TO CHECK EACH WORD WHETHER THEY REQUIRE 
       EXPANSION OR NOT.------*/
int check_wild(char a[])
{
	int len;
	int i;
	len = strlen(a);
	for(i=0;i<len;i++)
	{
		if(a[i]=='*' || a[i]=='$' || a[i]=='~')
			return 1;
	}
	return 0;
}
