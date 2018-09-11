/*

a. Write two separate C programs (one for Server and other for client) using socket APIs for TCP, in which the client will accept strings one by one from the user and send it to the server. 

The server will reverse the strings received by the client and send it back to the client. Client will display the reversed string sent by the server. Client should continue to send the messages until the user enters the string “stop”.


CLIENT
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int clientSocket;
	char buffer[1024],message[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	clientSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1111);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
	
	addr_size = sizeof serverAddr;
	connect(clientSocket,(struct sockaddr *) &serverAddr,addr_size);
	
	while(strcmp(message,"stop")!=0)
	{
		printf("Enter text: ");
    	scanf("%s",message);
    	send(clientSocket,message,255,0);
	
		recv(clientSocket,buffer,1024,0);
		printf("Received from Server: %s \n",buffer);
	}
	
	return 0;
}
