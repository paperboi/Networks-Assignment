#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT        8080        /* port number as an integer */
#define IP_ADDRESS "10.42.0.216"   /* IP address  of the server as a string */

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	//Variable declarations
	int i, sockfd;
	char buffer[BUFSIZE];
    char status_ok[] = "OK";
    char http_not_found[] = "HTTP/1.0 404 Not Found";
    char http_ok[] = "HTTP/1.0 200 OK";
    char location[] = "Location: ";
    char contentType[] = "Content-Type: ";
    int sPos, ePos;
    char *url;
    int portNumber;

    struct sockaddr_in serv_addr;
    
    url = argv[1];
    portNumber = atoi(argv[2]);
	
    if (argc<4)
        printf("\nusage: [url] [port number]");

    if (strstr(url, "http://") != NULL)
        url = url + 7;
    else if (strstr(url, "https://") != NULL)
        url = url + 8;

    if (portNumber > 65536 || portNumber < 0)
    {
        printf("Invalid Port Number!");
        exit(1);
    }

    printf("The client is trying to connect to %s and port %d\n",IP_ADDRESS,PORT);
    if((sockfd = socket(AF_INET, SOCK_STREAM,0)) <0) 
        perror("socket() failed");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    serv_addr.sin_port = htons(PORT);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
    {
    	perror("connect() failed");
    	exit(1);
    }
    write(sockfd, "GET \t", 18);
    while( (i=read(sockfd,buffer,BUFSIZE)) > 0)
        write(1,buffer,i);
    printf("%s\n", buffer);

    return 0;
}
