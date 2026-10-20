// TCPdaytime.c - TCP client for DAYTIME service

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define  LINELEN    128
#define       MSG             "La horita por favor\n"
extern int  errno;

int  TCPdaytime(const char *host, const char *service);
int  errexit(const char *format, ...);
int  connectTCP(const char *host, const char *service);

int
main(int argc, char *argv[]) {
  char  *host = "localhost";  /* host to use if none supplied  */
  char  *service = "daytime";  /* default service port    */
  char  buf[LINELEN+1];    /* buffer for one line of text  */
  int  s, n;      /* socket, read count    */

  switch (argc) {
  case 1:
    host = "localhost";
    break;
  case 3:
    service = argv[2];
    /* FALL THROUGH */
  case 2:
    host = argv[1];
    break;
  default:
    fprintf(stderr, "USO: %s [host [port]]\n", argv[0]);
    exit(1);
  }
  s = connectTCP(host, service);
  write (s, MSG, strlen(MSG));
  while( (n = read(s, buf, LINELEN)) > 0) {
    buf[n] = '\0';    /* ensure null-terminated  */
    (void) fputs( buf, stdout );
  }
  exit(0);
}
