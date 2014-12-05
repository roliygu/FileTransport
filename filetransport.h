#ifndef _ROLIY_FILETRANSPORT_
#define _ROLIY_FILETRANSPORT_

// C
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
// C++
#include <iostream>
using namespace std;

extern const size_t BYTES4K;
extern const size_t BYTES1M;
extern const size_t BYTES64M;
extern const size_t BYTES128M;


void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg);
int Open(const char *pathname, int oflag);
int Creat(const char *pathname);
size_t ReadFile(int filedes, char *buffer);
ssize_t WriteFile(int filedes, const char *buffer, size_t nbytes);

# endif
