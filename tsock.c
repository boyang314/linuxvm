#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>


int main() {

    //int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4567);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (-1 == connect(sockfd, (const struct sockaddr*)&addr, sizeof(addr))) {
        perror("connect");
        return -1;
    }

    char i_buf[80];
    char o_buf[] = "hellow world!";
    ssize_t olen = send(sockfd, o_buf, sizeof(o_buf), 0);
    ssize_t ilen = recv(sockfd, i_buf, sizeof(i_buf), 0);
    printf("%s\n", i_buf);


    return 0;

}

