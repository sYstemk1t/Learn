/*���϶��¶�ת�������¶�*/
#include <stdio.h>
int main()
{
    printf("\t�¶ȱ���\n");
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;  //�¶ȵ�����
    upper = 300;	//�¶ȵ�����
    step = 20;		//����
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%3.0f\t%f\n", celsius, fahr);
        fahr = fahr + step;  //
    }
    system("pause");
}