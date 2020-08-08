//#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#define INFINITY 0x3f3f3f3f
using namespace std;

class Vertice{
	protected:
		string nombre;
		int numVertice;
	public:
		Vertice(){
			nombre = "none";
			numVertice = -1;
		}
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
		int obtenerNumVertice(){
			return numVertice;
		}
		void establecerNomVertice(string nom){
			nombre = nom;
		}
		void establecerNumVertice(int num){
			numVertice = num;
		}
		bool igual(Vertice vertice){
			return nombre == vertice.nombre;
		}
};

class GrafoMatriz{
	protected:
		int maxVerts;
		int numVerts;
		Vertice * verts;
		int ** matAd;
	public:
		GrafoMatriz(){
			maxVerts = 1;
			GrafoMatriz(maxVerts);
		}
		GrafoMatriz(int max){
			maxVerts = max;
			verts = new Vertice[max];
			numVerts = 0;
			matAd = new int * [max];
			for (int i=0;i<max;i++){
				matAd[i] = new int [max];
				for(int j=0;j<max;j++){
					matAd[i][j] = INFINITY;
				}
			}
		}
		int obtenerNumeroDeVertices(){
			return numVerts;
		}
		void estableceNumeroDeVertices(int n){
			numVerts = n;
		}
		int numVertice(string nombre){
			int i = 0;
			bool encontrado = false;
			while((i<numVerts) && (!encontrado)){
				encontrado = (nombre == verts[i].obtenerNomVertice());
				if(!encontrado)i++;
			}
			return (i < numVerts) ? i : -1;
		}
		void nuevoVertice(string nombre){
			
			if(numVertice(nombre) < 0){
				Vertice v = Vertice(nombre, numVerts);
				verts[numVerts++] = v;
			}
		}
		void nuevoArco(string nomVert1, string nomVert2, int valor){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			nuevoArco(v1,v2,valor);
		}
		void nuevoArco(int v1, int v2, int valor){
			//if (v1 < 0 || v2 < 0 || v1 > numVerts || v2 > numVerts) 
				//throw "Vertice no existe";
			matAd[v1][v2] = matAd[v2][v1] = valor;
		}
		bool adyacente(string nomVert1, string nomVert2){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			return adyacente(v1,v2);
		}
		bool adyacente(int v1, int v2){
			//if (v1 < 0 || v2 < 0 || v1 >= numVerts || v2 >= numVerts)
				//throw "Vertice no existe";
			return (bool)matAd[v1][v2];
		}
		int obtenerValor(string nomVert1, string nomVert2){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			return obtenerValor(v1,v2);
		}
		int obtenerValor(int v1, int v2){
			//if (v1 < 0 || v2 < 0 || v1 >= numVerts || v2 >= numVerts)
				//throw "Vertice no existe";
			return matAd[v1][v2];
		}
		void establecerValor(string nomVert1, string nomVert2, int valor){
			int v1, v2;
			v1 = numVertice(nomVert1);
			v2 = numVertice(nomVert2);
			establecerValor(v1,v2,valor);
		}
		void establecerValor(int v1, int v2, int valor){
			//if (v1 < 0 || v2 < 0 || v1 >= numVerts || v2 >= numVerts)
				//throw "Vertice no existe";
			//else 
			matAd[v1][v2] = valor;
		}
		Vertice obtenerVertice(string nomVert){
			return obtenerVertice(numVertice(nomVert));
		}
		Vertice obtenerVertice(int v){
			//if(v < 0 || v >= numVerts) throw "Vertice no existe";
			//else 
			return verts[v];
		}
		void establecerVertice(string nomVert, Vertice v){
			establecerVertice(numVertice(nomVert),v);
		}
		void establecerVertice(int nv, Vertice v){
			//if( nv < 0 || nv >= numVerts) throw "Vertice no existe";
			//else 
			verts[nv] = v;
		}
};



class Pila{
	protected:
		class Nodo{
			protected:
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
		int tope(){return cima->obtenerDato();}
		bool colaVacia(){
			return cima == NULL;
		}
		int obtenerCantidadElementos(){return length;}
};

void bellmanFord(GrafoMatriz grafo, int vertIni){
	int numVertices = grafo.obtenerNumeroDeVertices();
	int dist[numVertices];
	int prev[numVertices];
	for(int i=0; i<numVertices; i++){
		dist[i]=INFINITY;
		prev[i]=-1;
	}
	dist[vertIni] = 0;
	for (int k = 0; k < numVertices - 1; k++)
		for (int i = 0; i < numVertices; i++)		
			for (int j = 0; j < numVertices; j++)
				if((dist[i] + grafo.obtenerValor(i,j)) < dist[j]){
					dist[j] = dist[i] + grafo.obtenerValor(i,j);
					prev[j] = i;
				}
				
	for (int k = 0; k < numVertices - 1; k++)
		for (int i = 0; i < numVertices; i++)
			for (int j = 0; j < numVertices; j++)
				if(dist[i] + grafo.obtenerValor(i,j) < dist[j]){
					dist[j] = -INFINITY;
					prev[j] = -2;
				}
	
	Pila camino;
	int en;
	for (int i=0; i<numVertices; i++){
		cout << "El camino mas corto entre el vertice "<<grafo.obtenerVertice(vertIni).obtenerNomVertice()<< " y el vertice " <<grafo.obtenerVertice(i).obtenerNomVertice()<<" es: ";
		en = i;
		for (; prev[en] > 0; en = prev[en]){
			camino.insertar(en);
			
		}
		camino.insertar(vertIni);
		if(prev[en] == -2){
			cout << "Numero infinito de caminos"<<endl;
		}
		else{
			
			for(int j = 0, n=camino.obtenerCantidadElementos(); j < n-1;j++){
				cout << grafo.obtenerVertice(camino.sacar()).obtenerNomVertice() << " -> ";
			}
			cout << grafo.obtenerVertice(camino.sacar()).obtenerNomVertice()<<". Con un coste de: "<<dist[i]<<endl;
		}
	}
}

void bellmanFord(GrafoMatriz grafo, string nomVert){
	bellmanFord(grafo, grafo.numVertice(nomVert));
}

int main(){
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
	bellmanFord(grafo,"F");
}