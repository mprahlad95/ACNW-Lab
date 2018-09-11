/*

a. Write two separate C programs (one for server and other for client) using socket APIs for TCP, to implement the File server, which will display the contents of the text file at the server side. 

The client program should send the name of the text file to the server whose contents are to be displayed at the client side. If the file is not present on server side, then the server should display a proper error message. Client should continue to send the file names until the user enters the string ‘stop’.

CLIENT
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main()
{

	int clientSocket,i;
	char buffer[10][100],text[100];
	char message[20],search[100],content[100];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	clientSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1315);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
	
	addr_size = sizeof serverAddr;
	connect(clientSocket,(struct sockaddr *) &serverAddr,addr_size);
	
	while(1)
	{
		printf("Send 'search' to search and 'stop' to exit.\n");
		scanf("%s",message);
		
		send(clientSocket,message,20,0);		//1
		
		if(strcmp(message,"stop")==0)	break;
		else if(strcmp(message,"search")==0)
		{
			
			printf("\nServer says::\n");
			
			i=0;
			do
			{
				recv(clientSocket,buffer[i],100*sizeof(char),0);	//2
				printf("%s\n",buffer[i]);	
				i++;			
			}while(i!=10);
		
			printf("\n\nEnter Search String: ");
    		scanf("%s",search);
    		send(clientSocket,(char*)search,100*sizeof(char),0);	//3
		
			recv(clientSocket,message,20,0);			//4
			printf("\nServer says:: %s \n",message);
			
			if(strcmp("Found",message)==0)
			{
				recv(clientSocket,content,100,0);			//5
				printf("\n\nFile says:: %s\n\n",content);
			}
		}
		else continue;
	}
	
	return 0;
}
