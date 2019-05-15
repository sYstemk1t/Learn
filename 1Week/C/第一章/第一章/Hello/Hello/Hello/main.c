#include <stdio.h>
/*正常代码
int main()
{
    printf("hello,world\n");
    getchar();
}
*/

/*输出结果为，语法错误，缺少}*/
int main()
{
    printf("hello world\n);
        getchar();
}