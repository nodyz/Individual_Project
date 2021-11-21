#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>

#define SVR_PORT 43454   //port for TCP/UDP protocol
#define CLI_PORT 43455   //port for TCP/UDP protocol
#define IP_STR "127.0.0.1"  //loopback address
 

int main(int argc, char *argv[])
{
  int sockd;
  int num = 1;
  struct sockaddr_in server;
  struct sockaddr_in client;
  time_t startTime, rtt, currentTime;
  socklen_t add_length;


  //create socket

  if ((sockd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
  {

    printf("Could not create socket!\n");
    
  }


  //prepare sockaddr_in structure

   memset((char *)&server, 0, sizeof(server));
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = inet_addr(IP_STR);
   server.sin_port = htons(SVR_PORT);

   memset((char *)&client, 0, sizeof(client));
   client.sin_family = AF_INET;
   client.sin_addr.s_addr = inet_addr(IP_STR);
   client.sin_port = htons(CLI_PORT);


  //bind

   if((bind(sockd,(struct sockaddr *)&client,sizeof(client)))!=0)
   {

       printf("Cannot bind bind socket!");
       
   }


   printf("Client is running at %s:%d\n", IP_STR, CLI_PORT);
   startTime = time(NULL);


  //sendto

   sendto(sockd, &num, sizeof(num), 0,(struct sockaddr *)&server, sizeof(server));
   add_length = sizeof(client);



  //receivefrom

   recvfrom(sockd, &currentTime, sizeof(currentTime), 0, (struct sockaddr *)&client, &add_length);
   rtt = time(NULL) - startTime;
   currentTime += rtt / 2;



   return 0;

}
