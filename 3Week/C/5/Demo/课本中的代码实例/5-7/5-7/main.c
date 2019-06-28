#include <stdio.h>
static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	//非闰年
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	//闰年
};

int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;	//判断是否闰年
	for (i = 1; i < month; i++)
		day += daytab[leap][i];		//循环加，加到传递的月份，然后计算
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
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
	printf("月：%d日：%d\r\n", m, d);
	system("pause");
}