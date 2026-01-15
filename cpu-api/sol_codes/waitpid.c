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

// a child can't use waitpid to wait for parent because waitpid is for child
// processes.
int main(int argc, char *argv[]) {
  pid_t id = fork_or_die();
  if (id == 0) {
    sleep(0);
    exit(100);
  }
  int status;
  waitpid(id, &status, 0);
  printf("child status: %d", status);
  return 0;
}
