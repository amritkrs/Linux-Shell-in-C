/*-----------------------------------VARIABLE.C-------------------------------------------*/
/*THIS FILE CONTAINS ALL THE NECESSARY FUNCTION FOR SUCCESSFUL IMPLEMENTATION OF THE VARIABLES IN SHELL
  IT USES ONE STRUCTURE FOR CONTAINING ALL VARIABLES.
  
  THE IDEA IS TO STORE TWO TYPES OF VALUE FOR A VARIABLE.
	1> STRING
	2> FLOAT
  ALSO WE HAVE PRIORITY FOR OPERATORS WHICH RESIDE IN UNION WITH VALUE OF OPERAND
	
  WE TREAT BOTH OPERATOR AND OPERAND AS A SINGLE VARIABLE WITH APPROPRIATE ENTRIES FILLED IN THEIR DEF.

  THE IDEA IS TO PROVIDE USER TO STORE BOTH VARIABLES OR STRING ONE AT A TIME WITHOUT DECLARING THE 
  DATA TYPE.
 
  BUT TO KNOW THAT USER WANT TO USE THE VAR AS DATA OR STRING,HE MUST PUT A (') BEFORE THE EXPRESSION TO  BE EVALUATED.

  EXAMPLE:-
		A = 12   	//STRING VAR
		B = '13		//FLOAT VAR
		B = AMRIT	//MAKES B A STRING VAR.
		A = '(EXPRESSION(MATHEMATICAL))		//EVALUATE THE EXPRESSION AND ASSIGN TO A
							// A LOSES ITS STRING VALUE

		'EXPRESSION	//EVALUATE AND PRINT THE RESULT ON SCREEN

  USER CAN ALSO WRITE MANY MATHEMATICAL FUNCTIONS AS PROGRAM SUPPORTS IT.
  FUNCTION SUPPORT ARE
  {
	1> SINE
	2> COSINE
	3> SQRT
	ETC.

	BOOLEAN FUNCTION ALSO SUPPORTED
		1> <
		2> >
		3> <=
		4> >=
		5> ==
		6> !=
		7> &
		8> |
  }

  THE MAINTAINER CAN ANY TIME ADD MORE SUPPORT AS AND WHEN NEEDED BY PUTTING IT IN LEXICON,AND WRITING
  ITS WORKING IN DOBINARY OR DOUNARY AS DEPENDENT ON FUNCTION TYPE

--------------------------------------**************---------------------------------------------------

--------------------------------------***FOR PROGRAMMERS***--------------------------------------------
THE FILE USES ALMOST EVERYTHING WHICH YOU WOULD HAVE LEARNT IN C.
JUST FOR LISTING SAKE
{
	1> UNION
	2> STRUCTURE
	3> ENUM
	4> LIST
	5> STACK
	6> DYNAMIC ALLOCATION
	7> REALLOC

	I FEEL I MISSED OUT TREE BUT I COULD HAVE USED IT FOR EVALUATION OF POSTFIX EXPRESSION
	
}

AS SOON AS EXPRESSION IS WRITTEN , I START TO SEE IF EVALUATION IS NEDDED OR NOT,
IF NOT
{
	ASSIGN TO VARIABLE THE STRING VALUE
	
}
ELSE
{
	PUT STRING VALUE TO BE NULL;
	ASSIGN THE VALUE TO ITS FLOAT VAL.
}

NOTE:-IF I ENCOUNTER A DECIMAL VAL SAY 5.
      I THEN STORE IT IN MY LEXICON LIST OF VARIABLES AS IT IS A TOKEN

HOW TO CHECK WHETHER THE VARIABLE IS STRING OR REAL?
:> CHECK IF STR VALUE IS NULL:
	IF YES
		STRING
	ELSE
		REAL
<:

I HAVE USED TOKENS TO DEFINE A VARIABLE,NUMBER,BOOLEAN ETC.,AND ALL OF THEM ARE
MANIPULATED USING LISTS.
	THE CHOICE OF USING LIST WAS DUE TO SEVERAL REASONS:
	1> EASY MANIPULATION
	2> NO NEED FOR USING REALLOC.
	3> SAVES MEMORY
	4> SINCE WE DEAL ONLY WITH BEGINNING LIST TOKENS,THERE IS NO WASTE IN 
	   TRAVERSING THE LIST,HENCE LIST WAS MOST ECONOMICAL CHOICE.

ONE MORE THING:	DON'T GET CONFUSED IF U SEE ANY MATCH FUNCTION RETURNING 0 AS TRUE.
		ALL MATCH FUNCTIONS FOLLOW THE POLICY OF STRCMP FUNCTION.

NOW LETS SEE PROGRAM----------***/

