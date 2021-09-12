#include<string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "struct.c"

int main() {
struct flock lock;
struct Customer fi;
struct txn t;
struct txid tid;
int fd,i,a,sel;
int fd5=open("tid.txt",O_RDWR|O_CREAT);

printf("   ----->1 Search using Transaction id \n");
printf("   ----->2 Search using Username \n");
scanf("%d",&sel);
if(sel==1)
{
while(1){
printf("Enter the Transaction id  or Enter -1 to quit\n");
scanf("%d",&i);
if(i==-1)
break;
fd = open("TXN.txt", O_RDWR);
lock.l_type   = F_RDLCK;  
lock.l_whence = SEEK_SET; 
lock.l_start  = (i-1)*sizeof(t);        
lock.l_len    = sizeof(t);        
lock.l_pid    = getpid(); 
lseek(fd,(i-1)*sizeof(t),SEEK_SET);

fcntl(fd,F_SETLKW,&lock);
read(fd,&t,sizeof(t));
printf("Transaction id   : %d\n",i);
printf("Name             : %s\nAccount number   : %d\nAction           : %s\n%s\nAmount           : %f\nCurrent balance  : %f\n",t.name,t.account_number,t.type,t.time,t.amt,t.balance);

lock.l_type=F_UNLCK;

fcntl(fd,F_SETLK,&lock);}
}
else if(sel==2)
{

int k=1;
read(fd5,&tid,sizeof(tid));
k=tid.id;
printf("enter name or   enter -1 to quit\n");
char buffer[100]="";
int i=0;
getchar();
scanf("%[^\n]",buffer);
while(i<k){



fd = open("TXN.txt", O_RDWR);
lock.l_type   = F_RDLCK;  
lock.l_whence = SEEK_SET; 
lock.l_start  = (i-1)*sizeof(t);        
lock.l_len    = sizeof(t);        
lock.l_pid    = getpid(); 
lseek(fd,(i-1)*sizeof(t),SEEK_SET);

fcntl(fd,F_SETLKW,&lock);
read(fd,&t,sizeof(t));
if(strcmp(buffer,t.name)==0)
{
printf("--------------------------------------------\n");
printf("\n");
printf("Name             : %s\nAccount number   : %d\nAction           : %s\n%s\nAmount           : %f\nCurrent balance  : %f\n",t.name,t.account_number,t.type,t.time,t.amt,t.balance);

printf("\n");
printf("--------------------------------------------\n");

}
else if(strcmp(t.name,"")==0)
{
break;
}
lock.l_type=F_UNLCK;

fcntl(fd,F_SETLK,&lock);

i++;
}

}
}












