#include "header.h"

int
main(int argc, char **argv)
{
    int					sockfd, n;
    char				recvline[MAXLINE + 1];
    struct sockaddr_in	servaddr;

    if (argc != 2)
    {
        printf("usage: a.out <IPaddress>");
        exit(1);
    }


    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(10000);	/* daytime server */
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s", argv[1]);
        exit(1);
    }
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error for %s", argv[1]);
        exit(1);
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;	/* null terminate */
        if (fputs(recvline, stdout) == EOF)
        {
            printf("fputs error for %s", argv[1]);   
            exit(1);
        }

    }
    if (n < 0)
    {
        printf("read error");
        exit(1);
    }

    exit(0);
}