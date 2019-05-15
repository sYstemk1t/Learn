/*验证表达式结果getchar*/
/*这个时候不管输入任何值，都是1*/
#include <stdio.h>
int main()
{
    int c = NULL;
    printf("%d", getchar() != EOF);
    system("pause");
}