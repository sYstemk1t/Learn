/*摄氏度温度转换华氏温度*/
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
        printf("%3.0f\t%f\n", celsius, fahr);
        fahr = fahr + step;  //
    }
    system("pause");
}