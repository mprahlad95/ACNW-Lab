#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int clientSocket,k,op;
    char nbuffer[10]; 
    char message[15];
    char rbuffer[1024]; 
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(10000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	while(1)
	{
		printf("1)Details\n2)Enrollment\n3)Marks\n4)Exit\n");
		scanf("%d",&op);
		sprintf(nbuffer,"%d",op);
		send(clientSocket,nbuffer,1,0);
		if(op==1)
		{
			recv(clientSocket,rbuffer,100,0);
			printf("%s\n",rbuffer);
		}
		if(op==2)
		{
			recv(clientSocket,rbuffer,100,0);
			printf("%s\n",rbuffer);
		}
		if(op==3)
		{
			recv(clientSocket,rbuffer,18,0);
			printf("%.*s",18,rbuffer);
			int code;
			scanf("%d",&code);
			sprintf(rbuffer,"%d",code);
			send(clientSocket,rbuffer,3,0);
			recv(clientSocket,rbuffer,30,0);
			printf("%.*s",25,rbuffer);
		}
		if(op==4)
		{
			shutdown(clientSocket,2);
			break;
		}
	}
	return 0;
}
