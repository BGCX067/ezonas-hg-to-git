#include "nit.h"

class sender
{
public:
	sender(string _port):
	port(_port)
	{ printf("No IP given, using default %s\n", DEF_IP); }
	sender(string _hostname, string _port):
	hostname(_hostname),
	port(_port)
	{
		memset(& hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE;
		ret = getaddrinfo(hostname.c_str(), port.c_str(), & hints, & servinfo);
		if (ret != 0)
		{
			strerror(ret);
			exit(ret);
		}
	}

	~sender()
	{
	
	}

protected:
	string ip_addr, port, hostname;
	int sockdesc, ret;
	sockaddr_in sock;
	addrinfo hints, * servinfo;
};

