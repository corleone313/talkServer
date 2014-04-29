#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 6000

int main(int argc, char **argv){
	int sfp, nfp;
	struct sockaddr_in saddr, caddr;
	int sin_size;
	printf("talk server.....\n");

	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfp){
		printf("socket failed\n");
		return -1;
	}
	bzero(&saddr, sizeof(struct sockaddr_in));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(PORT);
	if(-1 == bind(sfp, (struct sockaddr *)(&saddr), sizeof(struct sockaddr))){
		printf("bind failed\n");
		return -1;
	}
	if(-1 == listen(sfp, 100)){
		printf("listen failed \n");
		return -1;
	}
	sin_size = sizeof(struct sockaddr_in);
	while(1){
		nfp = accept(sfp, (struct sockaddr *)(&caddr), &sin_size);
		if(-1 == nfp){
			printf("accept failed\n");
			return -1;
		}
		printf("accept connect from \r %#x : %#x \r\n", ntohl(caddr.sin_addr.s_addr),
				ntohs(caddr.sin_port));
	}
	return 0;
}
