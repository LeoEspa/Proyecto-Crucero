//Proyecto-Crucero

#include <iostream>
#include <string>

using namespace std;

// Estructura para un pasajero
struct Pasajero {
    string nombre;
    int edad;
    string genero;           // "Masculino" o "Femenino"
    string tipo_camarote;    // "Interior", "Exterior", "Balcón", "Suite"
    double precio_pasaje;    // Precio en euros
};

// Estructura para fecha (salida y reserva)
struct Fecha {
    int dia;
    int mes;
    int año;
};

// Estructura para hora de embarque
struct Hora {
    int horas;
    int minutos;
};

// Estructura principal de reserva
struct ReservaCrucero {
    string numero_reserva;   // Identificador único
    
    struct {
        string nombre;
        string pasaporte;
        int edad;
        string genero;
    } solicitante;
    
    string puerto_salida;    // Ej: Miami, Barcelona
    string destino;          // Ej: Caribe, Mediterráneo
    string linea_crucero;    // Ej: "Harmony of the Seas"
    string codigo_viaje;     // Código de itinerario
    
    Fecha fecha_salida;
    Hora hora_embarque;
    string categoria_cabina; // "Interior", "Exterior", etc.
    
    vector<Pasajero> pasajeros;  // Máximo 4 pasajeros
    Fecha fecha_reserva;
    bool activa;            // true = activa, false = cancelada
}; de 

int validar(int ini, int fin){
	int N;
	do{
		cout<<"Ingresa un valor entre ("<<ini<< "-" <<fin<<") ";cin>>N;
		if(N<ini||N>fin)cout<<"Ingrese un numero valido entre ("<<ini<< "-" <<fin<<")";
		
	}while(N<ini||N>fin); return N;
}//Fin de la funcion validar



//Inicio de la Funció Main
int main() {
	
int opcion;
bool salir = false;


//Despliegue del Menu de Opciones
    while (!salir) {
        cout << "\n--- MENU OPCIONES ---" << endl;
        cout << "1. INCLUIR" << endl;
        cout << "2. CONSULTAR" << endl;
        cout << "3. MODIFICAR" << endl;
        cout << "4. ELIMINAR" << endl;
        cout << "5. CANCELAR/REACTIVAR" << endl;
        cout << "6. REPORTES" << endl;
        cout << "7. SALIR" << endl;
        cout << "Ingrese opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarDatos(estados, numEstados);
                break;
                
            case 2:
                mostrarDatos(estados, numEstados);
                break;
                
            case 3:
                mostrarGanadoresPorEstado(estados, numEstados);
                break;
                
            case 4:
                totalVotosPartido(estados, numEstados);
                break;
                
            case 5:
                calcularAbstencion(estados, numEstados);
                break;
                
            case 6: //Despliegue del menun de opciones para el Menu de Reportes
            	
        bool salir2=false; int opcion2;
        
        while (!salir2) {
        cout << "\n--- MENU OPCIONES DE REPORTE ---" << endl;
        cout << "1. CONSULTAS POR LINEA DE CRUCERO" << endl;
        cout << "2. VIAJES POR TEMPORADA" << endl;
        cout << "3. CANCELACION POR EDAD" << endl;
        cout << "4. REVISION DE CAPACIDADES DE CABINA" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese opción: ";
        cin >> opcion;

        switch (opcion2) {
            case 1:
                cargarDatos(estados, numEstados);
                break;
                
            case 2:
                mostrarDatos(estados, numEstados);
                break;
                
            case 3:
                mostrarGanadoresPorEstado(estados, numEstados);
                break;
                
            case 4:
                totalVotosPartido(estados, numEstados);
                break;
                
           
            case 5:
            	cout<<"---Saliendo del Menu de Opciones de Reporte---"<<endl;
                salir2 = true;
                break;
            default:
                cout << "---Opcion invalida!---" << endl;
        }
    }
        //Cierre del menu de opcione para el Menu de Reportes
                break;
                
            case 7:
            	cout<<"---Saliendo del Menu de Opciones---"<<endl;
                salir = true;
                break;
            default:
                cout << "---Opcion invalida!---" << endl;
        }
    }//Fin del Menu de opciones Global

	
	
	
	
	
	
	
	return 0;
}//Fin de la Función Main
