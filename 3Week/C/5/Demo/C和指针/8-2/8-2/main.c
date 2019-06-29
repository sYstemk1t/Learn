
#include <stdio.h>
#include <float.h>
double income_limits[] = { 0, 23350, 56550, 117950, 256500, DBL_MAX };//DBL_MAX��ͷ�ļ�float.h������������ӵ�����б��ĩβ����֤ѭ��������е�̫��
float base_tax[] = { 0, 3502.5, 12798.5, 31832.5, 81710.5 };
float percentage[] = { 0.15, 0.28, 0.31, 0.36, 0.396 };

double single_tax(double income)
{
	int category;
	for (category = 1; income >= income_limits[category]; category += 1)
	{
		;
	}
	category -= 1;
	return base_tax[category] + percentage[category] * (income - income_limits[category]);
}

int main()
{
	double S, Y;
	printf("input your income S:");
	scanf("%lf", &S);		//�ó�˫���ȸ������������double����
	Y = single_tax(S);
	printf("%lf\n", Y);
	system("pause");
	return 0;
}
