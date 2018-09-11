/*

a. Write two separate C programs (one for server and other for client) using socket APIs for TCP, to implement the File server, which will display the contents of the text file at the server side. 

The client program should send the name of the text file to the server whose contents are to be displayed at the client side. If the file is not present on server side, then the server should display a proper error message. Client should continue to send the file names until the user enters the string ‘stop’.

SERVER
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>

int main()
{	
	FILE *fptr;

	DIR *d;
  	struct dirent *dir;
  	d = opendir("./");
	
	int welcomeSocket,newSocket;
	int i,flag=0;
	
	char buffer[10][100];
	char message[20];
	char search[100];
	char content[100]="";
	
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(1315);	
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
		recv(newSocket,message,20,0);			//1. receive message 
		
		if(strcmp(message,"stop")==0)	break;
		else if(strcmp(message,"search")==0)
		{		
			i=0;
			if(d != NULL)
				while ((dir = readdir(d)) != NULL)
			    {
			      printf("%s\n", dir->d_name);
			      strcpy(buffer[i],dir->d_name);
			      send(newSocket,buffer[i],100*sizeof(char),0);	//2
			      i++;
			      if(i==10) break;
			    }
			closedir(d);

			printf("\nI Have The File List! \n");

			
			recv(newSocket,search,100*sizeof(char),0);		//3
			printf("Received Search String! ->> %s\n",search);
			
			for(i=0;i<10;i++)
			{
				if(strcmp(buffer[i],search)==0)
				{
					flag=1;
					break;
				}
				else flag=0;					
			}
			
			if(flag==1)
				{
					send(newSocket,"Found",20,0);		//4
					//send contents of found file to client
					
					fptr = fopen(search, "r");
					fscanf(fptr,"%[^\n]",content);
    				
    				printf("%s\n\n",content);
    				
    				send(newSocket,content,100,0); //5
    				fclose(fptr);					
				}
			else
				send(newSocket,"Not Found",20,0);		//4		
		}
		else continue;
	}
	
	return 0;
}
