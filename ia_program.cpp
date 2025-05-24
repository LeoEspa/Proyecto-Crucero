#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

// Estructuras de datos
struct Pasajero {
    string nombre;
    int edad;
    string genero;
    string tipo_camarote;
    double precio_pasaje;
};

struct Fecha {
    int dia;
    int mes;
    int año;
};

struct Hora {
    int horas;
    int minutos;
};

struct ReservaCrucero {
    string numero_reserva;
    struct {
        string nombre;
        string pasaporte;
        int edad;
        string genero;
    } solicitante;
    string puerto_salida;
    string destino;
    string linea_crucero;
    string codigo_viaje;
    Fecha fecha_salida;
    Hora hora_embarque;
    string categoria_cabina;
    vector<Pasajero> pasajeros;
    Fecha fecha_reserva;
    bool activa;
};

// Funciones auxiliares
int validar(int ini, int fin) {
    int N;
    do {
        cout << "Ingresa un valor entre (" << ini << "-" << fin << "): ";
        cin >> N;
        if (N < ini || N > fin) cout << "Ingrese un numero valido!\n";
    } while (N < ini || N > fin);
    return N;
}

Fecha leerFecha() {
    Fecha f;
    cout << "Dia: "; f.dia = validar(1, 31);
    cout << "Mes: "; f.mes = validar(1, 12);
    cout << "Año: "; f.año = validar(2023, 2100);
    return f;
}

Hora leerHora() {
    Hora h;
    cout << "Hora (0-23): "; h.horas = validar(0, 23);
    cout << "Minutos (0-59): "; h.minutos = validar(0, 59);
    return h;
}

void guardarReservas(const vector<ReservaCrucero>& reservas) {
    ofstream archivo("info_crucero.dat", ios::binary);
    if (!archivo) {
        cout << "Error al crear el archivo!\n";
        return;
    }

    for (const auto& r : reservas) {
        archivo.write((char*)&r, sizeof(ReservaCrucero));
    }
    archivo.close();
}

vector<ReservaCrucero> cargarReservas() {
    vector<ReservaCrucero> reservas;
    ifstream archivo("info_crucero.dat", ios::binary);
    if (!archivo) return reservas;

    ReservaCrucero r;
    while (archivo.read((char*)&r, sizeof(ReservaCrucero))) {
        reservas.push_back(r);
    }
    archivo.close();
    return reservas;
}

// Funciones del menú
void incluirReserva(vector<ReservaCrucero>& reservas) {
    ReservaCrucero nueva;
    cout << "\n--- NUEVA RESERVA ---\n";
    
    cout << "Numero de reserva: "; cin >> nueva.numero_reserva;
    
    cout << "\nDatos del solicitante:\n";
    cout << "Nombre: "; cin.ignore(); getline(cin, nueva.solicitante.nombre);
    cout << "Pasaporte: "; getline(cin, nueva.solicitante.pasaporte);
    cout << "Edad: "; nueva.solicitante.edad = validar(1, 120);
    cout << "Genero (M/F): "; 
    nueva.solicitante.genero = (validar(1, 2) == 1) ? "Masculino" : "Femenino";
    
    cout << "\nDatos del viaje:\n";
    cout << "Puerto de salida: "; getline(cin, nueva.puerto_salida);
    cout << "Destino: "; getline(cin, nueva.destino);
    cout << "Linea de crucero: "; getline(cin, nueva.linea_crucero);
    cout << "Codigo de viaje: "; getline(cin, nueva.codigo_viaje);
    
    cout << "\nFecha de salida:\n";
    nueva.fecha_salida = leerFecha();
    
    cout << "\nHora de embarque:\n";
    nueva.hora_embarque = leerHora();
    
    cout << "Categoria de cabina (1.Interior 2.Exterior 3.Balcon 4.Suite): ";
    int op = validar(1, 4);
    nueva.categoria_cabina = (op == 1) ? "Interior" : 
                            (op == 2) ? "Exterior" : 
                            (op == 3) ? "Balcon" : "Suite";
    
    cout << "\nNumero de pasajeros (1-4): ";
    int num_pasajeros = validar(1, 4);
    
    for (int i = 0; i < num_pasajeros; i++) {
        Pasajero p;
        cout << "\nPasajero " << i+1 << ":\n";
        cout << "Nombre: "; cin.ignore(); getline(cin, p.nombre);
        cout << "Edad: "; p.edad = validar(1, 120);
        cout << "Genero (1.Masculino 2.Femenino): ";
        p.genero = (validar(1, 2) == 1) ? "Masculino" : "Femenino";
        cout << "Tipo de camarote: "; getline(cin, p.tipo_camarote);
        cout << "Precio pasaje (EUR): "; cin >> p.precio_pasaje;
        nueva.pasajeros.push_back(p);
    }
    
    cout << "\nFecha de reserva:\n";
    nueva.fecha_reserva = leerFecha();
    nueva.activa = true;
    
    reservas.push_back(nueva);
    guardarReservas(reservas);
    cout << "\nReserva registrada exitosamente!\n";
}

