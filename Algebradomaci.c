#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 100

//spisak deklaracija funkcija
void getMinor(double[MAX][MAX],double[MAX][MAX],int,int,int);
double Det(double[MAX][MAX],int);
void transpMatrix(double[MAX][MAX],double[MAX][MAX],int);
void matrixInput(double[MAX][MAX],int);
void printMatrix(double[MAX][MAX],int);
double getCofactor(double[MAX][MAX],int, int, int);
void adjMatrix(double[MAX][MAX],double[MAX][MAX],int);
int invMatrix(double[MAX][MAX],double[MAX][MAX],int);
int dimInput();



int main()
{
	double x;
	int dim,n; // n - da se cekira da li matrica ima inv matricu
	double matrix[MAX][MAX];
	double invmatrix[MAX][MAX];	
 
	printf("Unesite neki prirodan broj kako bi ste nastavili: ");
	scanf("%lf",&x);
	
pocetak:	

	dim = dimInput();
	
	printf("\nUnesite clanove matrice:\n");
	
	matrixInput(matrix,dim);
	
	printf("\nUneta matrica:\n");
	printMatrix(matrix,dim);
		
	double det = Det(matrix,dim);
	printf("\ndet(A) = %.2lf\n",det);
	
    invMatrix(invmatrix,matrix,dim);
    
    if(det == 0) printf("\nMatrica nema inverznu matricu!\n");
    else
    {	
       printf("\nInverzna matrica unete matrice je:\n");
	   printMatrix(invmatrix,dim);
    } 
    
    int c;
    printf("\nUnesite 0 ako hocete da izadjete iz programa ili bilo koji drugi broj ako hocete ponovo da pokrenete:\n");
    scanf("%d",&c);
    if (c != 0)
    {
      goto pocetak;	
	}
	else if (c == 0)
	{
		exit(EXIT_SUCCESS);
	}
    
    
	return 0;
}

int dimInput()
{
	int dim;
ponovni_unos:
	printf("\nUnesite dimenziju matrice: ");
	scanf("%d",&dim);
	
	if(dim>0 && dim<MAX)
	{
		return dim;
	}
	else
	{
		printf("Los unos dimenzije!\n");
		goto ponovni_unos;
	}
}

// uzima mionar na datoj poziciju
void getMinor(double minor[MAX][MAX], double matrix[MAX][MAX], int dim , int v, int k) // k je kolona koja ce se odstraniti v je vrsta koja ce se odstranitio
{
	int i,j;
	int n = 0,m = 0; // sluze za odredjivanje pozicije elemenata u novoj matrici minora
	double min[MAX][MAX];
	
	for(i=0; i<dim;i++)
	{
		n=0; // reset
		if(i == v) //proverava da li je ciljana vrsta jednaka brojacu u tom trenutku i ako jeste samo je preskace
		{
			continue;
		}
		for(j=0;j<dim;j++)
		{
			if(j == k)//slicno kao i za vrstu
			{
				continue;
			}
			min[m][n] = matrix[i][j];
			n++;
		}
		m++;
	}
	
	memcpy(minor,min,sizeof(double)*100*100);
}
//f-ja koja odredjuje determinantu
double Det(double matrix[MAX][MAX], int dim)
{
	if(dim == 1) return matrix[0][0]; //primalni uslov da bi se prekinula rekurzivna funkcija
	
	double det = 0;
	int k;
	
	for(k=0;k<dim;k++)
	{
		double minor[MAX][MAX]; // za dati element nadje mu minor 
		double sign = k%2 ? -1:1; // na osnovu toga da li je brojac paran ili ne odredjuje znak na parnim i neparnim mestima
		getMinor(minor,matrix,dim,0,k);
		
		det = det + matrix[0][k]*sign*Det(minor,dim-1);
	}
	
	return det;
}
//f-ja za unos matrice
void matrixInput(double matrix[MAX][MAX], int dim)
{
	int i,j;
	
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++)
		{
			printf("a[%d][%d]: ",i,j);
			scanf("%lf",&matrix[i][j]);
			if(matrix[i][j] == (-0)) matrix[i][j] = 0; // popravlja -0 na 0 prilikom upisa
		}
	}
}
//f-ja za ispis matrice
void printMatrix(double matrix[MAX][MAX],int dim)
{
	int i,j;
	
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++)
		{
			if (matrix[i][j] == (-0)) matrix[i][j] = 0; // popravka -0 na 0 prilikom ispisa
			if(matrix[i][j]<0)
			{
				printf("%.2lf",matrix[i][j]);
			}
			else printf(" %.2lf ",matrix[i][j]);
			if(j == dim-1)
			{
				printf("\n");
			}
		}
	}
}
//f-ja za transponovanu matricu
void transpMatrix(double transpmatrix[MAX][MAX], double matrix[MAX][MAX],int dim)
{
	int i,j;
	double tmatrix[MAX][MAX];
	
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++)
		{
			tmatrix[j][i] = matrix[i][j];
		}
	}
	
	memcpy(transpmatrix,tmatrix,sizeof(double)*100*100);
}
//prakticno izracunava determinantu minora na datoj poziciji
double getCofactor(double matrix[MAX][MAX], int dim, int n, int m) // m i n pozicija clana ciljanog kofaktora
{
    if(dim == 1) return matrix[0][0]; 
    
    double cof = 0;
    double minor[MAX][MAX];
    double sign = ((n+m)%2) ? -1: 1;
    getMinor(minor,matrix,dim,n,m);
    cof = sign*Det(minor,dim-1);
    
    if(cof == -0) return cof = 0; //da pri ispisu ne bi izbaciva -0 zbog bitnog zapisa 0
    
    
    return cof;
}
//f-ja za adjungovanu matrica
void adjMatrix(double adjMatrix[MAX][MAX],double matrix[MAX][MAX],int dim)
{
	int i,j;
	double adjmatrix[MAX][MAX];
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim;j++)
		{
			adjmatrix[i][j] = getCofactor(matrix,dim,i,j); 
		}	
	}
	
	memcpy(adjMatrix,adjmatrix,sizeof(double)*100*100);
}
//f-ja za inverznu matricu 
int invMatrix(double invMatrix[MAX][MAX],double matrix[MAX][MAX],int dim)
{
	double det = Det(matrix,dim);
	if(det == 0) return 0;
	
	int i,j;
	double adjmatrix[MAX][MAX];
	adjMatrix(adjmatrix,matrix,dim); // nadjena adjungovana matrica
	double invmatrix[MAX][MAX];
	transpMatrix(invmatrix,adjmatrix,dim); //transponovana adjungovana matrica
	
	for(i=0;i<dim;i++) // 1/detA * adjungovana transponovana matrica
	{
		for(j=0;j<dim;j++)
		{
			invmatrix[i][j]*= (1/det);
		}
	}
	
	memcpy(invMatrix,invmatrix,sizeof(double)*100*100);
	return 1;
}


 

