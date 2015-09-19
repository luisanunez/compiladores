//  g++ -std=c++11 lexico.cpp -o lexico


#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;


    



vector<string> lista_tokens;
vector<string> palabras_reservadas;
vector<string> datos_por_lexema;
vector<vector<string>> estructura;

void add_reservadas(){
    palabras_reservadas.push_back("int");
    palabras_reservadas.push_back("float");
    palabras_reservadas.push_back("string");
    palabras_reservadas.push_back("bool");
    palabras_reservadas.push_back("do");
    palabras_reservadas.push_back("while");
    palabras_reservadas.push_back("return");
    palabras_reservadas.push_back("fun");
    palabras_reservadas.push_back("print");
    palabras_reservadas.push_back("main");
    palabras_reservadas.push_back("void");
       
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













string verificar(string inputString){
   string token;
 /*   string inputString;
    cin >> inputString;*/
   
    add_reservadas();
    Estado_variable ultimo_variable = reconocerVariable(inputString);
    Estado_num ultimo_num = reconocerNumero(inputString);
    Estado_string ultimo_string = reconocerString(inputString);
    Estado_funcion ultimo_funcion = reconocerFuncion(inputString);
    Estado_mas ultimo_mas = reconocerMas(inputString);

  
     if(ultimo_mas==Estado_mas::MAS){
        token="mas_mas";
        lista_tokens.push_back(token);
    }



    if(ultimo_funcion==Estado_funcion::Q2){
        token="nombre_funcion";
        lista_tokens.push_back(token);
    }

    if((ultimo_variable==Estado_variable::LETRA or ultimo_variable==Estado_variable::LETRA_NUMERO 
        or ultimo_variable==Estado_variable::NUMERO_LETRA) and es_reservada(inputString) == true)
        {
         token="pr_"+inputString;
         lista_tokens.push_back(token);
        }


    if(ultimo_string== Estado_string::STRING)
    {
      token="variable_string";
      lista_tokens.push_back(token);
    }

    
    if((ultimo_variable==Estado_variable::LETRA or 
       ultimo_variable==Estado_variable::LETRA_NUMERO or ultimo_variable==Estado_variable::NUMERO_LETRA )
        and es_reservada(inputString)==false)
        {
         token="nombre_variable";
         lista_tokens.push_back(token);
        }

    if(ultimo_num == Estado_num::ENTERO)
        {
         token="variable_int";         
         lista_tokens.push_back(token);
        }


    if(ultimo_num == Estado_num::REAL)
    {
         token="variable_float";         
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

     if(inputString==",")
        {
          token="coma" ;
          lista_tokens.push_back(token); 
        }




/*     for(int i =0 ; i< lista_tokens.size();i++){
        cout<< lista_tokens[i]<<" - ";
     }   
*/

     //cout<<endl;

     return token;

}




int main() {

  string token;
  int line=1;
  char cadena[128];
    ifstream fe("codigo2.txt");
    ofstream fs("tokens2.txt"); 

   while(fe.good()) {

      fe >> cadena;
      token= verificar(cadena);
      fs << token << " | " << cadena << " | "<< line <<endl; 
      if(fe.get()=='\n') line++;


   }

   fe.close();

fs.close();
 return 0;
}

