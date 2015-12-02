#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/signal.h>
#include <string.h>

#define DEFDATALEN      56
#define MAXIPLEN        60
#define MAXICMPLEN      76

static char *hostname = NULL;

static unsigned short calcsum(unsigned short *buffer, int length)
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

static void noresp(int ign)
{
	printf("No response from %s\n", hostname);
	exit(0);
}

static void ping(char *host)
{
	struct addrinfo *addrinfo;
	struct sockaddr_in pingaddr;
	struct icmp *pkt;
	int pingsock, c;
	char packet[DEFDATALEN + MAXIPLEN + MAXICMPLEN];

	if ((pingsock = socket(AF_INET, SOCK_RAW, 1)) < 0)
	{
		perror("ping: creating a raw socket");
		return ;
	}

	// memset(&pingaddr, 0, sizeof(struct sockaddr_in));
	// pingaddr.sin_family = AF_INET;

	if (getaddrinfo(host, NULL, NULL, &addrinfo) != 0)
	{
		printf("we got an error getting adress info!\n");
		return ;
	}

	pkt = (struct icmp *) packet;
	memset(pkt, 0, sizeof(packet));
	pkt->icmp_type = ICMP_ECHO;
	pkt->icmp_cksum = calcsum((unsigned short *) pkt, sizeof(packet));

	c = sendto(pingsock, packet, sizeof(packet), 0, addrinfo->ai_addr, addrinfo->ai_addrlen);

	if (c < 0 || c != sizeof(packet)) {
		if (c < 0)
			perror("ping: sendto");
		fprintf(stderr, "ping: write incomplete\n");
    		return ;
	}

	struct sockaddr_in from;
	socklen_t fromlen = sizeof(from);
	if ((c = recvfrom(pingsock, packet, sizeof(packet), 0,(struct sockaddr *) &from, &fromlen)) < 0)
	{
		 perror("ping: recvfrom");
	}
	if (c >= 76)
	{
		struct iphdr *iphdr = (struct iphdr *) packet;
		char *saddr = malloc(24 * sizeof(char));
		char *daddr = malloc(24 * sizeof(char));
		inet_ntop(AF_INET, &(iphdr->saddr), saddr, 24 * sizeof(char));
		inet_ntop(AF_INET, &(iphdr->daddr), daddr, 24 * sizeof(char));
		printf("TTL:%d from:%s to destination:%s\n", iphdr->ttl, saddr, daddr);
	}

	printf("%s is alive!\n", hostname);
	return;
}

int main (int ac, char**av)
{
	hostname = av[1];
	ping(av[1]);
	return 0;
}
