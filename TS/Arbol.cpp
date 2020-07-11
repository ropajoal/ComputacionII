#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <time.h>

using namespace std;

typedef int TipoElemento;

class NodoArbol{
    protected:
        TipoElemento dato;
        NodoArbol *izdo, *dcho;

    public:
        NodoArbol(TipoElemento valor){
            dato = valor;
            izdo = dcho = NULL;
        }
        NodoArbol(NodoArbol *ramaIzdo, TipoElemento valor, NodoArbol *ramaDcho){
            dato = valor;
            izdo = ramaIzdo;
            dcho = ramaDcho;
        }
        TipoElemento valorNodo(){
            return dato;
        }
        NodoArbol* subArbolIzdo(){
            return izdo;
        }
        NodoArbol* subArbolDcho(){
            return dcho;
        }
        void nuevoValor(TipoElemento valor){
            dato = valor;
        }
        void ramaIzdo(NodoArbol *n){
            izdo = n;
        }
        void ramaDcho(NodoArbol *n){
            dcho = n;
        }
};

class ArbolBinario{
    protected:
        NodoArbol *raiz;
    public:
        ArbolBinario(){
            raiz = NULL;
        }
        ArbolBinario(NodoArbol *r){
            raiz = r;
        }
        void Praiz(NodoArbol *r){
            raiz = r;
        }
        
        NodoArbol* Oraiz(){
            return raiz;
        }
        NodoArbol raizArbol(){
            if(raiz)
                return *raiz;
            else
                throw " arbol vacio";
        }
        bool esVacio(){
            return raiz == NULL;
        }
        NodoArbol* hijoIzdo(){
            if(raiz)
                return raiz->subArbolIzdo();
            else
                throw " arbol vacio";
        }
        NodoArbol* hijoDcho(){
            if(raiz)
                return raiz->subArbolDcho();
            else
                throw " arbol vacio";
        }
        NodoArbol* nuevoArbol(NodoArbol *ramaIzdo, TipoElemento dato, NodoArbol *ramaDcho){
            return new NodoArbol(ramaIzdo,dato, ramaDcho);
        }
        void insertar (TipoElemento valor){
            raiz = insertar(raiz, valor);
        }
        NodoArbol* insertar (NodoArbol* raizSub, TipoElemento dato){
            if ( raizSub == NULL)
                raizSub = new NodoArbol(dato);
            else if (dato < raizSub->valorNodo()){
                NodoArbol *iz;
                iz = insertar(raizSub->subArbolIzdo(),dato);
                raizSub->ramaIzdo(iz);
            }
            else if (dato > raizSub->valorNodo()){
                NodoArbol *dr;
                dr = insertar(raizSub->subArbolDcho(), dato);
                raizSub->ramaDcho(dr);
            }
            else
                throw "Nodo Duplicado";
            return raizSub;
        }
};

int numeroAleatorio(int limite){
    srand(time(NULL));
    return rand() % limite;
}

int altura(NodoArbol *raiz){
    if(raiz == NULL) return -1;
    int alturaIz = altura(raiz->subArbolIzdo());
    int alturaDr = altura(raiz->subArbolDcho());
    if(alturaIz > alturaDr) return alturaIz + 1;
    else return alturaDr + 1;
}

ArbolBinario llenarArbolAltura(int alt){
    int numero;
    ArbolBinario arbol;
    while(altura(arbol.Oraiz()) < alt){
        numero = numeroAleatorio(100);
        arbol.insertar(numero);
    }
    return arbol;
}

int contarElementosPorNivel(NodoArbol *raiz, int nivel){
    if(raiz == NULL) return 0;
    if(nivel == 0) return 1;
    return contarElementosPorNivel(raiz->subArbolIzdo(),nivel-1) + contarElementosPorNivel(raiz->subArbolDcho(),nivel-1);
}

int main(){
    ArbolBinario arbol = llenarArbolAltura(6);
    cout << arbol.Oraiz()->valorNodo() << altura(arbol.Oraiz());
}