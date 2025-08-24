#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void err(const char *msg) {
	fprintf(stderr, "%s", msg);
	exit(1);
}

const char *req = "GET / HTTP/1.1\r\nHost: ifconfig.me\r\nUser-Agent: curl\r\n\r\n";

int main() {
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	struct hostent *host = gethostbyname("ifconfig.me");
	if (host == NULL) return 1;
	memcpy(&addr.sin_addr.s_addr, host->h_addr, host->h_length);
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) return 1;
	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) return 1;
	if (send(fd, req, strlen(req), 0) == -1) return 1;
	char buf[1024];
	recv(fd, buf, sizeof(buf)-1, 0);
	close(fd);
	char *ip = strstr(buf, "\r\n\r\n")+4;
	printf("%s\n", ip);
}

