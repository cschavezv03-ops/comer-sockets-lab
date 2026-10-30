#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Error. Expected: ./client <IP> <PORT>\n");
        return 1;
    }

    printf("SERVER IP: %s\n", argv[1]);
    printf("PORT: %s\n", argv[2]);

    struct addrinfo hints, *res, *p;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(argv[1], argv[2], &hints, &res);

    if(status != 0){
        printf("Error. %s\n", gai_strerror(status));
        return 1;
    }

    printf("Status: %d\n", status);

    freeaddrinfo(res);

    return 0;
}