#ifndef __HEADER_H__
#define __HEADER_H__

#include	<sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include	<stdio.h>
#include	<stdlib.h>
#include <zconf.h>
#include <errno.h>
#define SA  struct sockaddr

#define	MAXLINE		4096	/* max text line length */
/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

#endif