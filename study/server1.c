#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

/* 从socketfd描述字中读取"size"个字节. */
size_t readn(int fd, void *buffer, size_t size)
{
	char *buffer_pointer = buffer;
	int length = size;

	while (length > 0)
	{
		int result = read(fd, buffer_pointer, length);

		if (result < 0)
		{
			if (errno == EINTR)
				continue; /* 考虑非阻塞的情况，这里需要再次调用read */
			else
				return (-1);
		}
		else if (result == 0)
			break; /* EOF(End of File)表示套接字关闭 */

		length -= result;
		buffer_pointer += result;
	}
	return (size - length); /* 返回的是实际读取的字节数*/
}

void read_data(int sockfd)
{
	ssize_t n;
	char buf[1024];

	int time = 0;
	for (;;)
	{
		fprintf(stdout, "block in read\n");
		if ((n = readn(sockfd, buf, 1024)) == 0)
		{
			return;
		}
		time++;
		fprintf(stdout, "1K read for %d\n", time);
		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	int listenfd, connfd;
	socklen_t client;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	//分配空间
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 1024);

	for (;;)
	{
		client = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &client);
		read_data(connfd);
		close(connfd);
	}
	return 0;
}
