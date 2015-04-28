#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "include\LinkedList.h"
#include "include\Turtle.h"

using namespace std;


Turtle * tortuga = new Turtle;
LinkedList<string> historial, archivo, instrucciones;
// historial: lista de instrucciones
// archivo: lista de instrucciones cargadas por loadfile
// instrucciones: lista utilizada para graficar

LinkedList<string> split(string pInstruccion){ //Divide un string en elementos, los cuales se encuentran entre espacios, corchetes ([]) o comillas ("")
    int size = pInstruccion.size();
    LinkedList<string> listaInstrucciones;
    string instruccionTemp;

    for (int i = 0; i < size; i++){
        if (pInstruccion[i] == ' '){
            listaInstrucciones.append(instruccionTemp);
            instruccionTemp.clear();
        }
        else if(pInstruccion[i] == '"'){
            instruccionTemp.clear();
            i += 1;
            for (int j = i; j < size; j++){
                if (pInstruccion[j] != '"') {
                    instruccionTemp += pInstruccion[j];
                }
                else {
                    listaInstrucciones.append(instruccionTemp);
                    return listaInstrucciones;
                }
            }
        }
        else if(pInstruccion[i] == '['){
            instruccionTemp.clear();
            i += 1;
            for (int j = i; j < size; j++){
                if (pInstruccion[j] != ']') {
                    instruccionTemp += pInstruccion[j];
                }
                else {
                    listaInstrucciones.append(instruccionTemp);
                    return listaInstrucciones;
                }
            }
        }
        else{
            instruccionTemp += pInstruccion[i];
        }
    }
    listaInstrucciones.append(instruccionTemp); //Pone el ultimo elemento al final del vector
    return listaInstrucciones;
}

LinkedList<string>* strToLinkedList(string strList){ // Convierte una lista de elementos separados por comas (,) en una lista enlazada
    int sizeStr = strList.size();
    LinkedList<string>* list = new LinkedList<string>();
    string auxString = "";
    for (int i = 0; i < sizeStr; i++){
        if (strList[i] != ','){
            auxString += strList[i];
        }
        else{
            list->append(auxString);
            auxString.clear();
        }
    }
    list->append(auxString);
    return list;
}

bool validarEntero(string pNumero){
    int sizeNumero = pNumero.size();
    for (int i = 0; i < sizeNumero; i++){
        if (!isdigit(pNumero[i])) return false;
    }
    return true;
}

bool validarInstruccion(string pInstruccion){ // Valida las entradas en cuanto a cantidad de parametros se refiere
    string error = "\nLa cantidad de parametros no es correcta\n\n";
    LinkedList<string> instruccionAEvaluar = split(pInstruccion);
    instruccionAEvaluar.goToStart();
    if (instruccionAEvaluar.getElement() == "forward" || instruccionAEvaluar.getElement() == "back" || instruccionAEvaluar.getElement() == "setx" || instruccionAEvaluar.getElement() == "sety" || instruccionAEvaluar.getElement() == "right" || instruccionAEvaluar.getElement() == "left" || instruccionAEvaluar.getElement() == "setheading" || instruccionAEvaluar.getElement() == "circle" || instruccionAEvaluar.getElement() == "pensize" || instruccionAEvaluar.getElement() == "loadfile"){
        if (instruccionAEvaluar.getSize() != 2){
            cout << error;
            return false;
        }
    }
    if (instruccionAEvaluar.getElement() == "setpos" || instruccionAEvaluar.getElement() == "write" || instruccionAEvaluar.getElement() == "repeat"){
        if (instruccionAEvaluar.getSize() != 3){
            cout << error;
            return false;
        }
    }
    if (instruccionAEvaluar.getElement() == "color"){
        if (instruccionAEvaluar.getSize() != 2 && instruccionAEvaluar.getSize() != 4){
            cout << error;
            return false;
        }
    }
    if (instruccionAEvaluar.getElement() == "home" || instruccionAEvaluar.getElement() == "pos" || instruccionAEvaluar.getElement() == "xcor" || instruccionAEvaluar.getElement() == "ycor" || instruccionAEvaluar.getElement() == "heading" || instruccionAEvaluar.getElement() == "pendown" || instruccionAEvaluar.getElement() == "penup" || instruccionAEvaluar.getElement() == "pen" || instruccionAEvaluar.getElement() == "reset" || instruccionAEvaluar.getElement() == "clear" || instruccionAEvaluar.getElement() == "exec" || instruccionAEvaluar.getElement() == "history" || instruccionAEvaluar.getElement() == "clearhistory" || instruccionAEvaluar.getElement() == "exit"){
        if (instruccionAEvaluar.getSize() != 1){
            cout << error;
            return false;
        }
    }
    if (instruccionAEvaluar.getElement() == "write"){
        instruccionAEvaluar.next();
        if (!validarEntero(instruccionAEvaluar.getElement().c_str())){
            cout << "\nEl tamano no es valido\n\n";
            return false;
        }
    }
    return true;
}

