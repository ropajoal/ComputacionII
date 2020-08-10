#include <iostream>
#include <time.h>
#define N 100
#define LIMIT 1000

using namespace std;

void quickSort(float[],int,int=0);
int busquedaBinaria(float[],int,float);

int main(){
	srand(time(NULL));
	float globulosRojos[N];
	for(int i=1;i<N;i++)globulosRojos[i]=((float)(rand()%LIMIT))/100;
	quickSort(globulosRojos,N-1);
	for(int i=0;i<N;i++)cout<<globulosRojos[i]<<" ";
	cout <<endl<<"El numero 4.7 esta en la ubicacion: "<<busquedaBinaria(globulosRojos,N,4.7);
}

template <typename T>
void intercambiar(T& a, T& b){
	T aux;
	aux = a;
	a = b;
	b = aux;
}

void quickSort(float array[], int ultimo, int primero){
	int i, j, central;
	float pivote;	
	central = (primero + ultimo)/2;
	pivote = array[central];
	i=primero;
	j=ultimo;
	do{
		while(array[i]<pivote)i++;
		while(array[j]>pivote)j--;
		if(i<=j){
			intercambiar(array[i],array[j]);
			i++;
			j--;
		}
	}while (i <= j);
	if(primero < j){
		quickSort(array,j,primero);}
	if(i<ultimo){
		quickSort(array,ultimo,i);
	}
}

int busquedaBinaria(float array[], int n, float clave){
	int central, bajo, alto;
	float valorCentral;
	bajo = 0;
	alto = n-1;
	while(bajo <= alto){
		central = (bajo+alto)/2;
		valorCentral = array[central];
		if(clave==valorCentral)
			return central;
		else if(clave < valorCentral)
			alto = central - 1;
		else
			bajo = central + 1;
	}
	return -1;
}