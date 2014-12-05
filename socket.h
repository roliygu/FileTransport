# ifndef _ROLIY_SOCKET
# define _ROLIY_SOCKET

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_storage sockaddr_storage;

extern const int SERV_PORT;
extern const int MAXLINE;
void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg);
int Socket(int domain, int type, int protocol);
int SocketTCP4(void);
int SocketUDP4(void);
void SetServServAddr(sockaddr_in *servaddr);
void SetCliServAddr(sockaddr_in *servaddr, const char *serverip);
int Connect(int socket, const sockaddr *foreignAddress, socklen_t addressLength);
int Close(int socket);
int Bind(int socket, sockaddr *localAddress, socklen_t addressSize);
int Inet_pton(int domain, const char *src, void *dst);
const char *Inet_ntop(int domain, const void *src, char *dst, socklen_t dstBytes);
void Listen(int socket, int queueLimit);
int Accept(int socket, sockaddr *clientAddress, socklen_t *addressLength);
ssize_t Send(int socket, const void *msg, size_t msgLength, int flags);
ssize_t Recv(int socket, void *rcvBuffer, size_t bufferLength, int flags);
ssize_t Readn(int filedes, void *buffer, size_t nbytes);
ssize_t Writen(int filedes, const void *buffer, size_t nbytes);
ssize_t Readline(int filedes, void *buffer, size_t maxlen);

/*
struct sockaddr{
	sa_family_t sa_family;   // 地址簇，比如AF_INET
	char sa_data[14];  // 端口号和IP地址，具体形式依赖于地址簇
};

struct in_addr{
	uint32_t s_addr; // IP地址
};

struct sockaddr_in{
	sa_family_t sin_family; // 地址簇
	in_port_t sin_port; // 端口号
	struct in_addr sin_addr; // IP地址
	char sin_zero[8]; // 填充位
};
// sockaddr和sockaddr_in都是16个字节
*/

# endif