void loadFile(string nombreDelArchivo){ // Carga un archivo especificado

    ifstream file(nombreDelArchivo.c_str());
    string linea;
    if(file.is_open()){ // Valida si el archivo existe o no
        archivo.clear();
        while(getline(file, linea)) {
            if (validarInstruccion(linea) == false){ // Lanza un error en pantalla en caso de que la linea no sea valida
                cout << "\nLa linea " << linea << " no es valida y no se va a cargar el archivo.\n\n";
                archivo.clear();
                break;
            }
            else archivo.append(linea); //Rellena un vector con todas las lineas del txt
        }
        if (archivo.getSize() != 0){
            cout << "\n";
            archivo.print();
            cout << "\n\nEl archivo se termino de cargar.\n\n";
        }
    }
    else{
        cout << "\nNo existe el archivo.\n\n";
    }

}

void history(){ // Mustra el historial de instrucciones
    if (historial.getSize() == 0) cout << "\nEl historial esta vacio\n\n";
    else{
        cout << "\nHistorial de instrucciones: \n\n";
        historial.print();
        cout << "\n";
    }
}

void exec(){ // Ejecuta el archivo cargado

    if (archivo.getSize() == 0) cout << "\nNo hay un archivo cargado\n\n"; // Si no se ha cargado un archivo, muestra un error

    else{
        for(archivo.goToStart(); archivo.getPos() < archivo.getSize(); archivo.next()){
            instrucciones.append(archivo.getElement());
        }
    }

}

void repeat(int iteraciones, LinkedList<string>* pInstrucciones){ // Ejecuta un conjunto de instrucciones una cantidad de veces especificada
    for (int i = 0; i < iteraciones; i++){
        for(pInstrucciones->goToStart(); pInstrucciones->getPos() < pInstrucciones->getSize(); pInstrucciones->next()){
            if (validarInstruccion(pInstrucciones->getElement()) == false){
                cout << "\nLa instruccion " << pInstrucciones->getElement() << " no es correcta y no se graficara\n\n"; // Si una instruccion no es correcta, no se graficara
            }
            else instrucciones.append(pInstrucciones->getElement());
        }
    }
}

