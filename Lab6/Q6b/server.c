/*Write two separate C programs (one for server and other for client) using socket APIs for UDP, to implement the following client-server model. The client sends two matrices along with option to perform addition or multiplication.

The server should perform the required operation as per the choice received. Client should continue to send the messages until the user enters selects the choice “exit”.*/

//SERVER

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
	int A[10][10],B[10][10],C[10][10],p=0,i,k,j;
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


	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}
	printf("\nMessage Recieved: ");
	printf("%s", buff);

	strcpy(buff,"Enter data for 3x3 matrix.\n\n");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}

	recb=recvfrom(s,A,sizeof(A),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	strcpy(buff,"Enter next 3x3 Matrix.\n\n");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}

	recb=recvfrom(s,B,sizeof(B),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");
		close(s);
		exit(0);
	}

	strcpy(buff,"Enter operation(Add/Mul): ");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}	

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}

	if(!strcmp(buff,"Add"))
	{
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				C[i][j]=A[i][j]+B[i][j];
		printf("\nSum Matrix: \n");	
		for(i=0; i<3; i++)
		{	for(j=0; j<3; j++)
				printf("%d ", C[i][j]);
			printf("\n");
		}
		strcpy(buff,"Type exit");
	}	
	else if(!strcmp(buff,"Mul"))
	{
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				C[i][j]=0;
		
		for(i=0; i<3; i++)
			for(j=0; j<3; j++)
				for(k=0; k<3; k++)
					C[i][j]+=A[i][k]+B[k][j];
		printf("\nProduct Matrix: \n");	
		for(i=0; i<3; i++)
		{	for(j=0; j<3; j++)
				printf("%d ", C[i][j]);
			printf("\n");
		}
		strcpy(buff,"exit");
	}	

	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}	

	close(s);
}
