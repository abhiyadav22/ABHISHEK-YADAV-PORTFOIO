#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define GOTOXY(x,y) printf("\003[%d,%df]",y,x)

void delay(int time)
{
    int milli = 1000 * time ;
    clock();
    while(clock()<milli);
}

void input();
void writefile();
void search();
void output();

struct date {
    int month;
    int day;
    int year;

};
struct account {
    int number;
    char name[100];
    int acct_no ;
    float mobile_no;
    char street[100];
    char city[100];
    char acct_type;
    float oldbalance;
    float newbalance;
    float payment;
    struct date lastpayment;
}customer;
int tl,sl,ts;

int main()
{
 int i,n;
 char ch;
 system("clear");
 printf("CUSTOMER BILLING SYSTEM : \n\n");
 printf("========================\n\n");
 printf("1: ADD ACCOUNT ON LIST \n");
 printf("2: SEARCH CUSTOMER ACCOUNT \n");
 printf("3: EXIT\n");
 printf("=========================\n");

 do
 {
    printf("\n select what you want to do ?? \n");
    ch=getchar();
 }while(ch<='0' || ch>'3');

 switch(ch)
 {
  case '1':
  system("clear");
  printf("\n how many customer accounts :");
  scanf("%d",&n);
  getchar();
  for(i=0;i<n;i++)
  {
    input();
    if(customer.payment > 0.0)
    customer.acct_type=(customer.payment < customer.oldbalance) ? '0' : 'D' ;
    else
    customer.acct_type=(customer.oldbalance > 0) ? 'D' : 'C' ;
    customer.newbalance=customer.oldbalance -customer.payment ;
    writefile();
  }
  main();
  case '2':
  getchar();
  system("clear");
  printf("search by what ?? \n");
  printf("1:- - - - - - - - search by customer number \n");
  printf("2:- - - - - - - search by customer name \n");
  search();
  ch=getchar();
  main();
  case '3':
  system("clear");
  delay(500);
  GOTOXY(10,25);
  printf("A PROJECT THAT I AM LEARNING & OTHER ENJOYING ");
  delay(1500);
  exit(1);
 }
}
void input()
{
    FILE *fp=fopen("file.txt","ab+");
    fseek(fp,0,SEEK_END);
    tl=ftell(fp);
    sl=sizeof(customer);
    ts=tl/sl;
    fseek(fp,(ts-1)*sl,SEEK_SET);
    fread(&customer,sizeof(customer),1,fp);
    printf("\ncustomer no : %d \n" , ++customer.number);
    fclose(fp);
    printf("   Acount number :");
    scanf("%d" , &customer.acct_no);
    getchar();
    printf("\n NAME :");
    scanf("%s", customer.name);
    getchar();
    printf("\n  mobile no :");
    scanf("%f", &customer.mobile_no);
    getchar();
    printf("\n    street:  ");
    scanf("%s",customer.city);
    getchar();
    printf("\n    previous balance :");
    scanf("%f",&customer.oldbalance);
    getchar();
    printf("\n    current payment :");
    scanf("%f",&customer.payment);
    getchar();
    printf("        payment date (mm/dd/yyyy) : ") ;
    scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
    getchar();

}

void writefile()
{
    FILE *fp;
    fp=fopen("file.txt","ab+");
    fwrite(&customer,sizeof(customer),1,fp);
    fclose(fp);
    return;
}
void search()
{
    char ch;
    char nam[100];
    int n,i,m=1;
    FILE *fp;
    fp=fopen("file.txt","r+");
    do
    {
      printf("\n enter your choice : ");
      ch=getchar();
    }
    while(ch!='1' && ch!='2');
    switch(ch)
    {
        case '1' :
        fseek(fp,0,SEEK_END);
        tl = ftell(fp);
        sl=sizeof(customer);
        ts=tl/sl;
        do
        {
            printf("\n  choose customer number :");
            scanf("%d",&n);
            if(n<=0 || n>ts)
            printf("\n enter correct \n");
            else
            {
                fseek(fp,(n-1)*sl,SEEK_SET);
                fread(&customer,sl,1,fp);
                output();

            }
            printf("\n\n again ? (y/n)");
            ch=getchar();
        }
        while(ch =='y');
        fclose(fp);
        break;
        case '2':
        fseek(fp,0,SEEK_END);
        tl=ftell(fp);
        sl=sizeof(customer);
        ts=tl/sl;
        fseek(fp,(ts-1)*sl,SEEK_SET);
        fread(&customer,sizeof(customer),1,fp);
        n = customer.number;
        do
        {
            printf("\n enter the name :");
            scanf("%s", nam);
            fseek(fp,0,SEEK_SET);
            for(i=1;i<=n;i++)
            {
                fread(&customer,sizeof(customer),1,fp);
                if(strcmp(customer.name,nam)==0)
                {
                    output();
                    m=0;
                    break;
                }
            }
            if(m!=0)
            printf("\n\n doesn't exist \n");
            printf("\n another ?? (y/n)");
            ch=getchar();
        }
        while(ch=='y');
        fclose(fp);

    }
    return;

}
void output()
{
    printf("\n\n customer no : %d \n , customer.number");
    printf(" Name  :%s \n", customer.name);
    printf("mobile no. : %.f \n", customer.mobile_no);
    printf(" Account number  : %d  \n", customer.acct_no);
    printf(" street : %s \n , customer.street");
    printf(" city  :%s \n", customer.city);
    printf("  old balance : %.2f \n", customer.oldbalance);
    printf("  current payment  : %.2f  \n", customer.payment);
    printf("  New balance : %.2f  \n", customer.newbalance);
    printf("  payment date : %d/%d/%d  \n\n", customer.lastpayment.month, customer.lastpayment.day, customer.lastpayment.year);
    printf("    account status :");

    switch(customer.acct_type)
    {
     case 'c':
     break;
     case '0':
     printf("OVERDUE \n\n");
     break;
     case 'D' :
     printf("DELINQUENT \n\n");
     break;
     default :
     printf("ERROR \n\n");
    }
    return;
}