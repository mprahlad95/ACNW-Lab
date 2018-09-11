/*

a. Create a student database at the server side and store the following information: name, roll number, branch, year of joining, and percentage marks. Write C programs to implement the following client-server model: The client program should display a menu for the following operations.
1. Insert a new record
2. Delete a Record
3. Display all records
4. Search a Record(Based on Name or Roll number)
5. Exit

At the client side, the user selects the required option and sends it along with the necessary information to the server & server will perform the requested operation. Server should send appropriate messages back to the client informing the success or failure of the requested operation. Client should continue to request the operation until user selects the option “Exit”.


CLIENT
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
}s;

int main()
{
	int clientSocket;
	char buffer[1024],message[300];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	int choice,INDEX=0;
	char searchby[10];
	
	clientSocket = socket(PF_INET,SOCK_STREAM,0);	
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(11220);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);
	
	addr_size = sizeof serverAddr;
	connect(clientSocket,(struct sockaddr *) &serverAddr,addr_size);
	
	do
	{
		recv(clientSocket,message,300*sizeof(char),0);
		printf("%s",message);
		scanf("%d",&choice);	
		send(clientSocket,&choice,sizeof(&choice),0);
		
		if(choice==1)
		{	
			recv(clientSocket,message,20,0);	
			printf("%s",message);

			recv(clientSocket,message,20,0);		//name
			printf("%s",message);
				scanf("%s",s.name);
				send(clientSocket,s.name,40,0);
		
			recv(clientSocket,message,20,0);		//rno	
			printf("%s",message);
				scanf("%d",&s.rno);
				send(clientSocket,&s.rno,sizeof(&s.rno),0);
		
			recv(clientSocket,message,20,0);		//branch
			printf("%s",message);
				scanf("%s",s.branch);
				send(clientSocket,s.branch,20,0);
		
			recv(clientSocket,message,30,0);		//year
			printf("%s",message);
				scanf("%d",&s.year);
				send(clientSocket,&s.year,sizeof(&s.year),0);
		
			recv(clientSocket,message,20,0);		//marks
			printf("%s",message);
				scanf("%f",&s.marks);
				send(clientSocket,&s.marks,sizeof(&s.marks),0);	
				
			recv(clientSocket,&INDEX,sizeof(&INDEX),0);
		}
		
		else if(choice==2)
		{
			char name[40];
			int rno;
			
			//DELETE
			back1:
			if(INDEX==0) break;
			printf("Number of records = %d\n\n",INDEX);
			
			printf("\nRECORD DELETE\n");
			printf("Enter 'name' to delete by name and 'roll' to delete by roll number:\n");
			scanf("%s",searchby);
			send(clientSocket,searchby,10,0);
			
			if(strcmp(searchby,"name")==0)
			{
				printf("Enter name - ");
				scanf("%s",name);
				send(clientSocket,name,40,0);
				
				recv(clientSocket,&INDEX,sizeof(&INDEX),0);
				
				recv(clientSocket,message,20,0);
				printf("%s",message);
			}
			else if(strcmp(searchby,"roll")==0)
			{
				printf("Enter Roll Number - ");
				scanf("%d",&rno);
				send(clientSocket,&rno,sizeof(&rno),0);
				
				recv(clientSocket,&INDEX,sizeof(&INDEX),0);
				
				recv(clientSocket,message,20,0);
				printf("%s",message);				
			}
			
			else goto back1;
		}
		
		else if(choice==3)
		{
			int i=0;

			if(INDEX==0) break;
			
			printf("Number of records = %d\n",INDEX);
			for(i=0;i<INDEX;i++)
			{
				recv(clientSocket,&s,sizeof(&s),0);
				printf("Name: %s\n",s.name);
				printf("Roll Number: %d\n",s.rno);
				printf("Branch: %s\n",s.branch);
				printf("Year: %d\n",s.year);
				printf("Marks: %f\n\n",s.marks);
			}		
		}
		
		else if(choice==4)
		{
			char name[40];
			int rno;
			
			//SEARCH
			back:
			if(INDEX==0) break;
			printf("Number of records = %d\n\n",INDEX);
			
			printf("\nRECORD SEARCH\n");
			printf("Enter 'name' to search by name and 'roll' to search by roll number:\n");
			scanf("%s",searchby);
			send(clientSocket,searchby,10,0);
			
			if(strcmp(searchby,"name")==0)
			{
				printf("Enter name - ");
				scanf("%s",name);
				send(clientSocket,name,40,0);
				
				recv(clientSocket,message,20,0);
				printf("%s",message);
			}
			else if(strcmp(searchby,"roll")==0)
			{
				printf("Enter Roll Number - ");
				scanf("%d",&rno);
				send(clientSocket,&rno,sizeof(&rno),0);
				
				recv(clientSocket,message,20,0);
				printf("%s",message);				
			}
			
			else goto back;
		}
	
	}while(choice!=5);
	
	return 0;
}
