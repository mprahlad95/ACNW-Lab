/* 
b. Write two separate C programs (one for Server and other for client) using socket APIs for UDP, in which the client will accept strings one by one from the user and send it to the server. The server will display all the messages received by the client and will reply back. The client will display the string received from the server. Client should continue to send the messages until the user enters the string “stop”. 
*/

#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

main()
{
	int s,r,recb,sntb,x;
	int ca;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(client);
	ca=sizeof(client);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

while(1){

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	
	printf("\nMessage Recieved: ");
	printf("%s", buff);

	if(!strcmp(buff,"stop"))
		break;

	printf("\n\n");
	printf("Type Message: ");
	scanf("%s", buff);
	
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
	
	if(!strcmp(buff,"stop"))
		break;

}
	close(s);
}
