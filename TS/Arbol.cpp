#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <stdlib.h>
#include <time.h>

typedef int TipoElemento

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
            return new NodoArbol(ramaIzdo,dato ramaDcho);
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
                dr = insertar(raizsub->subArbolDcho(), dato);
                raizSub->ramaDcho(dr);
            }
            else
                throw "Nodo Duplicado";
            return raizSub;
        }
};

int numeroAleatorio(int limite){
    srand(time(NULL));
    return rand() % limite + 1;
}

int altura(NodoArbol *raiz){
    if(raiz == NULL) return 0;
    int alturaIz = altura(raiz->subArbolIzdo());
    int alturaDr = altura(raiz->subArbolDr());
    if(alturaIz > alturaDr) return alturaIz + 1;
    else return alturaDr + 1;
}

ArbolBinario crearArbolAltura(int alt){
    int numero;
    ArbolBinario arbol;
    while(altura(arbol.Oraiz()) < alt){
        numero = numeroAleatorio(100);
        arbol.insertar(numero);
    }
    return arbol;
}