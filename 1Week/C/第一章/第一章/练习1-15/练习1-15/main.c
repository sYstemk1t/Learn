/*修改温度转换程序，要求逆序排列*/
#include <stdio.h>
int power()
{
    int fahr;
    for (fahr = 0; fahr <= 300; fahr = fahr + 20)   //
    {
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0)*(fahr - 32));

    }
}
int main()
{
    power();
    system("pause");
}