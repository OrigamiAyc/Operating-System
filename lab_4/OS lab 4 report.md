# OS lab 4 report

<p align=right>PB18000227艾语晨</p>

## 第一部分

### 实现只读的FAT

#### 第一题（跑测试文件）

思路以及一些比较大的坑 (log) 都在注释里面，其中`find_root()`函数有一处修改：第434~437行

```c
		if (is_eq && Root->DIR_Attr == ATTR_DIRECTORY)
		{
			return find_subdir(fat16_ins, Root, paths, pathDepth, 2);
		}
```

其中436行最后一个参数由1改为2，因为在root函数中，currDepth的对应值为1

测试结果：

![Screenshot 2020-06-21 at 11.31.21 PM](/Users/lapland/Library/Application Support/typora-user-images/Screenshot 2020-06-21 at 11.31.21 PM.png)

![Screenshot 2020-06-21 at 11.50.58 PM](/Users/lapland/Library/Application Support/typora-user-images/Screenshot 2020-06-21 at 11.50.58 PM.png)

回答问题：

1. FAT16

	- 

	```c
	typedef struct
	{
	  FILE *fd;
	  DWORD FirstRootDirSecNum;
	  DWORD FirstDataSector;
	  BPB_BS Bpb;
	} FAT16;
	```

	- fd是用于挂载磁盘镜像文件（实验中为已实现的FAT）
	- FirstRootDirSecNum是根目录的第一个扇区绝对编号
	- FirstDataSector是数据区（2号蔟开始）第一个扇区的绝对编号
	- BPB存储着整个文件系统的配置信息

第二个不会……