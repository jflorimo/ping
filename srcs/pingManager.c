#include "pingManager.h"
#include <libft.h>
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
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>


#define PACKETSIZE	56

struct packet
{
	struct icmphdr hdr;
	char msg[PACKETSIZE-sizeof(struct icmphdr)];
};


struct Bigdata
{
	float min;
	float max;
	float average;
	float stddev;
	int number;
};

static char *hostname = NULL;
static int count = 0;
static int received = 0;
static struct Bigdata data = {0, 0, 0, 0, 0};
static t_list *elements = NULL;

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
static void displayStatistic()
{
	printf("--- %s ping statistics ---\n", hostname);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", count, received, 100-((received*100)/count));

	// float stddev = 0;
	float average = data.average/(float)data.number;
	// while (elements->next != NULL)
	// {
	// 	stddev += ((float)(elements->content) * (float)(elements->content))
	// }

	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", data.min, average, data.max, 1.1);
}

static void intHandler(int dummy) {
	(void)dummy;
    displayStatistic();
    exit(1);
}

int ping(char *host)
{
	struct timeval stop, start;
	struct addrinfo *addrinfo;
	struct sockaddr_in addr;
	struct sockaddr_in from;
	struct packet pkt;
	int pingsock, c;
	hostname = host;
	signal(SIGINT, intHandler);
	if ((pingsock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		perror("ping: creating a raw socket");
		return -1;
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
		printf("ping: unknown host\n");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = addrinfo->ai_family;
	addr.sin_port = 0;
	addr.sin_addr.s_addr = ((struct sockaddr_in*)(addrinfo->ai_addr))->sin_addr.s_addr;
	char adress[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr.sin_addr.s_addr), adress, INET_ADDRSTRLEN);
	//PING google.com (216.58.208.238): 48 data bytes
	printf("PING %s (%s): %d data bytes\n", host, adress, (int)(PACKETSIZE-sizeof(struct icmphdr)));
	int seq = 0;
	while (0x2A)
	{
		gettimeofday(&start, NULL);
		memset(&pkt, 0, sizeof(pkt));
		pkt.hdr.type = ICMP_ECHO;
		pkt.hdr.un.echo.id = getpid();
		int i = 0;
		for ( i = 0; i < (int)sizeof(pkt.msg) - 1; i++ )
			pkt.msg[i] = i + '0';
		pkt.msg[i] = 0;
		pkt.hdr.un.echo.sequence = seq;// sequence
		pkt.hdr.checksum = calcsum((short unsigned int *)&pkt, sizeof(pkt));

		c = sendto(pingsock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&addr, sizeof(addr));
		count++;
		if (c < 0 || c != sizeof(pkt)) {
			if (c < 0)
				perror("ping: sendto");
			fprintf(stderr, "ping: write incomplete\n");
	    	return -1;
		}

		memset(&from, 0, sizeof(from));
		socklen_t fromlen = sizeof(from);
		if ((c = recvfrom(pingsock, &pkt, sizeof(pkt), 0,(struct sockaddr *) &from, &fromlen)) < 0)
		{
			 perror("ping: recvfrom");
		}
		if (c >= PACKETSIZE)
		{
			received++;
			struct iphdr *iphdr = (struct iphdr *)&pkt;
			char saddr[INET_ADDRSTRLEN];
			char daddr[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &(iphdr->saddr), saddr, INET_ADDRSTRLEN);
			inet_ntop(AF_INET, &(iphdr->daddr), daddr, INET_ADDRSTRLEN);
			gettimeofday(&stop, NULL);
			float timeElapsed = (float)((float)stop.tv_usec - (float)start.tv_usec)/1000;
			data.number++;
			if (data.number == 1)
			{
					data.min = timeElapsed;
					data.max = timeElapsed;
			}
			else
			{
				if (timeElapsed < data.min)
					data.min = timeElapsed;
				if (timeElapsed > data.max)
					data.max = timeElapsed;
				data.average += timeElapsed;
			}
			if (elements == NULL)
				elements = ft_lstnew((void *)&timeElapsed, sizeof(float));
			else
				ft_lstadd(&elements, ft_lstnew((void *)&timeElapsed, sizeof(float)));
			printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", c, saddr, seq, iphdr->ttl, timeElapsed);
		}
		seq++;
		sleep(1);
	}
	
	return 0;
}