#include"variable.h"

//STARTING MEMORY FOR NUMBER OF TOKEN/VARIABLES
int number_of_token=10000;

//LEXICON IS OUR GLOBAL VAR TO BE USED FOR ACCESSING ANY VAR
Var_list Lexicon; /*global variable*/

/*IF VARIABLE ARRAY FILLED,REALLOC*/
void reassign_mem(void)
{
	struct var *tmp;
	number_of_token *= 2;

	tmp = realloc(Lexicon.Entry,number_of_token);
	if(tmp == NULL)
	{
		puts("fatal error!no memory to realloc");
		exit(2000);
	}
	
	Lexicon.Entry = tmp;

}

/*AS SOON AS PROGRAM STARTS,THIS FUNCTION SETS UP ALL THE PRE SUPPORTED OPERATIONS AND VARIABLES*/
void setup_lexicon(void)
{
	/*----ALLOCATE MEMORY-----*/
	Lexicon.Entry = calloc(number_of_token,sizeof(struct var));
	strcpy(Lexicon.Entry[0].name,"");
	Lexicon.Entry[0].kind = ENDEXPR;
	Lexicon.Entry[0].str  = NULL;
	
	strcpy(Lexicon.Entry[1].name,"(");
	Lexicon.Entry[1].kind = LEFTPAREN;
	Lexicon.Entry[1].str  = NULL;
	
	strcpy(Lexicon.Entry[2].name,")");
        Lexicon.Entry[2].kind = RIGHTPAREN;
	Lexicon.Entry[2].str  = NULL;

	strcpy(Lexicon.Entry[3].name,"@");		/*negation*/
        Lexicon.Entry[3].kind = UNARYOP;
	Lexicon.Entry[3].info.pri = 6;
	Lexicon.Entry[3].str  = NULL;

	strcpy(Lexicon.Entry[4].name,"abs");              
        Lexicon.Entry[4].kind = UNARYOP;
        Lexicon.Entry[4].info.pri = 6;
	Lexicon.Entry[4].str  = NULL;

	strcpy(Lexicon.Entry[5].name,"sqrt");            
        Lexicon.Entry[5].kind = UNARYOP;
        Lexicon.Entry[5].info.pri = 6;
	Lexicon.Entry[5].str  = NULL;

	strcpy(Lexicon.Entry[6].name,"exp");            
        Lexicon.Entry[6].kind = UNARYOP;
        Lexicon.Entry[6].info.pri = 6;
	Lexicon.Entry[6].str  = NULL;

	strcpy(Lexicon.Entry[7].name,"ln");            
        Lexicon.Entry[7].kind = UNARYOP;
        Lexicon.Entry[7].info.pri = 6;
	Lexicon.Entry[7].str  = NULL;

	strcpy(Lexicon.Entry[8].name,"log10");
        Lexicon.Entry[8].kind = UNARYOP;
        Lexicon.Entry[8].info.pri = 6;
	Lexicon.Entry[8].str  = NULL;

	strcpy(Lexicon.Entry[9].name,"sin");            
        Lexicon.Entry[9].kind = UNARYOP;
        Lexicon.Entry[9].info.pri = 6;
	Lexicon.Entry[9].str  = NULL;

	strcpy(Lexicon.Entry[10].name,"cos");            
        Lexicon.Entry[10].kind = UNARYOP;
        Lexicon.Entry[10].info.pri = 6;
	Lexicon.Entry[10].str  = NULL;

	strcpy(Lexicon.Entry[11].name,"tanh");
        Lexicon.Entry[11].kind = UNARYOP;
        Lexicon.Entry[11].info.pri = 6;
	Lexicon.Entry[11].str  = NULL;

	strcpy(Lexicon.Entry[12].name,"+");
        Lexicon.Entry[12].kind = BINARYOP;
        Lexicon.Entry[12].info.pri = 4;
	Lexicon.Entry[12].str  = NULL;

	strcpy(Lexicon.Entry[13].name,"-");
        Lexicon.Entry[13].kind = BINARYOP;
        Lexicon.Entry[13].info.pri = 4;
	Lexicon.Entry[13].str  = NULL;

	strcpy(Lexicon.Entry[14].name,"*");
        Lexicon.Entry[14].kind = BINARYOP;
        Lexicon.Entry[14].info.pri = 5;
	Lexicon.Entry[14].str  = NULL;

	strcpy(Lexicon.Entry[15].name,"/");
        Lexicon.Entry[15].kind = BINARYOP;
        Lexicon.Entry[15].info.pri = 5;
	Lexicon.Entry[15].str  = NULL;

	strcpy(Lexicon.Entry[16].name,"%");
        Lexicon.Entry[16].kind = BINARYOP;
        Lexicon.Entry[16].info.pri = 5;
	Lexicon.Entry[16].str  = NULL;

	strcpy(Lexicon.Entry[17].name,"^");
        Lexicon.Entry[17].kind = BINARYOP;
        Lexicon.Entry[17].info.pri = 6;
	Lexicon.Entry[17].str  = NULL;

	strcpy(Lexicon.Entry[18].name,"pi");
        Lexicon.Entry[18].kind = OPERAND;
        Lexicon.Entry[18].info.val = 3.14159;
	Lexicon.Entry[18].str  = NULL;

	strcpy(Lexicon.Entry[19].name,"e");
        Lexicon.Entry[19].kind = OPERAND;
        Lexicon.Entry[19].info.val = 2.71828;
	Lexicon.Entry[19].str  = NULL;
	
	strcpy(Lexicon.Entry[20].name,"<");
        Lexicon.Entry[20].kind = BINARYOP;
        Lexicon.Entry[20].info.pri = 3;
        Lexicon.Entry[20].str  = NULL;

	strcpy(Lexicon.Entry[21].name,">");
        Lexicon.Entry[21].kind = BINARYOP;
        Lexicon.Entry[21].info.pri = 3;
        Lexicon.Entry[21].str  = NULL;

	strcpy(Lexicon.Entry[22].name,"<=");
        Lexicon.Entry[22].kind = BINARYOP;
        Lexicon.Entry[22].info.pri = 3;
        Lexicon.Entry[22].str  = NULL;

	strcpy(Lexicon.Entry[23].name,">=");
        Lexicon.Entry[23].kind = BINARYOP;
        Lexicon.Entry[23].info.pri = 3;
        Lexicon.Entry[23].str  = NULL;

	strcpy(Lexicon.Entry[24].name,"&");
        Lexicon.Entry[24].kind = BINARYOP;
        Lexicon.Entry[24].info.pri = 2;
        Lexicon.Entry[24].str  = NULL;

	strcpy(Lexicon.Entry[25].name,"|");
        Lexicon.Entry[25].kind = BINARYOP;
        Lexicon.Entry[25].info.pri = 2;
        Lexicon.Entry[25].str  = NULL;

	strcpy(Lexicon.Entry[26].name,"==");
        Lexicon.Entry[26].kind = BINARYOP;
        Lexicon.Entry[26].info.pri = 2;
        Lexicon.Entry[26].str  = NULL;

	strcpy(Lexicon.Entry[27].name,"!=");
	Lexicon.Entry[27].kind = BINARYOP;
	Lexicon.Entry[27].info.pri = 2;
	Lexicon.Entry[27].str = NULL;

	Lexicon.count = 27;	//TO KEEP TRACK OF NUMBER OF VARIABLES
}

