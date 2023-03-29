#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 2 // Buffer Size of 2
#define errorExt(msg)

struct buffer {
  sem_t notEmpty, notFull;
  size_t count; // # of bytes used
  int buffer[BUFFER_SIZE];
};

#endif
