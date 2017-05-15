#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5


void kopirajm(int matrix1[N][N], int matrix2[N][N]){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			matrix2[i][j]=matrix1[i][j];
		}
	}
}

int brNula(int m[N][N], int row){
	int i, j, nule;

	nule=0;

	for(i=0; i<N; i++){
		if(m[row][i]==0){
			nule++;
		}
		
	}

	return nule;
}

void printn(int *niz, int n){
	int i;

	for(i=0; i<n; i++){
		printf("%d ", niz[i]);
	}
}

void printm(int m1[N][N]){
	int i, j;
	for(i=0; i<N; i++){
		for (j=0; j<N; j++){
			printf("%d ", m1[i][j]);
		}
		printf("\n");
	}
}

void rand_matrica(int m1[N][N]){
	srand(time(NULL));
	int i, j;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			int r=rand()%100;
			m1[i][j]=r;
		}
	}
}

int min_row(int matrix[N][N], int row){
	int i;
	int min=matrix[row][0];

	for(i=0; i<N; i++){
		if(matrix[row][i]<min){
			min=matrix[row][i];
		}
	}

	return min;
}

int min_col(int matrix[N][N], int col){
	int i;
	int min=matrix[0][col];

	for(i=0; i<N; i++){
		if(matrix[i][col]<min){
			min=matrix[i][col];
		}
	}

	return min;
}

void sub_row(int matrix[N][N]){
	int i, j, min;
	//min = min_row(matrica, 0);

	for(i=0; i<N; i++){
		min = min_row(matrix, i);
		for(j=0; j<N; j++){
			matrix[i][j]-=min;
		}
		//min = min_row(matrica, i+1);
	}
}

void sub_col(int matrix[N][N]){
	int i, j, min;

	for(j=0; j<N; j++){
		min = min_col(matrix, j);
		for(i=0; i<N; i++){
			matrix[i][j]-=min;
		}
	}
}

int hvMax(int m1[N][N], int row, int col){
	int i, horizontalno, vertikalno;

	horizontalno=0;
	vertikalno=0;
	//int col1=col;
	//int row1=row1;
	//broj nula u vrsti:

	for(i=0; i<N; i++){
		if(m1[row][i]==0){
			horizontalno++;
		}
	}
	//broj nula u koloni
	for(i=0; i<N; i++){
		if(m1[i][col]==0){
			vertikalno++;
		}
	}

	if(vertikalno>horizontalno){
		return vertikalno;
	}else if(horizontalno>vertikalno){
		return horizontalno * -1;
	}else if(horizontalno==0 && vertikalno==0){
		return 0;
	}else{
		return vertikalno;
	}
}

int hvMax2(int m1[N][N], int row, int col){
	int i, horizontalno, vertikalno;

	horizontalno=0;
	vertikalno=0;
	//int col1=col;
	//int row1=row1;
	//broj nula u vrsti:

	for(i=0; i<N; i++){
		if(m1[row][i]==0){
			horizontalno++;
		}
	}
	//broj nula u koloni
	for(i=0; i<N; i++){
		if(m1[i][col]==0){
			vertikalno++;
		}
	}

	if(vertikalno>horizontalno){
		return vertikalno;
	}else if(horizontalno>vertikalno){
		return horizontalno * -1;
	}else if(horizontalno==0 && vertikalno==0){
		return 0;
	}else{
		return horizontalno * -1;
	}
}

int proveri_matricu(int m1[N][N]){
	int i, j, nule;

	nule=0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m1[i][j]==0){
				nule++;
			}
		}
	}

	if (nule<=N){
		return 1;
	}else{
		return 0;
	}
}

void ispravi_matricu(int m[N][N]){
	int i, j, k;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m[i][j]>0){
				for (k=0; k<N; k++){
					if(m[k][j]==m[i][j] && k!=i){
						m[k][j]=0;
					}
				}
			}else if(m[i][j]<0){
				for(k=0; k<N; k++){
					if(m[i][k]==m[i][j] && k!=j){
						m[i][k]=0;
					}
				}
			}
		}
	}
}

