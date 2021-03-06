#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

#define MAXLINE 	80
#define BUFFERSIZE 	1024
#define TRUE 		1
#define FALSE 		0
#define CHKERR(rc, msg) if(rc<0) { \
	perror(msg); \
	exit(-1); \
}


void GetArgs(char**, char*);

int main()
{
	char *args[MAXLINE/2+1]; //point array
	char line[BUFFERSIZE];
	int should_run = TRUE;
	int pid;
	int status = 0;
	int ppid= 0;
	char c;
	int backrun = FALSE;
	while(should_run)
	{
		backrun = FALSE;
		int idx = 0;
		printf("\e[34;40m simpleshell> \e[0m");
		fflush(stdout);
		fgets(line, MAXLINE, stdin);
		line[strlen(line)-1] = '\0';
		GetArgs(args, line);
		pid = fork();
		if(strlen(args[0]) == 0) 
		{
			continue;
		}
		CHKERR(pid ,"Create child Filed :");
		while(args[idx] != NULL)
		{
			if(strcmp(args[idx] ,"&") == 0)
				backrun = TRUE;
			idx++;
		}
		
		if(pid == 0)//Child process
		{
			
			ppid = execvp(args[0], args);	
			CHKERR(ppid, "Creat process Failed : ");	
		}
		else
		{
			int i = 0;
			if(backrun == FALSE) wait(&status);
		}
	}
}

void GetArgs(char** args, char *line)
{
	int index = 0;
	char *token = NULL;
	while((token = strsep(&line, " "))!=NULL)
	{
		args[index] = token;
		index++;
	}
	if(index == 0) 
	{
		args[index] = line;
		args[index++] = NULL;
	}
	else args[index] = NULL;
}
