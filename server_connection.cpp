#include "includes/Webserv.h"
#include "includes/GetResponse.hpp"
#include "includes/ParseRequest.hpp"
#include "includes/PostResponse.hpp"
#include "includes/CgiMaker.hpp"
#include "includes/DeleteRequest.hpp"
#include "includes/ServerConf.hpp"

void reset_connection(std::vector<ServerConf*> serv)
{
	unsigned long i = 0;
	while (i < serv.size())
	{
		serv[i]->set_can_accept_connection(false);
		i++;
	}
}

struct pollfd create_socket(int port, t_socket *t)
{
	struct pollfd fds;
	int on = 1;
	t->addrlen = sizeof(t->address);
	t->port = port;
	if ((t->socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(t->socket, SOL_SOCKET, SO_REUSEADDR,
			   (char *)&on, sizeof(on));
	if ((fcntl(t->socket, F_SETFL, O_NONBLOCK)) < 0)
	{
		close(t->socket);
		exit(-1);
	}
	memset(&t->address, 0, sizeof(t->address));
	t->address.sin_family = AF_INET;
	t->address.sin_addr.s_addr = INADDR_ANY;
	t->address.sin_port = htons(port);
	memset(t->address.sin_zero, '\0', sizeof t->address.sin_zero);
	if (bind(t->socket, (struct sockaddr *)&t->address, sizeof(t->address)) < 0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	if (listen(t->socket, MAX_CONNECTION) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}
	fds.fd = t->socket;
	fds.events = POLLIN;
	return fds;
}