void iscrtaj(int m1[N][N], int m2[N][N], int m3[N][N], int *broj_linija){
	int i, j, k;
	int brLinija=0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m1[i][j]==0){
				m2[i][j]=hvMax(m1, i, j);
			}else{
				m2[i][j]=0;
			}
		}
	}

	ispravi_matricu(m2);

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m2[i][j]>0){
				brLinija++;
				for (k=0; k<N; k++){
					m3[k][j]+=1;
				}
			}else if(m2[i][j]<0){
				brLinija++;
				for(k=0; k<N; k++){
					m3[i][k]+=1;
				}
			}
		}
	}

	*broj_linija=brLinija;
}

void iscrtaj2(int m1[N][N], int m2[N][N], int m3[N][N], int *broj_linija){
	int i, j, k;
	int brLinija=0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m1[i][j]==0){
				m2[i][j]=hvMax2(m1, i, j);
			}else{
				m2[i][j]=0;
			}
		}
	}

	ispravi_matricu(m2);

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m2[i][j]>0){
				brLinija++;
				for (k=0; k<N; k++){
					m3[k][j]+=1;
				}
			}else if(m2[i][j]<0){
				brLinija++;
				for(k=0; k<N; k++){
					m3[i][k]+=1;
				}
			}
		}
	}

	*broj_linija=brLinija;
}

void niz_init(int *niz_nule, int n){
	int i=0;

	for(i=0; i<n; i++){
		niz_nule[i]=0;
	}
}

int prebroj_nule_row(int m1[N][N], int i){
	int nule, j;

	nule=0; 

	for(j=0; j<N; j++){
		if (m1[i][j]==0){
			nule++;
		}
	}

	return nule;
}

int prebroj_nule_col(int m1[N][N], int j){
	int nule, i;

	nule=0; 

	for(i=0; i<N; i++){
		if (m1[i][j]==0){
			nule++;
		}
	}

	return nule;
}

void precrtaj_nule_col(int m1[N][N], int row, int col){
	int i;

	for(i=0; i<N; i++){
		if(m1[i][col]==0 && i!=row){
			m1[i][col]=-1;
		}
	}
}

void precrtaj_nule_row(int m1[N][N], int row, int col){
	int i;

	for(i=0; i<N; i++){
		if(m1[row][i]==0 && i!=col){
			m1[row][i]=-1;
		}
	}
}

void proveri_nule_linije(int m1[N][N], int *dodeljeni_row, int *tickRow){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m1[i][j]==0 && dodeljeni_row[i]==0){
				dodeljeni_row[i]=j+1;
				tickRow[i]=1;
			}
		}
	}
}

void linije(int m1[N][N], int m3[N][N], int *broj_linija){
	int i, j, k;

	(*broj_linija)=0;

	int tickRow[N], tickCol[N], dodeljeni_row[N], dodeljeni_col[N];

	niz_init(tickRow, N);
	niz_init(tickCol, N);
	niz_init(dodeljeni_row, N);
	niz_init(dodeljeni_col, N);

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m1[i][j]==0 && prebroj_nule_row(m1, i)==1){
				tickRow[i]=1;
				dodeljeni_row[i]=j+1;
				//dodeljeni_col[j]=i+1;
				precrtaj_nule_col(m1, i, j);
				continue;
			}
		}
	}

	for(j=0; j<N; j++){
		for(i=0; i<N; i++){
			if(m1[i][j]==0 && dodeljeni_row[i]!=j+1 &&  prebroj_nule_col(m1, j)==1){
				dodeljeni_row[i]=j+1;
				tickRow[i]=1;
				precrtaj_nule_row(m1, i, j);
				continue;
			}/*else if(m1[i][j]==0){
				m1[i][j]=-1;
			}*/
		}
	}

	proveri_nule_linije(m1, dodeljeni_row, tickRow);

	for(i=0; i<N; i++){
		if(tickRow[i]==1){
			tickRow[i]=0;
		}else if(tickRow[i]==0){
			tickRow[i]=1;
		}
	}

	for(i=0; i<N; i++){
		if(tickRow[i]==1){
			for(j=0; j<N; j++){
				if(m1[i][j]==-1){
					tickCol[j]=1;
					for(k=0; k<N; k++){
						if(dodeljeni_row[k]==j+1){
							tickRow[k]=1;
						}
					}
				}
			}
		}
	}

	for(i=0; i<N; i++){
		if(tickRow[i]==0){
			(*broj_linija)++;
			for(j=0; j<N; j++){
				m3[i][j]+=1;
			}
		}
	}

	for(i=0; i<N; i++){
		if(tickCol[i]==1){
			(*broj_linija)++;
			for(j=0; j<N; j++){
				m3[j][i]+=1;
			}
		}
	}
}

