#include	"header.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	socklen_t			len;
	struct sockaddr_in	servaddr,cliaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		printf("socket error ,errno:%d\n",errno);
		perror("opendir: ");  
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(10000);	/* daytime server */

	if(bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
	{
		printf("bind error ,errno:%d\n",errno);
		perror("opendir: ");  
		exit(1);
	}

	if(listen(listenfd, LISTENQ) < 0)
	{
		printf("listen error ,errno:%d\n",errno);
		exit(1);
	}

	for ( ; ; ) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *) &cliaddr, &len);
		if(connfd < 0)
		{
			printf("accept error ,errno:%d\n",errno);
			exit(1);
		}
		printf("connection from %s, port %d\n",
			   inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
			   ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        strftime(buff,sizeof(buff),"%Y-%m-%d %H:%M:%S \r\n",localtime(&ticks));
        //snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

		close(connfd);
	}
}
