# Summary for OS Lab 2
<p align="right">by 鸢一折纸</p>

## 添加 Linux 系统调用

### 分配系统调用号，修改系统调用表

首先，需要找到要修改的文件的位置，鉴于讲义比较含蓄，我建议去 Google（多看几遍或者问问）

需要保持命名格式统一。。。（比如`sys_balabala`）因为别的地方会有带着这些前缀的

需要添加的文件里面：

- `system_call.s` 和 `sys_xxx` 都位于源码里面（就是 `~/oslab/Linux-0.11` 目录）=·=
	- `kernel/system_calls.s`，参数加上2
	- `include/linux/sys.h`，放最后面就行（原型和 table 表（就是最后面黑色的一大堆））
- `unistd.h` 是既要在挂载的文件系统里面修改，<font color=coral>又要在源码修改的</font>
	- `include/unistd.h`
	- `hdc/usr/include/unistd.h`

> 以及，关于为什么建议不要直接拷贝linux源码中的 `unistd.h` 文件，助教大大的官方解释是：<font color=coral>内容其实是差不多的，但是Linux 0.11 不支持` // `这种形式的注释，但是Linux源码中的这个文件有这个注释，所以说需要换成`/* */` </font>

> 对题的注释（这段可能是我蠢了，不需要的直接跳过）

1. 题里面的`sys_xxx`是一个代称。。。没有真的什么叫`xxx`的
2. 讲义里面路径有点混乱诶 /摊手

### 实现系统调用函数

#### 分析如下：

> 转载并改编自XT大佬的提示@Xiao2002



在使用**print_val()**之前（比如在**test.c**文件中），我们应当先使用`_syscall1(int, print_val, int, a)`函数，**_syscallx**的x由调用函数的参数个数决定。该函数的目的是调用真正实现**print_val()**系统调用功能的函数（本例中为在**print_str2num.c**（xxx.c)文件中定义的`sys_print_val()`函数）。

> 对于文件的编辑：两个`sys_`的函数在**xxx.c**文件中实现（系统调用）；而实际上用户调用的不带`sys_`的函数在各自的**.c**文件（同放在kernel目录下）



然后根据`syscall1()`的宏定义，有关系统调用`print_val()`的各种参数被传入寄存器，其中参数**__NR_print_val**（上一问）被传入寄存器**%eax**。然后进行**0x80**中断调用，此时来到了**kernel/system_calls.s**文件中的**system_call**部分。执行到语句`call *sys_call_table(,%eax,4)`时，系统再次跳转到了**include/linux/sys.h**文件中的**sys_call_table[]**数组中，并将寄存器**%eax**的值传给该数组，寻找对应的真正实现系统调用功能的函数`sys_print_val()`。可知之前定义的参数**__NR_print_val**的值便是数组**sys_call_table[]**中真正实现系统调用功能的函数`sys_print_val()`的下标，然后操作系统便会到其他文件中去寻找该函数的实现代码（这里是**print_str2num.c**文件）。

> 为什么会这样呢？实际上，回顾一下之前有关Kernel态和User态的课程可知，这次 I/O 请求需要通过内核态，于是**test**调用`sys_print_val`（stdlib中声明），而这个函数的实现是通过`_syscallx`系列，传参了`print_val`来完成的



在这一切的调用都结束后，我们回到**test.c**文件中。

#### 编写系统调用实现

##### 总共实现1个文件

- 也就是**xxx.c**

如果说前面那一堆没看懂的话，需要实现的表面来看是：

- kernel目录下的一个系统调用函数文件（xxx.c），会用于makefile
- 测试文件，里面调用用户函数，放到qemu

##### 需要有define和include

```c
#define __LIBRARY__
#include <linux/kernel.h>
#include <asm/segment.h>
```

其中，include的文件绝对路径就是在\<\>里面的前面加上`Linux-0.11/include`

至于为什么需要添加这几个头文件···

- `#define __LIBRARY__`：在(include/unistd.h)中有叙述：

- ```c
	#ifdef __LIBRARY
	
	...
	define __NR_write 4 // 系统调用编号
	...
	int write(int fildes, const char * buf, off_t count); // 系统调用原型
	...
	```

- `asm/segment.h`：在makefile中添加的编译路径为这个文件（**如果我们修改了include的文件(如增加),需要在makefile文件中做对应的修改**.）

- 不需要`#define put_fs_long`

#### 修改Makefile

xxx指上面那个**print_str2num**

#### 编写测试程序

第一行的printf一定要加换行符，否则会出现那一行输出到了最后面的情况

（薄弱的C语言基础暴露无遗=·=

使用**memset**函数将数组置为`'\0'`，而strlen函数读取到\0就会截止。。。

---

## 熟悉Linux下常见的系统调用函数

由于这一部分没有参考文档，建议参照习题课的Hint（PPT）

残留了一些问题，比如那个`execl`为什么这么填参数

### 使用上述系统调用实现三个进程创建相关的函数

这里需要写的并不多其实

##### `os_open()`

fork函数，以及对于父子进程的**if**分支；一个 execl 函数调用

##### `os_system`

