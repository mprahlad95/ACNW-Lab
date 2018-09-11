/*

a. Create a student database at the server side and store the following information: name, roll number, branch, year of joining, and percentage marks. Write C programs to implement the following client-server model: The client program should display a menu for the following operations.
1. Insert a new record
2. Delete a Record
3. Display all records
4. Search a Record(Based on Name or Roll number)
5. Exit

At the client side, the user selects the required option and sends it along with the necessary information to the server & server will perform the requested operation. Server should send appropriate messages back to the client informing the success or failure of the requested operation. Client should continue to request the operation until user selects the option “Exit”.


SERVER
*/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

struct Student
{
	char name[40];
	int rno;
	char branch[20];
	int year;
	float marks;
}s[10];

int main()
{
	int welcomeSocket,newSocket;
	char message[20];
	int choice,INDEX=0;
	
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;	
	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(11220);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);	
	bind(welcomeSocket,(struct sockaddr *) &serverAddr,sizeof(serverAddr));	
	
	if(listen(welcomeSocket,5)==0)	printf("Listening: \n");
	else  printf("Error!\n");
	
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket,(struct sockaddr*)&serverStorage,&addr_size);
	
	char menuMessage[300] = "1. Insert a new record\n2. Delete a Record\n3. Display all records\n4. Search a Record(Based on Name or Roll number)\n5. Exit\n\nEnter Choice - ";
	
	do
	{
		send(newSocket,menuMessage,300*sizeof(char),0);	//Send menuMessage to Client
		recv(newSocket,&choice,sizeof(&choice),0);		//Receive choice from Client

		if(choice==1)	//INSERT
		{
				send(newSocket,"NEW RECORD\n\n",20,0);
	
				send(newSocket,"Enter name: ",20,0);
				recv(newSocket,s[INDEX].name,40,0);

				send(newSocket,"Enter roll number: ",20,0);
				recv(newSocket,&s[INDEX].rno,sizeof(&s[INDEX].rno),0);
	
				send(newSocket,"Enter branch: ",20,0);
				recv(newSocket,s[INDEX].branch,20,0);
	
				send(newSocket,"Enter year of joining: ",30,0);
				recv(newSocket,&s[INDEX].year,sizeof(&s[INDEX].year),0);
	
				send(newSocket,"Enter percentage: ",20,0);
				recv(newSocket,&s[INDEX].marks,sizeof(&s[INDEX].marks),0);
				
				printf("\nADDED RECORD!\n");
								
				INDEX++;				
				send(newSocket,&INDEX,sizeof(&INDEX),0);
				
				printf("Index = %d\n",INDEX);
		}
		
		else if(choice==2)
		{
				char name[40];
				int rno;
				int flag=0;
				int i,c;
				char searchby[10];
				
				//DELETE
				back1:
				recv(newSocket,searchby,10,0);
				if(strcmp(searchby,"name")==0)
				{
					recv(newSocket,name,40,0);
					
					for(i=0;i<INDEX;i++)
						if(strcmp(s[i].name,name)==0) 
						{
							flag = 1;
							c=i;
							while (c<INDEX) 
							{
								s[c-1]=s[c];
      							c++;
   							}
   							INDEX--;
       						send(newSocket,&INDEX,sizeof(&INDEX),0);
							break;
						}
					
					if(flag==1)
						send(newSocket,"Found! Deleted!\n",20,0);
					else
						send(newSocket,"Not Found!\n",20,0);
				}
				else if(strcmp(searchby,"roll")==0)
				{
					recv(newSocket,&rno,sizeof(&rno),0);
					
					for(i=0;i<INDEX;i++)
						if(s[i].rno==rno) 
						{
							flag = 1;
							c=i;
							while (c<INDEX) 
							{
								s[c-1]=s[c];
      							c++;
   							}
   							INDEX--;
       						send(newSocket,&INDEX,sizeof(&INDEX),0);
							break;
						}
					
					if(flag==1)
						send(newSocket,"Found! Deleted!\n",20,0);
					else
						send(newSocket,"Not Found!\n",20,0);
				}
				else goto back1;
				
				
				
		}
		else if(choice==3)
		{
				int i=0;
				printf("\nDISPLAYING ALL RECORDS ON CLIENT SIDE!\n");
				
				printf("Number of records on server = %d\n",INDEX);
				
				if(INDEX==0)	break;
				
				for(i=0;i<INDEX;i++)
					send(newSocket,&s[i],sizeof(&s[i]),0);
		}
		else if(choice==4)
		{
				char name[40];
				int rno;
				int flag=0;
				int i;
				char searchby[10];
				
				//SEARCH
				back:
				recv(newSocket,searchby,10,0);
				if(strcmp(searchby,"name")==0)
				{
					recv(newSocket,name,40,0);
					
					for(i=0;i<INDEX;i++)
						if(strcmp(s[i].name,name)==0) 
						{
							flag = 1;
							break;
						}
					
					if(flag==1)
						send(newSocket,"Found!\n",20,0);
					else
						send(newSocket,"Not Found!\n",20,0);
				}
				else if(strcmp(searchby,"roll")==0)
				{
					recv(newSocket,&rno,sizeof(&rno),0);
					
					for(i=0;i<INDEX;i++)
						if(s[i].rno==rno) 
						{
							flag = 1;
							break;
						}
					
					if(flag==1)
						send(newSocket,"Found!\n",20,0);
					else
						send(newSocket,"Not Found!\n",20,0);
				}
				else goto back;
		}

	}while(choice!=5);
	
	return 0;
}