/*TO CHECK IF THIS FILE FUNCTION IS NEEDED*/
int check_var_eval(char a[])
{
	if(check_assign(a) ==1 || check_evaluate(a) == 1)
		return 1;
	return 0;
}

/*RETURN PRIORITY OF GIVEN TOKEN*/
int priority(char a[])
{
	int i=0;
	int j;

	j = Lexicon.count;	

	for(i=3;i<=j;i++)
	{
		 if(strcmp(a,Lexicon.Entry[i].name)==0)
                {
                        return Lexicon.Entry[i].info.pri;
                }
	}
	return 0;
}

/*RETURN TYPE OF TOKEN*/
KindType kind(char a[])
{
	int count;
	count = Lexicon.count;
	int i=0;

	if(a==NULL)
		return ENDEXPR;

	for(i=1;i<=count;i++)
	{
		if(strcmp(a,Lexicon.Entry[i].name)==0)
		{
			return Lexicon.Entry[i].kind;
		}
	}

	//error_message("no such variable",FATAL);
}

/*RETURN TRUE IF EVALUATION IS NEEDED*/
int check_evaluate(char a[])
{
	int i=0;
	for(i=0;a[i]!='\0';i++)
	{
		if(a[i]=='\'')
			return 1;
	}
	return 0;
}

