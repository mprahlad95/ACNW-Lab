/*

a. Write two separate C programs (one for Server and other for client) using socket APIs for TCP, in which the client will accept strings one by one from the user and send it to the server. 

The server will reverse the strings received by the client and send it back to the client. Client will display the reversed string sent by the server. Client should continue to send the messages until the user enters the string “stop”.


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
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1111);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);	
	bind(welcomeSocket,(struct sockaddr *) &serverAddr,sizeof(serverAddr));
	
	if(listen(welcomeSocket,5)==0)
		printf("Listening: \n");
	else
		printf("Error!\n");
	
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket,(struct sockaddr*)&serverStorage,&addr_size);
	
	while(strcmp(buffer,"stop")!=0)
	{
		recv(newSocket,buffer,1024,0);
		printf("Received from Client: %s \n",buffer);
		
		strrev(buffer);
		
		send(newSocket,buffer,255,0);
	}
	
	return 0;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
