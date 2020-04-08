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
you might face the following error: `mv: 1.txt: Not owner`

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

#### in the Ubuntu system

You must create a 'hdc' dir first, then do the `mount` command.

有一个奇怪的···在之前 `umount` 的 dir 下挂载新的文件系统，会报错(俺也不知道为啥)
```shell
mount: /home/stark/oslab/Linux-0.11/hdc: failed to setup loop device for /home/stark/oslab/Linux-0.11/hdc-0.11.img.
```

#### While unmounting a file system

The old files might remain there, so make sure you've deleted them before you redo this experiment.

## While committing

Remember that on MacOS, there's NO embedded FTP file installed, so use a Ubuntu (not xUbuntu) to commit your homework. The server is in the <font color=red>'files'</font> app, like the screenshot attached in this folder.
