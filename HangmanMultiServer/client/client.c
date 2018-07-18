#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    printf("Welcome Client\n");

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(8088);

    //TO Set ip address
    inet_pton(AF_INET,"localhost",&(servaddr.sin_addr));

    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    while(1)
    {
        bzero( sendline, 100);
        bzero( recvline, 100);

        read(sockfd,recvline,100);
        printf("[SERVER] %s\n",recvline);

        if(recvline[0] == '-'){
            break;
        }

        if(strcmp(recvline,"Waiting for another player.\n") != 0){
            if(strcmp(recvline,"GAME START\n") == 0){
                printf("Wait your turn...\n");
            }else{
                if(strcmp(recvline,"Good job ! :)\n") != 0 && strcmp(recvline,"Bad choice ! :(\n") != 0) {
                    fgets(sendline,100,stdin);
                    write(sockfd,sendline,strlen(sendline)+1);
                }else{
                    printf("Wait your turn...\n");
                }
            }
        }
    }
}
