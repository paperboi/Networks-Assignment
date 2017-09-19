#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 3000

int main(int argc, char const *argv[])
{
    struct sockaddr_in server_addr,client_addr;
    int sock_fd, server_len;
    char buffer1[100],buffer2[100];

    sock_fd=socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=PORT;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    server_len=sizeof(server_addr);
    
    printf("\nEnter the url: ");
    scanf("%s", buffer2);
    sendto(sock_fd, buffer2, sizeof(buffer2), 0,(struct sockaddr *)&server_addr, server_len);
    recvfrom(sock_fd, buffer1,sizeof(buffer1), 0, NULL, NULL);
    printf("%s \n",buffer1);
    return 0;
}
