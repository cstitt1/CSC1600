#include <stdio.h>
#include <string.h>

void login() {
    int authenticated=0;
    char pw[4];
    char un[4];
    
    printf("enter user name\n");
    scanf("%s",un);
    //gets(un);
    printf("enter password\n");
   scanf("%s",pw);
   //gets(pw);
   //printf("pw is %s",pw);

    if(strcmp(pw,"pw")==0) {
        authenticated=1;
    }
    if(authenticated!=0)
    puts("Logged in\n");
    else
    puts("Incorrect password\n"); 
}

int main(int argc, char const *argv[])
{
    login();
     return 0;
    
}
