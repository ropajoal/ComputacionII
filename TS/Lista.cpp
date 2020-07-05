#define _GLIBCXX_USE_CXX11_ABI 0
#include <string.h>
#include <iostream>

using namespace std;

struct Contacto{
    string nombre, telefono, email;
}

class ConNodo{
    protected:
        Contacto contacto;
        ConNodo* enlace;
    public:
        ConNodo(string nombre, string telefono, string email){
            contacto.nombre = nombre;
            contacto.telefono = telefono;
            contcto.email = email;
        }
        ConNodo(string nombre, string telefono, string email, ConNodo* link){
            contacto.nombre = nombre;
            contacto.telefono = telefono;
            contcto.email = email;
            enlace = link;
        }
        Contacto obtenerContacto() const{
            return contacto;
        }
        ConNodo* enlaceNodo() const{
            return enlace;
        }
        void ponerEnlace(ConNodo* sig){
            enlace = sig;
        }
};

bool operator < (string a, string b){
    return strcmp(a,b ) < 0;
}

class Agenda{
    protected:
        ConNodo* primero;
    public:
        Agenda(){
            primero = NULL;
        }
        void nuevoContacto(string nombre, string telefono, string email){
            ConNodo* nuevo;
            nuevo = new ConNodo(nombre, telefono, email);
            if(primero == NULL) primero = nuevo;
            else{
                if(nuevo->obtenerContacto().nombre < primero->obtenerContacto().nombre){
                    nuevo->ponerEnlace(primero);
                    primero = nuevo;
                }
                else{
                    ConNodo* actual;
                    actual = primero;
                    while (actual != NULL){
                        if(nuevo->obtenerContacto().nombre < actual->enlaceNodo()->obtenerContacto().nombre || actual->enlaceNodo() == NULL){
                            nuevo->ponerEnlace(actual->enlaceNodo());
                            actual->ponerEnlace(nuevo);
                        }
                        else{
                            actual = actual->enlaceNodo();
                        }
                    }
                }
            }
        }
}