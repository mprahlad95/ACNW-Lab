/*Write two separate C programs (one for server and other for client) using socket APIs for UDP, to implement the following client-server model. The client should send a set of integers along with the choice to sort in ascending/descending order to the server. 

The server should arrange these integers as per the choice received. Client should continue to send the messages until the user enters selects the choice “exit”.*/

//SERVER

#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

void sortA(int st[], int n)
{
	int i,j,l;
 	for(i=1;i<n;i++)
    		for(j=0;j<n-i;j++)
				if(st[j]>st[j+1])
				{
					l=st[j];
	 				st[j] = st[j+1];
	 				st[j+1]=l;
				}
}

void sortD(int st[], int n)
{
	int i,j,l;
 	for(i=1;i<n;i++)
    		for(j=0;j<n-i;j++)
				if(st[j]<st[j+1])
				{
					l=st[j];
	 				st[j] = st[j+1];
	 				st[j+1]=l;
				}
}

main()
{
	int s,r,recb,sntb,x;
	int ca,A[40],i,j;
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

	strcpy(buff,"Enter no of numbers to sort:- ");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}

	recb=recvfrom(s,&j,sizeof(j),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	printf("\nMessage Recieved: ");
	printf("%d", j);
	
	strcpy(buff,"Enter next number:- ");
	for(i=0; i<j; i++)
	{
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			exit(0);
		}

		recb=recvfrom(s,&A[i],sizeof(A[i]),0,(struct sockaddr*)&client,&ca);
		if(recb==-1)
		{
			printf("\nMessage Recieving Failed");		
			close(s);
			exit(0);
		}	
		printf("\nMessage Recieved: ");
		printf("%d", A[i]);
	}

	strcpy(buff, "Ascending or Descending (0/1):- ");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
	
	recb=recvfrom(s,&i,sizeof(i),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}
	int l=i;

	printf("\n\nUnsorted Array:- ");
	for(i=0; i<j; i++)
		printf("%d ", A[i]);

	if(l==0)
		sortA(A,j);
	else
		sortD(A,j);
	printf("\n\nSorted Array:- ");
	for(i=0; i<j; i++)
		printf("%d ", A[i]);
	
	strcpy(buff, "Enter another array or stop (array/stop):- ");
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

	if(!strcmp(buff,"stop"))
		break;

}
	close(s);
}
