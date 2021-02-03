#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include<errno.h>
#include<sys/wait.h>
void error(char*msg)
{
    fprintf(stderr,"%s: %s\n",msg,strerror(errno));
    exit(1);
}

int main(int argc, char* argv)
{
    char *feeds[]={"https://ilyachalov.livejournal.com/107799.html"};
    int times=1;
    char *phrase=argv[1];
	FILE *f=fopen("story.txt","w");
	if(!f)
	{
		error("Не могу открыть файл");
	}
    for(int i=0;i<times;i++)
    {
        char var[255];
        sprintf(var,"FSS_FEED=%s",feeds[i]);
        char *vars[]={var,NULL};
        pid_t pid=fork();

        if(pid==-1)
        {
            fprintf("Не могу клонировать процесс: %s\n",strerror(errno));
            return 1;
        }
        if(!pid){
			if(dup2(fileno(f),1)==-1)
			{
				error("Не могу перенаправить стандартный вывод");
			}
        if(execle("/bin","/bin","./rssgossip.py",phrase,NULL,vars)==-1)
        {
            fprintf(stderr,"Не могу запустить скрипт: %s\n",strerror(errno));
            return 1;
        }
    }
    }
	int pid_status;
	if(waitpid(pid,%pid_status,0)==-1)
	{
		error("Ошибка во время ожидания дочернего процесса");
	}
    return 0;
}
