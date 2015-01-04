/*----------DEMO OF opendir(),closedir(),readdi()------------*/
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char *myname;
int process(char *dir);

int main(int argc,char*argv[])
{
	int i;
	int errs=0;
	
	myname = argv[0];
	
	if(argc == 1)
		errs = printdir(".",0);//current directory
	else
		for(i = 1;i<argc;i++)
			errs += printdir(argv[i],0);

	return (errs != 0);
}


int printdir(char *dir,int depth)
{
	DIR *dp;
	struct dirent *ent;
        struct stat statbuf;
	int i;
//	errno = 0;	
	if((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr,"%s:%s:cannot open file for reading: %s\n",myname,dir,strerror(errno));
		return 1;
	}

	errno = 0;
	chdir(dir);
	while((ent = readdir(dp)) != NULL)
	{
		lstat(ent->d_name,&statbuf );
		if(S_ISDIR(statbuf.st_mode))
		{
			/*FOUND A DIRECTORY BUT IGNORE ".",".."*/
			if(strcmp(".",ent->d_name)==0 || strcmp("..",ent->d_name)==0)
				continue;
			for(i = depth;i>0;i--)
			printf("  ");
			printf("%s",ent->d_name);
			printf("\n");
	
			/*RECURSE AT NEW LEVEL*/
			printdir(ent->d_name,depth+4);
		}

		else 
		{
			 for(i = depth;i<0;i--)
                        printf(" ");
			printf("  %s",ent->d_name);
			printf("\n");
		}
	}
	chdir("..");
//	closedir(dp);


//		printf("%81d %s\n",ent->d_ino,ent->d_name);
//	}	
	if(errno != 0)
	{
		fprintf(stderr,"%s:%s:reading directory entries :%s\n",myname,dir,strerror(errno));
	return 1;
	}
	
	if(closedir(dp) != 0)
	{
		fprintf(stderr,"%s:%s:closing directory  :%s\n",myname,dir,strerror(errno));
	return 1;
	}
	
	return 0;
}
