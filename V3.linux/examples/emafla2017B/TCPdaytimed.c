// TCPdaytimed.c -  main - Iterative TCP server for DAYTIME service

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define QLEN  32
extern int  errno;
int    errexit(const char *format, ...);
void    TCPdaytimed(int fd);
int    passiveTCP(const char *service, int qlen);
char  *ctime();

int
main(int argc, char *argv[]) {
  struct  sockaddr_in fsin;  /* the from address of a client  */
  char  *service = "daytime";  /* service name or port number  */
  int  msock, ssock;    /* master & slave sockets  */
  unsigned int  alen;    /* from-address length    */
  char  *pts;      /* pointer to time string  */
  time_t  now;      /* current time      */

  switch (argc) {
  case  1:
    break;
  case  2:
    service = argv[1];
    break;
  default:
    errexit("USO: %s [port]\n", argv[0]);
  }

  msock = passiveTCP(service, QLEN);

  while (1) {
    alen = sizeof(fsin);
    if ((ssock = accept(msock, (struct sockaddr *)&fsin, &alen)) < 0)
      errexit("accept failed: %s\n", strerror(errno));
  printf ("ssock: %d\n", ssock);

    (void) time(&now);
    pts = ctime(&now);
    (void) write(ssock, pts, strlen(pts));
    (void) close(ssock);
  }
}
