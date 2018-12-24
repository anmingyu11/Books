#include <stdio.h>
int main()
{
    short a = 0b1010110;  //二进制数字
    int b = 02713;  //八进制数字
    long c = 0X1DAB83;  //十六进制数字
   
    printf("a=%ho, b=%o, c=%lo\n", a, b, c);  //以八进制形似输出
    printf("a=%hd, b=%d, c=%ld\n", a, b, c);  //以十进制形式输出
    printf("a=%hx, b=%x, c=%lx\n", a, b, c);  //以十六进制形式输出（字母小写）
    printf("a=%hX, b=%X, c=%lX\n", a, b, c);  //以十六进制形式输出（字母大写）
    return 0;
}
