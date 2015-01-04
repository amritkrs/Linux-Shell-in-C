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
#include <readline/readline.h>
#include <readline/history.h>
#include"myreadline.h"
#include"program_exit.h"
#include"redirection.h"
#include"pipe.h"
#include"background.h"
#include"built_in_command.h"
#include"variable.h"
#include"wildcard_expansion.h"

#define TRUE 1

void run_script(char *filename);
void clear_comment(struct line *ebuf);
int check_empty_line(char a[]);
int check_else(char a[]);
int check_if(char a[]);
int check_brace(char a[]);
char* remove_else(char *p);
char* remove_if(char *p);
int if_driver(FILE *fp,char *p);
void mainprg(struct line *ebuf,FILE *fp);
int check_while(char p[]);
char* remove_while(char *p);
void while_driver(FILE *fp,char *p);
