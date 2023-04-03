#include "buffer.h"

int main() {
  // Set up buffer
  sh_buff.buffer[0] = 0; // Empty
  sh_buff.buffer[1] = 0; // Empty

  int shelf = 0;
  int value = 99; // I/O from user
  
  // Create Semaphores
  sem_init(&sh_buff.notFull, 1, 0);
  sem_init(&sh_buff.notEmpty, 1, 1);

  while (value != 0) { // Until loop finishes...
    if (value == 1) {
      sem_wait(&sh_buff.notFull);
      sleep(rand()%2+1); // Wait for other processes
      if (sh_buff.buffer[1] != 1) {// If it isn't full, add an item
        if (sh_buff.buffer[0] == 1) {
          sh_buff.buffer[0] = 1;
          shelf++;
        }
        else {
          sh_buff.buffer[1] = 1; // Full
          shelf++;
        }
        printf("Item Created\n");
      }
      else {
        printf("Buffer Full!\n");
      }
      sem_post(&sh_buff.notEmpty);
    }
  }
    
  // Remove and Detach Semaphores
  sem_destroy(&sh_buff.notFull);
  sem_destroy(&sh_buff.notEmpty);
  
  return 0;
}
