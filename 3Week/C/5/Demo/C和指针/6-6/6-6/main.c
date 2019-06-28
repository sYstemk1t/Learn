#define MAX 1000001

int Eratosthenes(char[], int max);

int main()
{
	int i;
	int sum = 0;
	int count = 0;
	char prime[MAX];
	int max;
	for (i = 1; i < MAX; i++)
		prime[i] = 1;

	for (max = 1000; max < MAX; max += 1000){
		count = Eratosthenes(prime, max) - sum;
		printf("%d\t%d\n", max, count);
		sum += count;
	}
	system("pause");
}

int Eratosthenes(char prime[], int max)
{
	int count = 0;
	int i = 0;
	int i_p;
	int j;
	int j_p;

	for (i = 1; i < max; i++)
		prime[i] = 1;

	for (i = 1; i < max; i++){
		if (prime[i] == 1){
			i_p = 2 * i + 1;
			for (j = 2 * i_p; j < max * 2 + 1; j += i_p)
				if (j % 2 == 1 && prime[(j - 1) / 2] == 1){
					j_p = (j - 1) / 2;
					prime[j_p] = 0;
					count++;
				}
		}
	}
	return count;
}