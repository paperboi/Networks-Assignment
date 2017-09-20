// When web server starts,
// 1. It should create a socket - socket()
// 2. Then it should bind the socket to a address - bind()
// 3. Then listen to incoming connections - listen()
// 4. Accept connections - accept()
// 5. Fork()
// 6. Child should read and write. 4,5 and 6 runs forever.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>	

#define PORTNO 8080
#define BACKLOG 10

int main()
{
	//Variable declarations
	int sock_fd, new_sock_fd;	//Socket file descriptors
	struct sockaddr_in client_addr, server_addr;
	socklen_t client_len;	//To store length of client ip address

	pid_t pid;
	int buffer_size=512;
	char *buffer=malloc(buffer_size);

	//Creating a socket
	if ((sock_fd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("\nsocket() failed");
		exit(1);
	}
	else
		printf("\nThe socket was created.");

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORTNO);
	server_addr.sin_addr.s_addr=INADDR_ANY;

	//Binding the socket to the server address
	if (bind(sock_fd,(struct sockaddr *) &server_addr, sizeof(server_addr)) == 0)
		printf("\nBinding the socket");
	fflush(stdout);
	while(1)
	{
		//Listening to incoming connections
		if(listen(sock_fd, BACKLOG) < 0)
		{
			perror("\nlisten() failed");
			exit(1);
		}

		client_len=sizeof(client_addr);

		//Accepting the client connection
		if((new_sock_fd=accept(sock_fd, (struct sockaddr *) &client_addr, &client_len)) < 0)
		{
			perror("\naccept() failed");
			exit(1);
		}
		else
		{
			printf("\nThe client is connected");
		}

		pid=fork();
		if (pid==0)
		{
			close(sock_fd);
			recv(new_sock_fd, buffer, buffer_size, 0);
			printf("\n%s\n", buffer);
			write(new_sock_fd, "Message recieved!\n", 47);
			exit(0);
			close(new_sock_fd);
		}
		else
			close(new_sock_fd);
	}
	close(sock_fd);
	return 0;
}