#ifndef _ROLIY_FILETRANSPORT_
#define _ROLIY_FILETRANSPORT_

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <iostream>
using namespace std;

extern const size_t NBYTES4K;
extern const size_t FILESIZEMAX;
extern const size_t FILESIZE;


void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg);
int Open(const char *pathname, int oflag);
int Creat(const char *pathname);
size_t ReadFile(int filedes, char *buffer);
ssize_t WriteFile(int filedes, const char *buffer, size_t nbytes);

# endif
