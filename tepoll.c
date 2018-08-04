#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>

#define MAX_EVENTS 5
#define READ_SIZE  10

int main() {
    int epoll_fd = epoll_create1(0); //why create1, why 0
    if (-1 == epoll_fd) {
        perror("epoll_create1");
        return -1;
    }

    struct epoll_event event;
    event.events = EPOLLIN; //other values
    event.data.fd = 0; //why 0

    if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) //why 0
    {
        perror("epoll_ctl");
        return -1; //close epoll_fd
    }

    int event_count;
    struct epoll_event events[MAX_EVENTS];
    size_t bytes_read;
    char read_buffer[READ_SIZE+1];
    while(1) {
        printf("polling for input...\n");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000); //timeout 30s
        printf("%d ready revents\n", event_count);
        for (int i=0; i<event_count; ++i) {
            printf("reading file descriptor '%d' -- ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            if (-1 == bytes_read) {
                perror("read");
                return -1;
            }
            printf("%zd bytes read.\n", bytes_read);
            read_buffer[bytes_read] = '\0';
            printf("read '%s'\n", read_buffer);
        }
    }

    if (-1 == close(epoll_fd)) {
        perror("close");
        return -1;
    }

    return 0;
}
