#ifndef PINGMANAGER_H
# define PINGMANAGER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct			s_data
{
	char				*adress;
	struct addrinfo		*addrinfo;
	int					server_fd;
	struct sockaddr_in	addr_in;
	struct icmp_echo	*icmp;
	struct ip_header	*ipheader;
	char				*packet;
	char 				*response;
}						t_data;

int ft_ping(char *adress);
t_data *initConnexion(char *adress);

#endif