#include <stdio.h>
char arr[4096] = {0};
char* ptr = arr;
int main() {
*ptr = getchar();
++*ptr;
--*ptr;
putchar(*ptr);
return (int) *ptr;
}
