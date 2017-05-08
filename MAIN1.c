#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* CalculateArray(char* );

int main ()
{
    char buffer[50];
    char* rez;
    int i;

    printf ("Unesi niz: ");
    gets (buffer);

    rez = CalculateArray(buffer);

    puts(rez);

    printf("\n");
    
    for (i=0; i<8; i++) {
        printf ("%c", rez[i]);
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

    //cout << "Duzina je " << duzina << endl;

    printf("Duzina je: %d\n", duzina);

    if (duzina == temp) {
        printf("Validan niz.\n");
    } else {
        printf("Niz nije validan. Nije dobar broj karaktera u nizu kao sto je zadato na pocetku.\n");
        return 0;
    }

    /// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float prosek;
    int suma = 0;

    for (i = 0; i < duzina; i++) {
        suma += (int)(buffer[i+4]-48);
    }

    printf("Suma je: %d\n", suma);

    prosek = (float)suma/duzina;

    //cout << "Prosek je " << prosek << endl;

    printf("Prosek je: %f\n", prosek);


    char *rez = (char*)malloc(8*sizeof(char));
    char ssuma[4];
    char pprosek[4];

    sprintf(ssuma, "%d", suma);
    sprintf(pprosek, "%.2f", prosek);

    strcat(rez, pprosek);
    strcat(rez, ssuma);

    return rez;
}
