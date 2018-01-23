#ifndef NETWORK_ENGINE_H
#define NETWORK_ENGINE_H
#include <errno.h>
#include <string>

#if defined _WIN32 || defined _WIN64
/* si vous êtes sous Windows */
//#include <pthread_VC.h>
#include <WinSock2.h>
#define SLEEP10MS Sleep(10);
#define SOCKET_ERRNO    WSAGetLastError()
#elif defined linux || defined __linux || defined __linux__
/* si vous êtes sous linux */
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define SOCKET_ERRNO    errno
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define SLEEP10MS usleep(10000);
#else
/* sinon vous êtes sur une plateforme non supportée */
#error not defined for this platform
#endif
#define h_addr h_addr_list[0] /* for backward compatibility */
#define PORT 1977
#define MAX_BUFFER 4096


class NetworkEngine
{
public:
	void init(const char *address, SOCKADDR_IN *sin);
	bool connect(void);
	void clean(void);
	int64_t readClient(const std::string *readBuffer);
	int64_t writeClient(const std::string *writeBuffer, const int64_t length);

private:
	SOCKET sock;
	SOCKADDR_IN *psin;
};

#endif