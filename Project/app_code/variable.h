
#ifndef _VARIABLE_H
#define _VARIABLE_H

#include<string.h>
#include<math.h>
#include"stackf.h"
#include"stack.h"


#define MAXPRIORITY   6
#define MAXNAME      30
#define MAXLINE     100
#define FIRSTUNARY    3
#define LASTUNARY    11
#define FIRSTBINARY  12
#define LASTBINARY   17
#define FIRSTOPERAND 18
#define LASTOPERAND  19
#define HASHSIZE    101

typedef enum errorlevel{WARNING,BADVALUE,BADEXPR,FATAL}ErrorLevel;

typedef enum kindtype{OPERAND,UNARYOP,BINARYOP,LEFTPAREN,RIGHTPAREN,ENDEXPR}KindType;

typedef double Value;

struct var
{
        char name[MAXNAME];
        KindType kind;
        union
        {
                int pri;
                Value val;
        }info;
        char *str;
};

struct node_v
{
        struct var *Entry;
        int count;
};

typedef struct node_v Var_list;



void setup_lexicon(void);
int priority(char a[]);
KindType kind(char a[]);
int check_evaluate(char a[]);
void Createlist(char *exp,List infix_l);
char* Extract_word(char *exp,char *s);
int match_break(char a);
int match_char(char a);
int add_var(char exp[],int ret);
void Gettoken(char p[],List l);
void infix_to_postfix(List infix_l,List postfix_l);
void add_lexicon(char name[],KindType k,float f,char *val);
int check_var(char n[]);
int get_count(char n[]);
float evaluate(List Postfix_l);
void add_value(char name[],KindType k,char *val);
float get_num(char a[]);
int check_float(char a[]);
int get_point(char a[]);
float DoBinary(float x,float y,char a[]);
int match_num(char a);
char* Extract_num(char *p,char s[]);
int check_assign(char a[]);
int m_break_num(char a);
int check_var_eval(char a[]);
void reassign_mem(void);
void Print_var_value(char a[]);
void cmp_str(char a[],char b[]);
int str_cmp(char a[],char b[]);
int match_bool(char a);
char* Extract_bool(char *exp,char p[]);
float DoUnary(float x,char a[]);

#endif
