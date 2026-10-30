/* connectsock.c - connectsock */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "sockutil.h"

/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int
connectsock(const char *host, const char *service, const char *transport)
/*
 * Arguments:
 *      host      - name of host to which connection is desired
 *      service   - service name (/etc/services) or port number
 *      transport - name of transport protocol to use ("tcp" or "udp")
 */
{
	struct addrinfo	hints, *res, *ai;
	int	s = -1, err, saved = 0;

	/* getaddrinfo replaces getservbyname/gethostbyname/getprotobyname:
	 * it resolves name, service and protocol in one call (IPv4 only,
	 * the servers use struct sockaddr_in) */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = (strcmp(transport, "udp") == 0) ? SOCK_DGRAM
							    : SOCK_STREAM;

	err = getaddrinfo(host, service, &hints, &res);
	if (err != 0)
		errexit("can't resolve %s.%s: %s\n", host, service,
			gai_strerror(err));

	/* try each address until one connects */
	for (ai = res; ai != NULL; ai = ai->ai_next) {
		s = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (s < 0) {
			saved = errno;
			continue;
		}
		if (connect(s, ai->ai_addr, ai->ai_addrlen) == 0)
			break;
		saved = errno;
		close(s);
		s = -1;
	}
	freeaddrinfo(res);

	if (s < 0)
		errexit("can't connect to %s.%s: %s\n", host, service,
			strerror(saved));
	return s;
}
