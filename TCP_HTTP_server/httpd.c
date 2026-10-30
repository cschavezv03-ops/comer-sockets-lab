#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "sockutil.h"

int main(int argc, char *argv[]){
    int sd;
    int nsd;
    int fd;
    int nread;
    ssize_t status;
    char buf[4096];
    char fname[4096];

    struct sockaddr_in cltAddr;

    sd = passiveTCP("http", 5);
    while(1){
        nsd = accept(sd, (struct sockaddr *)&cltAddr, NULL);
        status = read(nsd, buf, sizeof(buf));
        //fname PARSING
        fd = open(fname, O_RDONLY);
        while(nread = read(fd, buf, sizeof(buf))){
            write(nsd, buf, nread);
        }
        close(fd);
    }
    close(nsd);
}