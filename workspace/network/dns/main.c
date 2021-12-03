
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "dns.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)                   sizeof(a)/sizeof(a[0])
#endif

void http_get_ip_addr(const char *dns_server, const char *domain, char *ip_addr)
{
    int32_t i;
    struct hostent *host = NULL;

    if (dns_server) {
		host = (struct hostent *)my_gethostbyname_with_dns_server(dns_server, domain);
	} else {
		host = (struct hostent *)my_gethostbyname(domain);
	}

    for (i = 0; host->h_addr_list[i]; i++) {
        strcpy(ip_addr, inet_ntoa( * (struct in_addr*) host->h_addr_list[i]));
        break;
    }
}

int main(int argc, const char *argv[])
{
	const char *dns_server_list[] = 
	{
		"",
		"8.8.8.8",
		"114.114.114.114",
	};
	const char *domain_list[] = 
	{
		"www.baidu.com",
		"www.hao123.com",
	};
	const char *dns_server = NULL;
	char ip_addr[128] = {0};
	int i, j;

	for (i = 0; i < ARRAY_SIZE(domain_list); i++) {		
		for (j = 0; j < ARRAY_SIZE(dns_server_list); j++) {
			if (!strlen(dns_server_list[j])) {
				dns_server = NULL;
			} else {
				dns_server = dns_server_list[j];
			}
			memset(ip_addr, 0, sizeof(ip_addr));
			http_get_ip_addr(dns_server, domain_list[i], ip_addr);
			printf("DNS resolve %-32s by %-32s => %-32s\n", \
				domain_list[i], dns_server ? dns_server : "default", ip_addr);
		}
	}

	return 0;
}