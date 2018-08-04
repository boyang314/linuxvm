#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>


int main() {

    //int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567);
    addr.sin_addr.s_addr = inet_addr("225.2.0.1");

    char o_buf[] = "hellow world!\n";
    while(1) {
        ssize_t olen = sendto(sockfd, o_buf, sizeof(o_buf), 0, (struct sockaddr*)&addr, sizeof(addr));
        sleep(1);
    }

    return 0;
}

