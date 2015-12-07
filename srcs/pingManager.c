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
	struct sockaddr_in addr;
	struct sockaddr_in from;
	struct packet pkt;
	struct iphdr *ip;
	struct icmphdr *icmp;
	int pingsock, c;

	if ((pingsock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		perror("ping: creating a raw socket");
		return ;
	}
	// const int	val = 64;
	// if (setsockopt(pingsock, SOL_IP, IP_TTL, &val, sizeof(val)) != 0)
	// {
	// 	perror("setsockopt:");
	// 	printf("Error with setsockopt\n");
	// 	return ;
	// }
	if (getaddrinfo(host, NULL, NULL, &addrinfo) != 0)
	{
		printf("we got an error getting adress info!\n");
		return ;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = addrinfo->ai_family;
	addr.sin_port = 0;
	addr.sin_addr.s_addr = ((struct sockaddr_in*)(addrinfo->ai_addr))->sin_addr.s_addr;

	int seq = 0;
	while (0x2a)
	{

		memset(&pkt, 0, sizeof(pkt));
		pkt.hdr.type = ICMP_ECHO;
		pkt.hdr.un.echo.id = getpid();
		int i = 0;
		for ( i = 0; i < sizeof(pkt.msg) - 1; i++ )
			pkt.msg[i] = i + '0';
		pkt.msg[i] = 0;
		pkt.hdr.un.echo.sequence = seq;// sequence
		pkt.hdr.checksum = calcsum((short unsigned int *)&pkt, sizeof(pkt));

		c = sendto(pingsock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&addr, sizeof(addr));
		if (c < 0 || c != sizeof(pkt)) {
			if (c < 0)
				perror("ping: sendto");
			fprintf(stderr, "ping: write incomplete\n");
	    	return ;
		}

		memset(&from, 0, sizeof(from));
		socklen_t fromlen = sizeof(from);
		if ((c = recvfrom(pingsock, &pkt, sizeof(pkt), 0,(struct sockaddr *) &from, &fromlen)) < 0)
		{
			 perror("ping: recvfrom");
		}
		if (c >= PACKETSIZE)
		{
			struct iphdr *iphdr = (struct iphdr *)&pkt;
			char saddr[INET_ADDRSTRLEN];
			char daddr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(iphdr->saddr), saddr, INET_ADDRSTRLEN);
			inet_ntop(AF_INET, &(iphdr->daddr), daddr, INET_ADDRSTRLEN);
			//56 bytes from 216.58.208.238: icmp_seq=0 ttl=61 time=9.695 ms
			printf("%d bytes from %s: icmp_seq=%d, ttl=%d time=0000 ms\n", c, saddr, seq, iphdr->ttl);
			//printf("TTL:%d size:%d, seq=%d from:%s to destination:%s\n", iphdr->ttl, c, seq, saddr, daddr);
		}
		seq++;
		sleep(1);
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
