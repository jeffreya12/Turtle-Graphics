#ifndef TURTLE_H
#define TURTLE_H

#define PI 3.14159265358979323846

#include <iostream>
#include <fstream>
#include <winbgim.h>
#include <math.h>
#include <stdlib.h>
#include "LinkedList.h"

using namespace std;

class Turtle{
    private:

        int currentX;
        int currentY;
        int color;
        int penSize;
        int heading;
        bool penUp;

    public:
        Turtle(){

            initwindow(1200, 700);
            init();

        }

        ~Turtle(){

            closegraph();

        };

        void init(){ // Inicializa todos los atributos

            currentX = 600;
            currentY = 350;
            heading = 0;
            color = COLOR (255, 255, 255);;
            penSize = 1;
            penUp = false;
            setlinestyle(0, 0, penSize);
            setcolor(color);

        }

        void tortuga(){ // Dibuja la tortuga

            int centerX = currentX + 10 * cos(heading * PI / 180);
            int centerY = currentY - 10 * sin(heading * PI / 180);
            int nextX, nextY;

            setlinestyle(0, 0, 1);
            setfillstyle(1, 2);
            setcolor(2);

            nextX = centerX + 10 * cos((heading + 60) * PI / 180);
            nextY = centerY - 10 * sin((heading + 60) * PI / 180);

            fillellipse(nextX, nextY, 4, 4); // Pata delantera izquierda

            nextX = centerX + 10 * cos((heading - 60) * PI / 180);
            nextY = centerY - 10 * sin((heading - 60) * PI / 180);

            fillellipse(nextX, nextY, 4, 4); // Pata delantera derecha

            nextX = centerX + 10 * cos((heading + 120) * PI / 180);
            nextY = centerY - 10 * sin((heading + 120) * PI / 180);

            fillellipse(nextX, nextY, 4, 4); // Pata trasera izquierda

            nextX = centerX + 10 * cos((heading - 120) * PI / 180);
            nextY = centerY - 10 * sin((heading - 120) * PI / 180);

            fillellipse(nextX, nextY, 4, 4); // Pata trasera derecha

            nextX = centerX + 15 * cos(heading * PI / 180);
            nextY = centerY - 15 * sin(heading * PI / 180);

            fillellipse(nextX, nextY, 5, 5);

            setfillstyle(5, 2);

            fillellipse(centerX, centerY, 10, 10); // Cuerpo

            setlinestyle(0, 0, penSize);
            setcolor(color);

        }

        void forward (int largoDeLinea){ // Mueve la tortuga en la direccion actual a la distancia indicada.

            int nextX = currentX + largoDeLinea * cos(heading * PI / 180);
            int nextY = currentY - largoDeLinea * sin(heading * PI / 180);

            if (!penUp){ //Dibuja si el lapiz esta abajo
                line(currentX, currentY, nextX, nextY);
            }

            currentX = nextX;
            currentY = nextY;
        }

        void back (int largoDeLinea){ // Mueve la tortuga en la direccion contraria a la distancia indicada.

            int nextX = currentX - largoDeLinea * cos(heading * PI / 180);
            int nextY = currentY + largoDeLinea * sin(heading * PI / 180);

            if (!penUp){ //Dibuja si el lapiz esta abajo
                line(currentX, currentY, nextX, nextY);
            }

            currentX = nextX;
            currentY = nextY;

        }

        void right(int grados){ // Cambia la direccion de la tortuga la cantidad de grados indicados a la derecha
            heading = heading - grados;

        }

        void left(int grados){ // Cambia la direccion de la tortuga la cantidad de grados indicados a la izquierda
            heading = heading + grados;
        }

        void setPos(int pX, int pY){  // Coloca la tortuga en las posiciones X y Y indicadas

            if(!penUp){ //Dibuja si el lapiz esta abajo
                line(currentX, currentY, pX, pY);
            }

            currentX = pX;
            currentY = pY;

        }

        void setX(int pX){ // Coloca la tortuga en la posicion X indicada

            if(!penUp){ //Dibuja si el lapiz esta abajo
                line(currentX, currentY, pX, currentY);
            }

            currentX = pX;
        }

        void setY(int pY){ // Coloca la tortuga en la posicion Y indicada

            if(!penUp){ //Dibuja si el lapiz esta abajo
                line(currentX, currentY, currentX, pY);
            }

            currentY = pY;
        }

