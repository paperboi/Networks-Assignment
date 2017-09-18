#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define PORT 49153

int main()
{
  FILE *fp;
  struct sockaddr_in server_addr,client_addr;
  int sock_fd;
  socklen_t client_len;
  char buffer1[100],buffer2[100],a[100];
 
  if ((sock_fd=socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("\nsocket() failed");
    exit(1);
  }

  server.sin_family=AF_INET;
  server.sin_port=PORT;
  server.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  if (bind(s,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
  {
    perror("bind() failed\n");
    exit(1);
  }
  
  client_len=sizeof(client_addr);
  
  while(1)
  {
    strcpy(buffer2,"");
    fp=fopen("dns.txt","r");
    recvfrom(sock_fd,buffer1,sizeof(buffer1), 0,(struct sockaddr *)&client_addr,&client_len);
    while(!feof(fp))
    {
      fscanf(fp,"%s",a);
      if(strcmp(a,buffer1)==0)
      {
            fscanf(fp,"%s",buffer2);
            break;
      }
    }
    if(strcmp(buffer2,"")==0)
      strcpy(buffer2,"Not found...");
    sendto(sock_fd,buffer2,sizeof(buffer2),0,(struct sockaddr *)&client_addr,client_len);  
  }
  return 0;
}