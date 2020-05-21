# Summary for lab 3

<p align="right">by 鸢一折纸</p>

### 可能出现的问题

> makefile 意外报错

- `malformed input file`
	- ![1C64ED04F0583A572319C8BF19BEF507](/Users/lapland/Library/Containers/com.tencent.qq/Data/Library/Caches/Images/1C64ED04F0583A572319C8BF19BEF507.png)
	- 报错信息就说mm.o文件格式有问题 由于linux-0.11系统rm命令有问题 可以挂载之后 把生成的文件清楚一下 然后再编译一次试一下
- `ENOENT`：没有那个文件或目录
	- ![68B39952D24FD2D6BDE44CB22719F731](/Users/lapland/Downloads/68B39952D24FD2D6BDE44CB22719F731.jpg)
	- 应该是makefile出现了问题（这个是makefile就没有生成mmdriver）

> 测试文件报错

- 90%的可能是在`place()`函数出现的问题
- 检查PUT的指针指向位置
- 有可能是没有`HDRP(bp)`，HDRP很容易被忽视，尤其是一大堆括号的时候

> 其他

如果卸载文件系统出现busy：关闭所有窗口或者重启

### 关于堆空间的分配

堆分配的空间利用情况：总共5MB的堆空间，分成一个一个的块（占用、空闲）并用链表连接。块内部由头部、有效载荷、填充组成

这个总空间是5MB，从`mem_start_brk`到`mem_max_addr`，用`sbrk`来扩展

需要自己实现的链表分配是在这个堆内部的一部分空间 (即原文档第7页的`Mymalloc`)，放了一个链表，调用`mem_brk` (封装为`extend_heap`) 来进行扩容

> 关于指针

![FAFB6D6FBAD2A01122A1F38442F5F2E4](/Users/lapland/Downloads/FAFB6D6FBAD2A01122A1F38442F5F2E4.png)

箭头所指的位置是bp指针指向的，在有效载荷的首位