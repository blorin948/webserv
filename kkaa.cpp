#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream> 
#include <fstream>
//#include "parsing/parsing.hpp"
#include <utility> 
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "vector"
#include <poll.h>
#include <sys/select.h>

#define PORT 8080
#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

int makeSocket(int port)
{
	int len, rc, on = 1;
	int listen_sd = -1, new_sd = -1;
	int desc_ready, end_server = FALSE, compress_array = FALSE;
	int close_conn;
	char buffer[80];
	struct sockaddr_in addr;
	int timeout;
	struct pollfd fds[200];
	int nfds = 1, current_size = 0, i, j;

	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sd < 0)
	{
		perror("socket() failed");
		exit(-1);
	}
	rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR,
					(char *)&on, sizeof(on));
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(listen_sd);
		exit(-1);
	}
	rc = fcntl(listen_sd, F_SETFL, O_NONBLOCK);
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(listen_sd);
		exit(-1);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	rc = bind(listen_sd,
			  (struct sockaddr *)&addr, sizeof(addr));
	if (rc < 0)
	{
		perror("bind() failed");
		close(listen_sd);
		exit(-1);
	}
	rc = listen(listen_sd, 32);
	if (rc < 0)
	{
		perror("listen() failed");
		close(listen_sd);
		exit(-1);
	}
	return listen_sd;
}

int main(int argc, char *argv[])
{
	int len, rc, on = 1;
	int listen_sd = -1, new_sd = -1;
	int desc_ready, end_server = FALSE, compress_array = FALSE;
	int close_conn;
	char buffer[80];
	struct sockaddr_in6 addr;
	int timeout;
	int list[3];
	struct pollfd fds[200];
	int nfds = 1, current_size = 0, i, j;

	i = 0;
	memset(fds, 0, sizeof(fds));
	while (i < 3)
	{
		listen_sd = makeSocket(8000 + i);
		list[i] = listen_sd;
		fds[i].fd = listen_sd;
		fds[i].events = POLLIN;
		i++;
	}
	nfds = 3;
	timeout = (3 * 60 * 1000);
	do
	{
		printf("Waiting on poll()...\n");
		rc = poll(fds, nfds, timeout);
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		if (rc == 0)
		{
			printf("  poll() timed out.  End program.\n");
			break;
		}
		current_size = nfds;
		for (i = 0; i < current_size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)
			{
				printf("  Error! revents = %d\n", fds[i].revents);
				end_server = TRUE;
				break;
			}
			if (fds[i].fd == list[i])
			{
				printf("  Listening socket is readable\n");
				do
				{
					new_sd = accept(list[i], NULL, NULL);
					if (new_sd < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							end_server = TRUE;
						}
						break;
					}
					printf("  New incoming connection - %d\n", new_sd);
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				} while (new_sd != -1);
			}
			else
			{
				printf("  Descriptor %d is readable\n", fds[i].fd);
				close_conn = FALSE;
				do
				{
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							close_conn = TRUE;
						}
						break;
					}
					if (rc == 0)
					{
						printf("  Connection closed\n");
						close_conn = TRUE;
						break;
					}
					len = rc;
					printf("  %d bytes received\n", len);
					rc = send(fds[i].fd, buffer, len, 0);
					if (rc < 0)
					{
						perror("  send() failed");
						close_conn = TRUE;
						break;
					}

				} while (TRUE);
				if (close_conn)
				{
					close(fds[i].fd);
					fds[i].fd = -1;
					compress_array = TRUE;
				}
			}
		}	  
	} while (end_server == FALSE); /* End of serving running.    */

	/*************************************************************/
	/* Clean up all of the sockets that are open                 */
	/*************************************************************/
	for (i = 0; i < nfds; i++)
	{
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
}
