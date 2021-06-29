#include <stdio.h>
int main () {
  for(int i=0; i<257; i++){
    printf("\033[38;5;%dm", i);
    printf("Hello world\n");
  }
  printf("\033[0m");
  return 0;
}
