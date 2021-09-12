#include <stdio.h>
struct Customer{
char username1[1024];
char password1[1024];
char username2[1024];
char password2[1024];
int account_number;
int type;
double balance;
};
struct delc{
int delcount;
};
struct rCount{
int count;
int accno;
};
struct txid{
int id;
};
struct txn{
char name[1024];
char time[1024];
int account_number;
char type[1024];
double amt;
double balance;
};
