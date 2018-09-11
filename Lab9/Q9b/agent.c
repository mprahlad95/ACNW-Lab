#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int sc,ss,rc,rs,recb,sntb,x,ns,y;
	socklen_t len;
	struct sockaddr_in server,client,cs;
	char buff[50];

	printf("INPUT port number for client: ");
	scanf("%d", &x);
	ss=socket(AF_INET,SOCK_STREAM,0);
	printf("\nSocket created.");
	cs.sin_family=AF_INET;
	cs.sin_port=htons(x);
	cs.sin_addr.s_addr=inet_addr("127.0.0.1");

	rs=connect(ss,(struct sockaddr*)&cs,sizeof(cs));
	printf("\nSocket connected.");

	printf("\n\nINPUT port number for server: ");
	scanf("%d", &y);
	sc=socket(AF_INET,SOCK_STREAM,0);
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(y);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	rc=bind(sc,(struct sockaddr*)&server,sizeof(server));
	printf("\nSocket binded.");

	rc=listen(sc,1);
	printf("\nSocket listening.");

	len=sizeof(client);

	ns=accept(sc,(struct sockaddr*)&client, &len);
	printf("\nSocket accepting.");

	while(1)
	{
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(sc);
			close(ns);
			exit(0);
		}	
		
		sntb=send(ss,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(ss);
			exit(0);
		}	

		printf("\nDomain Name: ");
		printf("%s", buff);
	
		if(!strcmp(buff,"stop"))
			break;

		recb=recv(ss,buff,sizeof(buff),0);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(ss);
			exit(0);
		}	
	
		sntb=send(ns,buff,sizeof(buff),0);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(ss);
			close(ns);
			exit(0);
		}

		printf("\nIP Address: ");
		printf("%s", buff);

		if(!strcmp(buff,"stop"))
			break;
	}
	close(ns);
	close(sc);
	close(ss);
}
