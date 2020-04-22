# Summary for OS Lab 2
<p align="right">by 鸢一折纸</p>

## 添加 Linux 系统调用

~~我个人认为，后面让提前看的背景知识并没什么卵用~~  
理由如下：  
1. 实际上对理解实验内容有帮助的课上都讲了，~~鬼知道放网课的时候我干什么了~~
2. 我觉得最有用的是最后给的两个链接，~~这课不本来就是全靠自学么~~
3. 晚开始的人会有群讨论福利（只要肯翻记录，基本上你出的问题别人都问过了）
---
<font color=deeppink>华丽丽的分割线～～</font>  
不扯皮啦，回到正题（认真脸）

---

### 分配系统调用号，修改系统调用表

首先，需要找到要修改的文件的位置，鉴于讲义比较含蓄，我建议去 Google（多看几遍或者问问）

我觉得保持命名格式统一是个好习惯。。。（意思是`sys_balabala`）

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
2. 讲义里面路径比较混乱 /摊手

#### 这一步的结果如图：<img src="/Users/lapland/Library/Application Support/typora-user-images/Screenshot 2020-04-15 at 8.54.40 PM.png" alt="Screenshot 2020-04-15 at 8.54.40 PM" style="zoom:80%;" />

![Screenshot 2020-04-15 at 8.06.24 PM](/Users/lapland/Library/Application Support/typora-user-images/Screenshot 2020-04-15 at 8.06.24 PM.png)

### 实现系统调用函数

