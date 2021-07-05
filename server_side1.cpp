#include "Webserv.h"
#define PORT 8006
#include "GetResponse.hpp"
#include "ParseRequest.hpp"
#include "ServerConf.hpp"
#include "PostResponse.hpp"

std::vector<std::string> split_request(std::string buffer)
{
	std::vector<std::string> ok;
	char	*str = new char [buffer.length() + 1];
	strcpy (str, buffer.c_str());
	size_t a = 0;
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			ok.push_back(str + a);
			a = i + 1;
		}
		i++;
	}
	return (ok);
}

void do_get(t_response t, std::string &serv_response)
{
	GetResponse ok;
	serv_response = ok.getFullResponse(t);
}

void do_post(t_response &res, t_request req,  std::string &serv_response, ServerConf *serv)
{
	PostResponse ok;
	std::cout << "req size = " << req.size << " seerv limit = " << serv->getLimit() <<std::endl;
	if (req.size > serv->getLimit())
		res.code = 413;
	serv_response = ok.makePost(req, res);
}

void find_request(t_response t, t_request req, std::string &response, ServerConf *serv)
{
	int i = 0;
	if (t.method.compare("GET") == 0)
	{
		do_get(t, response);
	}
	if (t.method.compare("POST") == 0)
	{
		do_post(t, req, response, serv);
	}
}

std::vector<ServerConf *> create_server(char *conf)
{
	std::ostringstream buf;
	std::string file;
	std::ifstream myfile(conf, std::ifstream::in);
	std::vector<ServerConf *> serv;
	if (!(myfile.is_open()))
	{
		std::cout << "Error while opening conf file" << std::endl;
		return serv;
	}
	while (getline(myfile, file))
	{
		buf << file;
		buf << "\n";
	}
	file = buf.str();
	while (file.find("server") != std::string::npos)
	{
		ServerConf *t = new ServerConf(file);
		if (serv.size() == 0)
			t->setDefault(true);
		serv.push_back(t);
	}
	return (serv);
}

t_request parse_request(std::string buffer)
{
	t_request req;
	std::vector<std::string> requestTab = split_request(buffer);
	ParseRequest request;
	request.getRequest(req, requestTab);
	return (req);
}

t_response parse_response(std::vector<ServerConf*> serv, int i, t_request req)
{
	t_response res;
	initResponse(res);
	res = serv[i]->getReponse(res, req);
	return res;
}

int		is_port(std::vector<int> port, int p)
{
	int i = 0;
	
	while (i != port.size())
	{
		if (port[i] == p)
			return (1);
		i++;
	}
	return (0);
}

void reset_connection(std::vector<ServerConf*> serv)
{
	int i = 0;
	while (i < serv.size())
	{
		serv[i]->set_can_accept_connection(false);
		i++;
	}
}

int		get_serv(std::vector<ServerConf*> serv, std::string host, int port)
{
	int i = 0;
	int a = 0;
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
	int i = 0;
	std::vector<int> port_list;
	int count = 0;
	int a = 0;
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
		perror("ioctl() failed");
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
	if (listen(t->socket, 32) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}
	fds.fd = t->socket;
	fds.events = POLLIN;
	return fds;
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
	new_socket = -1;
	int timeout = 1 * 60 * 1000;
	do
	{
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
		for (a = 0; a < current_size; a++)
		{
			if (fds[a].revents == 0)
				continue;
			if (fds[a].revents != POLLIN)
			{
				printf("  Error! fdgrevents = %d\n", fds[a].revents);
				end_server = TRUE;
				break;
			}
			if (fds[a].fd == sock[a].socket)
			{
				do
				{
					printf("\n+++++++ Waiting for new connection ++++++++\n\n");
					new_socket = accept(sock[a].socket, NULL, NULL);
					if (new_socket < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  accept() failed");
							end_server = TRUE;
						}
						break;
					}
					fds[count].fd = new_socket;
					fds[count].events = POLLIN;
					count++;
				} while (new_socket != -1);
			}
			else
			{
				close_conn = FALSE;
				char buffer[80000] = {0};
				valread = recv(fds[a].fd, buffer, sizeof(buffer), 0);
				std::cout << buffer << std::endl;
				if (valread < 0)
				{
					if (errno != EWOULDBLOCK)
					{
						perror("  recv() failedfhgh");
						close_conn = TRUE;
					}
					break;
				}
				if (valread == 0)
				{
					printf("  Connection closed\n");
					close_conn = TRUE;
				}
				if (close_conn == FALSE)
				{
					buffstr = buffer;
					t_request req = parse_request(buffstr);
					printAllRequest(req);
					t_response res = parse_response(serv, get_serv(serv, req.host, req.port), req);
					find_request(res, req, hello, serv[get_serv(serv, req.host, req.port)]);
					valread = send(fds[a].fd, hello.c_str(), strlen(hello.c_str()), 0);
					hello.erase();
				}
				if (valread < 0)
				{
					perror("  send() failed");
					close_conn = TRUE;
					break;
				}
				close(fds[a].fd);
				fds[a].fd = -1;
			}
		}
	} while (end_server == FALSE);
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please use .conf file as argument." << std::endl;
		return (0);
	}
	int i = 0;
	std::vector<ServerConf *> serv;
	std::vector<int> port_list;
	t_socket *sock;
	struct pollfd fds[200];
	try
	{
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
	return 0;
}
