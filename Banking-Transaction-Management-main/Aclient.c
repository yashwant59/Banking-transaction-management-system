#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<strings.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include "struct.c"
#include<string.h>

struct Customer fi;
int count;
int main()
{
	int socketFd;
	struct sockaddr_in serverAdd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	perror("socket");
	bzero(&serverAdd,sizeof(serverAdd));
	serverAdd.sin_family=AF_INET;
	serverAdd.sin_port=htons(6085);
	serverAdd.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(socketFd,(struct sockaddr*)&serverAdd,sizeof(serverAdd));
	perror("connect");
	printf("-------------------Welcome to bank-----------------------\n");
	printf("Enter login id\n");

        char buffer[1024] = "";
        char bufferi[1024] = "";
        
        int sel;
        double Damt=0;
        double bal=0;
        int acno=0;
        int ty=5;
        scanf("%[^\n]",buffer);

        write(socketFd,&buffer,strlen(buffer));
        read(socketFd,&buffer,sizeof(buffer));
        printf("%s\n",buffer);
        
        getchar();
        scanf("%[^\n]",buffer);
        
        getchar();
		write(socketFd,&buffer,strlen(buffer));
		
		read(socketFd,&buffer,sizeof(buffer));
		if(strcmp(buffer,"admin login successful")==0)
		{while(1){
			printf("\n");  
			
			printf("----------------------HELLO ADMIN---------------------\n");
						printf("  1.     Search Records      \n");
						printf("  2.     Add new Account     \n");
						printf("  3.     Delete Record       \n");
						printf("  4.     Modify Record       \n");
						printf("  5.     View Record Count   \n");
						printf("  6.     Exit                \n");
			printf("\n");
			
			scanf("%d",&sel);     
			getchar();
			
			write(socketFd,&sel,sizeof(sel));
			
			if(sel==1)
			{
				printf("You should know Username\n");
				memset(buffer, 0, sizeof buffer);
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			
       			memset(buffer, 0, sizeof buffer);
      			scanf("%[^\n]",buffer);
     			
				write(socketFd,&buffer,strlen(buffer));
       			
       			memset(buffer, 0, sizeof buffer);  // checking for username exist
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			if(strcmp(buffer,"ok")==0)
       			{
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Username1        :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&buffer,sizeof(fi.username1));
       			printf("%s\n",buffer);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Password1        :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&buffer,sizeof(fi.password1));
       			printf("%s\n",buffer);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Username2        :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&buffer,sizeof(fi.username2));
       			printf("%s\n",buffer);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Password2        :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&buffer,sizeof(fi.password2));
       			printf("%s\n",buffer);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Account number   :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&acno,sizeof(fi.account_number));
       			printf("%d\n",acno);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Account balance  :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&bal,sizeof(fi.balance));
       			printf("%f\n",bal);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			
       			printf("	Record number    :");
       			memset(buffer, 0, sizeof buffer);
				read(socketFd,&ty,sizeof(fi.type));
       			printf("%d\n",ty);
       			printf("\n");
       			write(socketFd,&sel,sizeof(sel));
       			}
       			else
       			{
       				printf("\n");
       				printf("Sorry admin the username you entered does not exist\n");
       				
       				printf("\n");
       			}
       			memset(buffer, 0, sizeof buffer);
			}
			else if(sel==2)
			{
				printf("Adding new account please enter the details carefully\n");
				        char bufferx1[1024] = "";
				        int sync=1;
				        memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				memset(bufferx1, 0, sizeof bufferx1);
     					
     					scanf("%[^\n]",bufferx1);
						write(socketFd,&bufferx1,sizeof(bufferx1));
				        
				        memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
						printf("%s\n",buffer);
						if(strcmp(buffer,"ok")==0)
						{
				        write(socketFd,&sync,sizeof(sync));
				        for(int n=0;n<3;n++)
				        {
				        memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				memset(bufferx1, 0, sizeof bufferx1);
     					getchar();
     					scanf("%[^\n]",bufferx1);
						write(socketFd,&bufferx1,sizeof(bufferx1));
						}
						
						memset(bufferx1, 0, sizeof bufferx1);
						read(socketFd,&bufferx1,sizeof(bufferx1));
        				printf("%s\n",bufferx1);
        				printf("\n");
        				}
        				else
        				{
        					printf("Username already exist please try again\n");
        				}
					
			}
			else if(sel==3)
			{
				printf("You should know Username\n");
				memset(buffer, 0, sizeof buffer);
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			
       			memset(buffer, 0, sizeof buffer);
      			scanf("%[^\n]",buffer);
     			
				write(socketFd,&buffer,strlen(buffer));
       			
       			memset(buffer, 0, sizeof buffer);  // checking for username exist
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			if(strcmp(buffer,"ok")==0)
       			{
       					
						
					printf("Are you sure you want to delete this account\n");
					printf("   1-----> YES  \n");
					printf("   2-----> NO   \n"); 	
					scanf("%d",&sel);     
					getchar();
			
					write(socketFd,&sel,sizeof(sel));	
					
					if(sel==1)
					{
						
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
       					printf("%s\n",buffer);
					}
					
					else if(sel==2)
					{
						printf("Account not deleted");
					}
						
					else
					{
						printf("sorry wrong input\n");
						exit(0);
					}
       			
       			}
       			else
       			{
       				printf("\n");
       				printf("Sorry admin the username you entered does not exist\n");
       				
       				printf("\n");
       			}
       			memset(buffer, 0, sizeof buffer);
			
			}
			else if(sel==4)
			{
				printf("You should know Username\n");
				memset(buffer, 0, sizeof buffer);
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			
       			memset(buffer, 0, sizeof buffer);
      			scanf("%[^\n]",buffer);
     			
				write(socketFd,&buffer,strlen(buffer));
       			
       			memset(buffer, 0, sizeof buffer);  // checking for username exist
				
				read(socketFd,&buffer,sizeof(buffer));
       			printf("%s\n",buffer);
       			
       			if(strcmp(buffer,"ok")==0)
       			{
       					printf("  You must not modify username of account holder you still have these choices       \n");
       					printf("  \n");
						printf("  1--->  Modify Password 1       \n");
						printf("  2--->  Modify username 2       \n");
						printf("  3--->  Modify Password 2       \n");
						
						
					scanf("%d",&sel);     
					getchar();
			
					write(socketFd,&sel,sizeof(sel));	
					
					if(sel==1)
					{
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
       					printf("%s\n",buffer);
       					
       					memset(buffer, 0, sizeof buffer);
      					scanf("%[^\n]",buffer);
						write(socketFd,&buffer,strlen(buffer));
						
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
       					printf("%s\n",buffer);
					}
					else if(sel==2)
					{
						
       						memset(buffer, 0, sizeof buffer);
							read(socketFd,&buffer,sizeof(buffer));
       						printf("%s\n",buffer);
       					
       						memset(buffer, 0, sizeof buffer);
      						scanf("%[^\n]",buffer);
							write(socketFd,&buffer,strlen(buffer));
							
							memset(buffer, 0, sizeof buffer);
							read(socketFd,&buffer,sizeof(buffer));
       						printf("%s\n",buffer);
       					
					}
					else if(sel==3)
					{
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
       					
       					
       					if(strcmp(buffer,"ok")==0)
       					{
       						write(socketFd,&sel,sizeof(sel));
       					
       						memset(buffer, 0, sizeof buffer);
							read(socketFd,&buffer,sizeof(buffer));
       						printf("%s\n",buffer);
       					
       						memset(bufferi, 0, sizeof bufferi);
      						scanf("%[^\n]",bufferi);
							write(socketFd,&bufferi,strlen(bufferi));
							
							memset(buffer, 0, sizeof buffer);
							read(socketFd,&buffer,sizeof(buffer));
       						printf("%s\n",buffer);
       					}
       					else
       					{
       						printf("%s\n",buffer);
       					}
					}
						
					else
					{
						printf("sorry wrong input\n");
						exit(0);
					}
       			
       			}
       			else
       			{
       				printf("\n");
       				printf("Sorry admin the username you entered does not exist\n");
       				
       				printf("\n");
       			}
       			memset(buffer, 0, sizeof buffer);
			
			}
			else if(sel==5)
			{
				//write(socketFd,&sel,sizeof(sel));
				read(socketFd,&count,sizeof(count));
       			printf("Total Records in Master data is  :%d\n",count);
       			printf("\n");
			}
			else if(sel==6)
			{				
       			printf("bye bye admin\n");
				exit(0);
			}
			else
			{
				printf("sorry this function is yet to be finished\n");
				//exit(0);
			}}
		}
		else if(strcmp(buffer,"user login successful")==0)
			{while(1){
				//printf("user login success\n");
				
				printf("\n");
				printf("--------------WELCOME USER---------------\n");
				printf("\n");
				
				printf(" 1.     Deposit         \n");
				printf(" 2.     Withdraw        \n");
				printf(" 3.     Balance Enquiry \n");
				printf(" 4.     Password Change \n");
				printf(" 5.     Account details \n");
				printf(" 6.     Exit            \n");
				printf("\n");		
				
			
				scanf("%d",&sel);
				
				write(socketFd,&sel,sizeof(sel));
				if(sel==6)		//Exit
				exit(0);
				
				if(sel==1)		// Deposit  
				{
						int id=0;
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				if(strcmp(buffer,"not ok")!=0){
        				scanf("%le",&Damt);
						getchar();
						write(socketFd,&Damt,sizeof(Damt));
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				write(socketFd,&Damt,sizeof(Damt));
        				memset(buffer, 0, sizeof buffer);
						read(socketFd,&id,sizeof(id));
        				printf("----------------------------------\n");
        				printf("---->Transaction id is : %d  <----\n",id);
        				printf("Please note this for further refrence \n ");
        				printf("\n");
        				}
				}
				else if(sel==2)				//Withdraw
				{
						int id=0;
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				if(strcmp(buffer,"not ok")!=0){
        				scanf("%le",&Damt);
						getchar();
						write(socketFd,&Damt,sizeof(Damt));
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				write(socketFd,&Damt,sizeof(Damt));
        				memset(buffer, 0, sizeof buffer);
						read(socketFd,&id,sizeof(id));
						printf("----------------------------------\n");
        				printf("---->Transaction id is : %d  <----\n",id);
        				printf("Please note this for further refrence \n ");
        				printf("\n");
        				}
				}
				else if(sel==3)				//Balance Enquiry
				{
						printf("	Your Account balance is	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&bal,sizeof(fi.balance));
       					printf("%f\n",bal);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
				}
				else if(sel==4)				//Password Change
				{
						char bufferx[1024] = "";
						memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(buffer));
        				printf("%s\n",buffer);
        				printf("\n");
        				
        				memset(bufferx, 0, sizeof bufferx);
        				
     					getchar();
     					scanf("%[^\n]",bufferx);
						write(socketFd,&bufferx,sizeof(bufferx));
						
						memset(bufferx, 0, sizeof bufferx);
						read(socketFd,&bufferx,sizeof(bufferx));
        				printf("%s\n",bufferx);
        				printf("\n");
				
				}
				else if(sel==5)				//Account details
				{
						
       					printf("	Name             	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(fi.username1));
       					printf("%s\n",buffer);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
       			
       					printf("	Password        	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(fi.password1));
       					printf("%s\n",buffer);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
       			
       					printf("	Joint holder name	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(fi.username2));
       					printf("%s\n",buffer);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
       			
       					printf("	Password        	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&buffer,sizeof(fi.password2));
       					printf("%s\n",buffer);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
       			
       					printf("	Account number  	:");
       					memset(buffer, 0, sizeof buffer);
						read(socketFd,&acno,sizeof(fi.account_number));
       					printf("%d\n",acno);
       					printf("\n");
       					write(socketFd,&sel,sizeof(sel));
       			
				}
				else
				{
					printf("sorry invalid input\n");
					exit(0);
				}
			}}
			else
			{
       			printf("wrong id or password\n");
				exit(0);
			}
	close(socketFd);
	return 0;
}
