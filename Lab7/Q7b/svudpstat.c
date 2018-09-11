#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

main()
{
	int s,r,recb,sntb,x;
	int ca;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	len=sizeof(client);
	ca=sizeof(client);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");
	FILE *fp;
	int c;
	int alpha,line,space,dig,other;

while(1){
	alpha=line=space=dig=other=0;
	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		exit(0);
	}	
	
	if(!strcmp(buff,"stop"))
		break;
	if(fp=fopen(buff,"r"))
	{
		printf("\nTransfering contents of %s \n\n", buff);
		strcpy(buff, "File Found");
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			exit(0);
		}
		while(1)
		{
			c=fgetc(fp);
			if(feof(fp))
				break;
			if( (c>='a' && c<='z') || (c>='A' && c<='Z') )
				alpha++;
			else if(c>='0' && c<='9')
				dig++;
			else if(c==' ' || c=='\t')
				space++;
			else if(c=='\n')
				line++;
			else
				other++;
			sntb=sendto(s,&c,sizeof(c),0,(struct sockaddr*)&client,len);
			if(sntb==-1)
			{
				printf("\nMessage Sending Failed");
				close(s);
				exit(0);
			}
		}
		c='\0';
		sntb=sendto(s,&c,sizeof(c),0,(struct sockaddr*)&client,len);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			exit(0);
		}
		line++;
		int XX[5]= { alpha, dig, space, line, other };
		sntb=sendto(s,XX,sizeof(XX),0,(struct sockaddr*)&client,len);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			exit(0);
		}
		printf("\nTransferred content");
	}
	else
	{
		strcpy(buff,"Error opening file.");
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(sntb==-1)
		{
			printf("\nMessage Sending Failed");
			close(s);
			exit(0);
		}
	}

	printf("\n\n");
	strcpy(buff,"Next file or stop.");
	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		exit(0);
	}
}


	close(s);
}
