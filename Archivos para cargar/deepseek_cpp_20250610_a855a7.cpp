#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

// Definición de estructuras (igual que en el código original)
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
    char viaja[2];
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

void crearArchivoEjemplo() {
    ofstream archivo("CRUCEROS.dat", ios::binary);
    if (!archivo) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    // Reserva 1: Individual, solicitante viaja solo
    Reserva r1;
    strcpy(r1.numero_reserva, "RES0012024");
    strcpy(r1.soli.nombre, "Juan Perez");
    strcpy(r1.soli.pasaporte, "AB123456");
    r1.soli.edad = 35;
    strcpy(r1.soli.genero, "Masculino");
    strcpy(r1.soli.viaja, "Si");
    strcpy(r1.puerto_salida, "Miami");
    strcpy(r1.destino, "Caribe");
    strcpy(r1.linea_crucero, "Harmony of the Seas");
    strcpy(r1.codigo_viaje, "CAR20240601");
    r1.fecha_salida = {15, 6, 2024};
    r1.embarque = {14, 30};
    strcpy(r1.categoria_cabina, "Interior");
    r1.num_pasajeros = 1;
    strcpy(r1.pasajeros[0].nombre, "Juan Perez");
    r1.pasajeros[0].edad = 35;
    strcpy(r1.pasajeros[0].genero, "Masculino");
    strcpy(r1.pasajeros[0].tipo_camarote, "INT-101");
    r1.pasajeros[0].precio_pasaje = 1200.50;
    r1.fecha_reserva = {10, 5, 2024};
    r1.activa = true;
    r1.precio_total = 1200.50;
    archivo.write((char*)&r1, sizeof(Reserva));

    // Reserva 2: Familiar (solicitante + 3 pasajeros)
    Reserva r2;
    strcpy(r2.numero_reserva, "RES0022024");
    strcpy(r2.soli.nombre, "Maria Gonzalez");
    strcpy(r2.soli.pasaporte, "CD654321");
    r2.soli.edad = 42;
    strcpy(r2.soli.genero, "Femenino");
    strcpy(r2.soli.viaja, "Si");
    strcpy(r2.puerto_salida, "Barcelona");
    strcpy(r2.destino, "Mediterraneo");
    strcpy(r2.linea_crucero, "MSC Virtuosa");
    strcpy(r2.codigo_viaje, "MED20240715");
    r2.fecha_salida = {20, 7, 2024};
    r2.embarque = {12, 0};
    strcpy(r2.categoria_cabina, "Balcon");
    r2.num_pasajeros = 4;
    
    // Pasajero 1 (solicitante)
    strcpy(r2.pasajeros[0].nombre, "Maria Gonzalez");
    r2.pasajeros[0].edad = 42;
    strcpy(r2.pasajeros[0].genero, "Femenino");
    strcpy(r2.pasajeros[0].tipo_camarote, "BAL-202");
    r2.pasajeros[0].precio_pasaje = 1800.00;
    
    // Pasajero 2
    strcpy(r2.pasajeros[1].nombre, "Carlos Gonzalez");
    r2.pasajeros[1].edad = 45;
    strcpy(r2.pasajeros[1].genero, "Masculino");
    strcpy(r2.pasajeros[1].tipo_camarote, "BAL-202");
    r2.pasajeros[1].precio_pasaje = 1800.00;
    
    // Pasajero 3
    strcpy(r2.pasajeros[2].nombre, "Ana Gonzalez");
    r2.pasajeros[2].edad = 16;
    strcpy(r2.pasajeros[2].genero, "Femenino");
    strcpy(r2.pasajeros[2].tipo_camarote, "BAL-202");
    r2.pasajeros[2].precio_pasaje = 1500.00;
    
    // Pasajero 4
    strcpy(r2.pasajeros[3].nombre, "Luis Gonzalez");
    r2.pasajeros[3].edad = 12;
    strcpy(r2.pasajeros[3].genero, "Masculino");
    strcpy(r2.pasajeros[3].tipo_camarote, "BAL-202");
    r2.pasajeros[3].precio_pasaje = 1200.00;
    
    r2.fecha_reserva = {5, 6, 2024};
    r2.activa = true;
    r2.precio_total = 6300.00;
    archivo.write((char*)&r2, sizeof(Reserva));

    // Reserva 3: Grupo (solicitante no viaja)
    Reserva r3;
    strcpy(r3.numero_reserva, "RES0032024");
    strcpy(r3.soli.nombre, "Agencia Viajes SA");
    strcpy(r3.soli.pasaporte, "AG987654");
    r3.soli.edad = 0; // No aplica
    strcpy(r3.soli.genero, "Masculino");
    strcpy(r3.soli.viaja, "No");
    strcpy(r3.puerto_salida, "Venecia");
    strcpy(r3.destino, "Islas Griegas");
    strcpy(r3.linea_crucero, "Celebrity Edge");
    strcpy(r3.codigo_viaje, "GRI20240810");
    r3.fecha_salida = {10, 8, 2024};
    r3.embarque = {16, 0};
    strcpy(r3.categoria_cabina, "Suite");
    r3.num_pasajeros = 4;
    
    // Pasajero 1
    strcpy(r3.pasajeros[0].nombre, "Roberto Jimenez");
    r3.pasajeros[0].edad = 55;
    strcpy(r3.pasajeros[0].genero, "Masculino");
    strcpy(r3.pasajeros[0].tipo_camarote, "SUI-301");
    r3.pasajeros[0].precio_pasaje = 2500.00;
    
    // Pasajero 2
    strcpy(r3.pasajeros[1].nombre, "Laura Jimenez");
    r3.pasajeros[1].edad = 52;
    strcpy(r3.pasajeros[1].genero, "Femenino");
    strcpy(r3.pasajeros[1].tipo_camarote, "SUI-301");
    r3.pasajeros[1].precio_pasaje = 2500.00;
    
    // Pasajero 3
    strcpy(r3.pasajeros[2].nombre, "Pedro Jimenez");
    r3.pasajeros[2].edad = 28;
    strcpy(r3.pasajeros[2].genero, "Masculino");
    strcpy(r3.pasajeros[2].tipo_camarote, "SUI-302");
    r3.pasajeros[2].precio_pasaje = 2200.00;
    
    // Pasajero 4
    strcpy(r3.pasajeros[3].nombre, "Sofia Jimenez");
    r3.pasajeros[3].edad = 25;
    strcpy(r3.pasajeros[3].genero, "Femenino");
    strcpy(r3.pasajeros[3].tipo_camarote, "SUI-302");
    r3.pasajeros[3].precio_pasaje = 2200.00;
    
    r3.fecha_reserva = {15, 4, 2024};
    r3.activa = true;
    r3.precio_total = 9400.00;
    archivo.write((char*)&r3, sizeof(Reserva));

    // Reserva 4: Cancelada
    Reserva r4;
    strcpy(r4.numero_reserva, "RES0042024");
    strcpy(r4.soli.nombre, "Carlos Ruiz");
    strcpy(r4.soli.pasaporte, "EF456789");
    r4.soli.edad = 60;
    strcpy(r4.soli.genero, "Masculino");
    strcpy(r4.soli.viaja, "Si");
    strcpy(r4.puerto_salida, "Sídney");
    strcpy(r4.destino, "Alaska");
    strcpy(r4.linea_crucero, "Queen Mary 2");
    strcpy(r4.codigo_viaje, "ALA20240905");
    r4.fecha_salida = {5, 9, 2024};
    r4.embarque = {10, 0};
    strcpy(r4.categoria_cabina, "Exterior");
    r4.num_pasajeros = 2;
    
    // Pasajero 1 (solicitante)
    strcpy(r4.pasajeros[0].nombre, "Carlos Ruiz");
    r4.pasajeros[0].edad = 60;
    strcpy(r4.pasajeros[0].genero, "Masculino");
    strcpy(r4.pasajeros[0].tipo_camarote, "EXT-105");
    r4.pasajeros[0].precio_pasaje = 2000.00;
    
    // Pasajero 2
    strcpy(r4.pasajeros[1].nombre, "Elena Ruiz");
    r4.pasajeros[1].edad = 58;
    strcpy(r4.pasajeros[1].genero, "Femenino");
    strcpy(r4.pasajeros[1].tipo_camarote, "EXT-105");
    r4.pasajeros[1].precio_pasaje = 2000.00;
    
    r4.fecha_reserva = {20, 3, 2024};
    r4.activa = false; // Cancelada
    r4.precio_total = 4000.00;
    archivo.write((char*)&r4, sizeof(Reserva));

    // Reserva 5: Diferente categoría de cabina
    Reserva r5;
    strcpy(r5.numero_reserva, "RES0052024");
    strcpy(r5.soli.nombre, "Ana Martinez");
    strcpy(r5.soli.pasaporte, "GH789012");
    r5.soli.edad = 28;
    strcpy(r5.soli.genero, "Femenino");
    strcpy(r5.soli.viaja, "Si");
    strcpy(r5.puerto_salida, "Miami");
    strcpy(r5.destino, "Caribe");
    strcpy(r5.linea_crucero, "Harmony of the Seas");
    strcpy(r5.codigo_viaje, "CAR20240620");
    r5.fecha_salida = {20, 6, 2024};
    r5.embarque = {15, 0};
    strcpy(r5.categoria_cabina, "Suite");
    r5.num_pasajeros = 1;
    
    // Pasajero 1 (solicitante)
    strcpy(r5.pasajeros[0].nombre, "Ana Martinez");
    r5.pasajeros[0].edad = 28;
    strcpy(r5.pasajeros[0].genero, "Femenino");
    strcpy(r5.pasajeros[0].tipo_camarote, "SUI-401");
    r5.pasajeros[0].precio_pasaje = 3000.00;
    
    r5.fecha_reserva = {1, 5, 2024};
    r5.activa = true;
    r5.precio_total = 3000.00;
    archivo.write((char*)&r5, sizeof(Reserva));

    // Reserva 6: Diferente destino
    Reserva r6;
    strcpy(r6.numero_reserva, "RES0062024");
    strcpy(r6.soli.nombre, "Luis Fernandez");
    strcpy(r6.soli.pasaporte, "IJ012345");
    r6.soli.edad = 50;
    strcpy(r6.soli.genero, "Masculino");
    strcpy(r6.soli.viaja, "Si");
    strcpy(r6.puerto_salida, "Barcelona");
    strcpy(r6.destino, "Mediterraneo");
    strcpy(r6.linea_crucero, "MSC Virtuosa");
    strcpy(r6.codigo_viaje, "MED20240725");
    r6.fecha_salida = {25, 7, 2024};
    r6.embarque = {11, 30};
    strcpy(r6.categoria_cabina, "Balcon");
    r6.num_pasajeros = 2;
    
    // Pasajero 1 (solicitante)
    strcpy(r6.pasajeros[0].nombre, "Luis Fernandez");
    r6.pasajeros[0].edad = 50;
    strcpy(r6.pasajeros[0].genero, "Masculino");
    strcpy(r6.pasajeros[0].tipo_camarote, "BAL-203");
    r6.pasajeros[0].precio_pasaje = 1900.00;
    
    // Pasajero 2
    strcpy(r6.pasajeros[1].nombre, "Marta Fernandez");
    r6.pasajeros[1].edad = 48;
    strcpy(r6.pasajeros[1].genero, "Femenino");
    strcpy(r6.pasajeros[1].tipo_camarote, "BAL-203");
    r6.pasajeros[1].precio_pasaje = 1900.00;
    
    r6.fecha_reserva = {10, 6, 2024};
    r6.activa = true;
    r6.precio_total = 3800.00;
    archivo.write((char*)&r6, sizeof(Reserva));

    // Reserva 7: Diferente línea de crucero
    Reserva r7;
    strcpy(r7.numero_reserva, "RES0072024");
    strcpy(r7.soli.nombre, "Sara Lopez");
    strcpy(r7.soli.pasaporte, "KL123456");
    r7.soli.edad = 33;
    strcpy(r7.soli.genero, "Femenino");
    strcpy(r7.soli.viaja, "Si");
    strcpy(r7.puerto_salida, "Venecia");
    strcpy(r7.destino, "Islas Griegas");
    strcpy(r7.linea_crucero, "Celebrity Edge");
    strcpy(r7.codigo_viaje, "GRI20240815");
    r7.fecha_salida = {15, 8, 2024};
    r7.embarque = {17, 0};
    strcpy(r7.categoria_cabina, "Interior");
    r7.num_pasajeros = 1;
    
    // Pasajero 1 (solicitante)
    strcpy(r7.pasajeros[0].nombre, "Sara Lopez");
    r7.pasajeros[0].edad = 33;
    strcpy(r7.pasajeros[0].genero, "Femenino");
    strcpy(r7.pasajeros[0].tipo_camarote, "INT-102");
    r7.pasajeros[0].precio_pasaje = 1100.00;
    
    r7.fecha_reserva = {20, 5, 2024};
    r7.activa = true;
    r7.precio_total = 1100.00;
    archivo.write((char*)&r7, sizeof(Reserva));

    // Reserva 8: Pasajeros de diferentes edades
    Reserva r8;
    strcpy(r8.numero_reserva, "RES0082024");
    strcpy(r8.soli.nombre, "Pedro Sanchez");
    strcpy(r8.soli.pasaporte, "MN234567");
    r8.soli.edad = 40;
    strcpy(r8.soli.genero, "Masculino");
    strcpy(r8.soli.viaja, "Si");
    strcpy(r8.puerto_salida, "Sídney");
    strcpy(r8.destino, "Alaska");
    strcpy(r8.linea_crucero, "Queen Mary 2");
    strcpy(r8.codigo_viaje, "ALA20240910");
    r8.fecha_salida = {10, 9, 2024};
    r8.embarque = {9, 0};
    strcpy(r8.categoria_cabina, "Exterior");
    r8.num_pasajeros = 3;
    
    // Pasajero 1 (solicitante)
    strcpy(r8.pasajeros[0].nombre, "Pedro Sanchez");
    r8.pasajeros[0].edad = 40;
    strcpy(r8.pasajeros[0].genero, "Masculino");
    strcpy(r8.pasajeros[0].tipo_camarote, "EXT-106");
    r8.pasajeros[0].precio_pasaje = 2100.00;
    
    // Pasajero 2
    strcpy(r8.pasajeros[1].nombre, "Lucia Sanchez");
    r8.pasajeros[1].edad = 38;
    strcpy(r8.pasajeros[1].genero, "Femenino");
    strcpy(r8.pasajeros[1].tipo_camarote, "EXT-106");
    r8.pasajeros[1].precio_pasaje = 2100.00;
    
    // Pasajero 3
    strcpy(r8.pasajeros[2].nombre, "Pablo Sanchez");
    r8.pasajeros[2].edad = 10;
    strcpy(r8.pasajeros[2].genero, "Masculino");
    strcpy(r8.pasajeros[2].tipo_camarote, "EXT-106");
    r8.pasajeros[2].precio_pasaje = 1000.00;
    
    r8.fecha_reserva = {25, 4, 2024};
    r8.activa = true;
    r8.precio_total = 5200.00;
    archivo.write((char*)&r8, sizeof(Reserva));

    archivo.close();
    cout << "Archivo CRUCEROS.dat creado con 8 registros de ejemplo." << endl;
}

int main() {
    crearArchivoEjemplo();
    return 0;
}