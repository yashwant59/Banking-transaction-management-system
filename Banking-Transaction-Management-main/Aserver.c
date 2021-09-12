#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include <time.h>
#include <sys/time.h>
#include<strings.h>
#include<netinet/in.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include "struct.c"

#include<string.h>

struct flock lock;
struct Customer fi;
struct Customer fj;
struct txn t;
struct rCount rc;
struct delc dc;
struct txid tid;
int fd,i,a,x;


struct timeval time1;
int main()
{
	fd = open("masterData.txt", O_RDWR);
	int fd2=open("datacount.txt",O_RDWR|O_CREAT);
	int fd3=open("delete.txt",O_RDWR|O_CREAT);
	int fd4=open("TXN.txt",O_RDWR|O_CREAT);
	int fd5=open("tid.txt",O_RDWR|O_CREAT);
	
	read(fd2,&rc,sizeof(rc));
	a=rc.count;
	
	int listenfd,connfd;
	socklen_t cLen;
	struct sockaddr_in clientAdd,serverAdd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bzero(&serverAdd,sizeof(serverAdd));
	serverAdd.sin_family = AF_INET;
	serverAdd.sin_addr.s_addr=INADDR_ANY;
	serverAdd.sin_port=htons(6085);
	bind(listenfd,(struct sockaddr*)&serverAdd,sizeof(serverAdd));
	perror("bind");
	listen(listenfd,15);
	perror("listen");
	while(1)
	{
		cLen=sizeof(clientAdd);
		connfd=accept(listenfd,(struct sockaddr*)&clientAdd,&cLen);
		printf("Awaiting client actions \n");
		pid_t pid=fork();

		if(pid==0)
		{
					
			int sel;
			double Damt=0;
			close(listenfd);	
			char buffer[1024] = "";
			char buffer2[1024] = "";
			char name[1024] = "";
			memset(buffer, 0, sizeof buffer);
            read(connfd,&buffer,sizeof(buffer));
            printf("Username from client is %s\n",buffer);
            memcpy(name,buffer,sizeof(buffer));
            
				if(strcmp(buffer,"admin")==0)
				{
					printf("Admin login detected\n");
					write(connfd,"Enter password",strlen("Enter password"));
					read(connfd,&buffer2,sizeof(buffer2));
					printf("Password from client is %s\n",buffer2);
					if(strcmp(buffer2,"asdfg")==0)
					{
						write(connfd,"admin login successful",strlen("admin login successful"));
						//write(connfd,"enter 1 to read record",strlen("enter 1 to read record"));
						//write(connfd,"enter 2 to quit",strlen("enter 2 to quit"));
						
						while(1){
						printf("Awaiting admin query\n");
						read(connfd,&sel,sizeof(sel));
						if(sel==1)
						{
							int s1=0;
							int s2=0;
							write(connfd,"Enter Username",strlen("Enter Username"));
							memset(buffer, 0, sizeof buffer);
							read(connfd,&buffer,sizeof(buffer));
							
							for(int pp1=1;pp1<=rc.count;pp1++)
								{
									lock.l_type   = F_RDLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp1-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp1-1)*sizeof(fi),SEEK_SET);
									
									fcntl(fd,F_SETLKW,&lock);
									read(fd,&fi,sizeof(fi));
									if(strcmp(buffer,fi.username1)==0  || strcmp(buffer,fi.username2)==0 )
										{
											i=pp1;
															
											lock.l_type   = F_RDLCK;  
											lock.l_whence = SEEK_SET; 
											lock.l_start  = (i-1)*sizeof(fi);        
											lock.l_len    = sizeof(fi);        
											lock.l_pid    = getpid(); 
											lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
											printf("Before Critical section\n");
											fcntl(fd,F_SETLKW,&lock);
											read(fd,&fi,sizeof(fi));
								
											printf("Sending account details to admin\n");
											if(s2==0)
											{
											write(connfd,"ok",strlen("ok"));
											read(connfd,&i,sizeof(i));
											
											write(connfd,fi.username1,strlen(fi.username1));
											read(connfd,&i,sizeof(i));
											write(connfd,fi.password1,strlen(fi.password1));
											read(connfd,&i,sizeof(i));
											write(connfd,fi.username2,strlen(fi.username2));
											read(connfd,&i,sizeof(i));
											write(connfd,fi.password2,strlen(fi.password2));
											read(connfd,&i,sizeof(i));
											write(connfd,&fi.account_number,sizeof(fi.account_number));
											read(connfd,&i,sizeof(i));
											write(connfd,&fi.balance,sizeof(fi.balance));
											read(connfd,&i,sizeof(i));
											write(connfd,&fi.type,sizeof(fi.type));
											read(connfd,&i,sizeof(i));

											printf("Account details sent to admin\n");

											lock.l_type=F_UNLCK;
											printf("File Unlocked\n");
											fcntl(fd,F_SETLK,&lock);
											s2=1;
											}
										}
										else
										s1=1;
																					
								}
								if(s2==0 && s1 ==1)
								{
									write(connfd,"not ok",strlen("not ok"));
								}
								memset(buffer, 0, sizeof buffer);
								
						}
						else if(sel==2)
						{
								int imp=0;
								lseek(fd3,0,SEEK_SET); 
								read(fd3,&dc,sizeof(dc));
								int g=dc.delcount;
								if(g>0)
								{
									for(int pp1=1;pp1<=rc.count;pp1++)
									{
									lock.l_type   = F_RDLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp1-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp1-1)*sizeof(fi),SEEK_SET);
									
									fcntl(fd,F_SETLKW,&lock);
									read(fd,&fi,sizeof(fi));
									if(strcmp("*121#",fi.username1)==0  || strcmp("*121#",fi.username2)==0 )
										{
											imp=pp1;
											break;
										}
									}
									int s=1;
   									char bufferx[1024] = "";
									write(connfd,"Enter username1",strlen("Enter username1"));
									read(connfd,&fi.username1,sizeof(fi.username1));
									strcpy(bufferx,fi.username1);
									for(int pp=1;pp<=a;pp++)
										{
											lock.l_type   = F_RDLCK;  
											lock.l_whence = SEEK_SET; 
											lock.l_start  = (pp-1)*sizeof(fj);        
											lock.l_len    = sizeof(fj);        
											lock.l_pid    = getpid(); 
											lseek(fd,(pp-1)*sizeof(fj),SEEK_SET);
											//printf("Before Entering the Critical section\n");
											fcntl(fd,F_SETLKW,&lock);
											read(fd,&fj,sizeof(fj));
											if(strcmp(fj.username1,bufferx)==0  || strcmp(fj.username2,bufferx)==0)
											{
												printf("invalid username\n");
												write(connfd,"not ok",strlen("not ok"));
												s=0;
											}
											lock.l_type=F_UNLCK;
											//printf("File unlocked\n");
											fcntl(fd,F_SETLK,&lock);	
										}
									
									if(s==1)
									{
									int i1=1;
									write(connfd,"ok",strlen("ok"));
									read(connfd,&i1,sizeof(i1));
										
									write(connfd,"Enter password1",strlen("Enter password1"));
									read(connfd,&fi.password1,sizeof(fi.password1));
										
									write(connfd,"Enter username2 (enter - if null)",strlen("Enter username2 (enter - if null)"));
									read(connfd,&fi.username2,sizeof(fi.username2));
										
									write(connfd,"Enter password2 (enter - if null)",strlen("Enter password2 (enter - if null)"));
									read(connfd,&fi.password2,sizeof(fi.password2));
										
										
										
									fi.balance=0;
									fi.account_number=rc.accno+1;

									fi.type=rc.count+1;
									rc.count++;
									rc.accno++;
										printf("%s\n%s\n%s\n%s\n%d\n%f\n%d\n",fi.username1,fi.password1,fi.username2,fi.password2,fi.account_number,fi.balance,fi.type);
									lseek(fd,(imp-1)*sizeof(fi),SEEK_SET);
									write(fd,&fi,sizeof(fi));
									lseek(fd,0,SEEK_SET);
										
									lseek(fd2,-1*sizeof(rc),SEEK_CUR);   //increment record count and store
									write(fd2,&rc,sizeof(rc));
									
									lseek(fd3,0,SEEK_SET); 
									read(fd3,&dc,sizeof(dc));
									dc.delcount--;
									lseek(fd3,0,SEEK_SET); 
									write(fd3,&dc,sizeof(dc));
									
									write(connfd,"Account added successfully",strlen("Account added successfully"));
									}
								
								}
								else
								{
						
										int s=1;
   										char bufferx[1024] = "";
										write(connfd,"Enter username1",strlen("Enter username1"));
										read(connfd,&fi.username1,sizeof(fi.username1));
										strcpy(bufferx,fi.username1);
										for(int pp=1;pp<=a;pp++)
											{
												lock.l_type   = F_RDLCK;  
												lock.l_whence = SEEK_SET; 
												lock.l_start  = (pp-1)*sizeof(fj);        
												lock.l_len    = sizeof(fj);        
												lock.l_pid    = getpid(); 
												lseek(fd,(pp-1)*sizeof(fj),SEEK_SET);
												//printf("Before Entering the Critical section\n");
												fcntl(fd,F_SETLKW,&lock);
												read(fd,&fj,sizeof(fj));
												if(strcmp(fj.username1,bufferx)==0  || strcmp(fj.username2,bufferx)==0)
												{
													printf("invalid username\n");
													write(connfd,"not ok",strlen("not ok"));
													s=0;
												}
												lock.l_type=F_UNLCK;
												//printf("File unlocked\n");
												fcntl(fd,F_SETLK,&lock);	
											}
										
										if(s==1)
										{
										int i1=1;
										write(connfd,"ok",strlen("ok"));
										read(connfd,&i1,sizeof(i1));
										
										write(connfd,"Enter password1",strlen("Enter password1"));
										read(connfd,&fi.password1,sizeof(fi.password1));
										
										write(connfd,"Enter username2 (enter - if null)",strlen("Enter username2 (enter - if null)"));
										read(connfd,&fi.username2,sizeof(fi.username2));
										
										write(connfd,"Enter password2 (enter - if null)",strlen("Enter password2 (enter - if null)"));
										read(connfd,&fi.password2,sizeof(fi.password2));
										
										
										
										fi.balance=0;
										fi.account_number=rc.accno+1;
										fi.type=rc.count+1;
										rc.count++;
										rc.accno++;
										printf("%s\n%s\n%s\n%s\n%d\n%f\n%d\n",fi.username1,fi.password1,fi.username2,fi.password2,fi.account_number,fi.balance,fi.type);
										lseek(fd,0,SEEK_END);
										write(fd,&fi,sizeof(fi));
										lseek(fd,0,SEEK_SET);
										
										lseek(fd2,-1*sizeof(rc),SEEK_CUR);   //increment record count and store
										write(fd2,&rc,sizeof(rc));
										write(connfd,"Account added successfully",strlen("Account added successfully"));
										}
								}
   							
						}
						else if(sel==3)
						{
							int s1=0;
							int s2=0;
							int i1=1;
							char cc[1024]="";
							write(connfd,"Enter Username of account to delete",strlen("Enter Username of account to delete"));
							memset(buffer, 0, sizeof buffer);
							read(connfd,&buffer,sizeof(buffer));
							
							for(int pp1=1;pp1<=rc.count;pp1++)
								{
									lock.l_type   = F_RDLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp1-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp1-1)*sizeof(fi),SEEK_SET);
									
									fcntl(fd,F_SETLKW,&lock);
									read(fd,&fi,sizeof(fi));
									if(strcmp(buffer,fi.username1)==0  || strcmp(buffer,fi.username2)==0 )
										{
											i=pp1;
															
											lock.l_type   = F_RDLCK;  
											lock.l_whence = SEEK_SET; 
											lock.l_start  = (i-1)*sizeof(fi);        
											lock.l_len    = sizeof(fi);        
											lock.l_pid    = getpid(); 
											lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
											printf("Before Critical section\n");
											fcntl(fd,F_SETLKW,&lock);
											read(fd,&fi,sizeof(fi));
								
											printf("Admin is deleting account\n");
											if(s2==0)
											{
												write(connfd,"ok",strlen("ok"));
												read(connfd,&x,sizeof(x));
											
												if(x==1)
												{
													
													memset(fi.username1, 0, sizeof(fi.username1));
													memcpy(fi.username1,"*121#",sizeof("*121#"));
													memset(fi.username2, 0, sizeof(fi.username2));
													memcpy(fi.username2,"*121#",sizeof("*121#"));
													
													lseek(fd3,0,SEEK_SET); 
													read(fd3,&dc,sizeof(dc));
													dc.delcount++;
													lseek(fd3,0,SEEK_SET);   //increment count and store
													write(fd3,&dc,sizeof(dc));
													
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													write(fd,&fi,sizeof(fi));
													write(connfd,"successfully deleted",strlen("successfully deleted"));
												
												printf("Account deleted by admin\n");
												}
												else if(x==2)
												{
													printf("admin chose not to delete");
												}
												lock.l_type=F_UNLCK;
												printf("File Unlocked\n");
												fcntl(fd,F_SETLK,&lock);
												s2=1;
											}
										}
										else
										s1=1;
																					
								}
								if(s2==0 && s1 ==1)

								{
									write(connfd,"not ok",strlen("not ok"));
								}
								memset(buffer, 0, sizeof buffer);
							
								
						}
						else if(sel==4)
						{
							int s1=0;
							int s2=0;
							int i1=1;
							char cc[1024]="";
							write(connfd,"Enter Username",strlen("Enter Username"));
							memset(buffer, 0, sizeof buffer);
							read(connfd,&buffer,sizeof(buffer));
							
							for(int pp1=1;pp1<=rc.count;pp1++)
								{
									lock.l_type   = F_RDLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp1-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp1-1)*sizeof(fi),SEEK_SET);
									
									fcntl(fd,F_SETLKW,&lock);
									read(fd,&fi,sizeof(fi));
									if(strcmp(buffer,fi.username1)==0  || strcmp(buffer,fi.username2)==0 )
										{
											i=pp1;
															
											lock.l_type   = F_RDLCK;  
											lock.l_whence = SEEK_SET; 
											lock.l_start  = (i-1)*sizeof(fi);        
											lock.l_len    = sizeof(fi);        
											lock.l_pid    = getpid(); 
											lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
											printf("Before Critical section\n");
											fcntl(fd,F_SETLKW,&lock);
											read(fd,&fi,sizeof(fi));
								
											printf("Admin is modifying account details\n");
											if(s2==0)
											{
												write(connfd,"ok",strlen("ok"));
												read(connfd,&x,sizeof(x));
											
												if(x==1)
												{
													write(connfd,"Enter new password1",strlen("Enter new password1"));
													memset(fi.password1, 0, sizeof(fi.password1));
													read(connfd,&fi.password1,sizeof(fi.password1));
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													write(fd,&fi,sizeof(fi));
													write(connfd,"successfully modified",strlen("successfully modified"));
												}
												else if(x==2)
												{
													
													write(connfd,"Enter name of joint user",strlen("Enter name of joint user"));
													memset(fi.username2, 0, sizeof(fi.username2));
													read(connfd,&fi.username2,sizeof(fi.username2));
													
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													write(fd,&fi,sizeof(fi));
													write(connfd,"successfully added",strlen("successfully added"));
												
												}
												else if(x==3)
												{
													if(strcmp(fi.username2,"-")!=0)
													{
													write(connfd,"ok",strlen("ok"));
													read(connfd,&i1,sizeof(i1));
													write(connfd,"Enter new password2",strlen("Enter new password2"));
													memset(fi.password2, 0, sizeof(fi.password2));
													read(connfd,&fi.password2,sizeof(fi.password2));
													
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													write(fd,&fi,sizeof(fi));
													write(connfd,"successfully modified",strlen("successfully modified"));
													}
													else
													{
														write(connfd,"not a joint account",strlen("not a joint account"));
													}
												}
												
												printf("Account modified by admin\n");

												lock.l_type=F_UNLCK;
												printf("File Unlocked\n");
												fcntl(fd,F_SETLK,&lock);
												s2=1;
											}
										}
										else
										s1=1;
																					
								}
								if(s2==0 && s1 ==1)
								{
									write(connfd,"not ok",strlen("not ok"));
								}
								memset(buffer, 0, sizeof buffer);
							
								
						}
						else if(sel==5)
						{
							printf("Record count sent to admin\n");
							a=rc.count;
							write(connfd,&a,sizeof(a));
						}
						else if(sel==6 || sel>6)
						{
							break;
						}
						printf("Admin query finished\n");
					}}
				}
                
				else
				{
					lseek(fd2,0,SEEK_SET);
					read(fd2,&rc,sizeof(rc));
					for(int pp=1;pp<=rc.count;pp++)
					{
						lock.l_type   = F_RDLCK;  
						lock.l_whence = SEEK_SET; 
						lock.l_start  = (pp-1)*sizeof(fi);        
						lock.l_len    = sizeof(fi);        
						lock.l_pid    = getpid(); 
						lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);
						//printf("Before Entering the Critical section\n");
						fcntl(fd,F_SETLKW,&lock);
						read(fd,&fi,sizeof(fi));
						if(strcmp(buffer,fi.username1)==0  || strcmp(buffer,fi.username2)==0)
						{
							printf("normal user login detected\n");
							write(connfd,"Enter password",strlen("Enter password"));
							read(connfd,&buffer2,sizeof(buffer2));
							printf("Password from client is %s\n",buffer2);
							if(strcmp(buffer2,fi.password1)==0  || strcmp(buffer2,fi.password2)==0)
							{
								
								write(connfd,"user login successful",strlen("user login successful"));
								while(1){
								printf("Awaiting user queries\n");
								read(connfd,&sel,sizeof(sel));
								
								if(sel==1)			// Deposit
								{
									char bufferx[1024] = "";
									printf("Ongoing query for record :  ");
									printf("%d\n",pp);
									double bal;
									lock.l_type   = F_WRLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);
									printf("Before Entering the Critical section\n");
									printf("User is Depositing\n");
									if (fcntl(fd,F_SETLK,&lock) == -1) {
    								perror("fcntl");
    								write(connfd,"not ok",strlen("not ok"));
    								break;}
									
									write(connfd,"Enter amount to be deposited",strlen("Enter amount to be deposited"));
									read(connfd,&Damt,sizeof(Damt));
									bal=fi.balance;
									fi.balance=bal+Damt;
									
									
									gettimeofday(&time1, NULL);

    								strftime(bufferx, 40, "Date/time        : %m-%d-%Y/%T", localtime(&time1.tv_sec));
   									printf("%s\n",bufferx);
   									
									memcpy(t.time,bufferx,sizeof(bufferx));
									memcpy(t.name,fi.username1,sizeof(fi.username1));
									t.account_number=fi.account_number;
									memcpy(t.type,"deposit",sizeof("deposit"));
									t.amt=Damt;
									t.balance=fi.balance;
									
													lseek(fd5,0,SEEK_SET); 
													read(fd5,&tid,sizeof(tid));
													tid.id++;
													lseek(fd5,0,SEEK_SET);   //increment count and store
													write(fd5,&tid,sizeof(tid));
									
									write(fd,&fi,sizeof(fi));
									lock.l_type=F_UNLCK;
									
									lseek(fd4,0,SEEK_END);			//storing transaction
									write(fd4,&t,sizeof(t));
									
									fcntl(fd,F_SETLK,&lock);
									printf("File unlocked\n");
									write(connfd,"Amount deposited",strlen("Amount deposited"));
									read(connfd,&Damt,sizeof(Damt));
									write(connfd,&tid.id,sizeof(tid.id));
								}
								else if(sel==2)				//Withdraw
								{
									char bufferx[1024] = "";
									printf("Ongoing query for record :  ");
									printf("%d\n",pp);
									double bal;
									lock.l_type   = F_WRLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);
									printf("Before Entering the Critical section\n");
									printf("User is Withdrawing\n");
									if (fcntl(fd,F_SETLK,&lock)== -1) {
    								perror("fcntl");
    								write(connfd,"not ok",strlen("not ok"));
    								break;}
									
									write(connfd,"Enter amount to withdraw",strlen("Enter amount to withdraw"));
									read(connfd,&Damt,sizeof(Damt));
									bal=fi.balance;
									if(Damt<bal)
									{
									fi.balance=bal-Damt;
									
									gettimeofday(&time1, NULL);

    								strftime(bufferx, 40, "Date/time        : %m-%d-%Y/%T", localtime(&time1.tv_sec));
   									printf("%s\n",bufferx);
   									
									memcpy(t.time,bufferx,sizeof(bufferx));
									memcpy(t.name,fi.username1,sizeof(fi.username1));
									t.account_number=fi.account_number;
									memcpy(t.type,"withdraw",sizeof("withdraw"));
									t.amt=Damt;
									t.balance=fi.balance;
									
													lseek(fd5,0,SEEK_SET); 
													read(fd5,&tid,sizeof(tid));
													tid.id++;
													lseek(fd5,0,SEEK_SET);   //increment count and store
													write(fd5,&tid,sizeof(tid));
									
									write(fd,&fi,sizeof(fi));
									lock.l_type=F_UNLCK;
									
									lseek(fd4,0,SEEK_END);
									write(fd4,&t,sizeof(t));       //storing transaction
									
									
									fcntl(fd,F_SETLK,&lock);
									printf("File unlocked\n");
									write(connfd,"Money withdraw success",strlen("Money withdraw success"));
									read(connfd,&Damt,sizeof(Damt));
									write(connfd,&tid.id,sizeof(tid.id));
									}
									else
									{
	write(connfd,"You dont have sufficient money in your account",strlen("You dont have sufficient money in your account"));
									}
								}
								else if(sel==3)			//Balance Enquiry
								{
													i=pp;
															
													lock.l_type   = F_RDLCK;  
													lock.l_whence = SEEK_SET; 
													lock.l_start  = (i-1)*sizeof(fi);        
													lock.l_len    = sizeof(fi);        
													lock.l_pid    = getpid(); 
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													//printf("Before Critical section\n");
													fcntl(fd,F_SETLKW,&lock);
													read(fd,&fi,sizeof(fi));
										
													printf("Responding to balance enquiry\n");
													write(connfd,&fi.balance,sizeof(fi.balance));
													read(connfd,&i,sizeof(i));
													
													printf("Balance details sent to user\n");

													lock.l_type=F_UNLCK;
													printf("Record Unlocked\n");
													fcntl(fd,F_SETLK,&lock);
								}
								else if(sel==4)				//Password Change
								{
									printf("Ongoing query for record :  ");
									printf("%d\n",pp);
									char npass[1024]="";
									//char opass[1024]="";
									lock.l_type   = F_WRLCK;  
									lock.l_whence = SEEK_SET; 
									lock.l_start  = (pp-1)*sizeof(fi);        
									lock.l_len    = sizeof(fi);        
									lock.l_pid    = getpid(); 
									lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);
									printf("Before Entering the Critical section\n");
									printf("User is changing password\n");
									fcntl(fd,F_SETLKW,&lock);
									
									
									if(strcmp(name,fi.username1)==0)
										{
										char bufferx[1024] = "";
										write(connfd,"Enter new password user1",strlen("Enter new password user1"));
										read(connfd,&fi.password1,sizeof(fi.password1));
											
											gettimeofday(&time1, NULL);

    										strftime(bufferx, 40, "Date/time        : %m-%d-%Y/%T", localtime(&time1.tv_sec));
   											printf("%s\n",bufferx);
   									
											memcpy(t.time,bufferx,sizeof(bufferx));
											memcpy(t.name,fi.username1,sizeof(fi.username1));
											t.account_number=fi.account_number;
											memcpy(t.type,"password change",sizeof("password change"));
											t.amt=0;
											t.balance=fi.balance;
											
													lseek(fd5,0,SEEK_SET); 
													read(fd5,&tid,sizeof(tid));
													tid.id++;
													lseek(fd5,0,SEEK_SET);   //increment count and store
													write(fd5,&tid,sizeof(tid));
											
										lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);	
										write(fd,&fi,sizeof(fi));
										lock.l_type=F_UNLCK;
										
										lseek(fd4,0,SEEK_END);
										write(fd4,&t,sizeof(t));       //storing transaction
									
										fcntl(fd,F_SETLK,&lock);
										printf("File unlocked\n");
										write(connfd,"Password successfully changed",strlen("Password successfully changed"));
										}
									else
										{
										char bufferx[1024] = "";
										write(connfd,"Enter new password user2",strlen("Enter new password user2"));
										read(connfd,&fi.password2,sizeof(fi.password2));
										
											gettimeofday(&time1, NULL);

    										strftime(bufferx, 40, "Date/time        : %m-%d-%Y/%T", localtime(&time1.tv_sec));
   											printf("%s\n",bufferx);
   									
											memcpy(t.time,bufferx,sizeof(bufferx));
											memcpy(t.name,fi.username2,sizeof(fi.username2));
											t.account_number=fi.account_number;
											memcpy(t.type,"password change",sizeof("password change"));
											t.amt=0;
											t.balance=fi.balance;
										
										lseek(fd,(pp-1)*sizeof(fi),SEEK_SET);	
										write(fd,&fi,sizeof(fi));
										lock.l_type=F_UNLCK;
										
										lseek(fd4,0,SEEK_END);
										write(fd4,&t,sizeof(t));       //storing transaction
										
										fcntl(fd,F_SETLK,&lock);
										printf("File unlocked\n");
										write(connfd,"Password successfully changed",strlen("Password successfully changed"));
										}			
									
								}
								else if(sel==5)			//Account details
								{											
													i=pp;
															
													lock.l_type   = F_RDLCK;  
													lock.l_whence = SEEK_SET; 
													lock.l_start  = (i-1)*sizeof(fi);        
													lock.l_len    = sizeof(fi);        
													lock.l_pid    = getpid(); 
													lseek(fd,(i-1)*sizeof(fi),SEEK_SET);
													//printf("Before Critical section\n");
													fcntl(fd,F_SETLKW,&lock);
													read(fd,&fi,sizeof(fi));
										
													printf("Sending account details to user\n");

													write(connfd,fi.username1,strlen(fi.username1));
													read(connfd,&i,sizeof(i));
													write(connfd,fi.password1,strlen(fi.password1));
													read(connfd,&i,sizeof(i));
													write(connfd,fi.username2,strlen(fi.username2));
													read(connfd,&i,sizeof(i));
													write(connfd,fi.password2,strlen(fi.password2));
													read(connfd,&i,sizeof(i));
													write(connfd,&fi.account_number,sizeof(fi.account_number));
													read(connfd,&i,sizeof(i));
													
													printf("Account details sent to user\n");

													lock.l_type=F_UNLCK;
													printf("Record Unlocked\n");
													fcntl(fd,F_SETLK,&lock);
								
								}
								else if(sel==6 || sel>6)
								{
									break;
								}
								}
							}
						}
						else
						{
							continue;
						}
						lock.l_type=F_UNLCK;
						printf("File unlocked\n");
						fcntl(fd,F_SETLK,&lock);	
			
					}
				}
		exit(0);	 
		}
		else if(pid<0)
		{
			perror("fork");
			exit(1);
		}		
			close(connfd);	
	}
	return 0;
}
	
