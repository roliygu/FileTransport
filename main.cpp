#include "filetransport.h"

int main(int argc, char *argv[]){
    char *buffer = new char[NBYTES4K];
    int filefd = Open(argv[1], O_RDONLY);
    int filewrite = Creat("./new");
    size_t filesize = ReadFile(filefd, buffer);
    WriteFile(filewrite, buffer, filesize);
    //printf("the file size is : %d \n", (int) filesize);
    //cout<<"##"<<buffer[filesize-2]<<"##"<<endl;
    //printf("%s#", buffer);
    return 0;
}
