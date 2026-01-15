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
  if (fork_or_die() == 0) {
    close(STDOUT_FILENO);
    // this silently fails
    printf("hello");
    exit(0);
  }
  wait_or_die();
  // no problem as close only removes the STDOUT from child processes fd table.
  printf("hello from parent");
  return 0;
}
