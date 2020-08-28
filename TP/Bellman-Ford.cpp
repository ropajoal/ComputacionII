#include <iostream>
#include <conio.h>
#define INFINITO 0x3f3f3f3f
using namespace std;

//Tipo de dato Vertice en el que asocia su nombre de vertice con su número de vertice
class Vertice{
	private:
		string nombre;
		int numVertice;
	public:
		Vertice(){}
		Vertice(string nom){
			nombre = nom;
			numVertice = -1;
		}
		Vertice(string nom, int n){
			nombre = nom;
			numVertice = n;
		}
		string obtenerNomVertice(){
			return nombre;
		}
};

//Tipo de dato GrafoMatriz en el que internamente almacena un listado de vertices el que se relacionan mediante su matriz adyacente
class GrafoMatriz{
	private:
		int maxVerts;
		int numVerts;
		Vertice * verts;
		int ** matAd;
	public:
		GrafoMatriz(){
			maxVerts = 1;
			GrafoMatriz(maxVerts);
		}

		//Constructor de GrafoMatriz en el que recibe un número entero para crear los límites de la matriz de adyacencia 
		//Una vez inicializada la matriz inicializa todos los valores de la matriz a un valor muy grande en este caso la constante definida como INFINITO
		GrafoMatriz(int max){
			maxVerts = max;
			verts = new Vertice[max];
			numVerts = 0;
			matAd = new int * [max];
			for (int i=0;i<max;i++){
				matAd[i] = new int [max];
				for(int j=0;j<max;j++){
					matAd[i][j] = INFINITO;
				}
			}
		}

		//Crea un nuevo vertice y lo almacena en el array verts
		void nuevoVertice(string nombre){			
			if(numVertice(nombre) < 0){
				Vertice v = Vertice(nombre, numVerts);
				verts[numVerts++] = v;
			}
		}
		
		//Obtiene los nombres de los vertices para que ellos obtener sus numeros de vertice y crear un nuevo arco
		void nuevoArco(string nomVert1, string nomVert2, int valor){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			nuevoArco(v1,v2,valor);
		}

		//Registra en la matriz de adyacencia la ponderación de la relación entre dos vertices 
		void nuevoArco(int v1, int v2, int valor){
			if (v1 < 0 || v2 < 0 || v1 > numVerts || v2 > numVerts) throw "Vertice no existe";
			else matAd[v1][v2] = matAd[v2][v1] = valor;
		}

		//Retorna el numero de vertices que almacena actualmente el array de Vertices verts
		int obtenerNumeroDeVertices(){
			return numVerts;
		}

		//Busca dentro del array verts el vertice con el nombre buscado y retorna su numero de vertice
		int numVertice(string nombre){
			int i = 0;
			bool encontrado = false;
			while((i<numVerts) && (!encontrado)){
				encontrado = (nombre == verts[i].obtenerNomVertice());
				if(!encontrado)i++;
			}
			return (i < numVerts) ? i : -1;
		}

		//Obtiene los numero de vertice a partir de sus nombres y luego llama a la funcion que retorna la ponderación entre sus vertices	
		int obtenerValor(string nomVert1, string nomVert2){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			return obtenerValor(v1,v2);
		}

		//Retorna la ponderacion de la relacion entre dos vertices
		int obtenerValor(int v1, int v2){
			if (v1 < 0 || v2 < 0 || v1 >= numVerts || v2 >= numVerts) throw "Vertice no existe";
			else return matAd[v1][v2];
		}

		//Obtiene el numero de vertice a partir del nombre del vertice y llama a la funcion que retorna el vertice al darle el numero de vertice
		Vertice obtenerVertice(string nomVert){
			return obtenerVertice(numVertice(nomVert));
		}

		//Retorna el vertice a partir de su numero de vertice
		Vertice obtenerVertice(int v){
			if(v < 0 || v >= numVerts) throw "Vertice no existe";
			else return verts[v];
		}
};

//Tipo de dato Pila para construir los caminos cortos
class Pila{
	private:
		class Nodo{
			private:
				int dato;
				Nodo* enlace;				
			public:
				Nodo(int num){
					dato = num;
					enlace = NULL;
				}
				int obtenerDato(){return dato;}
				Nodo* obtenerEnlace(){return enlace;}
				void establecerDato(int d){dato = d;}
				void establecerEnlace(Nodo* link){enlace = link;}
		};
		Nodo* cima;
		int length;
	public:
		Pila(){cima = NULL; length = 0;}
		int obtenerCantidadElementos(){return length;}
		void insertar(int dato){
			Nodo* nuevo;
			nuevo = new Nodo(dato);
			nuevo->establecerEnlace(cima);
			cima = nuevo;
			length++;
		}
		int sacar(){
			int ext = cima->obtenerDato();
			Nodo* a = cima;
			cima = cima->obtenerEnlace();				
			delete a;
			length--;
			return ext;
		}
};

