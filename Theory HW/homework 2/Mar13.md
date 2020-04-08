# OS homework for week 4

​																																by 艾语晨 PB18000227

---

### Problem 1

> Q : Including the initial parent process, how many processes are created by the program shown in Figure 1?

![image-20200313210549010](/Users/lapland/Library/Application Support/typora-user-images/image-20200313210549010.png)



> A : 16 (Including the initial process of this program)

### Problem 2

> Q : Explain the circumstances under which the line of code marked printf (‘‘LINE J’’) in Figure 2 will be reached.

<img src="/Users/lapland/Library/Application Support/typora-user-images/image-20200313210600306.png" alt="image-20200313210600306" style="zoom:100%;" />

>A : When the `execlp()` function call is failed to be called, it will not reset the process but continue to execute the printf func, with a return value of `-1`.

### Problem 3

> Q : Using the program in Figure 3, identify the values of pid at lines A, B, C, and D. (Assume that the actual pids of the parent and child are 2600 and 2603, respectively.)

<img src="/Users/lapland/Library/Application Support/typora-user-images/image-20200313211941836.png" alt="image-20200313211941836" style="zoom:100%;" />

> A : 
>
> The PID values are as the table below :

| position | value |
| :------: | :---: |
|    A     |   0   |
|    B     | 2603  |
|    C     | 2603  |
|    D     | 2600  |

### Problem 4

> Q : Using the program shown in Figure 4, explain what the output will be at lines X and Y.

<img src="/Users/lapland/Library/Application Support/typora-user-images/image-20200313212707825.png" alt="image-20200313212707825" style="zoom:100%;" />

> A : 

```powershell
CHILD: 0CHILD: -1CHILD: -4CHILD: -9CHILD: -16CHILD: 0CHILD: -1CHILD: -4CHILD: -9CHILD: -16
```

> Note : Cause this program does *not* have a line break at its output...So the results were put altogether, yet it seems that there *is* a blank space between ':' and '%'.

### Problem 5

> Q : For the program in Figure 5, will LINE X be executed, and explain why.

```c
int main(void) {
    printf("before execl ...\n");
    execl("/bin/ls", "/bin/ls", NULL);
    printf("after execl ...\n");   /*LINE: X*/
    return 0;
}
```

> A : LINE X will *not* be actually executed (except for the condition that the function call `execl` is not executed cause an error has occurred).
>
> The reason is that the system call of `exec()` replaces the current process image with a new process image. While the new one is there to execute, the original process code or statistics are covered and will not be executed.

### Problem 6

> Q : Explain why “terminated state” is necessary for processes.

> A : In a `fork(), exec(), wait()` , a parent process is blocked when using a `wait()` call, and only can wake up again only when receiving a SIGCHLD *from an `exit()` call made by the dying child process*, destroying the zombie process, and move on to its former execution.
>
> I mean, when the child process is terminated, the kernel notifies the parent of the child process about the termination of its child.
>
> So, if there isn't a "terminated state", the parent will never be waken up, and the zombie will never be eliminated.

### Problem 7

> Q : Explain what a zombie process is and when a zombie process will be eliminated (i.e., its PCB entry is removed from kernel).

> A : When a process ends its execution and invokes `exit()`, it changes into terminated state, keeping its storage in the kernel-space memory to a minimum. It's called a *zombie process* before it's given a clean death by its parent's `wait()` call.
>
> A zombie process is eliminated either when its SIGCHLD is picked up by its parent process's signal handling routine, or become an orphan and be adopted by process 'init', before being destroyed by the periodically called `wait()`.