/*CREATE LIST OF TOKENS*/
void Createlist(char *exp,List infix_l)
{
	char p[MAXNAME];	//store var name
	int cnt;		
	

	while((*exp == ' ' || *exp == '\t')  && *exp!='\0')	//remove spaces
		exp++;
	if(*exp=='\'')				//override check eval symbol.
		exp++;
	
	if(*exp == '\0')
		return;
	while(*exp!='\0')			//read till end of line
	{
		while((*exp == ' ' || *exp == '\t') && *exp!='\0')
                exp++;

		if(match_char(*exp)==0)		//if variable
		{
			exp = Extract_word(exp,p);	
			cnt = Count(infix_l);
			InsertAfter(p,infix_l,cnt);
		}
		else if(match_num(*exp)==0)	//if number
		{
			exp = Extract_num(exp,p);
			cnt = Count(infix_l);
			InsertAfter(p,infix_l,cnt);
			add_value(p,0,p);
		}
		else if(match_bool(*exp)==0)	//if boolean op
		{
			exp = Extract_bool(exp,p);
			cnt = Count(infix_l);
			InsertAfter(p,infix_l,cnt);
		}
		else
		{
			p[0] = *exp;		//else single letter operator
			p[1]='\0';
			cnt = Count(infix_l);
			InsertAfter(p,infix_l,cnt);
			exp++;
		}
	}
}

int match_bool(char a)		//return true if bool char is found
{
	if(a =='>' || a == '<' || a == '=' || a == '!')
		return 0;
	return -1;
}

char* Extract_bool(char *exp,char p[])		//extract bool operator
{
	int i=0;
	p[i] = *exp;
	exp++;
	i++;

	if(match_bool(*exp)==0)
	{
		p[i]=*exp;
		exp++;
		i++;
	}

	p[i] = '\0';
	return exp;
}

int match_num(char a)		//return 0 if its a number
{
	int i = 0;
	char num[] = "1234567890.";
	for(i = 0; num[i]!='\0'; i++)
	{
		if(num[i] == a)
			return 0;
	}

	return -1;
}

char* Extract_num(char *exp,char s[])	//extract the number from array
{
	int i=0;

	while(m_break_num(*exp)!=0)
	{
		s[i] = *exp;
		i++;
		exp++;
	}
	s[i] = '\0';
	return exp;
}

int m_break_num(char a)		//return 1 if the char is not a num
{
	int i=0;
	if(match_num(a)!=0)
		return 0;
	return 1;
}

char* Extract_word(char *exp,char *s)	//extract the word
{
	int i=0;
	while(match_break(*exp)!=0)
	{
		s[i]=*exp;
		i++;
		exp++;
	}
	

	s[i]='\0';
	return exp;
}


