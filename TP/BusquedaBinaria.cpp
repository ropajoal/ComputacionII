#include <iostream>
#include <time.h>
#include <conio.h>
#define N 100
#define LIMIT 1000

using namespace std;

struct GlobulosRojos{
	int ubicacion;
	float conteo;
	GlobulosRojos(){}
	GlobulosRojos(int u, float c){
		ubicacion = u;
		conteo = c;
	}
};

//Funcion intercambiar para intercambiar los valores de entre dos posiciones de un array de cualquier tipo de dato
template <typename T>
void intercambiar(T& a, T& b){
	T aux;
	aux = a;
	a = b;
	b = aux;
}

//Metodo de ordenación quickSort adaptado a ordenar un array de GlobulosRojos segun el conteo de globulos rojos
void quickSort(GlobulosRojos array[], int ultimo, int primero=0){
	int i, j, central;
	float pivote;	
	central = (primero + ultimo)/2;
	pivote = array[central].conteo;
	i=primero;
	j=ultimo;
	do{
		while(array[i].conteo<pivote)i++;
		while(array[j].conteo>pivote)j--;
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

//Método BusquedaBinaria adaptado a buscar un valor clave en un arreglo de tipo de dato GlobulosRojos
int busquedaBinaria(GlobulosRojos array[], int n, float clave){
	int central, bajo, alto;
	float valorCentral;
	bajo = 0;
	alto = n-1;
	while(bajo <= alto){
		central = (bajo+alto)/2;
		valorCentral = array[central].conteo;
		if(clave==valorCentral)
			return central;
		else if(clave < valorCentral)
			alto = central - 1;
		else
			bajo = central + 1;
	}
	return -1;
}

int main(){
	srand(time(NULL));
	GlobulosRojos globulosRojos[N];

	//Rellena el array globulosRojos en donde se registra la ubicación de la muestra y el conteo
	for(int i=0;i<N;i++)
		globulosRojos[i]=GlobulosRojos(i+1,(((float)(rand()%LIMIT))/100));

	//Muestra todo el array en el orden en que se fue creando 
	for(int i=0;i<N;i++)
		cout << globulosRojos[i].ubicacion << ":" << globulosRojos[i].conteo << " ";

	//Ordena el array con el metodo de ordenación quickSort
	quickSort(globulosRojos,N-1);

	//Obtiene la posicion en que fue registrado en el arreglo el numero 4.7 y dependiendo si lo encuentra o no se va a mostrar un mensaje con su resultado
	int posicion = busquedaBinaria(globulosRojos,N,4.7);
	if(posicion >= 0)
		cout <<endl<<"El numero 4.7 esta en la ubicacion: "<< globulosRojos[posicion].ubicacion;
	else
		cout <<endl<<"El numero 4.7 no esta dentro del arreglo";

	//Pausa para ver el resultado si se ejecuta desde explorer
	cout <<endl<< "Presione cualquier tecla para salir... ";
	getch();
}

