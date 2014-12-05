#include "filetransport.h"

const size_t BYTES4K = 4*1024;                     // 4K
//const size_t BYTES1M = 256*BYTES4K;
const size_t BYTES1M = 1;
const size_t BYTES64M = 64*BYTES1M;
const size_t BYTES128M = 2*BYTES64M;
const int RWRWRW = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

void DieWithUserMessage(const char *msg, const char *detail){
	fputs(msg, stderr);
	fputs(": ", stderr);
	fputs(detail, stderr);
	fputc('\n', stderr);
	exit(1);
}
void DieWithSystemMessage(const char *msg){
	perror(msg);
	exit(1);
}
int Open(const char *pathname, int oflag){
    int n=open(pathname, oflag);
    if(n == -1)
        DieWithSystemMessage("open() failed");
    else
        return n;
}
int Creat(const char *pathname){
    umask(0);
    int n = open(pathname, O_WRONLY | O_CREAT | O_TRUNC,RWRWRW);
    if(n == -1)
        DieWithSystemMessage("creat() failed");
    else
        return n;
}
ssize_t WriteFile(int filedes, const char *buffer, size_t nbytes){
    ssize_t n = write(filedes, buffer, nbytes);
    if(n!=nbytes)
        DieWithSystemMessage("write() failed");
    else
        return n;
}
size_t ReadFile(int filedes, char *buffer){
    // 从filedes中读到buffer，直到filedes最后一个字符NULL
    size_t filesize = 0,n;
    char *start = buffer;
    while(n=read(filedes, start, BYTES4K)){
        filesize += n;
        start += n;
    }
    return filesize;
}
