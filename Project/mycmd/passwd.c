

char* password(void)
{
struct termios initialsettings,newsettings;
char passwd[PASSWD_LEN + 1];

        tcgetattr(fileno(stdin),&initialsettings);
        newsettings = initialsettings;

        newsettings.c_lflag &=~ECHO;

        printf("\nENTER PASSWD : ");
        /*NOW SET TERMINAL ATTRIBUTE TO NEWSETTINGS*/

        if(tcsetattr(fileno(stdin),TCSAFLUSH,&newsettings)!=0)
        {
                fprintf(stderr,"FAIL IN SETTING ATTRIBUTE : %s",strerror(errno));
        }

        else
        {
                fgets(passwd,PASSWD_LEN,stdin);
                tcsetattr(fileno(stdin),TCSANOW,&initialsettings);
        }

        return passwd;
}

