# OS homework week 16

<p align=right>PB18000227 艾语晨</p>

### Question 1

> Q :
>
>  **What is the 8+3 naming convention in FAT32 file system, and how to manage long filenames?**

> A :

- The 8+3 naming convention means :
	- In the 0~10 Bytes, 8 characters (each use 1 byte) are allocated for file name, including 1 byte representing if unallocated, while 3 characters are allocated for file extension
- Use LFN entries to store filename, every LFN entry is able to store 13 characters in Unicode, yet the sequence of LFN is upside down

### Question 2

> Q :
>
> **How are director entries managed in FAT and Ext file systems**

> A :

- FAT : A FAT table manages all director entries, a directory entry stores *filename*, extension name, etc. In every block visited stores the address of the next block, or EOF
- Ext : A directory file's content is the inode-number-table of files in this directory, while the inode table, as a layered linked list, provides the address of every block in this file

### Question 3

> Q :
>
> **What is the difference between hard link and symbolic link**

> A :

A hard link is a directory entry pointing to an existing file, and it will increase the link count of the file's inode.

A symbolic link is a file. Unlike the hard link, a new inode is created for each symbolic link. It stores the pathname (shortcut)

### Question 4

> Q :
>
> **What are the initial link counts when a regular file or a directory is created? Why**

> A :

The initial link count of a regular file is 1, which is its pathname.

The initial link count of a directory is 2, including its pathname and `.` (a hark link to itself)

### Question 5

> Q :
>
> **What is the difference between data journaling and metadata journaling? Explain the operation sequence for each of the two journaling methods**

> A :

Data journaling issues all blocks at once. Its operation sequence is "Journal write (Write the contents of the transaction (including TxB, metadata, and data)) -> Journal commit (metadata, and data (including TxE)) -> Checkpoint (Write the contents of the update to their on-disk locations)"

Metadata journaling logs metadata only. Its operation sequence is "Data write -> Journal metadatawrite -> Journal commit -> Checkpoint metadata -> Free", yet the first two steps can be issued in parallel.

### Question 6

> Q :
>
> **What are the three I/O control methods**

> A :

Polling, Interrupts, DMA (Direct Memory Access)

(以下复制粘贴自我自己的组成原理作业😂不再翻译一遍了就)

程序查询方式：由于在有I/O操作的时候，计算机就会暂停主程序，转而执行I/O，加以I/O的低效率，会浪费很多CPU周期和资源

程序中断方式：由于采用了CPU和I/O设备并行的结构，故占用很少的CPU周期（每一次I/O请求用一个时钟周期）

DMA方式：数据交换不经过CPU，占用CPU不访问内存的时间，几乎不占用CPU周期

### Question 7

> Q :
>
> **List at least three kinds of I/O devices and explain how to provide a standard and uniform application I/O interface**

> A :

- Devices 
	- Disk, Keyboard, CD-ROM, socket
- Provide a standard and uniform application I/O interface
	- Abstraction, encapsulation, layering
	- Abstract general models from various I/O devices, while put the interface into kernel, modifying interface ports towards devices.

### Question 8

> Q :
>
> **What services are provided by the kernel I/O subsystem**

> A :

- **I/O scheduling**
	- Maintain a per-device queue
	- Re-ordering the requests
	- Average waiting time, fairness, etc.
- **Buffering** - store data in memory while transferring between devices
	- To cope with device speed mismatch
	- To cope with device transfer size mismatch
	- To maintain “copy semantics” (e.g., copy from application’s buffer to kernel buffer)
- **Caching** - faster device holding copy of data
	- Always just a copy
	- Key to performance
	- Sometimes combined with buffering
- **Spooling** - hold output for a device
	- If device can serve only one request at a time, e.g., Printing
- **Error handling** and **I/O protection**
	-  OS can recover from disk read error, device unavailable, transient write failures
	- All I/O instructions defined to be privileged
- **Power management, etc.**

填空，名词解释，简答题，综合题（算法&计算）

