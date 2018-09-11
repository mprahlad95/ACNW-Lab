#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];
	char *DN[]={"tumblr.com"};
	char *IP[]={"66.6.44.4"};
	
	char dn[40];
	char ip[40];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	printf("\nSocket binded.");

	r=listen(s,1);
	printf("\nSocket listening.");

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	printf("\nSocket accepting.");

	while(1)
	{
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			close(ns);
			exit(0);
		}	
	
		printf("\nDomain Name: ");
		printf("%s", buff);

		if(!strcmp(buff,"stop"))
			break;

		for(a=0; a<10; a++)
			if(!strcmp(buff,DN[a]))
				break;

		if(a<10)
			strcpy(buff,IP[a]);
		else
			strcpy(buff,"Not Found");

		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			close(ns);
			exit(0);
		}

		printf("\nIP Address: ");
		printf("%s", buff);
		
		if(!strcmp(buff,"stop"))
			break;
	}
		close(ns);
		close(s);
}	
