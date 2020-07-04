#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>

using namespace std;

int MCD(int a,int b){
    int MCD, aux, r;
    MCD = a;
    aux = b;
    do{
        r = MCD % aux;
        MCD = aux;
        aux = r;
    }while(r!=0);
    return MCD;
}

int mcm(int a, int b){
    return a * b / MCD(a,b);
}

class Racional{
        
    public:
        int num, den;
        Racional(){}
        Racional(int a, int b){
            num = a;
            den = b;
        }
        friend ostream& operator << (ostream& pantalla, const Racional& r);
        Racional simplificado(){
            int MCDnum,numsim,densim;
            MCDnum = MCD(num,den);
            numsim = num/MCDnum;
            densim = den/MCDnum;
            return Racional(numsim,densim);
        }
        bool operator == (Racional& r){
            Racional r1, r2;
            r1 = this->simplificado();
            r2 = r.simplificado();
            return ( r1.num == r2.num && r1.den == r2.den );
        }
        Racional& operator = (const Racional& r){
            if(this==&r) return *this;
            num = r.num;
            den = r.den;
            return *this;
        }
        Racional operator + (Racional& r){
            int mcmnum,mul1,mul2;
            mcmnum = mcm(den,r.den);
            mul1=mcmnum/den;
            mul2=mcmnum/r.den;
            return Racional(num*mul1+r.num*mul2, mcmnum);
        }
        Racional operator - (Racional& r){
            int mcmnum,mul1,mul2;
            mcmnum = mcm(den,r.den);
            mul1=mcmnum/den;
            mul2=mcmnum/r.den;
            return Racional(num*mul1-r.num*mul2, mcmnum);
        }
        Racional operator * (Racional& r){
            return Racional(num*r.num,den*r.den);
        }
        Racional operator / (Racional& r){
            return Racional(num*r.den,den*r.num);
        }

        string esIgual(Racional& r){
            if (*this == r)
                return "Es Igual";
            else
                return "No es igual";
        }

};

ostream& operator << (ostream& pantalla, const Racional& r)
{
    pantalla <<  r.num;
    if(r.den != 1) pantalla << "/" << r.den << endl;
    return pantalla;
}

int main(){
    Racional r1(1,3),r2(2,3),r3(4,2),r4(6,2),suma;
    string resultado;
    suma = r1 + r2 + r3;
    resultado = suma.esIgual(r4);
    cout << "El numero racional es: " << suma.simplificado() << " " << resultado << " que " << r4 << endl;
}
