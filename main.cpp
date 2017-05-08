#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float rez;

float* Calculate (char* buffer)
{
	int o, a, b, i;
	int num[8];

	for (i = 0; i <= 8; i++) {
		num[i] = (int)buffer[i]-48;
	}


	o = num[0];
	a = num[1]*1000 + num[2]*100 + num[3]*10 + num[4];
	b = num[5]*1000 + num[6]*100 + num[7]*10 + num[8];

	if (o == 0) {
		rez = a+b;
	}
	else if (o == 1) {
		rez = a-b;
	}
	else if (o == 2) {
		rez = a*b;
	}
	else if (o == 3) {
		rez = (float)a/b;
	}
	else {
		printf ("Greska!\n");
		return 0;
	}

    printf ("Prvi operand je %d.\n", a);
    printf ("Drugi operand je %d.\n", b);

	return &rez;
}

int main ()
{
	char buffer[9];
	float *temp;

	printf("Unesi string: ");
    scanf("%s", buffer);

	buffer[9] = '\0';

	temp = Calculate(buffer);

	printf ("Rezultat je: %f\n", *temp);

	return 0;
}
