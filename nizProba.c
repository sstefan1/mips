#include<stdio.h>


int main(){
	long Niz[3];
	Niz[0] = Niz[1] = Niz[2] = 0x01020304;
	short *s = (short *)&Niz[1];
	char *ch = (char *)(s - 2);
	char *ch2 = (char *)&Niz[2];

	if(&ch[4] == (ch2-8)){
		printf("adrese se poklapaju!\n");
	}else{
		printf("nepoklapaju se\n");
	}

	printf("niz: %p\nch: %p\n&ch[4]: %p\n(ch-8): %p\nch2: %p\n", Niz, ch, &ch[4], (ch2-8), ch2);

	printf("%lu", sizeof(long long));

	return 0;
}

