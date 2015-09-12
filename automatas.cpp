//g++ -std=c++11 automatas.cpp -o main

#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

//AUTOMATA PARA NUMEROS REALES O ENTEROS
enum class Estado_num {INICIO, Q1, Q2, ENTERO, REAL, NO_RECONOCIDO};
Estado_num reconocerNumero(const string& inputString)
{
    int pos = 0;
    Estado_num actual = Estado_num::INICIO;
    bool cadenaRechazada = false;
    
    while ( !cadenaRechazada && pos < inputString.length()) {
        char simbolo = inputString[pos];
        switch (actual) {
        case Estado_num::INICIO:
            if (isdigit(simbolo)) {
                actual = Estado_num::ENTERO;
            } else if (simbolo == '+' or simbolo == '-') {
                actual = Estado_num::Q1;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_num::Q1:
            if (isdigit(simbolo)) {
                actual = Estado_num::ENTERO;
            } else if (simbolo == '.') {
                actual = Estado_num::Q2;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_num::Q2:
            if (isdigit(simbolo)) {
                actual = Estado_num::REAL;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_num::ENTERO:
            if (isdigit(simbolo)) {
                actual = Estado_num::ENTERO;
            } else if (simbolo == '.') {
                actual = Estado_num::Q2;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_num::REAL:
            if (isdigit(simbolo)) {
                actual = Estado_num::REAL;
            } else {
                cadenaRechazada = true;
            }
            break;
        }
        pos++;
    }
    if (cadenaRechazada) {
        return Estado_num::NO_RECONOCIDO;
    }
    return actual;
}





//AUTOMATA PARA  VARIABLES LETRAS MAYUSCULAS MINUSCULAS O NUMEROS

enum class Estado_variable {INICIO, Q1, LETRA, NUMERO_LETRA, LETRA_NUMERO, NO_RECONOCIDO};



Estado_variable reconocerVariable(const string& inputString){
    int pos = 0;
    Estado_variable actual = Estado_variable::INICIO;
    bool cadenaRechazada = false;    while ( !cadenaRechazada && pos < inputString.length()) {
        char simbolo = inputString[pos];
        switch (actual) {
        case Estado_variable::INICIO:
            if (isalpha(simbolo)) {
                actual = Estado_variable::LETRA;
            } else if (isdigit(simbolo)) {
                actual = Estado_variable::Q1;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_variable::LETRA:
            if (isalpha(simbolo)) {
                actual = Estado_variable::LETRA;
            } else if (isdigit(simbolo)) {
                actual = Estado_variable::LETRA_NUMERO;
            } else {    
                cadenaRechazada = true;
            }
            break;
        case Estado_variable::Q1:
            if (isdigit(simbolo)) {
                actual = Estado_variable::Q1;
            } else if (isalpha(simbolo)) {
                actual = Estado_variable::NUMERO_LETRA;
            } else {    
                cadenaRechazada = true;
            }
            break;
        case Estado_variable::LETRA_NUMERO:
            if (isdigit(simbolo)) {
                actual = Estado_variable::LETRA_NUMERO;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_variable::NUMERO_LETRA:
            if (isalpha(simbolo)) {
                actual = Estado_variable::NUMERO_LETRA;
            } else {
                cadenaRechazada = true;
            }
            break;
        }
        pos++;
    }
    if (cadenaRechazada) {
        return Estado_variable::NO_RECONOCIDO;
    }
    return actual;
}





void verificar(){
    string inputString;
    cin >> inputString;
    
    Estado_variable ultimo_variable = reconocerVariable(inputString);
    Estado_num ultimo_num = reconocerNumero(inputString);
    if(ultimo_variable==Estado_variable::LETRA or ultimo_variable==Estado_variable::LETRA_NUMERO or ultimo_variable==Estado_variable::NUMERO_LETRA )
        {cout<<"ES VARIABLE"<<endl;}
    if(ultimo_num == Estado_num::ENTERO or ultimo_num == Estado_num::REAL){
        cout<<"ES NUM"<< endl;
    }

}



int main() {

    verificar();
    



//    string inputString;
 //   cin >> inputString;
    
/*
    Estado_variable ultimo = reconocerVariable(inputString);
    if(ultimo==Estado_variable::LETRA or ultimo==Estado_variable::LETRA_NUMERO or ultimo==Estado_variable::NUMERO_LETRA ){
        cout<<"es variable"<<endl;
    } else{
        cout<<"No es variable";
    }

*/

   /* 
    Estado_num ultimo = reconocerNumero(inputString);
    if (ultimo == Estado_num::ENTERO or ultimo == Estado_num::REAL) {
        cout << "Es num" << endl;
    } else {
        cout << "No es num" << endl;
    }



*/

    cout << endl;
main();
    return 0;
}

