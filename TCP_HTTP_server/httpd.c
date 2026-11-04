#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "sockutil.h"
#include <unistd.h>


int main(int argc, char *argv[]){
    int sd;
    int nsd;
    int fd;
    int nread;
    ssize_t status;
    char buf[4096];
    char fname[] = "index.html";

    struct sockaddr_in cltAddr;

    sd = passiveTCP("http", 5);
    while(1){
        socklen_t cltLen = sizeof(cltAddr);
        nsd = accept(sd, (struct sockaddr *)&cltAddr, &cltLen);
        if(nsd == -1){
            perror("accept");
            continue;
        }
        
        status = read(nsd, buf, sizeof(buf)-1);

        if(status == -1){
            perror("read");
            close(nsd);
            continue;
        }
        //fname PARSING     
        fd = open(fname, O_RDONLY);
        while(nread = read(fd, buf, sizeof(buf)) > 0){
            write(nsd, buf, nread);
        }
        close(fd);
    }
    close(nsd);
}