// This program proves that child and parent processes really have separate
// memory (despite initially copied)
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_or_die() {
  int rc = wait(NULL);
  assert(rc > 0);
}

int fork_or_die() {
  int rc = fork();
  assert(rc >= 0);
  return rc;
}

int main(int argc, char *argv[]) {
  int x = 100;
  // process a
  if (fork_or_die() == 0) {
    printf("Child: Before change %d\n", x);
    x = 10;
    printf("Child: After change %d\n", x);
    exit(0);
  }
  // wait_or_die();
  printf("Parent: before change %d\n", x);
  x = 20;
  printf("Parent: after change %d\n", x);
  return 0;
}
