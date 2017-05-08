#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* CalculateArray(char* );

char rez[8] = {0};

int main ()
{
    char buffer[50];
    char* pok;
    int i;

    printf ("Unesi niz: ");
    gets (buffer);

    pok = CalculateArray(buffer);

    for (i = 0; i <  8; i++) {
        printf ("%c", pok[i]);
    }

    return 0;
}

char* CalculateArray(char* buffer)
{
    int i, duzina;
    int temp = 0;

    duzina = ((int)buffer[0]-48)*1000 + ((int)buffer[1]-48)*100 + ((int)buffer[2]-48)*10 + ((int)buffer[3]-48);

    for (i = 4; buffer[i] != '\0'; i++) {
        temp++;
    }

    if (duzina != temp) {
        printf("Nije validan.\n");
        return 0;
    }

    float prosek;
    int suma = 0;

    for (i = 0; i < duzina; i++){
        suma += (int)buffer[i+4]-48;
    }

    prosek = (float)suma/duzina;









    printf("Suma je %d.\n", suma);                        /// Proba
    printf("Prosek je %.2f.\n", prosek);                    /// Proba

    char ssuma[4];
    char pprosek[4];

    sprintf(ssuma, "%i", suma);
    sprintf(pprosek, "%f", prosek);

    printf("SSuma je %s.\n", ssuma);                      /// Proba
    printf("PProsek je %s.\n", pprosek);                  /// Proba

    strcat(rez, pprosek);
    strcat(rez, ssuma);

    return rez;
}
