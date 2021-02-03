//Обработка ошибок
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>

void handle_interrupt(int sig)
{
    puts("Прощай жестокий мир...\n");
    exit(1);
}

int catch_signal(int sig,void(*handler)(int))
{
    struct sigaction action;
    action.sa_handler=handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;
    return sigaction(sig,&action,NULL);
}

int main()
{
if (catch_signal(SIGINT, handle_interrupt) == -1)
{
    fprintf(stderr,"Не могу подобрать обработчик");
	exit(2);
}
char name[20];
printf("Введите свое имя: \n");
fgets(name,20,stdin);
printf("Привет, %s\n",name);
    return 0;
}
