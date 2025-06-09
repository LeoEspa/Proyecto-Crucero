#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void marco() {
    for (int x = 1; x <= 118; x++) {
        gotoxy(x, 1); printf("=");
        gotoxy(x, 29); printf("=");
    }
    for (int y = 1; y <= 29; y++) {
        gotoxy(1, y); printf("|");
        gotoxy(118, y); printf("|");
    }
}

void pantallaCargaSimple() {
    system("CLS");
    marco();
    
    
    const char* barco[] = {
        "   .  .   ",
        "  /|\\/|\\  ",
        "_|_o~~o_|_ ",
        " \\______/  "
    };
    
    int barco_ancho = 12;
    int barco_alto = 4;
    int max_x = 118 - barco_ancho;
    int pos_x = 5;
    
    // Olas más detalladas
    const char* ola[] = {"~~", "_\\_", "~/~"};
    
    gotoxy(45, 8); cout << "C A R G A N D O   S I S T E M A";
    
    // Dibujar olas estáticas
    for (int x = 5; x < 115; x += 4) {
        gotoxy(x, 20); cout << ola[0];
        gotoxy(x, 21); cout << ola[1];
        gotoxy(x+2, 22); cout << ola[2];
    }
    
    // Animación de un solo recorrido
    for (pos_x = 5; pos_x < max_x; pos_x += 3) {
        // Dibujar barco
        for (int y = 0; y < barco_alto; y++) {
            gotoxy(pos_x, 15 + y); cout << barco[y];
        }
        
        // Barra de progreso mejorada
        gotoxy(40, 23); cout << "[";
        int progreso = (pos_x - 5) * 100 / (max_x - 5);
        for (int p = 0; p < 50; p++) {
            cout << (p * 2 < progreso ? "=" : " ");
        }
        cout << "] " << progreso << "%";
        
        // Movimiento de las olas (alterna entre dos frames)
        if (pos_x % 6 < 3) {
            for (int x = 5; x < 115; x += 4) {
                gotoxy(x, 20); cout << ola[0];
                gotoxy(x, 21); cout << ola[2];
            }
        } else {
            for (int x = 5; x < 115; x += 4) {
                gotoxy(x, 20); cout << ola[1];
                gotoxy(x, 21); cout << ola[0];
            }
        }
        
        Sleep(100); // Velocidad de animación (ajustable)
        
        // Borrar barco para el siguiente frame
        for (int y = 0; y < barco_alto; y++) {
            gotoxy(pos_x, 15 + y); cout << "          ";
        }
    }
    
    // Dibujo final del barco
    for (int y = 0; y < barco_alto; y++) {
        gotoxy(max_x - 3, 15 + y); cout << barco[y];
    }
    
    gotoxy(40, 23); cout << "[================================================] 100%";
    gotoxy(45, 25); cout << "S I S T E M A   L I S T O";
    Sleep(1000);
}

int main() {
    system("mode con: cols=120 lines=30");
    system("title Pantalla de Carga Simplificada");
    
    pantallaCargaSimple();
    
    system("CLS");
    marco();
    gotoxy(40, 15); cout << "CARGA COMPLETADA";
    gotoxy(40, 17); cout << "Presione cualquier tecla para salir...";
    getch();
    
    return 0;
}
