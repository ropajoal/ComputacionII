#define _GLIBCXX_USE_CXX11_ABI 0
#include <string.h>
#include <iostream>

using namespace std;

struct Contacto{
    string nombre, telefono, email;
};

class ConNodo{
    protected:
        Contacto contacto;
        ConNodo* enlace;
    public:
        ConNodo(string nombre, string telefono, string email){
            contacto.nombre = nombre;
            contacto.telefono = telefono;
            contacto.email = email;
        }
        ConNodo(string nombre, string telefono, string email, ConNodo* link){
            contacto.nombre = nombre;
            contacto.telefono = telefono;
            contacto.email = email;
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

class Agenda{
    protected:
        ConNodo* primero;
    public:
        Agenda(){
            primero = NULL;
        }
        ConNodo* Oprimero(){
            return primero;
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
                    while (actual->enlaceNodo()->obtenerContacto().nombre < nuevo->obtenerContacto().nombre || actual->enlaceNodo() == NULL){
                        actual = actual->enlaceNodo();
                    }
                    nuevo->ponerEnlace(actual->enlaceNodo());
                    actual->ponerEnlace(nuevo);
                }
            }
        }
        void eliminarContacto(string nombre){
            if(primero->obtenerContacto().nombre == nombre) primero = primero->enlaceNodo();
            else{
                ConNodo* actual;
                actual = primero;
                while (actual->enlaceNodo() != NULL){
                    if(nombre == actual->enlaceNodo()->obtenerContacto().nombre){
                        actual->ponerEnlace(actual->enlaceNodo()->enlaceNodo());
                    }
                    actual = actual->enlaceNodo();
                }
            }
        }
        void mostrarContactos(){
            ConNodo* actual;
            Contacto contacto;
            actual = primero;            
            while(actual != NULL){
                contacto = actual->obtenerContacto();
                cout << contacto.nombre << "\t" << contacto.telefono << "\t" << contacto.email << endl;
                actual = actual->enlaceNodo();
            }
        }
};