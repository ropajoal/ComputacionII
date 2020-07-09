#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>

using namespace std;

typedef  int TipoElemento;
struct Componente{
    TipoElemento elemento;
    struct Componente * sig;
};
typedef Componente * Puntero;
struct Cola{
    Puntero principio, final;
};

Cola crearCola(){
    Cola cola;
    cola.principio = NULL;
    cola.final = NULL;
    return cola;
}

bool esVacio (Cola cola){
    return cola.principio == NULL;
}

TipoElemento Primero(Cola cola){
    if(!esVacio(cola)){
        return cola.principio->elemento;
    }
    throw "Cola Vacia";
}

void Encolar(Cola& cola, TipoElemento dato){
    Puntero puntero = new Componente;
    puntero->elemento = dato;
    puntero->sig = NULL;
    if(esVacio(cola)){
        cola.principio = puntero;
        cola.final = puntero;
    }
    else{
        cola.final->sig = puntero;
        cola.final = puntero;
    }
}

void sacarCola(Cola& cola, TipoElemento dato){
    if(!esVacio(cola)){
        if(cola.principio->elemento == dato) cola.principio = cola.principio->sig;
        else{
            Puntero actual;
            actual = cola.principio;
            while(actual->sig!=NULL){
                if(actual->sig->elemento == dato) actual->sig = actual->sig->sig;
                else{
                    actual = actual->sig;
                }            
            }
        }
    }
    else{
        throw "Cola vacia";
    }
}



int main(){
    Cola cola = crearCola();
    Encolar(cola,1);
    Encolar(cola,2);
    Encolar(cola,3);
    Encolar(cola,4);
    sacarCola(cola,2);
    sacarCola(cola,3);
}