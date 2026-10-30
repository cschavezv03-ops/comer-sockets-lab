/* connectTCP.c - connectTCP */

#include "sockutil.h"

/*------------------------------------------------------------------------
 * connectTCP - connect to a specified TCP service on a specified host
 *------------------------------------------------------------------------
 */
int
connectTCP(const char *host, const char *service)
{
	return connectsock(host, service, "tcp");
}
