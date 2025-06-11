#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
using namespace std;

// Estructuras de datos (con tamaños ajustados)
struct Fecha {
    long int dia, mes, anio;
};

struct Pasajero {
    char nombre[50];
    int edad;
    char genero[15];
    char tipo_camarote[20];
    float precio_pasaje;
};

struct Solicitante {
    char nombre[50];
    char pasaporte[20];
    int edad;
    char genero[15];
    char viaja[3]; // Aumentado a 3 para "Si" + null terminator
};

struct Horario {
    int hora, minuto;
};

struct Reserva {
    char numero_reserva[20];
    Solicitante soli;
    char puerto_salida[50];
    char destino[50];
    char linea_crucero[50];
    char codigo_viaje[20];
    Fecha fecha_salida;
    Horario embarque;
    char categoria_cabina[20];
    Pasajero pasajeros[4];
    int num_pasajeros;
    float precio_total;
    Fecha fecha_reserva;
    bool activa;
};

int main() {
    // Crear 12 reservas con datos variados (ajustando longitudes de strings)
    Reserva reservas[12] = {
        // Reserva 1
        {"RES001", {"Maria Lopez", "P123456", 45, "Femenino", "Si"}, "Miami", "Caribe", "Harmony of the Seas", "VIA001", 
        {15, 6, 2024}, {14, 30}, "Suite", 
        {{"Maria Lopez", 45, "Femenino", "Suite", 2500.0}, {"Carlos Lopez", 16, "Masculino", "Suite", 1800.0}}, 
        2, 4300.0, {10, 5, 2024}, true},
        
        // Reserva 2
        {"RES002", {"Juan Perez", "P654321", 50, "Masculino", "No"}, "Barcelona", "Mediterraneo", "MSC Virtuosa", "VIA002", 
        {20, 7, 2024}, {12, 0}, "Balcon", 
        {{"Ana Garcia", 35, "Femenino", "Balcon", 1200.0}, {"Luis Garcia", 10, "Masculino", "Balcon", 800.0}, {"Sofia Garcia", 8, "Femenino", "Balcon", 800.0}}, 
        3, 2800.0, {15, 4, 2024}, true},
        
        // Reserva 3
        {"RES003", {"Robert Smith", "P987654", 68, "Masculino", "Si"}, "Seattle", "Alaska", "Celebrity Edge", "VIA003", 
        {5, 8, 2024}, {10, 45}, "Exterior", 
        {{"Robert Smith", 68, "Masculino", "Exterior", 3200.0}}, 
        1, 3200.0, {1, 3, 2024}, false},
        
        // Reserva 4
        {"RES004", {"Elena Rodriguez", "P246810", 38, "Femenino", "Si"}, "Venecia", "Islas Griegas", "Queen Mary 2", "VIA004", 
        {12, 9, 2024}, {16, 15}, "Interior", 
        {{"Elena Rodriguez", 38, "Femenino", "Interior", 900.0}, {"Pedro Martinez", 40, "Masculino", "Interior", 900.0}, {"Lucia Martinez", 12, "Femenino", "Interior", 600.0}, {"Pablo Martinez", 8, "Masculino", "Interior", 600.0}}, 
        4, 3000.0, {20, 2, 2024}, true},
        
        // Reserva 5
        {"RES005", {"Martha Johnson", "P135790", 72, "Femenino", "Si"}, "Miami", "Caribe", "Harmony of the Seas", "VIA005", 
        {25, 6, 2024}, {13, 0}, "Suite", 
        {{"Martha Johnson", 72, "Femenino", "Suite", 2800.0}}, 
        1, 2800.0, {5, 1, 2024}, true},
        
        // Reserva 6
        {"RES006", {"David Brown", "P112233", 16, "Masculino", "Si"}, "Barcelona", "Mediterraneo", "MSC Virtuosa", "VIA006", 
        {8, 7, 2024}, {11, 30}, "Balcon", 
        {{"David Brown", 16, "Masculino", "Balcon", 1500.0}}, 
        1, 1500.0, {10, 4, 2024}, false},
        
        // Reserva 7
        {"RES007", {"Laura Wilson", "P445566", 42, "Femenino", "Si"}, "Seattle", "Alaska", "Celebrity Edge", "VIA007", 
        {18, 8, 2024}, {9, 15}, "Suite", 
        {{"Laura Wilson", 42, "Femenino", "Suite", 4100.0}, {"Tom Wilson", 45, "Masculino", "Suite", 4100.0}}, 
        2, 8200.0, {22, 3, 2024}, true},
        
        // Reserva 8
        {"RES008", {"James Taylor", "P778899", 55, "Masculino", "No"}, "Venecia", "Islas Griegas", "Queen Mary 2", "VIA008", 
        {30, 9, 2024}, {17, 45}, "Exterior", 
        {{"Emma Taylor", 52, "Femenino", "Suite", 1800.0}, {"Noah Taylor", 22, "Masculino", "Balcon", 1200.0}}, 
        2, 3000.0, {15, 4, 2024}, true},
        
        // Reserva 9
        {"RES009", {"Sophia Miller", "P554433", 29, "Femenino", "Si"}, "Miami", "Caribe", "Harmony of the Seas", "VIA009", 
        {10, 7, 2024}, {14, 0}, "Interior", 
        {{"Sophia Miller", 29, "Femenino", "Interior", 1100.0}}, 
        1, 1100.0, {1, 6, 2024}, true},
        
        // Reserva 10
        {"RES010", {"Michael Davis", "P221100", 48, "Masculino", "Si"}, "Barcelona", "Mediterraneo", "MSC Virtuosa", "VIA010", 
        {22, 8, 2024}, {15, 30}, "Balcon", 
        {{"Michael Davis", 48, "Masculino", "Balcon", 1300.0}, {"Olivia Davis", 17, "Femenino", "Balcon", 1000.0}, {"Liam Davis", 15, "Masculino", "Balcon", 1000.0}, {"Ava Davis", 12, "Femenino", "Balcon", 800.0}}, 
        4, 4100.0, {10, 2, 2024}, false},
        
        // Reserva 11
        {"RES011", {"Richard Moore", "P331122", 75, "Masculino", "Si"}, "Seattle", "Alaska", "Celebrity Edge", "VIA011", 
        {3, 9, 2024}, {10, 0}, "Exterior", 
        {{"Richard Moore", 75, "Masculino", "Exterior", 2900.0}}, 
        1, 2900.0, {12, 1, 2024}, false},
        
        // Reserva 12
        {"RES012", {"Jennifer Lee", "P998877", 33, "Femenino", "Si"}, "Venecia", "Islas Griegas", "Queen Mary 2", "VIA012", 
        {14, 10, 2024}, {16, 0}, "Suite", 
        {{"Jennifer Lee", 33, "Femenino", "Suite", 2700.0}, {"Daniel Lee", 35, "Masculino", "Suite", 2700.0}, {"Mia Lee", 5, "Femenino", "Suite", 500.0}}, 
        3, 5900.0, {20, 3, 2024}, true}
    };

    // Crear el archivo binario
    ofstream archivo("CRUCEROS.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al crear el archivo!";
        return 1;
    }

    // Escribir las reservas en el archivo
    for (int i = 0; i < 12; i++) {
        archivo.write(reinterpret_cast<char*>(&reservas[i]), sizeof(Reserva));
    }

    archivo.close();
    cout << "Archivo CRUCEROS.dat creado exitosamente con 12 reservas!";
    return 0;
}