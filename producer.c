#include "buffer.h"
#include <iostream>

int main() {
  const char* sem1 = "notEmpty";
  const char* sem2 = "notFull";
  const char* sem3 = "mutex";
  sem_t* notEmpty, notFull, mutex; // Shared semaphores between the processes (linked to semaphores in the buffer)
  int* shelf;
  int shared; // Locates share memory file and describes what is in it
  int loop = 2; // Loop program twice (max buffer size)
  
  shared = shm_open("buffer", O_CREAT | O_RDWR, 0666)
  ftruncate(shared, sizeof(int)); // Size of buffer segment
  
  // Map memory in process address
  shelf = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0);
  
  // Create Semaphores
  notEmpty = sem_open(sem1, O_CREAT, 0666, 0);
  notFull = sem_open(sem2, O_CREAT, 0666, 3);
  mutex = sem_open(sem3, OCREAT, 0666, 1);
  
  // Make first item
  printf("\nItem Created\n");
  while (loop--) { // Until loop finishes...
    sem_wait(notFull);
    sem_wait(mutex);
    (*shelf)++; // Add item to the shelf
    sem_post(mutex);
    printf("%d Items Avaliable\n"); // Announce # in the buffer
    sem_post(fill);
  }
  
  // Close and detach semaphores from buffer
  sem_close(notEmpty);
  sem_close(notFull);
  sem_close(mutex);
  sem_unlink(sem1);
  sem_unlink(sem2);
  sem_unlink(sem3);
  
  // Close and detach buffer
  munmap(shelf, sizeof(int));
  close(shared);
  shm_unlink("buffer");
  return 0;
}
