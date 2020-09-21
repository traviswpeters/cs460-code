#include <stdio.h>

int main() {

  int len = sizeof(&len);

  printf("an address has %d bytes\n", len);

}
