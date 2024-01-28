#include <stdio.h>
struct S {
  int i;
  char c;
} s;

int main(void) {
  printf("%d\n", sizeof(*(&s)));
}
