#include <stdio.h>
#include <stdlib.h>
#include "pingManager.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MTU 1400

struct icmp_echo
{
	unsigned char type;
	unsigned char code;
	unsigned short checksum;
	unsigned short identifier;
	unsigned short sequence;
	char data[MTU];
};


int ft_ping(char *adress)
{
	struct addrinfo *res;
	struct sockaddr_in addr_in;
	int error;
	int server_fd;
	const int val=255;
	// struct icmp_echo* icmp = malloc(sizeof(struct icmp_echo));

	char *packet;
	packet = malloc(80*sizeof(char));
	char *response = malloc(80*sizeof(char));

	error = getaddrinfo(adress, NULL, NULL, &res);
	if (error != 0)
	{
		printf("we got an error getting adress info!\n");
		return (-1);
	}
	server_fd = socket(res->ai_family,SOCK_RAW,1);
	if (server_fd == -1)
	{
		perror("socket");
		printf("we got an error while establishing the socket!\n");
		return (-1);
	}
	if (setsockopt(server_fd, SOL_SOCKET, IP_TTL, &val, sizeof(val)) != 0)
	{
		perror("Set TTL option");
		return -1;
	}

	printf("adress:%s\n", adress);
	addr_in.sin_family = AF_INET;
	sendto(server_fd, response, sizeof(response), 0, (struct sockaddr *)&addr_in, sizeof(addr_in));
	perror("sendto");
	if (recvfrom(server_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&res->ai_addr, &res->ai_addrlen) > 0 )
	{

		printf("***Got message!***\n");
	}
	perror("recvfrom");
	printf("message:%s", packet);

	return 0;
}

unsigned short calcsum(unsigned short *buffer, int length)
{
	unsigned long sum; 	

	for (sum=0; length>1; length-=2) 
		sum += *buffer++;

	if (length==1)
		sum += (char)*buffer;

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ~sum;
}