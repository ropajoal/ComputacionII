#include <iostream>
#include <conio.h>
#include <time.h>
#define MAX 35
#define MIN 15

using namespace std;

//Estructura de dato Alumno que contiene numero de Alumno y su peso
struct Alumno{
	int numero,peso;
	Alumno(){}
	Alumno(int n, int p){
		numero = n;
		peso = p;	
	}
};

//Metodo de ordenacion de Insercion adaptada a ordenar un array de tipo de dato Alumno por su atributo peso
void ordInsercion(Alumno array[], int n){
	int i, j;
	Alumno aux;
	for(int i=0;i<n;i++){
		j=i;
		aux=array[i];
		while(j>0 && (aux.peso < array[j-1].peso) ){
			array[j] = array[j-1];
			j--;
		}
		array[j]=aux;
	}
}

int main(){
	srand(time(NULL));
	int N;

	cout <<"Ingrese numero de alumnos a procesar: ";
	cin >> N;
	Alumno alumnos[N];

	//Puebla el array alumnos entre un rango de maximo y un mínimo
	for(int i=0;i<N;i++)alumnos[i]= Alumno(i+1,(rand()%(MAX + 1 - MIN))+MIN);

	//Muestra los numeros de los alumnos junto con sus respectivos pesos
	cout <<"Pesos de alumnos a ordenar:" <<endl;
	for(int i=0;i<N;i++)cout<<alumnos[i].numero<<":"<<alumnos[i].peso<<" ";
	cout << endl;

	//Ordena a los Alumnos por sus respectivos pesos mediante el metodo de Insercion
	ordInsercion(alumnos,N);

	//Muestra a todos los alumnos ya ordenados por sus pesos 
	cout <<"Pesos ordenados de alumnos:"<<endl;
	for(int i=0;i<N;i++)cout<<alumnos[i].numero<<":"<<alumnos[i].peso<<" ";
	
	//Pausa para ver el resultado si se ejecuta desde explorer
	cout <<endl<< "Presione cualquier tecla para salir... ";
	getch();
}

