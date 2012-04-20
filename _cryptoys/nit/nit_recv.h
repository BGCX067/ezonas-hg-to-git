#include "nit.h"

class receiver
{
public:
	receiver(string _port):
		port(_port)	
	{
		memset(& hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE;
		ret = getaddrinfo(NULL, port.c_str(), & hints, & servinfo);
		if (ret != 0)
		{
			strerror(ret);
			exit(ret);
		}
		
	}
	~receiver()
	{
		
	}
	bool set_port(string & _port){ port = _port; }
	
protected:
	string ip, port;
	int sockdesc, ret;
	sockaddr_in sock;
	addrinfo hints, * servinfo;
};

