/*Write two separate C programs (one for server and other for client) using socket APIs for UDP, to implement the following client-server model. The client sends two matrices along with option to perform addition or multiplication.

The server should perform the required operation as per the choice received. Client should continue to send the messages until the user enters selects the choice “exit”.*/

//CLIENT

#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

main()
{
	int s,r,recb,sntb,x;
	int sa,n,i,j;
	int A[10][10],B[10][10];
	socklen_t len;
	printf("INPUT port number: ");
	scanf("%d", &x);
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
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	len=sizeof(server);
	strcpy(buff, "Ready\n");

	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage sending Failed");
		exit(0);
	}

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&server,&sa);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	
	printf("\nMessage Recieved: ");
	printf("%s", buff);
	for(i=0; i<3;i++)
		for(j=0; j<3;j++)
		{
			printf("%d.%d ",i+1,j+1);
			scanf("%d", &A[i][j]);
		}

	sntb=sendto(s,A,sizeof(A),0,(struct sockaddr *)&server, len);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&server,&sa);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	printf("\nMessage Recieved: ");
	printf("%s", buff);

	for(i=0; i<3;i++)
		for(j=0; j<3;j++)
		{
			printf("%d.%d ",i+1,j+1);
			scanf("%d", &B[i][j]);
		}

	sntb=sendto(s,B,sizeof(B),0,(struct sockaddr *)&server, len);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&server,&sa);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	printf("\nMessage Recieved: ");
	printf("%s", buff);
	
	scanf("%s", buff);
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr *)&server, len);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	
	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&server,&sa);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	close(s);

}

