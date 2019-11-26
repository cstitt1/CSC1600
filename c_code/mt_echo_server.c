 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <netdb.h>
 #include <pthread.h>

 void* echo(void* arg)
 {
     
     int *p =(int *) arg;
     int comm_fd = *p;
     char string_from_client[100];
    /*use memset to 0 out the string that reads from the socket */
 	memset(string_from_client,0,strlen(string_from_client));
    //read data from the socket
    read(comm_fd,string_from_client,100);
 	
        //write back to the client
    write(comm_fd, string_from_client, strlen(string_from_client)+1); 

 }

 int main(int argc, char const *argv[])
 {   
    pthread_t tid; 
    int listen_fd;
    int* comm_fd;    
    /*this is a data structure that holds the server information */
    struct sockaddr_in servaddr;
 
    /*create a socket to listen on */
    //AF_NET is the network protocol IPV4
    //SOCK_STREAM stands for TCP - reliable connection
    //0 is IP or Internet protocol
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) 
        printf("ERROR opening socket");

    /*set the socket option to release the port when server is killed */
    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

    /*memset zeros out the memory allocated by malloc
    *You should use memset before sending or receiving anything
    *over the network*/
   /*We must bind our socket to a server at an ip address and port
   *we define the ip adderss and port in the data structure sockaddr_in
   */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY); //stands for localhost
    servaddr.sin_port = htons(22000); //htons converts int to value bytes understood by network
    
    //bind the server:port to the socket
    if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        printf("error binding");
    }
    
    //listen on this socket
    if (listen(listen_fd, 10) < 0) {
        printf("error listening");
    } 

    /*The server will run forever */
    while(1) {
        /*accept connections from clients. Once a connection is accepted,
        *create a new socket to communicate with the client */
       comm_fd = malloc(sizeof(int));
       *comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        if(comm_fd < 0) {
            printf("error accepting");
        }

        pthread_create(&tid,NULL,echo,comm_fd);
        
    }     
}