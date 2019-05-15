/*修改温度转换程序，使之能够在转换表顶部打印一个标题*/
#include <stdio.h>
int main()
{
    printf("\t温度标题\n");
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;  //温度的下线
    upper = 300;	//温度的上限
    step = 20;		//步长
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%3.0f\t%f\n", fahr, celsius);
        fahr = fahr + step;  //
    }
    system("pause");
}