void matrica_init(int matrica[N][N]){
	int i, j;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			matrica[i][j]=0;
		}
	}
}

int zauzeta(int *niz_nule, int col){
	int i;

	for(i=0; i<N; i++){
		if(niz_nule[i]==col){
			return 1;
		}
	}
	return 0;
}

int ponavljanje(int *niz_nule){
	int i, ponavljanje;

	ponavljanje=0;

	for(i=0; i<N; i++){
		if(zauzeta(niz_nule, niz_nule[i])==1){
			return ponavljanje + 1;
		}
	}
	return ponavljanje;
}

void find0row(int matrix[N][N], int *niz){
	int i, j, broj, kolona;
	kolona=0;

	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(matrix[i][j]==0 && brNula(matrix, i)==1){
					kolona=j+1;
					break;
			}else{
				kolona=0;
			}
			//niz[i]=kolona;
		}

		niz[i]=kolona;	
	}
}

void find0row2(int matrix[N][N], int *niz_nule){
	int i, j;

	for(i=0; i<N; i++){
		if(niz_nule[i]==0){
			for(j=0; j<N; j++){
				if(matrix[i][j]==0 && zauzeta(niz_nule, j+1)==0){
					niz_nule[i]=j+1;
				}
			}
		}
	}
}

void dodeljeni(int *niz, int n){
	int i, j, prvi, ponavljanje;

	for(i=0; i<n; i++){
		prvi = niz[i];
		for(j=i+1; j<n; j++){
			if(prvi==niz[j]){
				niz[j]=0;
			}
		}
	}
}

int min_neoznacen(int m1[N][N], int m3[N][N]){
	int i, j, min;

	min=0;

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m3[i][j]==0 && min==0){
				min=m1[i][j];
			}else if(m3[i][j]==0 && m1[i][j]<min){
				min=m1[i][j];
			}
		}
	}

	return min;
}

//pored oduzimanja, funkcija dodaje min neoznacen svim elementima oznacenim sa 2 linije
void oduzmi_min_neoznacen(int m1[N][N], int m3[N][N]){
	int i, j, min;

	min=min_neoznacen(m1, m3);

	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(m3[i][j]==0){
				m1[i][j]-=min;
			}else if(m3[i][j]==2){
				m1[i][j]+=min;
			}
		}
	}
}

/*void niz_init(int *niz_nule, int n){
	int i=0;

	for(i=0; i<n; i++){
		niz_nule[i]=0;
	}
}*/

void min_assignement(int m1[N][N], int m2[N][N], int m3[N][N], int m4[N][N], int *niz_nule, int n, int *broj_linija, int *ispisano){
	int i, nule, suma;

	nule=0;
	suma=0;

	for(i=0; i<n; i++){
		if(niz_nule[i]==0){
			nule++;
		}
	}


	if(nule==0 && *broj_linija>=N /*&& ponavljanje(niz_nule)==0*/){
		printf("Resenje je nadjeno");
		for(i=0; i<n; i++){
			//int col=n[]
			printf("\nRadnik %d radi posao %d po ceni %d\n", i+1, niz_nule[i], m4[i][niz_nule[i]-1] );
			suma+=m4[i][niz_nule[i]-1];
			printf("suma je: %d\n\n", suma);
		}
		*ispisano=1;
	}else{
		//printf("resenje nije nadjeno\n");
		//oduzmi_min_neoznacen(m1, m3);
		//iscrtaj(m1, m2, m3, broj_linija);
		//min_assignement(m1, m2, m3, m4, niz_nule, N, broj_linija);

		*ispisano=0;
	}
}


