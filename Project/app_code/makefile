Project: myreadline.o pipe.o redirection.o program_exit.o background.o built_in_command.o variable.o list.o stack.o listf.o stackf.o script.o wildcard_expansion.o help.o
	gcc -g -o Project myreadline.o pipe.o redirection.o program_exit.o background.o built_in_command.o variable.o list.o stack.o listf.o stackf.o script.o wildcard_expansion.o help.o shell.c -lm
myreadline.o:myreadline.c
	cc -g -c myreadline.c
pipe.o:pipe.c
	cc -g -c pipe.c
redirection.o:redirection.c
	cc -g -c redirection.c
program_exit.o:program_exit.c
	cc -g -c program_exit.c
background.o:background.c
	cc -g -c background.c
built_in_command.o:built_in_command.c
	cc -g -c built_in_command.c
variable.o:variable.c
	cc -g -c variable.c
list.o:list.c
	cc -g -c list.c
stack.o:stack.c
	cc -g -c stack.c
listf.o:listf.c
	cc -g -c listf.c
stackf.o:stackf.c
	cc -g -c stackf.c
script.o:script.c
	cc -g -c script.c
wildcard_expansion.o:wildcard_expansion.c
	cc -g -c wildcard_expansion.c
help.o:help.c
	cc -g -c help.c
clean:
	rm -f *.o Project
