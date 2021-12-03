/**
 * file dns.h
 * Define the DNS request packet header format.
 */

#ifndef __DNS_H__
#define __DNS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <netdb.h>
#include <netinet/in.h>

/* WARN: API non-thread-safe, the same usage as gethostbyname */
extern struct hostent *my_gethostbyname(const char *name);

/* WARN: API non-thread-safe, get ip with fixed dns server */
extern struct hostent *my_gethostbyname_with_dns_server(const char *dns_server, const char *name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DNS_H__ */

