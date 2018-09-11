/*

c. Write two separate C programs (one for server and other for client) using socket APIs for TCP, to implement the following client-server model. 

The client should send a set of integers and a search number to the server. The server should send proper message to the client. Client should continue to send the messages until the user enters selects the choice “exit”.

SERVER
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

char *strrev(char *str);

int main()
{
	int welcomeSocket,newSocket;
	int buffer[10],search,i,flag=0;
	
	char message[20];
	
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1114);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);	
	bind(welcomeSocket,(struct sockaddr *) &serverAddr,sizeof(serverAddr));
	
	if(listen(welcomeSocket,5)==0)
		printf("Listening: \n");
	else
		printf("Error!\n");
	
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket,(struct sockaddr*)&serverStorage,&addr_size);
	
	while(1)
	{
		recv(newSocket,message,20,0);
		
		if(strcmp(message,"exit")==0)	break;
		else if(strcmp(message,"search")==0)
		{		
			recv(newSocket,buffer,10*sizeof(int),0);
			printf("Received Integer Array! \n");
			
			for(i=0;i<10;i++)
			{
				printf("%d\n",buffer[i]);
			}
			
			recv(newSocket,&search,sizeof(int),0);
			printf("Received Search Integer! \n");
			
			for(i=0;i<10;i++)
			{
				if(buffer[i]==search)
				{
					flag=1;
					break;
				}
				else flag=0;					
			}
			
			if(flag==1)
				send(newSocket,"Found",20,0);
			else
				send(newSocket,"Not Found",20,0);			
		}
		else continue;
	}
	
	return 0;
}
