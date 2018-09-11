#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int welcomeSocket, newSocket,pid;
    char buffer[10];
    char sbuffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
     welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(10000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	while(1)
	{
		recv(newSocket,buffer,1,0);
		if(buffer[0]=='1')
		{
			pid=fork();
			if(pid==0)
			{
				pid=getpid();						
				sprintf(sbuffer,"%s%d","Name: Kashish\nResident: Delhi\nProcess id: ",pid);
				send(newSocket,sbuffer,100,0);
				exit(0);
			}
			wait(pid);
		}
		
		if(buffer[0]=='2')
		{
			pid=fork();
			if(pid==0)
			{
				pid=getpid();
				sprintf(sbuffer,"%s%d","Department: ICT\nCourse: ACNW\nSection: A\nSemester: 6\n",pid);
				send(newSocket,sbuffer,100,0);
				exit(0);
			}
			wait(pid);
		}
		
		if(buffer[0]=='3')
		{
			pid=fork();
			if(pid==0)
			{
				pid=getpid();
				send(newSocket,"Enter subject code: ",18,0);
				recv(newSocket,buffer,3,0);
				int code=atoi(buffer);
				if(code==101)
				{
					sprintf(sbuffer,"%s%d","Marks: 80\nProcess id: ",pid);
				}
				if(code==102)
				{
					sprintf(sbuffer,"%s%d","Marks: 90\nProcess id: ",pid);	
				}
				else
				{
					sprintf(sbuffer,"%s%d","Invalid\nProcess id: ",pid);	
				}
				send(newSocket,sbuffer,30,0);
				exit(0);
			}
			wait(pid);
		}
		if(buffer[0]=='4')
		{
			shutdown(newSocket,2);
			break;
		}
	}
	return 0;
}
