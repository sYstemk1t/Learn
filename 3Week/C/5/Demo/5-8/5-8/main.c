#include <stdio.h>
static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	//������
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	//����
};

int day_of_year(int year, int month, int day)
{
	int i, leap;
	if (0 > year || 0 > month || month > 12 || 0 > day || day > 31)		//û�м��������
	{
		return -1;
	}
		
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;	//�ж��Ƿ�����
	for (i = 1; i < month; i++)
		day += daytab[leap][i];		//ѭ���ӣ��ӵ����ݵ��·ݣ�Ȼ�����
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	if (0 > year || 0 > yearday || yearday > 366 || pmonth == NULL || pday == NULL)		//��ָ����г�ʼ����һ�����366��
	{
		*pmonth = 0;
		*pday = 0;
		return;
	}

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main()
{
	int m, d;
	int i = day_of_year(2019, 6, 26);
	month_day(2019, 177, &m, &d);
	printf("%d\r\n", i);
	printf("�£�%d�գ�%d\r\n", m, d);
	system("pause");
}