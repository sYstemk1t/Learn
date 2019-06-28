
#include <stdio.h>

#define MAX 1001
void Eratosthenes(char[]);

int main()
{
	int i;
	int count = 0;
	char prime[1001];
	for (i = 1; i < MAX; i++)
		prime[i] = 1;

	printf("the prime range is 2 to %d\n", MAX * 2 + 1);
	Eratosthenes(prime);
	printf("2\n");
	for (i = 1; i < MAX; i++){
		if (prime[i] == 1){
			printf("%d ", i * 2 + 1);
			count++;
		}
		if (count % 10 == 0)
			printf("\n");
	}
	system("pause");
}

void Eratosthenes(char prime[])
{
	int i = 0;
	int i_p;
	int j;
	int j_p;
	for (i = 1; i < MAX; i++){
		if (prime[i] == 1){
			i_p = 2 * i + 1;
			for (j = 2 * i_p; j < MAX * 2 + 1; j += i_p)
				if (j % 2 == 1){
					j_p = (j - 1) / 2;
					prime[j_p] = 0;
				}
		}
	}
}
