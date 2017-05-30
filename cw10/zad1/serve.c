
#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

void handlerError(char * message){
    printf(message);
    exit(1);
}

int main(int argc , char *argv[])
{
    int clientSocket[10];
    int i =0;
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
        handlerError("Could not create socket");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = INADDR_LOOPBACK;

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
		handlerError("bind failed. Error");

    printf("Socet created, waiting for clients.\n");

	//Listen
	listen(socket_desc , 100);

	//Accept and incoming connection
while(1){

	c = sizeof(struct sockaddr_in);
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	for ( int j=0; j<i; i++){
        if(clientSocket[j] == client_sock)
            write(client_sock , "You are connected" , strlen("You are connected"));
        }
    clientSocket[i] = client_sock;

	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");

	//Receive a message from client
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
	{
		//Send the message back to client
		write(client_sock , client_message , strlen(client_message));
	}
}

	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	return 0;
}
