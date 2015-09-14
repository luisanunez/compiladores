//g++ -std=c++11 automatas.cpp -o main

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;


vector<string> lista_tokens;
vector<string> palabras_reservadas;

void add_reservadas(){
    palabras_reservadas.push_back("num");
    palabras_reservadas.push_back("string");
    palabras_reservadas.push_back("bool");
    palabras_reservadas.push_back("do");
    palabras_reservadas.push_back("while");
    palabras_reservadas.push_back("return");
  
}



bool es_reservada(string inputString){
    bool result;
    for(int i =0; i<palabras_reservadas.size(); ++i){
        if(inputString == palabras_reservadas[i]){
            //cout<<"TOKEN: pr_" <<inputString<< endl;;
            result = true;
            
        }
    }
    return result;

 }



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
    string token;
    string inputString;
    cin >> inputString;
   
    add_reservadas();
    Estado_variable ultimo_variable = reconocerVariable(inputString);
    Estado_num ultimo_num = reconocerNumero(inputString);
   
    if((ultimo_variable==Estado_variable::LETRA or ultimo_variable==Estado_variable::LETRA_NUMERO 
        or ultimo_variable==Estado_variable::NUMERO_LETRA) and es_reservada(inputString) == true)
        {
         token="pr_"+inputString;
         lista_tokens.push_back(token);
        }



    
    if((ultimo_variable==Estado_variable::LETRA or 
       ultimo_variable==Estado_variable::LETRA_NUMERO or ultimo_variable==Estado_variable::NUMERO_LETRA )
        and es_reservada(inputString)==false)
        {
         token="cadena de caracteres";
         lista_tokens.push_back(token);
        }

    if(ultimo_num == Estado_num::ENTERO or ultimo_num == Estado_num::REAL)
        {
         token="cadena de numeros";         
         lista_tokens.push_back(token);
        }

    if(inputString==";")
        {
          token="fin de linea" ;
          lista_tokens.push_back(token); 
        }


    if(inputString=="(")
        {
          token="abrir parentesis" ;
          lista_tokens.push_back(token); 
        }

    if(inputString==")")
        {
          token="cerrar parentesis" ;
          lista_tokens.push_back(token); 
        }

    if(inputString=="=")
        {
          token="operador igual" ;
          lista_tokens.push_back(token); 
        }

    if(inputString=="+")
        {
          token="operacion mas" ;
          lista_tokens.push_back(token); 
        }


    if(inputString=="<")
        {
          token="menor que" ;
          lista_tokens.push_back(token); 
        }        

    if(inputString==">")
        {
          token="mayor que" ;
          lista_tokens.push_back(token); 
        }

    if(inputString=="==")
        {
          token="igual que" ;
          lista_tokens.push_back(token); 
        }
    if(inputString=="-")
        {
          token="operacion menos" ;
          lista_tokens.push_back(token); 
        }


    if(inputString=="*")
        {
          token="operacion por" ;
          lista_tokens.push_back(token); 
        }  


    if(inputString=="/")
        {
          token="operacion division" ;
          lista_tokens.push_back(token); 
        }

    if(inputString=="%")
        {
          token="comentario" ;
          lista_tokens.push_back(token); 
        }


    if(inputString=="{")
        {
          token="inicio bloque" ;
          lista_tokens.push_back(token); 
        }



    if(inputString=="}")
        {
          token="fin bloque" ;
          lista_tokens.push_back(token); 
        }



     for(int i =0 ; i< lista_tokens.size();i++){
        cout<< lista_tokens[i]<<" - ";
     }   


     cout<<endl;

}




int main() {

    for(int i=0; i<5;i++){
    verificar();
}
   

    return 0;
}

