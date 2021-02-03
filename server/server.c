//работа с серверами через IP протокол
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>

void error(char *msg)
{
    fprintf(stderr,"%s: %s\n",msg,strerror(errno));
    exit(1);
}

int main(int argc, char*argv[])
{
	char *advice[]={
		"Alex\r\n",
		"hello\r\n",
		"Okkk \r\n",
		"Nool\r\n",
		"Books \r\n"
	};
	int listener_d=socket(PF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in name;
	name.sin_family=PF_INET;
	name.sin_port=(in_port_t)htons(30000);
	name.sin_addr.s_addr=htonl(INADDR_ANY);
	int reuse=1;
	if(setsockopt(listener_d,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int))==-1)
		error("Не могу установить для сокета параметр повторного использования");
	if(bind(listener_d,(struct sockaddr*)&name,sizeof(name))==-1)
		error("Не могу подключиться к порту");
	listen(listener_d,10);
	puts("Ожидания подключения");
	while(1)
	{
		struct sockaddr_storage client_addr;
		unsigned int address_size=sizeof(client_addr);
		int connect_d=accept(listener_d,(struct sockaddr *) &client_addr,&address_size);
		char *msg=advice[rand()%5];
		send(connect_d,msg,strlen(msg),0);
		close(connect_d);
	}
		return 0;
	}
		