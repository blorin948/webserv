#include "includes/Webserv.h"
#include "includes/GetResponse.hpp"
#include "includes/ParseRequest.hpp"
#include "includes/PostResponse.hpp"
#include "includes/CgiMaker.hpp"
#include "includes/DeleteRequest.hpp"
#include "includes/ServerConf.hpp"

int		is_port(std::vector<int> port, int p)
{
	unsigned long i = 0;
	while (i != port.size())
	{
		if (port[i] == p)
			return (1);
		i++;
	}
	return (0);
}

void find_request(t_response t, t_request req, std::string &response, ServerConf *serv)
{
	if (t.code >= 400)
	{
		do_get(t, response);
		return ;
	}
	if (t.cgiResponse.empty() == 0)
	{
		do_cgi(t, response);
		return ;
	}
	std::cout << t.method + " " << t.code<<  std::endl;
	if (t.method.compare("GET") == 0)
	{
		do_get(t, response);
		return ;
	}
	if (t.method.compare("POST") == 0)
	{
		do_post(t, req, response, serv);
		return ;
	}
	if (t.method.compare("DELETE") == 0)
	{
		do_delete(t, response);
		return ;
	}
}

int		get_serv(std::vector<ServerConf*> serv, std::string host, int port)
{
	unsigned long i = 0;
	unsigned long a = 0;
	reset_connection(serv);
	while (i < serv.size())
	{
		while (a < serv[i]->getPort().size())
		{
			if (port == serv[i]->getPort()[a])
				serv[i]->set_can_accept_connection(true);
			a++;
		}
		a = 0;
		i++;
	}
	i = 0;
	while (i < serv.size())
	{
		if (serv[i]->get_can_accept_connection() == true)
		{
			if (serv[i]->getName().compare(host) == 0)
				return (i);
		}
		i++;
	}
	i = 0;
	while (i < serv.size())
	{
		if (serv[i]->get_can_accept_connection() == true)
			return (i);
		i++;
	}
	return (0);
}

std::vector<int> get_port_list(std::vector<ServerConf *> t)
{
	unsigned long i = 0;
	std::vector<int> port_list;
	unsigned long a = 0;
	while (i < t.size())
	{
		while (a < t[i]->getPort().size())
		{
			if (is_port(port_list, t[i]->getPort()[a]) == 0)
				port_list.push_back(t[i]->getPort()[a]);
			a++;
		}
		i++;
		a = 0;
	}
	return port_list;
}

int isEmpty(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	if (i == 0)
		return (1);
	return (0);
}

int send_request(int fd, std::vector<ServerConf*> serv)
{
	int valread = 0;
	char buffer[80000];
	std::string hello;
	std::string buffstr;
	bool close_conn;
	valread = read(fd, buffer, 80000);
	if (valread < 0)
		return 0;
	if (valread == 0)
	{
		std::cout << "closed " << std::endl;
		return 1;
	}
	buffstr = buffer;
	t_request req = parse_request(buffstr);
	t_response res = parse_response(serv, get_serv(serv, req.host, req.port), req);
	find_request(res, req, hello, serv[get_serv(serv, req.host, req.port)]);
	valread = send(fd, hello.c_str(), strlen(hello.c_str()), 0);
	if (valread < 0)
		return 0;
	if (valread == 0)
	{
		std::cout << "closed " << std::endl;
		return 1;
	}
	hello.clear();
	return 1;
}

int process_server(std::vector<ServerConf*> serv, std::vector<int> port_list, struct pollfd *fds, t_socket *sock)
{
	int end_server = FALSE;
	int new_socket;
	long valread;
	std::string hello;
	std::string buffstr;
	int count = port_list.size();
	int a = 0;
	int close_conn;
	int rc = 0;
	int current_size;
	int f = 0;
	new_socket = -1;
	int timeout = -1;
	int k = 0;
	int i =0;
	std::cout << count << std::endl;
	while (end_server == FALSE)
	{
		//std::cout << count << std::endl;
		rc = poll(fds, count, timeout);
		current_size = count;
		if (rc < 0)
		{
			perror("  poll() failed");
			break;
		}
		if (rc == 0)
		{
			std::cout << "Timeout" << std::endl;
			return 0;
		}
		for (a = 0; a < count; a++)
		{
			if (fds[a].revents == 0)
				continue;
			if (fds[a].fd == sock[a].socket)
			{
				new_socket = 0;
				while (new_socket != -1)
				{
					new_socket = accept(sock[a].socket, NULL, NULL);
					
					if (new_socket < 0)
					{
						if (errno != EWOULDBLOCK)
							end_server = TRUE;
						break;
					}
					fds[count].fd = new_socket;
					fds[count].events = POLLIN;
					count++;
				}
			}
			if (send_request(fds[a].fd, serv))
			{
				close(fds[a].fd);
				for (int j = a; j < count- 1; ++j)
					fds[j].fd = fds[j+1].fd;
				count--;
			}
		}
	}
	for (i = 0; i < count; ++i)
		if (fds[i].fd > 0)
			close(fds[i].fd);
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please use .conf file as argument." << std::endl;
		return (0);
	}
	unsigned long i = 0;
	std::vector<ServerConf *> serv;
	std::vector<int> port_list;
	t_socket *sock;
	struct pollfd fds[MAX_CONNECTION];
	try
	{
		check_bracer(av[1]);
		serv = create_server(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	if (serv.size() == 0)
		return 0;
	port_list = get_port_list(serv);
	sock = new t_socket[port_list.size()];
	memset(fds, 0, sizeof(fds));
	while (i < port_list.size())
	{
		fds[i] = create_socket(port_list[i], &sock[i]);
		i++;
	}
	process_server(serv, port_list, fds, sock);
	delete sock;
	serv.clear();
	return 0;
}
