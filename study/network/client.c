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
        error(1, 0, "usage: <IPAddress> <Port>");
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    //servsock.sin_addr.s_addr = argv[1];
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    socklen_t server_len = sizeof(server_addr);
    int connfd = connect(sockfd, (struct sockaddr *)&server_addr, server_len);

    if (connfd < 0)
    {
        error(-1, errno, "connect error");
    }

    char buff[1024];

    char *msg = "client>> ";
    // fputs(msg, stdout);
    while (1)
    {
        fputs(msg, stdout);
        char recv_buff[1024];
        if (fgets(buff, 1024, stdin) != NULL)
        {
            // fputs(msg, stdout);
            //printf("%s",buff);    
            int len = strlen(buff);

            if (len <= 1)
            {
                continue;
            }

            if (buff[len - 1] == '\n')
            {
                buff[len - 1] = 0;
            }
            if (strncmp(buff, "quit", strlen(buff)) == 0)
            {
                if (shutdown(sockfd, 1))
                {
                    error(1, errno, "shutdown failed");
                }
                break;
            }
            int l = strlen(buff);

            if (write(sockfd, buff, strlen(buff)) != strlen(buff))
            {
                error(1, errno, "write failed");
            }
            fputs(msg, stdout);
            if (read(sockfd, recv_buff, 1024) == 0)
            {
                printf("server closed\r\n");
                if (shutdown(sockfd, 1))
                {
                    error(1, errno, "shutdown failed");
                }
                break;
            }
            else
            {
                
                printf("recv data : %s\r\n", recv_buff);
            }
        }
    }

    return 0;
}
