#define __pipe__

int check_pipe(char *argv[]);
void parse_pipe(char **argv,char ***l_argv,int *last);
void left_child(char **argv,int last,int count);
void pipeline(char **argv);
