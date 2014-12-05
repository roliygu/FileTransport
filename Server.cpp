#include "filetransport.h"
#include "socket.h"

int main(int argc, char *argv[]){
    if(argc != 2)
        DieWithUserMessage("Parameter(s)","<filepath>");
    // 处理文件，判断是否需要多进程
    const char *filename = argv[1];
    int fileID = Open(filename, O_RDONLY);
    struct stat file;
    fstat(fileID, &file);
    if(file.st_size>BYTES128M)
        DieWithUserMessage("FileSize","is over 128MB");
    else if(file.st_size == 0)
        DieWithUserMessage("FileSize","is empty");
    bool focked = (file.st_size>BYTES64M)?true:false;
    // 建立监听
    sockaddr_in cliaddr, servaddr;
    int listensock = SocketTCP4();
    SetServServAddr(&servaddr);
    Bind(listensock, (sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listensock,2);
    // 等待连接
    socklen_t clilen;
    int connectsock = Accept(listensock, (sockaddr *) &cliaddr, &clilen);
    // 需要子进程时，开子进程准备新的连接
    if(focked){
        pid_t childpid = fork();
        if(childpid==0){
            Close(connectsock);
            sockaddr_in subclient;
            socklen_t subclilength;
            int subconnectsock = Accept(listensock, (sockaddr *) &subclient, &subclilength);
            char *part2buf = new char[BYTES64M];
            bzero(part2buf, BYTES64M);
            int subfileID = Open(filename, O_RDONLY);
            lseek(subfileID, (file.st_size/2), SEEK_SET);
            size_t part2size = ReadFile(subfileID, part2buf);
            if( (file.st_size-(file.st_size/2))!=part2size)
                DieWithUserMessage("Read part2 :", "cann't match");
           Writen(subconnectsock, part2buf, part2size);
            exit(0);
        }
    }
    char *part1buf = new char[BYTES64M];
    bzero(part1buf, BYTES64M);
    int part1fileID = Open(filename, O_RDONLY);
    size_t maxsize = (focked)?(file.st_size/2):file.st_size;
    size_t part1readsize = read(part1fileID, part1buf, maxsize);
    if(part1readsize != maxsize)
        DieWithUserMessage("Read part1:","cann't match");
    Writen(connectsock, part1buf, part1readsize);
    return 0;
}
