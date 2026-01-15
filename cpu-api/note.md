We are introduced several APIs related to process

1. `fork`
    It copies everything (registers and memory) of our current process and create a new process (child). However, they differ as the return value register for child and parent are not the same. The child after fork is at the instruction right after fork call

    For child, the return value of `fork` is `0` while the return code for parent is PID of the child (hence > 0).

2. `wait`
    `wait(NULL)` tells the kernel I don't care about the return code, just gets back to me whenever one of my children terminates and got cleared up. Therefore if you want to wait til all your children are done you should
    ```c
    while (wait(NULL) > 0) {
        // One children finished!
    }
    ```

3. `execvp`
    `execvp` will replace the current machine state of the process with the program we want to run and run it right in the current process. So it doesn't create a new process! Since it's inplace, it has no memory about who ran the new program, and it will never return. However, since it's still a child process, if you fork then exec then the parent will notice if it `wait`.

# A bit about shell
How shell is made (simplified):
1. You type in for example `cat example > example_copy`
2. Shell parses the arguments
3. Shell forks itself, and set the std output to `example_copy` file. Then it `execvp` program `cat`.
4. Since file descriptor of a process is kept across `execvp`, `cat` now outputs to `example_copy`.

Similarly, there is `pipe` which literally pipes processes inputs and outputs together. On default, only `stdout` is redirected, not `stderr`. If you want to redirect everything first redirect err to output: `prog1 2>&1 | prog 2`.

The exact thing is quite tricky:
- These `2>&1`, `|`, `>` are done before executing the programs
- pipelining always happens first: `prog1 2>&1 | prog2` -> `(prog1 2>&1) | prog2`
- Then each individual segment of the pipe gets parsed from left to right:
    - `2>&1` means basically `*ptr2 = *ptr1`, not `ptr2 = ptr1`. So later when we change `*ptr1 = fd`, `*ptr2` won't update automatically.
    - This is why these setup ordering matters...

# A bit about CPU
The CPU we use today has the conception of "privileged mode" and "user mode". Though look a bit ugly but this is necessary as some programs are not to be trusted to directly control other hardwares and manage their own progress (e.g. stall). So one program/process has to become dominant.


