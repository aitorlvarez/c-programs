#include <stdio.h>
#include <stdlib.h>


int main()
{


	int i = 0;
	double values[4];
	int count = 0;
	double result = 0;
	double result2 = 0;

	while (count != 4) {
		printf("Enter numbers: ");
		scanf("%lf", &values[i]);
		count++;
		i++;
	}

	/*printf("\nYou have entered %i numbers\n", count);                   //Descomentar para que se imprima el proceso
	for (int i = count; i > 0; i--) {
	printf("\nThe value of N is: %.2lf\n", values[i-1]);
	}*/
	for (int k = count - 1; k > 1; k--) {
		result = values[k - 1] + 1 / (values[k]);
		for (int j = count - 1; j > 0; j--) {
			result2 = values[j - 1] + 1 / result;
		}

	}
	printf("\nResult:\t%.2lf\n\n", result2);

	return 0;
}
