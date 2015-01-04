#define __readline__

struct line
{
        size_t buflen;
        char *buf;
        FILE *fp;
};

void Initialize_struct_line(struct line *ebuf);
void Initialize_struct_line_script(struct line *ebuf,FILE *fp);
long myreadline(struct line *ebuf);
void parse_arg(int *argc,char ***argv,char *line);
void parse_arg_script(int *argc,char ***argv,char *line);

