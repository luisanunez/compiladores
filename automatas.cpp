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








//AUTOMATA PARA RECONOCER STRING

enum class Estado_string {INICIO, Q1, Q2, STRING, NO_RECONOCIDO};
Estado_string reconocerString(const string& inputString)
{
    int pos = 0;
    Estado_string actual = Estado_string::INICIO;
    bool cadenaRechazada = false;
    
    while ( !cadenaRechazada && pos < inputString.length()) {
        char simbolo = inputString[pos];
        switch (actual) {
        case Estado_string :: INICIO:
            if (simbolo == '"') {
                actual = Estado_string ::Q1;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_string ::Q1:
            if ( isalpha(simbolo) or isdigit(simbolo) ) {
                actual = Estado_string::Q2;
            }  else if(simbolo == '"'){
                actual = Estado_string::STRING;
            }
           else {
                cadenaRechazada = true;
            }
            break;
        case Estado_string ::Q2:
            if(isalpha(simbolo) or isdigit(simbolo) ){
                actual = Estado_string ::Q2;
            }else if(simbolo == '"'){
                actual = Estado_string::STRING;
            }

            else 
            {
                
                cadenaRechazada = true;
            }
            break;
        }
        pos++;
    }
    if (cadenaRechazada) {
        return Estado_string::NO_RECONOCIDO;
    }
    return actual;
}








//AUTOMATA PARA RECONOCER FUNCION

enum class Estado_funcion {INICIO, Q1, Q2, FUNCION, NO_RECONOCIDO};
Estado_funcion reconocerFuncion(const string& inputString)
{
    int pos = 0;
    Estado_funcion actual = Estado_funcion::INICIO;
    bool cadenaRechazada = false;
    
    while ( !cadenaRechazada && pos < inputString.length()) {
        char simbolo = inputString[pos];
        switch (actual) {
        case Estado_funcion :: INICIO:
            if (simbolo == 'f') {
                actual = Estado_funcion ::Q1;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_funcion ::Q1:
            if ( simbolo == '.' ) {
                actual = Estado_funcion::Q2;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_funcion ::Q2:
            if(isalpha(simbolo) or isdigit(simbolo) ){
                actual = Estado_funcion ::Q2;
            }
            else 
            {                
                cadenaRechazada = true;
            }
            break;
        }
        pos++;
    }
    if (cadenaRechazada) {
        return Estado_funcion::NO_RECONOCIDO;
    }
    return actual;
}






//AUTOMATA PARA RECONOCER ++

enum class Estado_mas {INICIO, Q1, Q2, MAS, NO_RECONOCIDO};
Estado_mas reconocerMas(const string& inputString)
{
    int pos = 0;
    Estado_mas actual = Estado_mas::INICIO;
    bool cadenaRechazada = false;
    
    while ( !cadenaRechazada && pos < inputString.length()) {
        char simbolo = inputString[pos];
        switch (actual) {
        case Estado_mas :: INICIO:
            if (isalpha(simbolo) or isdigit(simbolo)) {
                actual = Estado_mas ::Q1;
            } else {
                cadenaRechazada = true;
            }
            break;
        case Estado_mas ::Q1:
            if ( simbolo == '+' ) {
                actual = Estado_mas::Q2;
            } else if (isalpha(simbolo) or isdigit(simbolo)) {
                actual = Estado_mas ::Q1;
            } else
            {
                cadenaRechazada = true;
            }
            break;
        case Estado_mas::Q2:
            if(simbolo == '+' ){
                actual = Estado_mas ::MAS;
            }
            else 
            {                
                cadenaRechazada = true;
            }
            break;
        }
        pos++;
    }
    if (cadenaRechazada) {
        return Estado_mas::NO_RECONOCIDO;
    }
    return actual;
}







void verificar(){
    string inputString;
    cin >> inputString;
    
    Estado_variable ultimo_variable = reconocerVariable(inputString);
    Estado_num ultimo_num = reconocerNumero(inputString);
    Estado_string ultimo_string = reconocerString(inputString);
    Estado_funcion ultimo_funcion = reconocerFuncion(inputString);
    Estado_mas ultimo_mas = reconocerMas(inputString);

    if(ultimo_variable==Estado_variable::LETRA or ultimo_variable==Estado_variable::LETRA_NUMERO or ultimo_variable==Estado_variable::NUMERO_LETRA )
        {cout<<"ES VARIABLE"<<endl;}
    if(ultimo_num == Estado_num::ENTERO or ultimo_num == Estado_num::REAL){
        cout<<"ES NUM"<< endl;
    }
    if(ultimo_string== Estado_string::STRING){
        cout<<"ES STRING"<<endl;
    }
    if(ultimo_funcion==Estado_funcion::Q2){
        cout<<"ES FuNcion"<<endl;
    }

    if(ultimo_mas==Estado_mas::MAS){
        cout<<"MAS MAS";
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

