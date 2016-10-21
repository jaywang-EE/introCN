#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define DEST_IP "140.112.42.161"
#define DEST_PORT 12008
#define SEND_SIZE 1024     // mag recv MAX size
#define RECV_SIZE 1024     // mag recv MAX size
int main() {
   int sockfd;
   socklen_t sin_size;
   char input[SEND_SIZE], rec[RECV_SIZE];
   struct sockaddr_in dest_addr; // will hold the destination addr

   if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) perror("sock"); //error checking
   dest_addr.sin_family = AF_INET; // host byte order
   dest_addr.sin_port = htons(DEST_PORT); // short, network byte order
   dest_addr.sin_addr.s_addr = DEST_PORT;
   memset(&(dest_addr.sin_zero), '\0', 8); // zero the rest of the struct
   // don't forget to error check the connect()!

/*
   sin_size = sizeof(struct sockaddr_in);
   if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) 
   {
      perror("accept");
   }
*/
//   scanf("%s", input);
   while(1)
   {
      inet_pton(AF_INET, DEST_IP, &dest_addr.sin_addr);
      if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) != 0)
         perror("connect ");
      printf("您輸入的是:");
      scanf("%s", input);
      if(send(sockfd, input, sizeof(input), 0) == -1)
         perror("send");
      if(recv(sockfd, rec, sizeof(rec), 0) == -1)
         perror("recieve");
      printf("您接收的是:%s\n", rec);
      close(sockfd);
      if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0) perror("sock");
   }

   return 0;
}
