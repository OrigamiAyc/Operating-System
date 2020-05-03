/* 有它，_syscallx等才有效。详见unistd.h */
#define __LIBRARY__

#include <unistd.h> /* 有它，编译器才能获知自定义的系统调用的编号 */
#include <stdio.h>
#include <string.h>

_syscall1(int, print_val,int, a); /* print_val()在用户空间的接口函数, 下同 */
_syscall3(int, str2num, char *, str, int, str_len, long *, ret);

int main(int argc, char const *argv[])
{
	long *lval = NULL;
	char cval[100];
	memset(cval, '\0', 100 * sizeof(char));
	printf("Give me a string:\n");
	scanf("%s", cval);
	str2num(cval, strlen(cval), lval);
	print_val(*lval);
	printf("\n");
	return 0;
}