int find0niz(int *niz_nule,int n){
	int i;

	int nule=0;

	for(i=0; i<n; i++){
		if(niz_nule[i]==0){
			nule++;
		}
	}
	return nule;
}

int main(){
	int m1[N][N], m2[N][N], m3[N][N], m4[N][N], m5[N][N];

	int niz_nule[N], niz1[N], niz2[N];

	niz_init(niz_nule, N);

	niz_init(niz1, N);

	niz_init(niz2, N);

	int broj_linija=0;
	
	int ispisano=0;

	int prolaz=0;

	matrica_init(m3);

	rand_matrica(m1);

	printm(m1);

	kopirajm(m1, m4);

	sub_row(m1);

	sub_col(m1);

	printf("\n");

	printm(m1);

	kopirajm(m1, m5);

	printf("\n");

	linije(m1, m3, &broj_linija);

	printm(m3);

	printf("\n");

	printf("BROJ LINIJA: %d\n", broj_linija);



	/*iscrtaj(m1, m2, m3, &broj_linija);

	printm(m2);

	printf("\n");

	printm(m3);

	//matrica_init(m3);

	//printm(m3);

	printf("\n");
	*/

	int k;

	for (k=0; k<N*N; k++){
		if(broj_linija>=N){
			find0row(m1, niz_nule);

			printn(niz_nule, N);

			printf("\n\n");

			find0row2(m1, niz_nule);

			printn(niz_nule, N);

			printf("\n\n");

			dodeljeni(niz_nule, N);

			printn(niz_nule, N);

			printf("\n\n");

			//if(prolaz%2==0){
			//	min_assignement(m1, m2, m3, m4, niz_nule, N, &broj_linija, &ispisano);
			//}

			min_assignement(m1, m2, m3, m4, niz_nule, N, &broj_linija, &ispisano);

			if(ispisano==1){
				break;
			}else{
			/*
				//oduzmi_min_neoznacen(m1, m3);

				matrica_init(m3);

				matrica_init(m2);

				//printf("\n");

				//printm(m1);

				//printf("\n\n");

				iscrtaj2(m1, m2, m3, &broj_linija);

				oduzmi_min_neoznacen(m1, m3);

				printf("BROJ LINIJA %d", broj_linija);

				printf("\n\n");

				printm(m3);

				//oduzmi_min_neoznacen(m1, m3);

				//matrica_init(m3);

				printf("\n\n");*/

				continue;
			}
		}else{
			//if (prolaz%2==0 && prolaz==0){
			kopirajm(m5, m1);

			oduzmi_min_neoznacen(m1, m3);

			matrica_init(m3);

			printf("\n");

			printm(m1);

			printf("\n\n");

				//iscrtaj(m1, m2, m3, &broj_linija);

			kopirajm(m1, m5);

			linije(m1, m3, &broj_linija);

			printf("\n\n");

			printm(m3);

				//matrica_init(m3);

			printf("\n\n");
			/*}else if(prolaz%2==0 && prolaz>0){
				kopiraj(m1, m4)
				oduzmi_min_neoznacen(m4, m3);

				matrica_init(m3);

				printf("\n");

				printm(m4);

				printf("\n\n");

				//iscrtaj(m1, m2, m3, &broj_linija);

				linije(m4, m3, &broj_linija)

				printf("\n\n");

				printm(m3);

				//matrica_init(m3);
			}
			else{
				kopiraj(m4, m1);

				oduzmi_min_neoznacen(m4, m3);

				matrica_init(m3);

				printf("\n");

				printm(m4);

				printf("\n\n");

				iscrtaj(m1, m2, m3, &broj_linija);

				printf("\n\n");

				printm(m3);

				//matrica_init(m3);

				printf("\n\n");
			}*/

			continue;
		}
	}

	return 0;
}