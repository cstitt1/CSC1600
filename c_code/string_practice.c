#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char msg[] = "I am on my way to class";
    char* mp = "string as pointer";

    printf("Message is: %s\n",msg);
    //this will print mp as a string
    printf("Message pointer as string is %s\n",mp);
    //this will print address of message pointer mp
    printf("Message pointer is %p\n", mp);

    //The character '\0' terminates all strings
    //to terminate a string add '\0' to it
    msg[14] = '\0';
    printf("Message is now %s\n",msg);

    //string.h has many functions to process strings
    //strstr returns the address of a substring
    char* full_string = "empowerment";
    //this will return the address of where the string power begins
    char* power = strstr(full_string, "power"); 
    printf("the address of power is %p\n",power);
    printf("the address of empowerment is %p\n",full_string);
	
    //now get index place by finding diff in addresses
    int diff = power - full_string;
    printf("the difference in addresses is the index place of the substring: %d\n",diff);

    //now let's create 2 strings
   //we want to create a 3 string with the concatenation of the 2

    char* m1 = "meet me ";
    char* m2 = "in the cafeteria";
    //below gives a seg fault because m3 is uninitialized
    //it must be initialized with malloc
    //char* m3 = strcpy(m3,m1);

    //find length of the 2 strings we are concatenating
    //and allocate that amount of space using malloc
    //try using strcat or strcpy without malloc and see what happens
    int sizem1 = strlen(m1);
    int sizem2 = strlen(m2);
    int totalSize = sizem1 + sizem2;
    
    char* m3 = malloc(sizeof(totalSize));
    strcpy(m3, m1);
    strcat(m3, m2);
    printf("The new message is %s\n", m3);
    free(m3);
    
    return 0;
}
