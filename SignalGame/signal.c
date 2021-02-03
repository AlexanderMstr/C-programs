//Таблица умножения на скорость 
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<errno.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
int score=0;
void end_game(int sig)
{
    printf("\nИтоговый счет: %i\n",score);
    exit(0);
}

int catch_signal(int sig,void (*handler)(int))
{
    struct sigaction action;
    action.sa_handler=handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;
    return sigaction(sig,&action,NULL);
}
void times_up(int sig)
{
    puts("\n\nВРЕМЯ ВЫШЛО!");
    raise(SIGINT);
}

void error(char *msg)
{
    fprintf(stderr,"%s: %s\n",msg,strerror(errno));
    exit(1);
}
int main()
{
	puts("Умножаем на скорость, на ответ 5 секунд, для выхода нажмите CTRL+C");
    catch_signal(SIGALRM,times_up);
    catch_signal(SIGINT,end_game);
    srandom(time(NULL));
    while(1)
    {
        int a=random()%11+1;
        int b=random()%11+1;
        char txt[5];
        alarm(3);
        printf("\nСколько будет %i * %i = ",a,b);
        fgets(txt,10,stdin);
        int answer=atoi(txt);
        if(answer==a*b)
        {
            score++;
        }else{
        printf("\nНеправильно! Счет: %i\n",score);
		
        }
    }
    return 0;
}
