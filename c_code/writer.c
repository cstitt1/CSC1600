#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <string.h>

int main() 
{ 
	// ftok to generate unique key 
    //System V IPC key
    //this key is used to create a segment of shared memory.
    //any process with this key can access the shared memory segment.
	key_t key = ftok("writer.c",65); 

	// shmget returns an identifier in shmid 
    //with the key, we'll get an id for the shared segment
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
    //use the id to attach a variable to the shared memory
    //any time we write to this variable the value is stored in the shared memory
    //segment which available to all processes with original key.
	char *str = (char*) shmat(shmid,(void*)0,0); 

	printf("Write Data : "); 
    //your first truly unsafe c function
	fgets(str, 100, stdin); 
    
	printf("Data written in memory: %s\n",str); 
	
	//detach from shared memory 
	shmdt(str); 

	return 0; 
} 
