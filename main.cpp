#include "filetransport.h"

int main(int argc, char *argv[]){
    //char *buffer = new char[NBYTES4K];
    //int filefd = Open(argv[1], O_RDONLY);
    //int filewrite = Creat("./new");
    //size_t filesize = ReadFile(filefd, buffer);
    //WriteFile(filewrite, buffer, filesize);
    //printf("the file size is : %d \n", (int) filesize);
    //cout<<"##"<<buffer[filesize-2]<<"##"<<endl;
    //printf("%s#", buffer);
     time_t startime,endtime;
    startime = time(NULL);
/*
    pid_t childpid;
    int filetmp = Creat("./datetest4");
    childpid = fork();
    if(childpid==0){
         int filedr = Open("./datetest4", O_WRONLY);
        lseek(filedr, 1024*1024*16*16, SEEK_SET);
        for(int i=1024*1024*16; i<1024*1024*32;i++)
            write(filedr, "123456789123456\n", 16);
            exit(0);
    }else if(childpid>0){
        int filedr = Open("./datetest4", O_WRONLY);
        for(int i = 0; i<1024*1024*16;i++)
            write(filedr, "abcdefghijklmno\n", 16);
    }*/
    int filetmp = Creat("./datetest5");
    for(int i=0;i<1024*1024*32;i++)
        write(filetmp, "123456789123456\n", 16);
    endtime = time(NULL);
    cout<<(endtime-startime)<<endl;
    return 0;
}
