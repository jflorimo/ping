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

#define PACKETSIZE	56
struct packet
{
	struct icmphdr hdr;
	char msg[PACKETSIZE-sizeof(struct icmphdr)];
};

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
	//struct icmp *pkt;
	int pingsock, c;

	struct iphdr *ip;
	struct icmphdr *icmp;
	char *packet;


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


	//icmphdr
	//http://stackoverflow.com/questions/13620607/creating-ip-network-packets
	/*
	pkt = (struct icmp *) packet;
	memset(pkt, 0, sizeof(packet));
	pkt->icmp_type = ICMP_ECHO;
	pkt->icmp_cksum = calcsum((unsigned short *) pkt, sizeof(packet));
	*/

	/*
	packet = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
	memset(packet, 0, sizeof(packet));
	ip = (struct iphdr*) packet;
	icmp = (struct icmphdr*)(packet + sizeof(strcut icmphdr));
	*/

	struct packet pkt;
	memset(&pkt, 0, sizeof(pkt));
	pkt.hdr.type = ICMP_ECHO;
	pkt.hdr.un.echo.id = getpid();
	int i = 0;
	for ( i = 0; i < sizeof(pkt.msg) - 1; i++ )
		pkt.msg[i] = i + '0';
	pkt.msg[i] = 0;
	pkt.hdr.un.echo.sequence = 1;// cnt ???
	pkt.hdr.checksum = calcsum((short unsigned int *)&pkt, sizeof(pkt));


	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = addrinfo->ai_family;
	addr.sin_port = 0;
	addr.sin_addr.s_addr = ((struct sockaddr_in*)(addrinfo->ai_addr))->sin_addr.s_addr;


	c = sendto(pingsock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&addr, sizeof(addr));

	if (c < 0 || c != sizeof(pkt)) {
		if (c < 0)
			perror("ping: sendto");
		fprintf(stderr, "ping: write incomplete\n");
    	return ;
	}

	struct sockaddr_in from;
	memset(&from, 0, sizeof(from));
	socklen_t fromlen = sizeof(from);
	if ((c = recvfrom(pingsock, &pkt, sizeof(pkt), 0,(struct sockaddr *) &from, &fromlen)) < 0)
	{
		 perror("ping: recvfrom");
	}
	if (c >= PACKETSIZE)
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