void consultarReserva(const vector<ReservaCrucero>& reservas) {
    cout << "\n--- CONSULTAR RESERVA ---\n";
    cout << "Buscar por: 1.Numero 2.Nombre solicitante: ";
    int op = validar(1, 2);
    
    if (op == 1) {
        string num;
        cout << "Ingrese numero de reserva: "; cin >> num;
        
        for (const auto& r : reservas) {
            if (r.numero_reserva == num) {
                cout << "\nReserva encontrada:\n";
                cout << "Solicitante: " << r.solicitante.nombre << endl;
                cout << "Destino: " << r.destino << endl;
                cout << "Estado: " << (r.activa ? "Activa" : "Cancelada") << endl;
                return;
            }
        }
    } else {
        string nombre;
        cout << "Ingrese nombre del solicitante: "; 
        cin.ignore(); getline(cin, nombre);
        
        for (const auto& r : reservas) {
            if (r.solicitante.nombre == nombre) {
                cout << "\nReserva encontrada:\n";
                cout << "Numero: " << r.numero_reserva << endl;
                cout << "Destino: " << r.destino << endl;
                cout << "Estado: " << (r.activa ? "Activa" : "Cancelada") << endl;
                return;
            }
        }
    }
    cout << "\nReserva no encontrada!\n";
}

// [Resto de funciones del menú...]

// Funciones de reportes
void reporteLineaCrucero(const vector<ReservaCrucero>& reservas) {
    cout << "\n--- REPORTE POR LINEA DE CRUCERO ---\n";
    string linea;
    cout << "Ingrese linea de crucero: "; 
    cin.ignore(); getline(cin, linea);
    
    cout << "Orden (1.Ascendente 2.Descendente): ";
    int orden = validar(1, 2);
    
    vector<pair<double, ReservaCrucero>> temp;
    double total = 0;
    
    for (const auto& r : reservas) {
        if (r.linea_crucero == linea) {
            double monto = 0;
            for (const auto& p : r.pasajeros) monto += p.precio_pasaje;
            temp.push_back({monto, r});
            total += monto;
        }
    }
    
    if (orden == 1) sort(temp.begin(), temp.end());
    else sort(temp.rbegin(), temp.rend());
    
    for (const auto& [monto, r] : temp) {
        cout << "\nNumero: " << r.numero_reserva;
        cout << "\nDestino: " << r.destino;
        cout << "\nPasajeros: " << r.pasajeros.size();
        cout << "\nMonto: " << monto << " EUR\n";
    }
    cout << "\nTOTAL: " << total << " EUR\n";
}

// [Resto de funciones de reportes...]

int main() {
    vector<ReservaCrucero> reservas = cargarReservas();
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. INCLUIR\n2. CONSULTAR\n3. MODIFICAR\n4. ELIMINAR\n";
        cout << "5. CANCELAR/REACTIVAR\n6. REPORTES\n7. SALIR\n";
        cout << "Opcion: "; opcion = validar(1, 7);

        switch (opcion) {
            case 1: incluirReserva(reservas); break;
            case 2: consultarReserva(reservas); break;
            // case 3: modificarReserva(reservas); break;
            // case 4: eliminarReserva(reservas); break;
            // case 5: cambiarEstadoReserva(reservas); break;
            case 6: 
                cout << "\n--- REPORTES ---\n";
                cout << "1. Por Linea de Crucero\n2. Viajes por Temporada\n";
                cout << "3. Cancelaciones por Edad\n4. Revision de Capacidad\n";
                cout << "Opcion: "; opcion = validar(1, 4);
                
                switch(opcion) {
                    case 1: reporteLineaCrucero(reservas); break;
                    // case 2: reporteTemporada(reservas); break;
                    // case 3: reporteCancelacionesEdad(reservas); break;
                    // case 4: reporteCapacidad(reservas); break;
                }
                break;
            case 7: salir = true; break;
        }
    }

    guardarReservas(reservas);
    cout << "\nDatos guardados. Hasta pronto!\n";
    return 0;
}