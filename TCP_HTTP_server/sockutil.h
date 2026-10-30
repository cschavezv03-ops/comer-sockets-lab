/* sockutil.h - prototipos de las funciones auxiliares de sockets */

#ifndef SOCKUTIL_H
#define SOCKUTIL_H

/* imprime el mensaje en stderr y termina el proceso con codigo 1 */
void errexit(const char *format, ...)
	__attribute__((noreturn, format(printf, 1, 2)));

/* cliente: crea un socket y lo conecta a host:service ("tcp" o "udp") */
int connectsock(const char *host, const char *service, const char *transport);
int connectTCP(const char *host, const char *service);
int connectUDP(const char *host, const char *service);

/* servidor: crea un socket enlazado a service ("tcp" o "udp") */
int passivesock(const char *service, const char *transport, int qlen);
int passiveTCP(const char *service, int qlen);
int passiveUDP(const char *service);

#endif /* SOCKUTIL_H */
