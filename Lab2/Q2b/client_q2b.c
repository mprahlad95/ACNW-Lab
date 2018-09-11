/*

b. Write two separate C programs (one for server and other for client) using socket APIs for TCP, in which the client will accept strings one from the user and send it to the server. 

The server will check whether the string is palindrome or not and accordingly it should send a proper message to the client. Client will display the received message sent by the server. Client should continue to send the messages until the user enters the string ‘stop’


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
	serverAddr.sin_port = htons(1112);	
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
		printf("Server says: %s \n",buffer);
	}
	
	return 0;
}
