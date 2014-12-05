#include "socket.h"


const int SERV_PORT = 5000;
const int MAXLINE = 2048;


int Socket(int domain, int type, int protocol){
	int sock;
	sock = socket(domain, type, protocol);
	if(sock<0)
		DieWithSystemMessage("socket() failed");
	return sock;
}
int SocketTCP4(void){
	return Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
int SocketUDP4(void){
	return Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}
void SetServServAddr(sockaddr_in *servaddr){
	if(servaddr == NULL)
		DieWithSystemMessage("servaddr is error");
	bzero(servaddr, sizeof(*servaddr));
	servaddr->sin_family = AF_INET;
	// servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	const char* ip = "192.168.0.100";
	Inet_pton(AF_INET, ip, &(servaddr->sin_addr));
	servaddr->sin_port = htons(SERV_PORT);
}
void SetCliServAddr(sockaddr_in *servaddr, const char *serverip){
	if(servaddr == NULL)
		DieWithSystemMessage("servaddr is error");
	bzero(servaddr, sizeof(*servaddr));
	servaddr->sin_family = AF_INET;
	servaddr->sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, serverip, &(servaddr->sin_addr));
}
int Close(int socket){
	int n;
	n = close(socket);
	if(n<0)
		DieWithSystemMessage("close() failed");
	return n;
}
int Connect(int socket, const sockaddr *foreignAddress, socklen_t addressLength){
	int n;
	n = connect(socket, foreignAddress, addressLength);
	if(n<0)
		DieWithSystemMessage("connect() failed");
	return n;
}
int Bind(int socket, sockaddr *localAddress, socklen_t addressSize){
	int n;
	n = bind(socket, localAddress, addressSize);
	if(n<0)
		DieWithSystemMessage("bind() failed");
	return n;
}
int Inet_pton(int domain, const char *src, void *dst){
	int n;
	n = inet_pton(domain, src, dst);
	if(n==0)
		DieWithUserMessage("inet_pton() failed", "invalid address string");
	else if(n<0)
		DieWithSystemMessage("inet_pton failed");
	return n;
}
const char *Inet_ntop(int domain, const void *src, char *dst, socklen_t dstBytes){
	if(inet_ntop(domain, src, dst, dstBytes) == NULL )
		DieWithSystemMessage("inet_ntop() failed");
	return dst;
}
void Listen(int socket, int queueLimit){
	char *ptr;
	if( (ptr=getenv("LISTENQ")) !=NULL ){
		int limitMax = atoi(ptr);
		queueLimit = (limitMax<queueLimit)?limitMax:queueLimit;
	}

	if( listen(socket, queueLimit) < 0 )
		DieWithSystemMessage("listen() failed");
}
int Accept(int socket, sockaddr *clientAddress, socklen_t *addressLength){
	int n;
	n = accept(socket, clientAddress, addressLength);
	if(n<0)
		DieWithSystemMessage("accept() failed");
	return n;
}
ssize_t Send(int socket, const void *msg, size_t msgLength, int flags){
	ssize_t n;
	n = send(socket, msg, msgLength, flags);
	if(n<0)
		DieWithSystemMessage("send() failed");
	else if(n!=msgLength)
		DieWithUserMessage("send()", "sent unexpected number of bytes");
	return n;
}
ssize_t Recv(int socket, void *rcvBuffer, size_t bufferLength, int flags){
	ssize_t n;
	n = recv(socket, rcvBuffer, bufferLength, flags);
	if(n<0)
		DieWithSystemMessage("recv() failed");
	return n;
}
ssize_t Readn(int fd, void *vptr, size_t n){
	char *ptr = (char *) vptr;
	size_t nleft = n;
	ssize_t nread;
	while(nleft>0){
		if( (nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR)
				nread = 0;
			else
				return (-1);
		}else if(nread == 0)
			break;
		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft);
}
ssize_t Writen(int fd, const void *vptr, size_t n){
	size_t nleft = n;
	const char *ptr = (char *) vptr;
	ssize_t nwritten;
	while(nleft>0){
		if( (nwritten = write(fd, ptr, nleft)) <= 0){
			if(nwritten<0 && errno == EINTR)
				nwritten = 0;
			else
				return (-1);
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}
ssize_t Readline(int fd, void *vptr, size_t maxlen){
	char *ptr = (char *) vptr;
	ssize_t rc,n;
	for(n=1; n<maxlen; n++){
	again:
		char c;
		if( (rc = read(fd, &c, 1)) == 1){
			*ptr++ = c;
			if(c == '\n')
				break;
		}else if(rc == 0){
			*ptr = 0;
			return (n-1);
		}else{
			if (errno == EINTR)
				goto again;
			return -1;
		}
	}
	*ptr  = 0;
	return n;
}
