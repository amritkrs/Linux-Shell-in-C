*******************************************************************************************************
************************************WELCOME TO AM-SHELL************************************************

NAME OF PROGRAM: AM-SHELL
WRITTEN BY: 	 AMRIT KUMAR

PURPOSE:
	TO WRITE A SHELL.

WHAT IS SHELL?
:-	A SHELL IS IN SIMPLE TERM A COMMAND INTERPRETOR.
	IT TAKES COMMAND FROM USER,SEARCHES FOR THE EXECUTABLE FILE WITH THAT 
	NAME AS PER THE PATH MENTIONED IN PATH ENVIRONMENT VARIABLE.
	
	IF IT FIND IT,IT EXECUTE ELSE IT SHOW AN ERROR MESSAGE AND CONTINUE 
	RUNNING THE SHELL WAITING NEXT COMMAND.

USE OF A SHELL:-
	IMAGINE THAT YOU WROTE SO MANY PROGRAMS THAT DOES DIFFERENT WORK,NOW
	WHEN YOU WANT TO USE IT YOU WILL HAVE TO GO TO DIRECTORY HAVING THAT
	PROGRAM AND RUN IT.
	AND HOW WILL YOU CHANGE A DIRECTORY,U MUST WRITE A PROGRAM FOR IT 
	AND ONLY INTERNALLY YOU CAN CHANGE DIRECTORY AND WORK.

	ALSO YOU WILL NOT HAVE FACILITIES TO COMBINE COMMANDS AND MAKE THEM
	RUN TOGETHER WHICH IS WHAT DIFFERENTIATE A POWER USER FROM A NORMAL
	USER.

	SO,HERE IS A LIST OF FEATURES PROVIDED FOR YOU TO MAKE YOU A POWER
	USER.

WHERE TO FIND SOURCE CODE:-
	THE SOURCE CODE IS AVAILABLE IN /home/amrit/Project/app_code

WHERE TO FIND EXECUTABLE FILE:
	THE EXECUTABLE FILE IS NAMED Project IN app_code.
	YOU CAN ALSO RUN EXECUTABLE FILE FROM ANYWHERE
	BY TYPING shell ON YOUR COMMAND INTERFACE.

WHAT IS IN  APP_DATA:
	APP_DATA IS MEANT FOR ALL TEXT FILES,BUT AS I DON'T HAVE ONE,
	I HAVE PUT SOME SAMPLE SCRIPTS.

WHAT IS IN REAL_CODE FOLDER.
	THE DIRECTORY real_code IN PROJECT FOLDER CONTAINS SOME REAL LIFE
	SOURCE CODES USED IN LINUX DISTROS.
	THESE ARE WRITTEN BY GNU,AND ARE OPEN SOURCE.

WHAT IS IN MYCMD FOLDER:
	THIS FOLDER CONTAINS SOME OF THE CODE WRITTEN BY ME FOR LINUX COMMANDS.

LIST OF FEATURES:-

	1> NO LIMITS FOR ANYTHING.
	2> RUN THE PROGRAM AS TYPED BY USER
	3> CHANGING DIRECTORY IS VERY INTUITIVE
	4> REDIRECTION
	5> PIPE AS MANY AS U WANT LIMITED ONLY BY SYSTEM CAPACITY
	6> BACKGROUND JOBS
	7> WILDCARD/METACHARACTER EXPANSION
	8> VARIABLES 
		A> NO NEED TO MENTION DATA TYPE TO USE A VARIABLE AS STRING OR
		   REAL NUMBERS.
		B> WIDE VARIETY OF MATHEMATICAL FUNCTIONS AVAILABLE ONLINE ON
		   THE SHELL.
	9> SCRIPTS

HOW TO USE?
	:- 1> RUN THE PROGRAM FROM YOUR TERMINAL
	   2> START USING IT AS YOU USE YOUR NORMAL SHELL.

