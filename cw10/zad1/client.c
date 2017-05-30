/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <unistd.h>

void handlerError(char * message){
    printf(message);
    exit(1);
}

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
        handlerError("Could not create socket");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = INADDR_LOOPBACK;

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
        handlerError("connect failed. Error");


    puts("Connected\n");

    //keep communicating with server
    while(1)
    {
        printf("Message : ");
        scanf("%s" , message);

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
            handlerError("Send failed");

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
            handlerError("recv failed");

    }

    close(sock);
    return 0;
}
