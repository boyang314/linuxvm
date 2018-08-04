#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char usage[] = "usage: %s -ltu -i ip -p port\n";

void createTcpClient(char *ipaddr, int port) {
    printf("tcp client to %s:%d\n", ipaddr, port);
}

void createTcpServer(char *ipaddr, int port) {
    printf("tcp server to %s:%d\n", ipaddr, port);
}

void createUdpClient(char *ipaddr, int port) {
    printf("udp client to %s:%d\n", ipaddr, port);
}

void createUdpServer(char *ipaddr, int port) {
    printf("udp server to %s:%d\n", ipaddr, port);
}

int main (int argc, char **argv)
{
    typedef enum {CLIENT, SERVER} Mode;
    typedef enum {TCP, UDP} Type;

    Mode mode = CLIENT; //default mode is CLIENT
    Type type = TCP;    //default type is TCP
    char *ipaddr = NULL;
    int port = 0;
    int c;

    while ((c = getopt (argc, argv, "ltui:p:")) != -1)
        switch (c)
        {
            case 'l':
                mode = SERVER;
                break;
            case 't':
                type = TCP;
                break;
            case 'u':
                type = UDP;
                break;
            case 'i':
                ipaddr = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            default:
                printf(usage, argv[0]);
                exit(-1);
        }

    if (optind < argc || NULL == ipaddr || 0 == port) {
        printf(usage, argv[0]);
        exit(-1);
    }
        
    if (CLIENT == mode && TCP == type)
        createTcpClient(ipaddr, port);
    else if (SERVER == mode && TCP == type)
        createTcpServer(ipaddr, port);
    else if (CLIENT == mode && UDP == type)
        createUdpClient(ipaddr, port);
    else if (SERVER == mode && UDP == type)
        createUdpServer(ipaddr, port);
    else {
        printf(usage, argv[0]);
        exit(-1);
    }

    return 0;
}