//Algoritmo para buscar caminos mínimos a partir de un vertice inicial, aunque no es el algoritmo mas eficaz para esta tarea este algoritmo acepta ponderaciones negativas
void bellmanFord(GrafoMatriz grafo, int vertIni){

	int numVertices = grafo.obtenerNumeroDeVertices();
	int dist[numVertices];
	int prev[numVertices];
	Pila camino;
	
	//Inicializa todos los valores del array dist a la constante INFINITO y al array prev a -1
	for(int i=0; i<numVertices; i++){
		dist[i]=INFINITO;
		prev[i]=-1;
	}

	//Inicializa la posición del vertice inicial a 0 
	dist[vertIni] = 0;

	//Para cada vertice se le aplica "relajacion" para cada una de las aristas
	for (int k = 0; k < numVertices - 1; k++)
		for (int i = 0; i < numVertices; i++)		
			for (int j = 0; j < numVertices; j++)
				if((dist[i] + grafo.obtenerValor(i,j)) < dist[j]){
					dist[j] = dist[i] + grafo.obtenerValor(i,j);
					prev[j] = i;
				}

	//Se aplica una segunda vez el algoritmo para detectar ciclos negativos	
	for (int k = 0; k < numVertices - 1; k++)
		for (int i = 0; i < numVertices; i++)
			for (int j = 0; j < numVertices; j++)
				if(dist[i] + grafo.obtenerValor(i,j) < dist[j]){
					dist[j] = -INFINITO;
					prev[j] = -2;
				}
	
	//Empieza a imprimir por pantalla los caminos
	for (int i=0; i<numVertices; i++){
		cout << "El camino mas corto entre el vertice "<<grafo.obtenerVertice(vertIni).obtenerNomVertice()<< " y el vertice " <<grafo.obtenerVertice(i).obtenerNomVertice()<<" es: ";
	
		//Por cada vertice se carga todo el camino previo en la Pila camino mediante el array prev
		int en;
		for (en = i; prev[en] >= 0; en = prev[en]){
			camino.insertar(en);
		}
		camino.insertar(vertIni);

		//Si hay un ciclo negativo en el vertice previo al vertice que se actual entonces imprime por pantalla Numro infinito de caminos
		if(prev[en] == -2){
			cout << "Numero infinito de caminos"<<endl;
		}
		else{

			//Se vacia la Pila camino a su vez que los datos extraídos de la pila se van mostrando por pantalla, creando el efecto de mostrar todo el camino hasta el vertice deseado.
			//A la final se muestra la distancia recorrida
			for(int j = 0, n=camino.obtenerCantidadElementos(); j < n-1;j++){
				cout << grafo.obtenerVertice(camino.sacar()).obtenerNomVertice() << " -> ";
			}
			cout << grafo.obtenerVertice(camino.sacar()).obtenerNomVertice()<<". Con un coste de: "<<dist[i]<<endl;
		}
	}
}

//Obtiene el numero de vertice a partir del nombre del vertice para luego llamar a la función que muestra por pantalla todos los caminos minimos a todos los vertices a partir del vertice inicial
void bellmanFord(GrafoMatriz grafo, string nomVert){
	bellmanFord(grafo, grafo.numVertice(nomVert));
}

int main(){
	
	//Construcción del grafo que se desea obtener los caminos cortos
	GrafoMatriz grafo(8);
	grafo.nuevoVertice("A");
	grafo.nuevoVertice("B");
	grafo.nuevoVertice("C");
	grafo.nuevoVertice("D");
	grafo.nuevoVertice("E");
	grafo.nuevoVertice("F");
	grafo.nuevoVertice("G");
	grafo.nuevoVertice("S");
	grafo.nuevoArco("A","B",12);
	grafo.nuevoArco("A","E",5);
	grafo.nuevoArco("B","E",9);
	grafo.nuevoArco("B","S",6);
	grafo.nuevoArco("B","D",1);
	grafo.nuevoArco("E","D",4);
	grafo.nuevoArco("E","F",2);
	grafo.nuevoArco("E","G",1);
	grafo.nuevoArco("S","D",8);
	grafo.nuevoArco("S","C",6);
	grafo.nuevoArco("D","C",4);
	grafo.nuevoArco("D","F",3);
	grafo.nuevoArco("C","F",8);
	grafo.nuevoArco("F","G",4);

	//Se llama a la funcion bellmanFord para que muestre por pantalla los caminos minimos del grafo que parte de un vertice inicial
	bellmanFord(grafo,"S");

	//Pausa para ver el resultado si se ejecuta desde explorer
	cout <<endl<< "Presione cualquier tecla para salir... ";
	getch();
}
