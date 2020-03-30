# Lab 01 report

---
by Lapland Stark

> This only includes some of the contents of this lab.

---
## Task One

### A choice
use `echo` to write into files, or vim/nano/code into it...

```shell
/ # echo <content> > <filename>
```

>Caution:

run the following command under the Linux-0.11 folder (your lab workspace)

```shell
$ make start
```

### problem you might face with
#### in the qemu

If you try to do the command
```shell
/ # mv 1.txt dir1
```
you might face the following error: `mv: 1.txt: Not owner

## Task Three

>caution:

In the part "卸载文件系统hdc"，you must check carefully about <font color=red>the actual name of **your own** hdc</font>. In the tutorial, the first column of the 'hdc' is /dev/loop15, but it can be different on your Ubuntu.

### problem you might face with

#### in the qemu (Linux-0.11)

During "查看Linux0.11文件", when you are executing this command:
```shell
/ # more hello.txt
```
Remind that you must be in the <font color=red>`/usr`</font> path
