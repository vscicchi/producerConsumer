#include "buffer.h"

int main() {
  // Print instructions
  printf("1 to Produce Item\n2 to Consume Item\n0 to Exit Program\n\n");

  int shelf = 0;
  int value = 99; // I/O from user (Arbitrary initialize value)
  
  while (value != 0) { // Until loop finishes...
    printf("Enter Instruction: ");
    scanf("%d", value);
    if (value == 2) {
      sem_wait(&sh_buff.full);
      sleep(rand()%2+1); // Wait for other processes
      if (sh_buff.buffer[0] != 0) {
        if (sh_buff.buffer[1] != 0) {
          sh_buff.buffer[1] = 0;
          shelf--;
        }
        else {
          sh_buff.buffer[0] = 0;
          shelf--;
        }
        printf("Item Consumed\n");
      }
      else {
        printf("Buffer Empty!\n");
      }
      printf("Item Consumed\n");
      sem_post(&sh_buff.empty);
    }
  }
  
  return 0;
}
