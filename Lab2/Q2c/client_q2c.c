/*

c. Write two separate C programs (one for server and other for client) using socket APIs for TCP, to implement the following client-server model. 

The client should send a set of integers and a search number to the server. The server should send proper message to the client. Client should continue to send the messages until the user enters selects the choice “exit”.

CLIENT
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int clientSocket,i,search;
	int buffer[10];
	char message[20];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	clientSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1114);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
	
	addr_size = sizeof serverAddr;
	connect(clientSocket,(struct sockaddr *) &serverAddr,addr_size);
	
	while(1)
	{
		printf("Send 'search' to search and 'exit' to exit.\n");
		scanf("%s",message);
		send(clientSocket,message,20,0);
		
		if(strcmp(message,"exit")==0)	break;
		else if(strcmp(message,"search")==0)
		{
			printf("Enter 10 Integers:\n");
    		for(i=0;i<10;i++)
    			scanf("%d",&buffer[i]);
    		send(clientSocket,(char*)buffer,10*sizeof(int),0);
    		
    		printf("Enter Search: ");
    		scanf("%d",&search);
    		send(clientSocket,&search,sizeof(int),0);
		
			recv(clientSocket,message,20,0);
			printf("Server says: %s \n",message);
		}
		else continue;
	}
	
	return 0;
}
