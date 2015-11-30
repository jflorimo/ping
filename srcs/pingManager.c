#include "pingManager.h"
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

/*
 * IP_HEADER prototype
 */
struct ip_header
{
	unsigned int	hl:4;		/* 4 bit header length */
	unsigned int	ver:4;		/* 4 bit version */
	unsigned char	tos;		/* type of service */
	unsigned short  totl;		/* total length of datagram */
	unsigned short	id;		/* identifier */
	unsigned short 	notused;	/* this is were flags and fragment offset would go */
	unsigned char 	ttl;		/* time to live */
	unsigned char	prot;		/* protocol */
	unsigned short	csum;		/* our checksum */
	unsigned long 	saddr;		/* source address */
	unsigned long 	daddr;		/* destination address */
};


// void displayPing(void* elem)
// {
// 	struct ipheader* ipheader = (struct ipheader*)elem;
// 	char *saddr;
// 	//char *daddr;

// 	inet_ntop(AF_INET, &(ipheader->saddr), saddr, 24 * sizeof(char));

// 	printf("TTL:%d from:\n", ipheader->ttl);
// }

// typedef struct addrinfo addrinfo;

t_data *initConnexion(char *adress)
{
	int error;
	const int val=255;
	t_data *data = malloc(sizeof(t_data));

	data->adress = adress;
	error = getaddrinfo(data->adress, NULL, NULL, &(data->addrinfo));
	if (error != 0)
	{
		printf("we got an error getting adress info!\n");
		return NULL;
	}
	data->server_fd = socket(AF_INET,SOCK_RAW,1);
	if (data->server_fd == -1)
	{
		perror("socket");
		printf("we got an error while establishing the socket!\n");
		return NULL;
	}
	if (setsockopt(data->server_fd, SOL_SOCKET, IP_TTL, &val, sizeof(val)) != 0)
	{
		perror("Set TTL option");
		return NULL;
	}
	data->packet = malloc(sizeof(struct ip_header) + sizeof(struct icmp_echo) );
	data->ipheader = (struct ip_header*)data->packet;
	data->icmp = (struct icmp_echo*)(data->packet+sizeof(struct ip_header));

	return data;
}

int ft_ping(char *adress)
{
	int error;
	const int val=255;
	struct addrinfo		*addrinfo;
	struct sockaddr_in	addr_in;

	error = getaddrinfo(adress, NULL, NULL, &addrinfo);
	if (error != 0)
	{
		printf("we got an error getting adress info!\n");
		return -1;
	}
	int server_fd = socket(AF_INET,SOCK_RAW,1);
	if (server_fd == -1)
	{
		perror("socket");
		printf("we got an error while establishing the socket!\n");
		return -1;
	}
	if (setsockopt(server_fd, SOL_SOCKET, IP_TTL, &val, sizeof(val)) != 0)
	{
		perror("Set TTL option");
		return -1;
	}

	char *response = malloc(68*sizeof(char));
	int i = 0;
	while (++i < 68)
		response[i] = 'A';
	response[67] = 0;

	printf("adress:%s - fd:%d\n", adress, server_fd);
	addr_in.sin_family = AF_INET;
	sendto(server_fd, response, sizeof(response), 0, (struct sockaddr *)&(addr_in), sizeof(addr_in));
	//sendto(d->server_fd, response, sizeof(response), 0, d->addrinfo->ai_addr, d->addrinfo->ai_addrlen);
	perror("sendto");

	// while(1)
	// {
		
	// 	if (recvfrom(server_fd,packet,sizeof(struct ip_header)+sizeof(struct icmp_echo),0, (struct sockaddr *)&res->ai_addr, &res->ai_addrlen) == -1)
	// 	{
			
	// 		fprintf(stderr, "Failed to receive packets\n");
	// 		free(packet);
	// 		exit(-1);
	// 	}
		
		
	// 	displayPing(ipheader);
	// 	//printf("id: %x\n", ntohs(ipheader->id) );

	// 	if( ntohs(ipheader->id) == 0x1337)
	// 	{
	// 		printf("%s", icmp->data);
	// 	}

	// 	/* if identifier is 0x2600 that means we're done */
	// 	if (ipheader->id == 0x2600)
	// 	{
	// 		free(packet);
	// 		exit(-1);
	// 	}
	// }


	/*
	if (recvfrom(server_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&res->ai_addr, &res->ai_addrlen) > 0 )
	{
		printf("***Got message!***\n");
	}
	perror("recvfrom");
	printf("message:%s", packet);
	*/



	return 0;
}



// unsigned short calcsum(unsigned short *buffer, int length)
// {
// 	unsigned long sum; 	

// 	for (sum=0; length>1; length-=2) 
// 		sum += *buffer++;

// 	if (length==1)
// 		sum += (char)*buffer;

// 	sum = (sum >> 16) + (sum & 0xFFFF);
// 	sum += (sum >> 16);
// 	return ~sum;
// }