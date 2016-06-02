#include <stdio.h>
#include <stdlib.h>


int main()
{

	
	int i = 0;
	float valores[4];
	int contador = 0;
	float resul = 0;

	while (contador != 4) {
		printf("Introduce el valor de los numeros a sumar: ");
		scanf("%f", &valores[i]);
		contador++;
		i++;
	}

	

	printf("\nHas introducido %i numeros\n", contador);
	for (int i = contador; i > 0; i--) {
		printf("\nEl valor de N es: %f\n", valores[i-1]);	
	}
	for (int k = contador-1; k > 0; k--) {
		resul = valores[k - 1] + 1 / (valores[k]);
	printf("\nOperacion%i:\t%f\n\n", k, resul);
		
	}
	
	
	
	
    return 0;
}

