
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "struct.c"
int main() {
struct flock lock;
struct Customer fi;
int fd,i,a;
while(1){
printf("enter the record num  you want to read  enter -1 to quit  :  ");
scanf("%d",&i);
if(i==-1)
break;
fd = open("masterData.txt", O_RDWR);
lock.l_type   = F_RDLCK;  
lock.l_whence = SEEK_SET; 
lock.l_start  = (i-1)*sizeof(fi);        
lock.l_len    = sizeof(fi);        
lock.l_pid    = getpid(); 
lseek(fd,(i-1)*sizeof(fi),SEEK_SET);

fcntl(fd,F_SETLKW,&lock);
read(fd,&fi,sizeof(fi));
//printf("%s\n%s\n%s\n%s\n%d\n%f\n%d\n",fi.username1,fi.password1,fi.username2,fi.password2,fi.account_number,fi.balance,fi.type);
printf("Name 1        : %s\nPassword 1    : %s\nName 2        : %s\nPassword 2    : %s\nAccount no.   : %d\nBalance       : %f\nRecord no.    : %d\n",fi.username1,fi.password1,fi.username2,fi.password2,fi.account_number,fi.balance,fi.type);
lock.l_type=F_UNLCK;

fcntl(fd,F_SETLK,&lock);}
}