        void setHeading (int pHeading) { //Coloca la direccion de la tortuga en los grados indicados
            if(pHeading >= 360){
                pHeading = pHeading % 360;
            }

            heading = pHeading;
        }

        void home (){ //Coloca la tortuga a la posicion inicial
            currentX = 600;
            currentY = 350;
            heading = 0;
        }

        void circulo (int pRadio){ //Dibuja un circulo segun el radio especificado

            if (penUp == false){ //Dibuja solo con el lapiz abajo
                int headingTemp, radio, nextX, nextY;
                headingTemp = heading;
                radio = abs(pRadio);
                if (pRadio < 0) right(90);
                if (pRadio > 0) left(90);
                nextX = currentX + radio * cos(heading * PI / 180);
                nextY = currentY - radio * sin(heading * PI / 180);
                circle(nextX, nextY, radio);
                heading = headingTemp;
            }

        }


        void pos(){ // Muestra en pantalla la posicion X y Y actual

            cout << "\nLa tortuga se encuentra en X = " << currentX << " y Y = " << currentY << "\n\n";

        }

        void xCor(){ // Muestra en pantalla la posicion X actual

            cout << "\nLa tortuga se encuentra en X = " << currentX << "\n\n";

        }

        void yCor(){ // Muestra en pantalla la posicion Y actual

            cout << "\nLa tortuga se encuentra en Y = " << currentY << "\n\n";

        }

        void getHeading(){ // Muestra en pantalla la direccion actual

            cout << "\nLa tortuga se encuentra con rumbo de " << heading << " grados\n\n";

        }

        void setPenDown(){ // Baja el lapiz

            penUp = false;

        }

        void setPenUp(){ // Sube el lapiz

            penUp = true;

        }

        void setPenSize(int pPenSize){ // Asigna el grosor del lapiz segun el especificado

            penSize = pPenSize;
            setlinestyle(0, 0, penSize);

        }

        void setColor(string pColor){ // Asigna el color segun su nombre

            if (pColor == "black") color = COLOR(0, 0, 0);
            else if (pColor == "blue") color = COLOR (0, 0, 255);
            else if (pColor == "green") color = COLOR (0, 255, 0);
            else if (pColor == "cyan") color = COLOR (0, 255, 255);
            else if (pColor == "red") color = COLOR (255, 0, 0);
            else if (pColor == "magenta") color = COLOR (255, 0, 255);
            else if (pColor == "brown") color = COLOR(165, 42, 42);
            else if (pColor == "lightgray") color = COLOR (211, 211, 211);
            else if (pColor == "darkgray") color = COLOR (127, 127, 127);
            else if (pColor == "lightblue") color = COLOR (127, 127, 255);
            else if (pColor == "lightgreen") color = COLOR (127, 255, 127);
            else if (pColor == "lightcyan") color = COLOR (127, 255, 255);
            else if (pColor == "lightred") color = COLOR (255, 127, 127);
            else if (pColor == "lightmagenta") color = COLOR (255, 127, 255);
            else if (pColor == "yellow") color = COLOR (255, 255, 0);
            else if (pColor == "white") color = COLOR (255, 255, 255);

            setcolor(color);

        }


        void setColor(int pR, int pG, int pB){ // Asigna el color segun sus valores RGB

            color = COLOR(pR, pG, pB);
            setcolor(color);

        }

        void pen(){ // Muestra en pantalla el grosor, color y si esta arriba o abajo

            string lapiz;
            if (penUp) lapiz = "arriba";
            else lapiz = "abajo";
            cout << "\nEl lapiz se encuentra " << lapiz << ", con grosor " << penSize << " y color " << RED_VALUE(color) << " " << GREEN_VALUE(color) << " " << BLUE_VALUE(color) << "\n\n";

        }

        void reset(){ // Limpia la pantalla y se coloca en las posiciones por defecto

            cleardevice();
            init();

        }

        void clear(){ // Limpia la pantalla

            cleardevice();

        }

        void write (int sizeText, string pTexto){ // Escribe un texto en la posicion actual con el tamano indicado
            const char * texto = pTexto.c_str();
            settextjustify(0, 0);
            settextstyle(0, 0, sizeText);
            outtextxy (currentX, currentY, texto);

        }

};

#endif // TURTLE_H
