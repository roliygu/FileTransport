#include "filetransport.h"

int main(){
    建立套接字，连接服务器
    等待服务器的文件信息和多进程标记
    打开保存的文件
    if(多进程标记)
        fork()新进程
        新进程关闭和服务器连接，重新连接服务器
        新的连接接受第二部分到buffer
        重新打开一个写权限+偏移的描述符
        buffer内容写到文件中
    父进程接受第一部分内容到buffer
    buffer内容写到文件中
    return 0;
}
