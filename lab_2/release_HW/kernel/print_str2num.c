#define __LIBRARY__
#include <linux/kernel.h>
#include <asm/segment.h>

int sys_print_val(int a)
{
	printk("in sys_print_val: %d", a);
}

int sys_str2num(char *str, int str_len, long *ret)
{
	/* *ret = (long)atoi(str); */
	long sum = 0;
	char temp;
	for (int i = 0; i < str_len; i++)
	{
		temp = get_fs_byte(str + i);
		sum = sum * 10 + temp - '0';
	}
	put_fs_long(sum, ret);
}
