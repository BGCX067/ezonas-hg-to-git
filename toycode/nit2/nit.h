class nit
{
	nit(string _ip_addr, int _port)
	{
		ip_addr = _ip_addr;
		port = _port;
	}

	~ nit()
	{
	
	}

	string ip_addr, hostname;
	int port;
	sockaddr_in sock;
};