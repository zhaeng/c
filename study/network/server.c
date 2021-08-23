#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        error(1, 0, "usage: <IPAddress> <port>");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int s = socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\r\n", s);
    if (s < 0)
    {
        error(1, errno, "create socket failed");
    }

    int bs = bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (bs < 0)
    {
        error(1, errno, "bind failed");
    }

    int ls = listen(s, 1024);
    if (ls < 0)
    {
        error(1, errno, "listen failed");
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buff[256];
    int connfd;

    for (;;)
    {
        connfd = accept(s, (struct sockaddr *)&client_addr, &client_len);
        if (connfd < 0)
        {
            error(1, errno, "accept error\r\n");
        }
        // printf("accept\r\n");
        while (1)
        {
            bzero(buff, sizeof(buff));
            int len = read(connfd, buff, sizeof(buff));
            // printf("read success\r\n");
            if (len == 0)
            {
                close(connfd);
                printf("client close\r\n");
                break;
            }
            else if (len < 0)
            {
                error(1, errno, "read data error\r\n");
                // if (errno == EINTR)
                // {
                //     printf("continue\r\n");
                //     continue;
                // }
                // else
                // {
                //     close(connfd);
                //     error(1, errno, "read data error\r\n");
                // }
            }
            buff[len] = 0;
            char send_buff[1024];
            // fputs(buff, stdout);
            printf("rvc data: %s\r\n", buff);
            sprintf(send_buff, "Hi, %s", buff);

            write(connfd, send_buff, strlen(send_buff));
        }
    }

    return 0;
}
