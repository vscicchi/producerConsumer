#include "buffer.h"

int main() {
  const char* sem1 = "notEmpty";
  const char* sem2 = "notFull";
  const char* sem3 = "mutex";
  sem_t* notEmpty, notFull, mutex; // Shared semaphores between the processes (linked to semaphores in the buffer)
  int* shelf;
  int shared; // Locates share memory file and describes what is in it
  int loop = 2; // Loop program twice (max buffer size)
  
  shared = shm_open("buffer", O_CREAT | O_RDWR, 0666)
  
  // Map memory in process address
  shelf = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0);
  
  // Create Semaphores
  notEmpty = sem_open(sem1, O_CREAT, 0666, 0);
  notFull = sem_open(sem2, O_CREAT, 0666, 3);
  mutex = sem_open(sem3, OCREAT, 0666, 1);
  while (loop--) { // Until loop finishes...
    sem_wait(notEmpty);
    sem_wait(mutex);
    (*shelf)--;
    sem_post(mutex);
    printf("Item Consumed\n");
    sem_post(notFull);
  }
  
  // Remove and Detach Semaphores
  sem_close(notEmpty);
  sem_close(notFull);
  sem_close(mutex);
  sem_unlink(sem1);
  sem_unlink(sem2);
  sem_unlink(sem3);
  
  munmpa(shelf, sizeof(int));
  close(shared);
  shm_unlink("buffer");
  return 0;
}
