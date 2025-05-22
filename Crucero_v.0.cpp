//Proyecto-Crucero

#include <iostream>
#include <string>

using namespace std;


//Estrutura pasajeros
struct Pasajeros{
	string NombreDelSolicitante;
	string Genero;
	int Edad, Npasaporte, Nreserva;
	
};


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
