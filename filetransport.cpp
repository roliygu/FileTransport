#include "filetransport.h"



const size_t NBYTES4K = 4*1024;                     // 4K
const size_t FILESIZE = 256*NBYTES4K;           // 1MB,默认一个文件不超过1MB
const size_t FILESIZEMAX = 64*FILESIZE;        // 64MB,单文件不超过64MB


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
    int n = open(pathname, (O_WRONLY|O_CREAT|O_TRUNC), (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP));
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
    size_t filesize = 0,n;
    char *start = buffer;
    while(n=read(filedes, start, NBYTES4K)){
        filesize += n;
        start += n;
    }
    return filesize;
}