FOR NAIVE USER:
	1> RUN THE PROGRAM FROM YOUR TERMINAL
	2> NOW YOU CAN EXECUTE PROGRAMS BY TYPING THEIR NAMES
	3> DELIMITER USED FOR SEPARATING ARGUMENTS IS SPACE.
_______________________________________________________________________________________________________
|__________________________________TABLE OF FEATURES___________________________________________________|
|												      |
|												      |
|_____________________________________________________________________________________________________|
| NAME		| SYMBOL	| HOW TO USE                                                          | 
|_______________|_______________|_____________________________________________________________________|
|		|		|						                      |
| PIPE		|  |		| JUST TYPE YOUR ARGUMENTS AND GIVE SPACE AND TYPE "|" FOR PIPE.      |
|		|		| EXAMPLE:- cat *.c *.h | wc					      |
|_______________|_______________|_____________________________________________________________________|
|		|		|								      |
| REDIRECTION   |  		| JUST TYPE YOUR ARGUMENTS AND SEPARATE ">" OR ">>" BY SPACES.	      |
|		|  >		| > IS FOR REDIRECTING AND WRITING TO FILE.			      |
|		|  >>		| >> IS FOR CONCATENATING TO FILE.				      |
|		|		| EXAMPLE: ls | cat > ls					      |
|		|		|								      |
|_______________|_______________|_____________________________________________________________________|
|		|		|								      |
| BACKGROUND 	|  &		| JUST PUT "&" AT END OF THE INPUT.				      |
|		|		| EXAMPLE: cmd &						      |
|		|		|								      |
|_______________|_______________|_____________________________________________________________________|
|		|		|								      |
| WILDCARD      |  *		| EXAMPLE: rm *.o WILL REMOVE ALL .O FILES FROM CURRENT DIRECTORY.    |
|		|  ~		| EXAMPLE: echo ~amrit WILL PRINT OUT home/amrit		      |
|		|  $		| EXAMPLE: echo $HOME WILL PRINT OUT /home/amrit		      |
|		| 		| 								      |
|_______________|_______________|_____________________________________________________________________|
|		|		|								      |
| VARIABLE	|		| TO TREAT THE EXPRESSION FOR MATHEMATICAL EVALUATION,PUT A APOSTOPHE |
|		|		| BEFORE THE EXPRESSION,THEN THE PROGRAM ACCEPT IT AS A REAL VALUE.   |
|		|		| TO BE ABLE TO USE IT AS A STRING,DONT PUT APOSTROPHE.		      |
|		|		|								      |
|		|		| EXAMPLE: a='12*35						      |
|		|		| pr a WILL PRINT a = 420.000000				      |
|		|		| 'a WILL ALSO PRINT a = 420.000000 AS "'" IS TREATED FOR EVALUATION  |
|		|		| AND SINCE NO ASSIGN OPERATION IS THERE,IT PRINTS ANSWER ON SCREEN.  |
|		|		|								      |
|		|		| EXAMPLE: A = AMRIT						      |
|		|		|          B = SHYAM						      |
|		|		|	   pr A WILL PRINT A = AMRIT				      |
|		|		|          cmp A B WILL PRINT NOT MATCHING.			      |
|		|		|	   THIS WAY VARIABLES CAN BE MANIPULATED.		      |
|		|		|								      |
|_______________|_______________|_____________________________________________________________________|
|		|		|								      |
| SCRIPT	| run		| JUST TYPE TO FILE COMMANDS AS YOU TYPE ON SHELL.		      |
|		|		| SCRIPT PROVIDE U WITH IF/ELSE CONDITION AND WHILE CONDITION.	      |
|		|		| CURRENTLY ONLY NUMERICAL EVALUATION CONDITION CAN BE USED FOR IF AND|
|		|		| WHILE.SO,PLEASE PUT APOSTROPHE JUST AFTER IF AND WHILE.	      |
|		|		|								      |
|		|		| EXAMPLE:if'(a<b)						      |
|		|		|         {							      |
|		|		|		do cmds....					      |
|		|		|	  }							      |
|		|		|	  while'(a<b)						      |
|		|		|	  {							      |
|		|		|		do cmds....					      |
|		|		|	  }							      |
|		|		|								      |
|		|		| NOTE:FOR ENFORCING GOOD PROGRAMMING PRACTISE,YOU MUST PROVIDE BRACES|
|		|		|      JUST AFTER IF CONDITION AS SHOWN ABOVE,AND DONT WRITE ANY LINE |
|		|		|      THERE.FOLLOW STRICTLY THE STYLE SHOWN FOR IF.SEE ALSO SCRIPT   |
|		|		|      BELOW.							      |
|		|		|      FOR WHILE,THIS STRICTNESS IS FOLLOWED,JUST TO GIVE LITTLE      |
|		|		|      FREEDOM AS WELL.						      |
|		|		| NOTE:HASH IS USED FOR	COMMENTING.				      |
|_______________|_______________|_____________________________________________________________________|

