/* passiveTCP.c - passiveTCP */

#include "sockutil.h"

/*------------------------------------------------------------------------
 * passiveTCP - create a passive socket for use in a TCP server
 *------------------------------------------------------------------------
 */
int
passiveTCP(const char *service, int qlen)
{
	return passivesock(service, "tcp", qlen);
}