int match_break(char a)		//return 1 if char a is not a char type
{
	char mbreak[] = "+-*^%@/' '()<>=!";
	int i=0;
	if(a == '\0')
	{
		return 0;
	}
	while(mbreak[i]!='\0')
	{
		if(mbreak[i]==a)
			return 0;
		i++;
	}
	return -1;
}

int match_char(char a)	//return 0 if a is char
{
	char match_alpha[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i=0;
	if(a == '\0')
        {
                return 0;
        }
        while(match_alpha[i]!='\0')
        {
                if(match_alpha[i]==a)
                        return 0;
                i++;
        }
        return -1;
}

/*-----MAIN FUNCTION WHICH MANAGE ENTIRE VARIABLE HANDLING-------*/
/*---RET IS 1 MEANS RETURN,0 MEANS DISPLAY ON SCREEN---*/
/*---IT USES LIST FOR KEEPING TOKENS---*/
int add_var(char exp[],int ret)		
{
	int i=0;
	float eval_ans;		//to store answer of evaluation expression
	char eval[20];
	char var_name[MAXNAME];		//VARIABLE NAME SHOULD NOT EXCEED MAXNAME.
	List infix_list;		//INFIX TOKENS
	List postfix_list;		//POSTFIX TOKENS
	
	// HEADER ASSUMED FOR LIST MANIPULATION
	infix_list = malloc(sizeof(struct node));	
	postfix_list = malloc(sizeof(struct node));

	if(infix_list == NULL || postfix_list == NULL)	//ERROR CHECK FOR MALLOC
	{
		printf("\nmemory not enough\n");
		exit(1000);
	}

	infix_list->Next = NULL;
	postfix_list->Next = NULL;

	if(check_assign(exp)==1)	//if '=' is there
	{
		/*store variable name*/
		i=0;
		int sp_val=0;	//to account for end of var_name and only spaces left
		char *tmp;	//to account for the knowledge of var_name end except for leftover spaces
		while(*exp==' ' || *exp=='\t')
			exp++;
		while(*exp!='=')
		{
			/*to remove all the spaces once the variable name ends i do this*/
			{
				tmp = exp;
				while(*tmp!='=')
				{
					if(*tmp!=' ')
						break;
					tmp++;
				}
				if(*tmp == '=')
				{
					sp_val=1;
					while(*exp!='=')
						exp++;
				}
			}

			if(sp_val != 1)
			{
			if(i==29)	/*the var_nmae is exceeding limit,TRUNCATE*/
			{
			 	while(*exp!='=')
					exp++;
				break;
			}
			
			else
			{

			var_name[i] = *exp;
			exp++;
			i++;
			}//else
			
			}//if(sp_val)
		}//while

		exp++;
		var_name[i]='\0';
	
		
		if(check_evaluate(exp)==1)
		{
			/*carry out evaluation*/
			Createlist(exp,infix_list);

			infix_to_postfix(infix_list,postfix_list);

			eval_ans = evaluate(postfix_list);
			
			add_lexicon(var_name,0,eval_ans,NULL);
		
		}//check_evaluate

		else
		{
			/*string value,just add it.*/
			add_lexicon(var_name,0,1,exp);
		}

	}//check_assign

	else
	{
		/*no variable to assign*/
		if(check_evaluate(exp)==1)
		{
			Createlist(exp,infix_list);
			infix_to_postfix(infix_list,postfix_list);
			eval_ans = evaluate(postfix_list);	
		
			/*ret = 0,implies that return ans on terminal,
			else it implies return the answer to program*/

			if(ret == 0)
			{
				printf("%f\n",eval_ans);
			}
			else
			{
				return eval_ans;
			}
		}
	}//else
	return ret;
}


/* return first element of list in p[]*/
void Gettoken(char p[],List l)
{
	char *a;
	TopandPop(l,p);
}

/*check if '=' is there*/
int check_assign(char a[])
{
	int i=0;
	while(a[i]!='\0')
	{
		if(a[i] == '=')
		{
			//check if bool operator is not confused with assign
			if(a[i-1]=='=' || a[i+1]=='=' || a[i-1]=='<' || a[i-1]=='>' || a[i-1]=='!')
			{
				i++;
				continue;
			}
			return 1;
		}
		i++;
	}

	return -1;
}

/*---THIS FUNCTION CONVERT INFIX TO POSTFIX EXPRESSION FOR ECONOMICAL EVALUATION OF EXPRESSION---*/
/*---IT USES STACK DATA STRUCTURE TO DO THIS---*/
/*---NOTE:- SINCE I HAVE USED STACKS USING LIST IMPLEMENTATION,TO DELETE FIRST ELEMENT,I USE POP &                  LIKEWISWE.---*/
void infix_to_postfix(List infix_l,List postfix_l)
{
	char *p;
	int cnt;
	Stack stack;
	stack = CreateStack();
	char token[MAXNAME],tmp[MAXNAME];
	KindType type;

	do
	{
		/*since i am using stack implementation using linked lists,to get the first value in 
		  list i will be using Top of stack,to delete first element,use pop*/
		if(!IsEmpty(infix_l))
		{
			Gettoken(token,infix_l);
		}
		switch(type = kind(token))
		{
			case OPERAND:
				cnt = Count(postfix_l);
				InsertAfter(token,postfix_l,cnt);
				break;
			case LEFTPAREN:
				Push(token,stack);
				break;
			case RIGHTPAREN:
				while(!IsEmpty(stack))
				{
					TopandPop(stack,tmp);
					
					if(kind(tmp)==LEFTPAREN)
						break;

					cnt = Count(postfix_l);
					InsertAfter(tmp,postfix_l,cnt);
				}
				break;
			case UNARYOP:
			case BINARYOP:
				do
				{

			 	      if(IsEmpty(stack))
				      {
				      		break;
				      }
				      else
				      {
				      	p = Top(stack);
					strcpy(tmp,p);
					if(kind(tmp)==LEFTPAREN)
						break;
					else if(priority(tmp)!=priority(token) &&                                                                                        priority(token)==MAXPRIORITY)
						break;
					else if(priority(token) > priority(tmp))
						break;

					else
					{
						TopandPop(stack,tmp);
						cnt = Count(postfix_l);
						InsertAfter(tmp,postfix_l,cnt);
					}

				       }
				  }while(1);

				  Push(token,stack);
				  break;
			  
		}//switch
		}while(!IsEmpty(infix_l));
		
		while(!IsEmpty(stack))
                {
                         TopandPop(stack,tmp);
                         cnt = Count(postfix_l);
                         InsertAfter(tmp,postfix_l,cnt);
                }

}
	

/*---FUNCTION TO ADD VARIABLES IN LEXICON LIST OF VARIABLES---*/
void add_lexicon(char name[],KindType k,float f,char *val)
{
	int count;
	int i,l;

	/*IF RUN OUT OF MEMORY,REALLOC*/
	if(Lexicon.count == number_of_token)
		reassign_mem();	
	
	//VAL IS NULL => USE IT AS FLOAT VARIABLE
	if(val == NULL)
	{
		count = Lexicon.count;
		count++;
		//IF NAME ALREADY THERE,JUST CHANGE ITS VALUE
		if(check_var(name)==1)
		{
			i = get_count(name);
			Lexicon.Entry[i].info.val=f;
			Lexicon.Entry[i].str=NULL;
		}
		//ELSE ADD A NEW VARIABLE
		else
		{
			i = count;
			strcpy(Lexicon.Entry[i].name,name);
			Lexicon.Entry[i].info.val = f;
			Lexicon.Entry[i].str = NULL;
			Lexicon.count += 1;
		}
	}
	//ELSE ITS A STRING VARIABLE
	else
	{
		count = Lexicon.count;
		count++;
		if(check_var(name)==1)
		{
			i = get_count(name);
			//free(Lexicon.Entry[i].str);
			l = strlen(val);
			
			Lexicon.Entry[i].str = calloc(l+1,sizeof(char));
			
			strcpy(Lexicon.Entry[i].str,val);
		}

		else
		{
			i = count;
			strcpy(Lexicon.Entry[i].name,name);
			Lexicon.Entry[i].kind = k;
			
			l = strlen(val);
			Lexicon.Entry[i].str = calloc(l+1,sizeof(char));

			strcpy(Lexicon.Entry[i].str,val);
			Lexicon.count += 1;


		}

	}
}


/*---TO CHECK IF VARIABLE IS ALREADY EXISTING IN LEXICON---*/
int check_var(char n[])
{
	int i,count;
	count = Lexicon.count;

	for(i = 18; i <= count;i++)
	{
		if(strcmp(Lexicon.Entry[i].name,n)==0)
		{
			return 1;
		}

	}
	return 0;
}

/*---RETURN THE POSITION NUMBER OF THE VARIABLE---*/
int get_count(char n[])
{
	int i,count;
        count = Lexicon.count;

        for(i = 1; i <= count;i++)
        {
                if(strcmp(Lexicon.Entry[i].name,n)==0)
                {
                        return i;
                }

        }

	
}

/*---FUNCTION TO EVALUATE POSTFIX EXPRESSION---*/
float evaluate(List Postfix_l)
{
	int i,count;
	count = Lexicon.count;
	char a[20];
	float x,y,f;
	KindType type;

	Stack_f S;
	S = CreateStack_f();
	while(!IsEmpty(Postfix_l))
	{
		Gettoken(a,Postfix_l);
		switch(type = kind(a))
		{
			case OPERAND:
				i = get_count(a);
				if(i > count)
				{
					puts("var not declared");
					exit(1004);
				}
				if(Lexicon.Entry[i].str!=NULL)
				{
					puts("var has no number value");
					exit(1005);
				}

				f = Lexicon.Entry[i].info.val;
				Push_f(f,S);
				break;
			case UNARYOP:
				f = TopandPop_f(S);
				f = DoUnary(f,a);
				Push_f(f,S);
				break;
			case BINARYOP:
				y = TopandPop_f(S);
				x = TopandPop_f(S);

				f = DoBinary(x,y,a);
				Push_f(f,S);
				break;
		}
	}
	
	if(IsEmpty_f(S))
	{
		puts("INVALID EXPRESSION");
		exit(1005);
	}

	f = TopandPop_f(S);

	if(!IsEmpty_f(S))
	{
		puts("INVALID EXPRESSION");
		       exit(1005);
	}

		
	return f;
}

/*---TO ADD NUMBERS AS VARIABLES AS AND WHEN ENCOUNTERED---*/
/*---NAME WILBE SAME AS VALUE---*/
void add_value(char name[],KindType k,char *val)
{
	float f;
	int count,i;

	if(Lexicon.count == number_of_token)
                reassign_mem();


	f = get_num(val);

	count = Lexicon.count;
	if(check_var(name)==1)
	{
		i = get_count(name);
		Lexicon.Entry[i].info.val = f;
	}
	else
	{
		count ++;
		i = count;
		strcpy(Lexicon.Entry[i].name,name);
		Lexicon.Entry[i].kind = k;
		Lexicon.Entry[i].str = NULL;
		Lexicon.Entry[i].info.val = f;
		Lexicon.count += 1;
	}
}

/*---CONVERT ARRAY OF CHAR TO NUMBER---*/
float get_num(char a[])
{
	int i=0,n,j,l;
	float f=0;

	l = strlen(a);

	if(check_float(a)==1)
	{
		n = get_point(a);

		for(j = 0; j < n; j++)
		{
			i = i*10;
			i += a[j] - 48;
		}

		for(j = n+1;j<l;j++)
		{
			f = f*10;
			f += a[j]-48;
		}

		for(j = 0; j<(l-n-1);j++)
		{
			f = f/10;
		}

		f = i+f;

		return f;
	}
	else
	{
		for(j=0;j<l;j++)
		{
			i = i*10;
			i += a[j]-48;
		}
		f = i;
		return f;
	}
}

/*---CHECK WHETHER THE NUMBER IS INT OR FLOAT---*/
int check_float(char a[])
{
	int i=0;
	while(a[i]!='\0')
	{
		if(a[i]=='.')
			return 1;

		i++;
	}
	return 0;
}

/*RETURN POSITION OF POINT IN REAL NUMBER*/
int get_point(char a[])
{
	int i=0;
	while(a[i]!='\0')
	{
		if(a[i]=='.')
			return i;
		i++;
	}
}

/*PERFORM BINARY OPERATION*/
float DoBinary(float x, float y,char a[])
{
	int i,j;
	i = get_count(a);
	j = Lexicon.Entry[i].info.pri;

	switch(i)
	{
		case 12:
			return x+y;
		case 13:
			return x-y;
		case 14:
			return x*y;
		case 15:
			return x/y;
		case 20:
			return (x<y?1:0);
		case 21:
			return (x>y?1:0);
		case 22:
			return (x<=y?1:0);
		case 23:
			return (x>=y?1:0);
		case 24:
			return (x&&y);
		case 25:
			return (x||y);
		case 26:
			return (x==y);
		case 27:
			return (x!=y);
	}


}

/*PERFORM UNARY OPERATION*/
float DoUnary(float x,char a[])
{
	int i,j;
	int cnt;

	i = get_count(a);
	
	switch(i)
	{
		case 3:
			return (-x);
		case 5:
			return sqrt(x);
		case 6:
			return exp(x);
		case 7:
			return log(x);
		case 8:
			return log(x);
		case 9:
			return sin(x);
		case 10:
			return cos(x);
	}
}

/*PRINT THE VALUE OF VARIABLE*/
void Print_var_value(char a[])
{
	int i;
	int cnt;

	cnt = Lexicon.count;

	i = get_count(a);

	if(i > cnt)
	{
		printf("\nNO SUCH VARIABLE\n");
	}

	else if(Lexicon.Entry[i].str == NULL)
	{
		printf("\n%s = %f \n",a,Lexicon.Entry[i].info.val);
	}
	else
	{
		printf("\n%s = %s\n",a,Lexicon.Entry[i].str);
	}
}

//to be used for user
/*RETURN TRUE/FALSE MESSAGE ON SCREEN IF STRING MATCHES OR NOT RESPECTIVELY*/
void cmp_str(char a[],char b[])
{
	int i,j;
	int cnt;
	

	cnt = Lexicon.count;

	i = get_count(a);
	j = get_count(b);

	if(i > cnt || j > cnt)
	{
		printf("\nERROR :- ONE OF THE VAR NOT DECLARED\n");
	}
	else if(Lexicon.Entry[i].str == NULL || Lexicon.Entry[j].str ==NULL)
	{
		puts("\nERROR:- VAR NOT DECLARED\n");
	}
	else
	{
		if(strcmp(Lexicon.Entry[i].str,Lexicon.Entry[j].str)==0)
		{
			printf("\nMATCHING\n");
		}
		else
		{
			printf("\nNOT MATCHING\n");
		}
	}
}

//to be used for script sake where ret value is needed

/*RETURN 0/1 IF MATCHES OR NOT*/
int str_cmp(char a[],char b[])
{
        int i,j;
        int cnt;
	int ret;

        cnt = Lexicon.count;

        i = get_count(a);
        j = get_count(b);

        if(i > cnt || j > cnt)
        {
		fprintf(stderr,"\nVAR NOT DECLARED\n");
                ret = -1;
        }
	else if(Lexicon.Entry[i].str == NULL || Lexicon.Entry[j].str ==NULL)
        {
               fprintf(stderr,"\nERROR:- VAR NOT DECLARED\n");
		ret = -1;
        }

        else
        {
                if(strcmp(Lexicon.Entry[i].str,Lexicon.Entry[j].str)==0)
                {
                        ret = 0;
                }
                else
                {
                        ret = 1;
                }
        }

	return ret;
}

	