EXAMPLE SCRIPT:
# THIS IS A FACTORIAL SCRIPT
echo Enter n to find its factorial
read n
fact='1
while'(n>1)
{
	fact='fact * n
	n='n-1
}

echo The factorial is
'fact

EXAMPLE SCRIPT:
#test the if driver routine.
echo enter variable a
read a
echo enter variable b
read b
echo enter variable c
read c



echo variable a value is

pr a

echo variable b value is
pr b
echo variable c value is
pr c


if'(a>b & a>c)
{
	echo highest number is
	'a
}
else if'(c>a & c>b)
{
	echo highest number is
	'c
}
else
{
	echo highest number is
	'b
}
		

FOR PROGRAMMER:
	THIS IS A SIMPLE WELL DOCUMENTED PROGRAMS(WITH COMMENTS) TO HELP ANY-ONE WHO IS
	TRYING TO BECOME COMFORTABLE WITH SYSTEM CALLS IN LINUX.
	
	REAL SHELLS ARE LARGE AND MESSY CREATURES.THEY MUST DEAL WITH MANY
	PORTABILITY ISSUES AS YOU WILL LEARN SOMETIME OR OTHER.
	
	FOR SEEING HOW PORTABILITY CAN AFFECT A PROGRAM,JUST GO THROUGH ANY
	GNU PROGRAM.I HAVE PUT SOME IN THIS FILE AS WELL,JUST FOR REFERENCE.

	NOW COMING BACK TO REAL SHELLS,THEY ALSO HAVE TO BE COMPATIBLE WITH
	THEIR EARLIER VERSIONS.

	SO,I JUST REFER YOU TO PROJECT DESCRIPTION IN THE BOOK 
		LINUX PROGRAMMING BY EXAMPLE,P-674
		AUTHOR:ARNOLD ROBBINS

	ALSO,FOR IMPLEMENTING COMMAND CALLED HISTORY,LEARN ABOUT TERMIOS.H
	FROM BOOK CALLED:
		BEGGINNING LINUX PROGRAMMING.
	IT'S AVAILABLE IN LIBRARY(RED AND BLACK COVER).