void leerInstruccion (string pInstruccion){ // Lee la instruccion y la ejecuta segun sea el caso

    LinkedList<string> instruccion = split(pInstruccion);
    instruccion.goToPos(0);

    if (instruccion.getElement() == "forward"){
        instruccion.next();
        tortuga->forward( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "back") {
        instruccion.next();
        tortuga->back( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "right") {
        instruccion.next();
        tortuga->right( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "left") {
        instruccion.next();
        tortuga->left( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "setpos") {
        instruccion.next();
        int xTemp = atoi(instruccion.getElement().c_str());
        instruccion.next();
        tortuga->setPos( xTemp, atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "setx") {
        instruccion.next();
        tortuga->setX( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "sety") {
        instruccion.next();
        tortuga->setY( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "setheading") {
        instruccion.next();
        tortuga->setHeading( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "home") tortuga->home();
    else if (instruccion.getElement()  == "circle") {
        instruccion.next();
        tortuga->circulo( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "pos") tortuga->pos();
    else if (instruccion.getElement()  == "xcor") tortuga->xCor();
    else if (instruccion.getElement()  == "ycor") tortuga->yCor();
    else if (instruccion.getElement()  == "heading") tortuga->getHeading();
    else if (instruccion.getElement()  == "penup") tortuga->setPenUp();
    else if (instruccion.getElement()  == "pendown") tortuga->setPenDown();
    else if (instruccion.getElement()  == "pensize") {
        instruccion.next();
        tortuga->setPenSize( atoi(instruccion.getElement().c_str()) );
    }
    else if (instruccion.getElement()  == "color") {
        if (instruccion.getSize() == 2){
            instruccion.next();
            tortuga->setColor( instruccion.getElement() );
        }
        else{
            int pR, pG;
            instruccion.next();
            pR = atoi(instruccion.getElement().c_str());
            instruccion.next();
            pG = atoi(instruccion.getElement().c_str());
            instruccion.next();
            tortuga->setColor( pR, pG, atoi(instruccion.getElement().c_str()) );
        }
    }
    else if (instruccion.getElement()  == "pen") tortuga->pen();
    else if (instruccion.getElement()  == "reset") {
        tortuga->reset();
        instrucciones.clear();
    }
    else if (instruccion.getElement()  == "clear"){
        tortuga->clear();
    }
    else if (instruccion.getElement()  == "write"){
        instruccion.next();
        int tamanoTexto = atoi(instruccion.getElement().c_str());
        instruccion.next();
        tortuga->write (tamanoTexto, instruccion.getElement());
    }
    else if (instruccion.getElement()  == "repeat") {
        instruccion.next();
        int iteracionesAux = atoi(instruccion.getElement().c_str());
        instruccion.next();
        LinkedList<string>* instruccionesAux = strToLinkedList(instruccion.getElement());
        repeat(iteracionesAux, instruccionesAux);
    }
    else if (instruccion.getElement()  == "loadfile"){
        instruccion.next();
        loadFile(instruccion.getElement());
    }
    else if (instruccion.getElement()  == "exec") {
        exec();
        return;
    }
    else if (instruccion.getElement()  == "history") history();
    else if (instruccion.getElement()  == "clearhistory") historial.clear();
    else if (instruccion.getElement()  == "exit") exit(0);
    else cout << "\nEse comando no es valido.\n\n";
}

void rewrite(){ // Se encarga de graficar todo en pantalla

    tortuga->reset();

    for(instrucciones.goToStart(); instrucciones.getPos() < instrucciones.getSize(); instrucciones.next()){
        leerInstruccion(instrucciones.getElement());
    }

    tortuga->tortuga();

}


int main(){

    string instruccion; // Instruccion a ejecutar
    tortuga->tortuga(); // Inicia el graficador
    HANDLE  hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Necesario para los cambios de color

    SetConsoleTextAttribute(hConsole, 9); cout << "\n===================Instituto Tecnologico de Costa Rica - 2015===================\n\n";
    SetConsoleTextAttribute(hConsole, 2); cout << "This program comes with ABSOLUTELY NO WARRANTY";
    SetConsoleTextAttribute(hConsole, 4); cout << " (of well-functioning)\n\n";

    SetConsoleTextAttribute(hConsole, 15); //Cambia el color de las letras

    char NombredeUsuario[100]; // Necesario para obtener el nombre de usuario
    DWORD nNombredeUsuario = sizeof(NombredeUsuario); // Necesario para obtener el nombre de usuario
    GetUserName( NombredeUsuario, &nNombredeUsuario ); // Obtiene el nombre de usuario

    while (!kbhit()){

        cout << "<" << NombredeUsuario << ">: "; getline(cin, instruccion);
        if (validarInstruccion(instruccion) == false) continue; // Si la instruccion no es valida, muestra un error y sigue a la siguiente iteracion
        else{
            leerInstruccion(instruccion);
            // La siguiente linea anade solo las instrucciones necesarias a la lista utilizada para graficar
            if(split(instruccion).getElement() == "forward" || split(instruccion).getElement() == "back" || split(instruccion).getElement() == "right" || split(instruccion).getElement() == "left" || split(instruccion).getElement() == "setpos" || split(instruccion).getElement() == "setx" || split(instruccion).getElement() == "sety" || split(instruccion).getElement() == "setheading" ||split(instruccion).getElement() == "home" ||split(instruccion).getElement() == "circle" ||split(instruccion).getElement() == "pendown" || split(instruccion).getElement() == "penup" ||split(instruccion).getElement() == "pensize" || split(instruccion).getElement() == "color" || split(instruccion).getElement() == "write" || split(instruccion).getElement() == "clear") instrucciones.append(instruccion);
            historial.append(instruccion); // Anade todas las instrucciones validas al historial
            rewrite(); // Refresca el grafico en pantalla
        }

    }


}
