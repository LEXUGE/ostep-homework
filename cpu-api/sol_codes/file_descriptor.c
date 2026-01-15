// This tests the file descriptor behavior after fork
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
  FILE *fptr;

  fptr = fopen("filename", "w");
  // with common we get
  // CommonParent writingCommonChild writing
  // fputs("Common", fptr);
  // as both processes inherit the buffer ant it hasn't been flushed
  if (fork_or_die() == 0) {
    fputs("Child writing", fptr);
    exit(0);
  }
  fputs("Parent writing", fptr);
  fflush(fptr);
  wait_or_die();
  fclose(fptr);
  return 0;
}