WHY DID I TOOK UP THIS AS PROJECT:
	I WAS QUITE COMFORTABLE WITH PROGRAMMING AND HAS ALREADY IMPLEMENTED
	QUITE A MANY ALGORITHMS ETC..
	
	SO,I WANTED TO TAKE A PROJECT THAT WILL HELP ME TO KNOW SOMETHING
	EXTRA IN C AND THEN I CAME ACROSS A BOOK CALLED:-
		LINUX PROGRAMMING BY EXAMPLE
                AUTHOR:ARNOLD ROBBINS

	THIS BOOK TAUGHT ME HOW REAL WORLD PROGRAMS ARE WRITTEN.
	SO IN BRIEF I MENTION THE REASONS BELOW:

	1> COMFORTABLE WITH C.
	2> HAD ALREADY IMPLEMENTED MANY ALGORITHMS.
	3> CAME TO KNOW ABOUT LINUX PROGRAMMING AS MENTIONED ABOVE.
	4> WAS AWED WITH REAL WORLD PROGRAMS.
	5> DECIDED TO LEARN SYSTEM PROGRAMMING.
	6> TO LEARN UNDERSTANDING REAL WORLD PROGRAMS,WHICH HELPED IN:
		A> SEE GOOD PROGRAMMING PRACTICES
		B> SEE HOW SOME OF THE BEST PROGRAMMERS WRITE PROGRAMS.
		C> LEARN ABOUT THE PROBLEM CONCERNED FOR YOUR PROGRAM 
		   TO BE PORTABLE AND USED BY PEOPLE.
		D> LEARN FROM MISTAKES COMMITTED BY PEOPLE EARLIER
		...
	7> FINALLY,AS A SHELL EFFECTIVELY ENCAPSULATE EVERYTHING FOR SYSTEM
	   PROGRAMMING,WITH IDEA TO HELP OTHER STUDENT LEARNING THIS
	   PROGRAMMING,I TOOK IT UP.

FEATURES LACKING:
	1> USER INTERFACE IS VERY ANNOYING FOR USERS USED TO BASH.
	2> LACK OF COLOUR WHILE EDITING C FILES.
	3> NO REDIRECTION IN INPUT DIRECTION.
	4> TO BE ABLE TO MOVE BACKGROUND PROGRAM TO FOREGROUND.
	5> NO FOR LOOP AND STRING SUPPORT IN EVALUATION CONDITION
	   FOR IF AND WHILE LOOPS.

TO OVERCOME USER INTERFACE PROBLEM:

	I COULD NOT DO IT DUE TO PROBLEM WITH readline FUNCTION AVAILABLE
	IN readline/readline.h LIBRARY.

	U JUST NEED TO HAVE A LIBRARY readline/readline.h
				      readline/history.h
	THEN CHANGE THE PRINT_PROMPT FUNCTION IN MAIN WITH readline function.
	FOR MORE INFO:
		TYPE info readline.

TO OVERCOME REDIRECTION:
	THIS FEATURE I JUST LEFT OUT AS IT HAS GOT NOTHING NEW IN IT.
	HOW TO ADD IT:
		1> ADD SYMBOL '<' FOR REDIRECTION CHECKING.
		2> WRITE A SEPARATE FUNCTION IF ENCOUNTERE THIS VARIABLE.
		   THE FUNCTION SHOULD CLOSE stdin AND TAKE INPUT FROM FILE.

TO OVERCOME BACKGROUND PROBLEM:
	MOVING BACKGROUND JOB TO FOREGROUND IS DONE BY:
		tcsetpgrp()function in unistd.h
		it must be called by process in foreground.

		FOR ME THIS FUNCTION RETURNED ERROR.
		SO,PLEASE TRY WITH HIGHER PRIVILEGE,AND IF U GET IT,
		PLEASE LET ME KNOW.

TO OVERCOME COLOUR PROBLEM:
	I DON'T KNOW.
	IF YOU KNOW,PLEASE INFORM ME AT MY GMAIL ADDRESS.

TO OVERCOME STRING EVALUATION IN IF AND WHILE LOOP:
	U WILL JUST HAVE TO WRITE A FUNCTION WHICH RETURN 1/0 AFTER COMPARING.

TO WRITE FOR LOOP:
	I DIDN'T GET TIME TO THINK FOR IT,I WILL DO IT IN VACATION,
	AS THIS WILL PROVIDE FULL SUPPORT FOR SCRIPTS IN SHELL.

TO CONTACT ME:
	EMAIL ME AT  amritkrs@gmail.com

