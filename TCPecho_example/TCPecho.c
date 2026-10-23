#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char *argv[]){
	struct addrinfo hints, *res, *p;
	int fd = -1;
	char m[1024];
	char r[1024];

	if(argc != 3){
		printf("Usage error: %s <server IP> <Port>", argv[0]);
		return 1;
	}

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if(getaddrinfo(argv[1], argv[2], &hints, &res) != 0){
		printf("Solve server error\n");
		return 1;
	}

	for(p = res; p != NULL; p = p->ai_next){
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if(fd < 0){
			continue;
		}

		if(connect(fd, p->ai_addr, p->ai_addrlen) == 0){
			break;
		}

		close(fd);
		fd = -1;
	}

	freeaddrinfo(res);
	if(fd < 0){
		printf("Connection error.\n");
		return 1;
	}

	printf("Connection established.\n");

	while(1){
		printf("Message: ");
		if(fgets(m, sizeof(m), stdin) == NULL){
			break;
		}

		if(strcmp(m, "Exit\n") == 0){
			break;
		}

		size_t len = strlen(m);
		size_t sent = 0;

		while(sent < len){
			ssize_t n = send(fd, m + sent, len - sent, 0);
			if(n <= 0){
				close(fd);
				return 1;
			}

			sent += n;
		}

		ssize_t rec = recv(fd, r, sizeof(r) - 1, 0);

		if(rec <= 0){
			break;
		}

		r[rec] = '\0';
		printf("Echo: %s", r);
	}
	close(fd);
	return 0;
}
