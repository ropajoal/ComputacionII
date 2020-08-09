#include <iostream>
#include <time.h>
#define N 100
#define LIMIT 2000

using namespace std;

void ordInsercion(int[],int);

int main(){
	srand(time(NULL));
	int alumnos[N];
	for(int i=0;i<N;i++)alumnos[i]=rand()%LIMIT;
	ordInsercion(alumnos,N);
	for(int i=0;i<N;i++)cout<<alumnos[i]<<" ";
}

void ordInsercion(int array[], int n){
	int i, j, aux;
	for(int i=0;i<n;i++){
		j=i;
		aux=array[i];
		while(j>0&&aux<array[j-1]){
			array[j] = array[j-1];
			j--;
		}
		array[j]=aux;
	}
}