#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *CalculateArray(char*);

int main(){
	char *buffer, *result;

	printf("Unesite niz: \n");
	gets(buffer);

	result = CalculateArray(buffer);

	puts(result);

	free(result);

	return 0;
}

char *CalculateArray(char *buffer){
	char *numElements = malloc(sizeof(char));

	memcpy(numElements, buffer, sizeof(int));

	int size = atoi(numElements);

	free(numElements);

	buffer+=4;

	int sum, i;
	float average;

	i = 0;
	sum = 0;

	char *num = malloc(sizeof(char));

	while(i<size){
		memcpy(num, buffer++, sizeof(char));
		sum+=atoi(num);
		i++;
	}

	free(num);

	average = (float)sum/size;

	char *result = malloc(8*sizeof(char));
	char *sumStr;

	sprintf(result, "%.2f", average);
	sprintf(sumStr, "%d", sum);

	strcat(result, sumStr);

	return result;
}