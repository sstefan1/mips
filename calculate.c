#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float* calculate(char *, int *, int *);

int main(){
	
	char buffer[10];

	scanf("%s", buffer);

	int a, b;

	float* rez = calculate(buffer, &a, &b);

	printf("rezultat je: %.2f\n", *rez);

	return 0;
}

float* calculate(char *buffer, int *a, int *b){
	char operacija;
	char *_operand1;
	char* _operand2;

	int operand1, operand2;

	_operand1 = malloc(4*sizeof(char));

	memcpy(_operand1, buffer+1, sizeof(int));
	_operand2 = (buffer + 5);

	operand1 = atoi(_operand1);
	free(_operand1);
	operand2 = atoi(_operand2);

	operacija = buffer[0];

	float *rez = malloc(sizeof(float));

	switch(operacija){
		case '0':
			*rez = operand1 + operand2;
			break;
		case '1':
			*rez = operand1 - operand2;
			break;
		case '2':
			*rez = operand1 * operand2;
			break;
		case '3':
			*rez = (float)operand1 / operand2;
			break;
	}

	return rez;

}