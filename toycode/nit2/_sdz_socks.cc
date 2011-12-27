//Si nous sommes sous Windows
#if defined (WIN32)

    #include <winsock2.h>

    // typedef, qui nous serviront par la suite
    typedef int socklen_t;

// Sinon, si nous sommes sous Linux
#elif defined (linux)

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    // Define, qui nous serviront par la suite
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)

    // De même
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;

#endif

// On inclut les fichiers standards
#include <stdio.h>
#include <stdlib.h> 

struct sockaddr_in
{
    short      sin_family;
    unsigned short   sin_port;
    struct   in_addr   sin_addr;
    char   sin_zero[8];
};

int main(void)
{
    // Si la plateforme est Windows
    #if defined (WIN32)
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,2), &WSAData);
    #endif
	//////////////////////////////////////////////////
    // ICI on mettra notre code sur les sockets
	//////////////////////////////////////////////////

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23);
	
	if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) return 0xdead0001;
	
	if (listen(sock, 5) == SOCKET_ERROR) return 0xdead0002;
	
	socklen_t taille = sizeof(csin);
	csock = accept(sock, (SOCKADDR*)&csin, &taille);
    if(csock == INVALID_SOCKET) return 0xdead0003;
		
	
	
	// Si la plateforme est Windows
    #if defined (WIN32)
        WSACleanup();
    #endif

    return EXIT_SUCCESS;
}

