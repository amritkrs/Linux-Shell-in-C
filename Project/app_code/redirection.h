
#define __redirection__
int check_red(char **argv);
int check_type_red(char **argv);
void parse_r_argv(char ***r_argv,char **argv,int *t_argc);
char *get_file(char **argv);
void re_execute(char **r_argv,char *filename,char **argv);
void redirection(char **argv);
