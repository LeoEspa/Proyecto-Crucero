#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <locale.h>
//Para los colores de la terminal

#define color SetConsoleTextAttribute
using namespace std;

// Estructuras de datos
struct Fecha {
    long int dia, mes, anio; //Long int para la validacion.
};

struct Pasajero {
    char nombre[50];
    int edad;
    char genero[15];
    char tipo_camarote[20];
    float precio_pasaje;
};

struct Solicitante{
	char nombre[50];
    char pasaporte[20];
    int edad;
    char genero[15];
	char viaja[2];
};

struct Horario{
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

// Prototipos de funciones, vayan agregandolas aqui?
void gotoxy(int x, int y);
void marco();
void pantallaCargaSimple();
void incluir();
long int validar_numero(long int ini,long int fin, string entrada, int pos1, int pos2);
char validar_dosletras(string entrada, int pos1, int pos2,const char letra1[],const char letra2[],const char minuscula1[],const char minuscula2[]);
double validar_float(int ini, int fin, string entrada, int pos1, int pos2);
int buscarReserva(char numero[20], Reserva &res);
void consultar();
void mostrarReservaCompleta(Reserva res); // Para mostrar todos los detalles de una reserva
void modificarReserva();
void modificarDatosReserva(Reserva res);
void eliminarReserva();
void cancelarReactivar();

//Prototipo Bryan
void reportes();
void reporteLineaCrucero();
void reporteViajesTemporada();
void mostrarReservaSimple(Reserva r); // Complementaria para op 1
void mostrar2(int pos1, int pos2, int desde, int hasta, Fecha fecha); // Complementaria para op 2
void borrarLinea(int x, int y); // Borra lineas en ambas funciones de reportes

//Prototipo Fort
void CancelacionesPorEdadDestino();
void revisionCapacidadCabina();
// Funcion principal

int main() {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//Colores terminal
	 color(hConsole, 31);
    setlocale(LC_ALL, "spanish");
    int op;

    system("mode con: cols=120 lines=30");
    system("title Pantalla de Carga Simplificada");

    pantallaCargaSimple();

    system("CLS");
    marco();
    gotoxy(40, 15); cout << "CARGA COMPLETADA";
    gotoxy(40, 17); cout << "Presione cualquier tecla para continuar...";
    getch();
    do {
        system("CLS");
        marco();
        gotoxy(40, 3); cout << "OCEANO AZUL - SISTEMA DE RESERVAS";
        gotoxy(40, 6); cout << "1. INCLUIR RESERVA";
        gotoxy(40, 8); cout << "2. CONSULTAR RESERVA";
        gotoxy(40, 10); cout << "3. MODIFICAR RESERVA";
        gotoxy(40, 12); cout << "4. ELIMINAR RESERVA";
        gotoxy(40, 14); cout << "5. CANCELAR/REACTIVAR";
        gotoxy(40, 16); cout << "6. REPORTES";
        gotoxy(40, 18); cout << "0. SALIR";
		gotoxy(40, 22); cout << "OPCION: ";
		cin >> op;

        switch(op) {
            case 1: incluir(); break;
            case 2: consultar(); break;
            case 3: modificarReserva(); break;
            case 4: eliminarReserva(); break;
            case 5: cancelarReactivar(); break;
            case 6: reportes(); break;
        }
    } while(op != 0);

    return 0;
}

// Implementacion de funciones
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}//Fin

// Estetica
void marco() {
    int x;
    for (x = 1; x <= 118; x++) {
        gotoxy(x, 1); printf("=");
        gotoxy(x, 29); printf("=");
        if (x <= 29) {
            gotoxy(1, x); printf("|");
            gotoxy(118, x); printf("|");
        }
    }
}//Fin de la funcion Marco

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

    // Olas mÃ¡s detalladas
    const char* ola[] = {"~~", "_\\_", "~/~"};

    gotoxy(45, 8); cout << "C A R G A N D O   S I S T E M A";

    // Dibujar olas estÃ¡ticas
    for (int x = 5; x < 115; x += 4) {
        gotoxy(x, 20); cout << ola[0];
        gotoxy(x, 21); cout << ola[1];
        gotoxy(x+2, 22); cout << ola[2];
    }

    // AnimaciÃ³n de un solo recorrido
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

        Sleep(100); // Velocidad de animaciÃ³n (ajustable)

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

bool validarHoraEmbarque(int horas, int minutos) {
    if (horas < 0 || horas > 23) return false;
    if (minutos < 0 || minutos > 59) return false;
    return true;
}//Fin validar hora de embarque

int buscarReserva(char numero[20], Reserva &res) {
    int encontrado = 0;
    FILE *arch = fopen("CRUCEROS.dat", "rb");
    if (arch != NULL) {
        Reserva temp_res;
        while (fread(&temp_res, sizeof(Reserva), 1, arch) == 1) {
            if (strcmp(temp_res.numero_reserva, numero) == 0) {
                res = temp_res;
                encontrado = 1;
                break;
            }
        }
        fclose(arch);
    }
    return encontrado;
}//Fin de Buscar Reserva

float calcularPrecioTotal(Reserva &r) {
    float total = 0;
    for (int i = 0; i < r.num_pasajeros; i++) {
        total += r.pasajeros[i].precio_pasaje;
    }
    return total;
}//Fin calucar Precio Total

long int validar_numero(long int ini,long int fin, string entrada, int pos1, int pos2) {
    long int n;
    int i=pos1, j=pos2, cont=0;
	do {
      gotoxy(i,j);
	  cout << "                                                 ";
      gotoxy(i,j);
      cout << entrada;
      cin >> n;
      if (n < ini || n > fin) {
			cont++;
			system("cls");
			marco();
			i=40;
			j=9;
			gotoxy(i,j);
			cout << "OPCION INVALIDA, PORFAVOR INTENTE DE NUEVO.";
			if(cont%3==0){ j=10;
				gotoxy(i,j);
				cout<<"Recuerde que debe ser de "<<ini<<" a "<<fin<<".";
			}
			j=11;
        } else {
            break;
        }
	} while (n < ini || n > fin);
    return (n);
}//Fin validar numero

char validar_dosletras(string entrada, int pos1, int pos2,const char letra1[],const char letra2[],const char minuscula1[],const char minuscula2[]){
	char aux[2];
    int i=pos1, j=pos2;
	do{
		gotoxy(i, j);
		cout << "                                                 "; 
		gotoxy(i, j);
		cout<< entrada;
		fflush(stdin);
		gets(aux);
		if(strcmp(aux,letra1)==0 || strcmp(aux,minuscula1)==0 || strcmp(aux,letra2)==0 || strcmp(aux,minuscula2)==0) {
			return(aux[0]);
		}
		else{
   		    system("cls");
			marco();
			i=10;
			j=10;
			gotoxy(i,j);
			cout<<"OPCION INVALIDA, PORFAVOR INTENTE DE NUEVO.";
			j=11;
		}
	} while(true);

}//Fin Validar Genero

double validar_float(int ini, int fin, string entrada, int pos1, int pos2) {
    double n;
	int cont=0, i=pos1, j=pos2;
	do {
        gotoxy(i,j);
		cout << "                                                 ";
        gotoxy(i,j);
		cout << entrada; cin >> n;
        if (n < ini || n > fin) {
			    cont++;
			    system("cls");
				marco();
				i=40;
				j=9;
				gotoxy(i,j);
				cout << "OPCION INVALIDA, PORFAVOR INTENTE DE NUEVO.";
				if(cont%3==0){ j=10;
					gotoxy(i,j);
					cout<<"Recuerde que debe ser de "<<ini<<" a "<<fin<<".";
			    }
			    j=11;
        } else {
            break;
        }
	}while (true);
    return n;
}//Fin Validar Float

void mostrar(int pos1, int pos2, int desde, int hasta, Reserva nueva){
	int op;
 	system("CLS");
 	marco();
	for(op=desde;op<=hasta;op++,pos2++)
	{
	gotoxy(pos1,pos2);
	switch(op){
		case 1: cout << "Nombre del solicitante: " << nueva.soli.nombre; break;
		case 2: cout << "Pasaporte: " << nueva.soli.pasaporte; break;
		case 3: cout << "Edad: " << nueva.soli.edad; break;
		case 4: cout << "Genero (M/F) : " << nueva.soli.genero; break;
		case 5: cout << "El solicitante viaja?: " << nueva.soli.viaja;break;
		case 6: cout << "Puerto de salida: " << nueva.puerto_salida; break;
		case 7: cout << "Destino: " << nueva.destino; break;
		case 8: cout << "Codigo de viaje: " << nueva.codigo_viaje; break;
		case 9: cout << "Categoria de cabina: " << nueva.categoria_cabina; break;
		case 10: cout << "Mes de salida: " <<  nueva.fecha_salida.mes; break;
		case 11: cout << "Dia de salida: " <<  nueva.fecha_salida.dia; break;
		case 12: cout << "Ano de salida: " << nueva.fecha_salida.anio; break;
		case 13: cout << "Hora de embarque: "<<nueva.embarque.hora; break;
		case 14: cout << "Minuto de embarque: "<<nueva.embarque.minuto; break;
		case 15: cout << "Mes de reserva: " <<nueva.fecha_reserva.mes; break;
		case 16: cout << "Dia de reserva: " << nueva.fecha_reserva.dia; break;
		case 17: cout << "Ano de reserva: " << nueva.fecha_reserva.anio; break;
		default: ;
		}
	}
}//Fin Mostrar

void mostrar_pasajeros(int pos1, int pos2, int desde, int hasta, Reserva nueva, int npasajero){

	int op;
 	system("CLS");
 	marco();
	for(op=desde;op<=hasta;op++,pos2++)
	{
	gotoxy(pos1,pos2);
	switch(op){
		case 1: cout << "Nombre: " << nueva.pasajeros[npasajero].nombre; break;
		case 2: cout << "Edad: " << nueva.pasajeros[npasajero].edad; break;
		case 3: cout << "Genero: " << nueva.pasajeros[npasajero].genero; break;
		case 4: cout << "Tipo de camarote: " << nueva.pasajeros[npasajero].tipo_camarote; break;
		case 5: cout << "Precio en euros:  " << nueva.pasajeros[npasajero].precio_pasaje; break;
		default: ;
		}
	}
}//Fin Mostrar Pasajeros

void incluir(){

	setlocale(LC_ALL, "spanish");
    Reserva nueva;
	char temp;
	int i, j, n, x, y = 7;
	system("CLS");
    marco();
    gotoxy(40, 12); cout << "INGRESANDO NUEVA RESERVA....";
    gotoxy(40, 14); cout << "Numero de reserva: ";
	fflush(stdin);
    gets(nueva.numero_reserva);

    if (buscarReserva(nueva.numero_reserva, nueva) == 0) {
        // Datos del solicitante
		system("cls");
		marco();
		gotoxy(3,2); cout<< "Numero de reserva: "<<nueva.numero_reserva;
		gotoxy(3,6); cout << "Nombre del solicitante: ";
        fflush(stdin);
        gets(nueva.soli.nombre);
        gotoxy(3, 7); cout << "Pasaporte: ";
        fflush(stdin);
        gets(nueva.soli.pasaporte);
        nueva.soli.edad=validar_numero(1,100,"Edad (1 al 100): ",3,8);
        //Carga y pregunta genero.
		mostrar(3,6,1,3,nueva);
		gotoxy(3,2); cout<< "Numero de reserva: "<<nueva.numero_reserva; //Encabezado
		temp=validar_dosletras("Genero (M/F): ",3,9,"M","F","m","f");
		if (temp == 'm' || temp== 'M'){
		strcpy(nueva.soli.genero,"Masculino");}
        else strcpy(nueva.soli.genero,"Femenino");
        //Carga y pregunta si viaja.
		mostrar(3,6,1,4,nueva);
		gotoxy(3,2); cout<< "Numero de reserva: "<<nueva.numero_reserva; //Encabezado
		gotoxy(3,10); cout<<"El solicitante viaja?: ";
  		gotoxy(3,11); cout<<"<1>Si.";
		gotoxy(3,12); cout<<"<2>No.";
		n=validar_numero(1,2,"Opcion: ",3,13);
		if(n==1) strcpy(nueva.soli.viaja,"Si");
			else strcpy(nueva.soli.viaja,"No");
		//Cargar para mostrar informacion completa.
		mostrar(3,6,1,5,nueva);
		gotoxy(3,2); cout<< "Numero de reserva: "<< nueva.numero_reserva;
		gotoxy(3,12); cout << "INFORMACION DEL SOLICITANTE CARGADA.....";
		gotoxy(3,13); cout<< "Pulse una tecla para continuar."; getch();
        // Datos del viaje
		system("cls");
		marco();
		gotoxy(40,2); cout<< "INFORMACION DEL VIAJE";//Encabezado
		gotoxy(3,6); cout << "Puerto de salida: ";
        fflush(stdin);
        gets(nueva.puerto_salida); gotoxy(3,7);
        cout << "Destino: ";
        fflush(stdin);
        gets(nueva.destino); gotoxy(3,8); cout << "Linea de crucero: ";
        fflush(stdin);
        gets(nueva.linea_crucero);
        gotoxy(3,9); cout << "Codigo de viaje: ";
        fflush(stdin);
        gets(nueva.codigo_viaje);
		gotoxy(3, 10); cout << "Seleccione una opcion de Categoria de cabina:(1-4):"; 
        gotoxy(3, 11); cout << "<1> Interior.";
        gotoxy(3, 12); cout << "<2> Exterior.";
        gotoxy(3, 13); cout << "<3> Balcon.";
        gotoxy(3, 14); cout << "<4> Suite.";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,15);
        switch(op) {
            case 1: strcpy(nueva.categoria_cabina, "Interior"); break;
            case 2: strcpy(nueva.categoria_cabina, "Exterior"); break;
            case 3: strcpy(nueva.categoria_cabina, "Balcon"); break;
            case 4: strcpy(nueva.categoria_cabina, "Suite"); break;
        }
		gotoxy(40,2); cout<< "INFORMACION DEL VIAJE";
		mostrar(3,6,6,9,nueva);
		gotoxy(40,2); cout<< "INFORMACION DEL VIAJE";//Encabezado
		gotoxy(3,12); cout << "INFORMACION DEL VIAJE CARGADA.....";
		gotoxy(3,13); cout<< "Pulse una tecla para continuar."; getch();
        // Fecha de salida
		do {
		system("cls");
		marco();
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.fecha_salida.mes=validar_numero(1,12,"Mes de salida (1-12): ",3,6);
		mostrar(3,6,10,10,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		if(nueva.fecha_salida.mes == 4 || nueva.fecha_salida.mes == 6 || nueva.fecha_salida.mes == 9 || nueva.fecha_salida.mes == 11)nueva.fecha_salida.dia=validar_numero(1,30,"Dia de salida (1-30): ",3,7);
		else nueva.fecha_salida.dia=validar_numero(1,30,"Dia de salida (1-31): ",3,7);
		mostrar(3,6,10,11,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.fecha_salida.anio = validar_numero(2025,2100,"Ano de la salida (2025-2100): ",3,8);
		mostrar(3,6,10,12,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.embarque.hora=validar_numero(0,23,"Hora de embarque (Formato militar 0-23): ",3,9);
		mostrar(3,6,10,13,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.embarque.minuto=validar_numero(0,59,"Minuto de embarque (0-59): ",3,10);
		mostrar(3,6,10,14,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		//Fecha de reserva
		long int total_reserva, total_salida;
		total_salida= nueva.fecha_salida.anio*365 + nueva.fecha_salida.mes * 30 + nueva.fecha_salida.dia;
		nueva.fecha_reserva.mes=validar_numero(1,12,"Mes de reserva (1-12): ",3,11);
		mostrar(3,6,10,15,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		if(nueva.fecha_reserva.mes == 4 || nueva.fecha_reserva.mes == 6 || nueva.fecha_reserva.mes == 9 || nueva.fecha_reserva.mes == 11)nueva.fecha_reserva.dia=validar_numero(1,30,"Dia de reserva (1-30): ",3,12);
		else nueva.fecha_reserva.dia=validar_numero(1,30,"Dia de reserva (1-31): ",3,12);
		mostrar(3,6,10,16,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.fecha_reserva.anio = validar_numero(2024,2100,"Ano de la reserva (2024-2100):",3,13);

		total_reserva = nueva.fecha_reserva.anio * 365 + nueva.fecha_reserva.mes * 30 + nueva.fecha_reserva.dia ;
        if (total_reserva < total_salida) break;
		else{
			gotoxy(3,17); cout<<"Fecha de reserva posterior a la salida. Intentelo de nuevo.";
			getch();
			system("cls");
			mostrar(3,10,10,14,nueva);
			gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
			}
			}while(true);
        mostrar(3,6,10,17,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		gotoxy(3,18); cout << "INFORMACION DE LOS HORARIOS CARGADA.....";
		gotoxy(3,19); cout<< "Pulse una tecla para continuar."; getch();

        // Datos de pasajeros
        system("cls");
		marco();
		gotoxy(40, 12); cout << "INGRESANDO INFORMACION DE PASAJEROS....";
		bool solicitanteViaja = (strcmp(nueva.soli.viaja, "Si") == 0);
	int maxPasajeros = 4; 
	int pasajerosAdicionales = 0;

if (solicitanteViaja) {
    pasajerosAdicionales = validar_numero(0, 3, "Numero de pasajeros adicionales (0-3): ", 40, 14);
    nueva.num_pasajeros = pasajerosAdicionales + 1; // +1 por el solicitante

    // Cargar datos del solicitante como primer pasajero
    strcpy(nueva.pasajeros[0].nombre, nueva.soli.nombre);
    nueva.pasajeros[0].edad = nueva.soli.edad;
    strcpy(nueva.pasajeros[0].genero, nueva.soli.genero);

    system("CLS");
    marco();
    mostrar_pasajeros(3, 6, 1, 3, nueva, 0);
    gotoxy(40, 3); cout << "DATOS DEL PASAJERO 1 (SOLICITANTE)";
    
	gotoxy(3, 9); cout << "Seleccione una opcion de Tipo de camarote:"; 
        gotoxy(3, 10); cout << "<1> Interior.";
        gotoxy(3, 11); cout << "<2> Exterior.";
        gotoxy(3, 12); cout << "<3> Balcon.";
        gotoxy(3, 13); cout << "<4> Suite.";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,14);
        switch(op) {
            case 1: strcpy(nueva.pasajeros[i].tipo_camarote, "Interior"); break;
            case 2: strcpy(nueva.pasajeros[i].tipo_camarote, "Exterior"); break;
            case 3: strcpy(nueva.pasajeros[i].tipo_camarote, "Balcon"); break;
            case 4: strcpy(nueva.pasajeros[i].tipo_camarote, "Suite"); break;
        }
    
    system("CLS");
    marco();
    mostrar_pasajeros(3, 6, 1, 4, nueva, 0);
    gotoxy(40, 3); cout << "DATOS DEL PASAJERO 1 (SOLICITANTE)";
	nueva.pasajeros[0].precio_pasaje = validar_float(1, 10000, "Precio pasaje (EUR): ", 3, 10);

    // Cargar pasajeros adicionales si los hay
    for (int i = 1; i <= pasajerosAdicionales; i++) {
        system("CLS");
        marco();
        gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;

        gotoxy(3, 6); cout << "Nombre: ";
        fflush(stdin);
        gets(nueva.pasajeros[i].nombre);

        nueva.pasajeros[i].edad = validar_numero(1, 100, "Edad (1-100): ", 3, 7);
		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 2, nueva, i);
    	gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
        char genero = validar_dosletras("Genero (M/F):", 3, 8, "M", "F", "m", "f");
        strcpy(nueva.pasajeros[i].genero, (genero == 'M' || genero == 'm') ? "Masculino" : "Femenino");

		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 3, nueva, i);
    	gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
        gotoxy(3, 9); cout << "Seleccione una opcion de Tipo de camarote:"; 
        gotoxy(3, 10); cout << "<1> Interior.";
        gotoxy(3, 11); cout << "<2> Exterior.";
        gotoxy(3, 12); cout << "<3> Balcon.";
        gotoxy(3, 13); cout << "<4> Suite.";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,14);
        switch(op) {
            case 1: strcpy(nueva.pasajeros[i].tipo_camarote, "Interior"); break;
            case 2: strcpy(nueva.pasajeros[i].tipo_camarote, "Exterior"); break;
            case 3: strcpy(nueva.pasajeros[i].tipo_camarote, "Balcon"); break;
            case 4: strcpy(nueva.pasajeros[i].tipo_camarote, "Suite"); break;
        }
		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 4, nueva, i);
    	gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
        nueva.pasajeros[i].precio_pasaje = validar_float(1, 10000, "Precio pasaje (EUR): ", 3, 10);
    }
} else {
    nueva.num_pasajeros = validar_numero(1, 4, "Numero de pasajeros (1-4): ", 40, 14);

    	// Cargar todos los pasajeros
    	for (int i = 0; i < nueva.num_pasajeros; i++) {
        system("CLS");
        marco();
        gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;

        gotoxy(3, 6); cout << "Nombre: ";
        fflush(stdin);
        gets(nueva.pasajeros[i].nombre);
		
        nueva.pasajeros[i].edad = validar_numero(1, 100, "Edad (1-100): ", 3, 7);
		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 2, nueva, i);
        gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
		char genero = validar_dosletras("Genero (M/F):", 3, 8, "M", "F", "m", "f");
        strcpy(nueva.pasajeros[i].genero, (genero == 'M' || genero == 'm') ? "Masculino" : "Femenino");

		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 3, nueva, i);
        gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
		gotoxy(3, 9); cout << "Seleccione una opcion de Tipo de camarote:"; 
        gotoxy(3, 10); cout << "<1> Interior.";
        gotoxy(3, 11); cout << "<2> Exterior.";
        gotoxy(3, 12); cout << "<3> Balcon.";
        gotoxy(3, 13); cout << "<4> Suite.";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,14);
        switch(op) {
            case 1: strcpy(nueva.pasajeros[i].tipo_camarote, "Interior"); break;
            case 2: strcpy(nueva.pasajeros[i].tipo_camarote, "Exterior"); break;
            case 3: strcpy(nueva.pasajeros[i].tipo_camarote, "Balcon"); break;
            case 4: strcpy(nueva.pasajeros[i].tipo_camarote, "Suite"); break;
        }
		system("CLS");
    	marco();
    	mostrar_pasajeros(3, 6, 1, 4, nueva, i);
    	gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;
        nueva.pasajeros[i].precio_pasaje = validar_float(1, 10000, "Precio pasaje (EUR): ", 3, 10);
    }
}
        // Calcular precio total
		nueva.precio_total=0;
		for(i=0;i<nueva.num_pasajeros;i++)
		nueva.precio_total+=nueva.pasajeros[i].precio_pasaje;

        // Estado inicial
        nueva.activa = true;

        FILE *arch = fopen("CRUCEROS.dat", "ab");
        if (arch != NULL) {
            fwrite(&nueva, sizeof(Reserva), 1, arch);
            fclose(arch);
            gotoxy(40, 26);
            cout << "RESERVA REGISTRADA - TOTAL: " << nueva.precio_total << " EUR";
        } else {
            gotoxy(40, 26);
            cout << "ERROR AL GUARDAR LA RESERVA";
        }
    } else {
        gotoxy(40, 16);
        cout << "RESERVA YA EXISTENTE";
    }
    getch();

}//Fin de Incluir

void mostrarReserva(Reserva res) {
    system("CLS");
    marco();
    int y = 3;

    gotoxy(3, y++); cout << "--- DETALLES DE LA RESERVA ---";
    y++;
    gotoxy(5, y++); cout << "Numero de Reserva: " << res.numero_reserva;
    gotoxy(5, y++); cout << "Estado: " << (res.activa ? "Activa" : "Cancelada");
    y++;
    gotoxy(3, y++); cout << "-- Solicitante --"; y++;
    gotoxy(5, y++); cout << "Nombre: " << res.soli.nombre;
    gotoxy(5, y++); cout << "Pasaporte: " << res.soli.pasaporte;
    gotoxy(5, y++); cout << "Edad: " << res.soli.edad;
    gotoxy(5, y++); cout << "Genero: " << res.soli.genero;
    gotoxy(5, y++); cout << "El solicitante viaja?: " << res.soli.viaja;
    y=3;
    gotoxy(60, y++); cout << "-- DETALLES DEL VIAJE --"; y++;
    gotoxy(62, y++); cout << "Puerto de Salida: " << res.puerto_salida;
    gotoxy(62, y++); cout << "Destino: " << res.destino;
    gotoxy(62, y++); cout << "Linea de Crucero: " << res.linea_crucero;
    gotoxy(62, y++); cout << "Codigo de Viaje: " << res.codigo_viaje;
    gotoxy(62, y++); cout << "Categoria de Cabina: " << res.categoria_cabina;
    gotoxy(62, y++); cout << "Fecha de Salida: " << res.fecha_salida.dia << "/" << res.fecha_salida.mes << "/" << res.fecha_salida.anio;
    gotoxy(62, y++); cout << "Hora de Embarque: " << res.embarque.hora << ":" << res.embarque.minuto;
    gotoxy(62, y++); cout << "Fecha de Reserva: " << res.fecha_reserva.dia << "/" << res.fecha_reserva.mes << "/" << res.fecha_reserva.anio;
    y++;

    gotoxy(60, y++); cout << "-- Total --";
    gotoxy(62, y+++1); cout << "Precio Total: " << res.precio_total << " EUR";

    y = 15; //Reinicio de Y para la informacion de pasajeros.
    char respuesta;
	gotoxy(3,y++); respuesta= validar_dosletras("Desea ver la informacion de los pasajeros? (S/N): ",3, y+++2,"S","N","s","n");
	y++;
if (respuesta == 'S' || respuesta == 's') {
    int i = 0;
    while (i < res.num_pasajeros) {
        system("cls");
        marco();
        int y = 3;
        gotoxy(35, y++); cout << "--- PASAJEROS DE LA RESERVA ---";
        y++;
        // Mostrar hasta 3 pasajeros por pantalla
        int mostrados = 0;
        for (; i < res.num_pasajeros && mostrados < 3; ++i, ++mostrados) {
            gotoxy(5, y++); cout << "  P" << i + 1 << ":";
            gotoxy(7, y++); cout << "Nombre: " << res.pasajeros[i].nombre;
            gotoxy(7, y++); cout << "Edad: " << res.pasajeros[i].edad;
            gotoxy(7, y++); cout << "Genero: " << res.pasajeros[i].genero;
            gotoxy(7, y++); cout << "Camarote: " << res.pasajeros[i].tipo_camarote;
            gotoxy(7, y++); cout << "Precio: EUR " << res.pasajeros[i].precio_pasaje;
            y++; // Línea en blanco entre pasajeros
        }
        if (i < res.num_pasajeros) {
            gotoxy(40, 27); cout << "Presione una tecla para ver más pasajeros...";
            getch();
        }
    }
}//Fin del if de mostrar pasajeros
    gotoxy(40, 27); cout << "Presione una tecla para continuar...";
    getch();
}
// Fin de la funcion mostrarReserva


void consultar() {
    int opcion_consulta;
    char num_busqueda[20];
    char nombre_busqueda[50];
    Reserva reserva_leida; // Para leer datos del archivo
    FILE *archivo_cruceros;

    do {
        system("CLS");
        marco();
        gotoxy(45, 3); cout << "CONSULTAR RESERVA";
        gotoxy(40, 6); cout << "1. Buscar por Numero de Reserva";
        gotoxy(40, 8); cout << "2. Buscar por Nombre de Solicitante";
        gotoxy(40, 10); cout << "0. Volver al Menu Principal";
        opcion_consulta=validar_numero(0,2,"SELECCIONE UNA OPCION: ",40,13);
        fflush(stdin);

        switch (opcion_consulta) {
            case 1: { // Buscar por Numero de Reserva
                system("CLS");
                marco();
                gotoxy(35, 3); cout << "BUSCAR RESERVA POR NUMERO";
                gotoxy(3, 6); cout << "INGRESE EL NUMERO DE RESERVA A BUSCAR: ";
				fflush(stdin);
				gets(num_busqueda);

                Reserva reserva_encontrada; // Variable para la funci?n buscarReserva
                if (buscarReserva(num_busqueda, reserva_encontrada) == 1) {
                    mostrarReserva(reserva_encontrada);
                } else {
                    gotoxy(3, 10); cout << "Reserva con numero '" << num_busqueda << "' no encontrada.";
                    gotoxy(3, 12); cout << "Presione una tecla para continuar...";
                    getch();
                }
                break;
            }
            case 2: { // Buscar por Nombre de Solicitante
                system("CLS");
                marco();
                gotoxy(30, 3); cout << "BUSCAR RESERVA POR NOMBRE DEL SOLICITANTE";
                gotoxy(3, 6); cout << "INGRESE EL NOMBRE DEL SOLICITANTE: ";
				fflush(stdin);
				gets(nombre_busqueda);

                archivo_cruceros = fopen("CRUCEROS.dat", "rb");
                if (archivo_cruceros == NULL) {
                    gotoxy(3, 10); cout << "Error al abrir el archivo CRUCEROS.dat";
                    gotoxy(3, 12); cout << "Presione una tecla para continuar...";
                    getch();
                    break;
                }

                bool alguna_encontrada = false;
                while (fread(&reserva_leida, sizeof(Reserva), 1, archivo_cruceros) == 1) {
                    if (strcmp(reserva_leida.soli.nombre, nombre_busqueda) == 0) {
                        alguna_encontrada = true;
                        mostrarReserva(reserva_leida);
                    }
                }
                fclose(archivo_cruceros);

                if (!alguna_encontrada) {
                    system("CLS");
                    marco();
                    gotoxy(3, 10); cout << "Ninguna reserva encontrada para el solicitante: " << nombre_busqueda;
                    gotoxy(3, 12); cout << "Presione una tecla para continuar...";
                    getch();
                } else {
                    system("CLS");
                    marco();
                    gotoxy(35, 12); cout << "Fin de la busqueda para: " << nombre_busqueda << ".";
                    gotoxy(35, 14); cout << "Presione tecla para volver al menu de consulta...";
                    getch();
                }
                break;
            }
            case 0:
                break;
            default:
                gotoxy(40, 15); cout << "Opcion no valida. Presione una tecla para intentar de nuevo...";
                getch();
                break;
        }
    } while (opcion_consulta != 0);

}//Fin de la Funcion consultar

void modificarReserva() {
    system("CLS");
    marco();

    FILE *fOriginal = fopen("CRUCEROS.dat", "rb");
    FILE *fTemp = fopen("CRUCEROS_temp.dat", "wb");

    if (!fOriginal || !fTemp) {
        gotoxy(10, 5); cout << "Error abriendo archivos.";
        if (fOriginal) fclose(fOriginal);
        if (fTemp) fclose(fTemp);
        getch();
        return;
    }

    char nroReservaBuscada[20];
    bool encontrado = false;
    bool cambios = false;

    gotoxy(10, 3); cout << "INGRESA EL NUMERO DE RESERVA A MODIFICAR: ";
    cin.ignore();
    cin.getline(nroReservaBuscada, 20);

    Reserva res;
    while (fread(&res, sizeof(Reserva), 1, fOriginal)) {
        bool reservaModificada = false; // Variable para cada reserva

        if (strcmp(res.numero_reserva, nroReservaBuscada) == 0) {
            encontrado = true;
            gotoxy(10, 5); cout << "RESERVA ENCONTRADA. MOSTRANDO DATOS ACTUALES...";
            getch();
            mostrarReserva(res); // Muestras la reserva antes de modificar

            int opcion_modificar;
            do {
                system("CLS");
                marco();
                gotoxy(30, 3); cout << "MODIFICAR RESERVA: " << res.numero_reserva;
                gotoxy(30, 5); cout << "Seleccione la seccion a modificar:";
                gotoxy(35, 7); cout << "1. Datos del Solicitante";
                gotoxy(35, 8); cout << "2. Datos del Viaje";
                gotoxy(35, 9); cout << "3. Fechas y Horarios";
                gotoxy(35,10); cout << "4. Pasajeros";
                gotoxy(35,11); cout << "5. Estado de la Reserva (Activa/Cancelada)";
                gotoxy(35,12); cout << "0. Guardar y salir";
                gotoxy(35,14); cout << "Opcion: ";
                opcion_modificar = validar_numero(0, 5, "", 45, 14);

                switch(opcion_modificar) {
                    case 1: {
                        // MODIFICAR DATOS DEL SOLICITANTE
                        system("CLS");
                        marco();
                        gotoxy(3,6); cout << "Nombre del solicitante: ";
                        cin.ignore();
                        cin.getline(res.soli.nombre, sizeof(res.soli.nombre));
                        gotoxy(3, 7); cout << "Pasaporte: ";
                        cin.getline(res.soli.pasaporte, sizeof(res.soli.pasaporte));
                        res.soli.edad = validar_numero(1,100,"Edad (1-100): ",3,8);
                        char temp = validar_dosletras("Genero (M/F): ",3,9,"M","F","m","f");
                        strcpy(res.soli.genero, (temp=='m'||temp=='M') ? "Masculino" : "Femenino");
                        gotoxy(3,10); cout << "El solicitante viaja? <1>Si <2>No: ";
                        int viaja = validar_numero(1,2,"Opcion: ",3,11);
                        strcpy(res.soli.viaja, viaja==1 ? "Si" : "No");
                        reservaModificada = true;
                        break;
                    }
                    case 2: {
                        // MODIFICAR DATOS DEL VIAJE
                        system("CLS");
                        marco();
                        gotoxy(3,6); cout << "Puerto de salida: ";
                        cin.ignore();
                        cin.getline(res.puerto_salida, sizeof(res.puerto_salida));
                        gotoxy(3,7); cout << "Destino: ";
                        cin.getline(res.destino, sizeof(res.destino));
                        gotoxy(3,8); cout << "Linea de crucero: ";
                        cin.getline(res.linea_crucero, sizeof(res.linea_crucero));
                        gotoxy(3,9); cout << "Codigo de viaje: ";
                        cin.getline(res.codigo_viaje, sizeof(res.codigo_viaje));
                        gotoxy(3,10); cout << "Categoria de cabina: ";
                        gotoxy(3,11); cout << "<1> Interior <2> Exterior <3> Balcon <4> Suite";
                        int op = validar_numero(1,4,"Opcion: ",3,12);
                        switch(op) {
                            case 1: strcpy(res.categoria_cabina, "Interior"); break;
                            case 2: strcpy(res.categoria_cabina, "Exterior"); break;
                            case 3: strcpy(res.categoria_cabina, "Balcon"); break;
                            case 4: strcpy(res.categoria_cabina, "Suite"); break;
                        }
                        reservaModificada = true;
                        break;
                    }
                    case 3: {
                        // MODIFICAR FECHAS Y HORARIOS
                        system("CLS");
                        marco();
                        gotoxy(3,6); cout << "Mes de salida (1-12): ";
                        res.fecha_salida.mes = validar_numero(1,12,"Mes de salida: ",3,6);
                        int maxdia = 31;
                        if(res.fecha_salida.mes==4 || res.fecha_salida.mes==6 || res.fecha_salida.mes==9 || res.fecha_salida.mes==11) maxdia=30;
                        gotoxy(3,7); cout << "Dia de salida (1-" << maxdia << "): ";
                        res.fecha_salida.dia = validar_numero(1,maxdia,"Dia de salida: ",3,7);
                        gotoxy(3,8); cout << "Ano de salida (2025-2100): ";
                        res.fecha_salida.anio = validar_numero(2025,2100,"AÃ±o de salida: ",3,8);
                        gotoxy(3,9); cout << "Hora de embarque (0-23): ";
                        res.embarque.hora = validar_numero(0,23,"Hora embarque: ",3,9);
                        gotoxy(3,10); cout << "Minuto de embarque (0-59): ";
                        res.embarque.minuto = validar_numero(0,59,"Minutos embarque: ",3,10);

                        gotoxy(3,11); cout << "Mes de reserva (1-12): ";
                        res.fecha_reserva.mes = validar_numero(1,12,"Mes reserva: ",3,11);
                        maxdia = (res.fecha_reserva.mes==4 || res.fecha_reserva.mes==6 || res.fecha_reserva.mes==9 || res.fecha_reserva.mes==11)?30:31;
                        gotoxy(3,12); cout << "Dia de reserva (1-" << maxdia << "): ";
                        res.fecha_reserva.dia = validar_numero(1,maxdia,"Dia reserva: ",3,12);
                        gotoxy(3,13); cout << "AÃ±o de reserva (2025-2100): ";
                        res.fecha_reserva.anio = validar_numero(2025,2100,"AÃ±o reserva: ",3,13);
                        reservaModificada = true;
                        break;
                    }
                    case 4: {
                        // MODIFICAR PASAJEROS
                        system("CLS");
                        marco();
                        gotoxy(3,6); cout << "Modificar pasajeros.";
                        gotoxy(3,7); cout << "Cantidad actual: " << res.num_pasajeros;
                        gotoxy(3,8); cout << "Desea cambiar la cantidad de pasajeros? <1>Si <2>No";
                        int cambiar = validar_numero(1,2,"Opcion: ",3,9);
                        int maxPasajeros = 4;
                        if (cambiar==1) {
                            gotoxy(3,10); cout << "Nueva cantidad de pasajeros (1-4): ";
                            res.num_pasajeros = validar_numero(1,4,"Num pasajeros: ",3,10);
                        }
                        for (int i=0; i<res.num_pasajeros; i++) {
                            gotoxy(3,12+i*6); cout << "Pasajero " << (i+1);
                            gotoxy(5,13+i*6); cout << "Nombre: ";
                            cin.ignore();
                            cin.getline(res.pasajeros[i].nombre, sizeof(res.pasajeros[i].nombre));
                            res.pasajeros[i].edad = validar_numero(1,100,"Edad (1-100): ",5,14+i*6);
                            char g = validar_dosletras("Genero (M/F): ",5,15+i*6,"M","F","m","f");
                            strcpy(res.pasajeros[i].genero,(g=='M'||g=='m') ? "Masculino":"Femenino");
                            gotoxy(5,16+i*6); cout << "Tipo de camarote: ";
                            cin.getline(res.pasajeros[i].tipo_camarote, sizeof(res.pasajeros[i].tipo_camarote));
                            res.pasajeros[i].precio_pasaje = validar_float(1,10000,"Precio (EUR): ",5,17+i*6);
                        }
                        // Recalcular precio total
                        res.precio_total = 0;
                        for (int i=0; i<res.num_pasajeros; i++) res.precio_total += res.pasajeros[i].precio_pasaje;
                        reservaModificada = true;
                        break;
                    }
                    case 5: {
                        // MODIFICAR ESTADO DE LA RESERVA
                        system("CLS");
                        marco();
                        gotoxy(10,5); cout << "Estado actual: " << (res.activa ? "Activa" : "Cancelada");
                        gotoxy(10,7); cout << "Cambiar estado? 1-Si 2-No: ";
                        int op = validar_numero(1,2,"Opcion: ",10,8);
                        if (op==1) res.activa = !res.activa;
                        reservaModificada = true;
                        break;
                    }
                    case 0: {
                        // GUARDAR Y SALIR
                        break;
                    }
                    default: {
                        gotoxy(35, 16); cout << "OPCION NO VALIDA. INTENTE DE NUEVO.";
                        getch();
                        break;
                    }
                }
            } while (opcion_modificar != 0);

            if (reservaModificada) {
                cambios = true; // Hubo cambios en alguna reserva
            }
        }

        // Guardar en temporal: solo guardar modificado si es la reserva que cambiÃ³,
        // y si hubo cambios, y si no, guardar como estaba
        if (encontrado && strcmp(res.numero_reserva, nroReservaBuscada) == 0) {
            if (cambios) {
                fwrite(&res, sizeof(Reserva), 1, fTemp);
            } else {
                // Si no hubo cambios, guarda la original (opcional, aquÃ­ igual que el actual)
                fwrite(&res, sizeof(Reserva), 1, fTemp);
            }
        } else {
            fwrite(&res, sizeof(Reserva), 1, fTemp);
        }
    }

    fclose(fOriginal);
    fclose(fTemp);

    if (encontrado && cambios) {
        remove("CRUCEROS.dat");
        rename("CRUCEROS_temp.dat", "CRUCEROS.dat");
        gotoxy(10, 27); cout << "PROCESO DE MODIFICACION FINALIZADO.";
    } else if (encontrado && !cambios) {
        remove("CRUCEROS_temp.dat");
        gotoxy(10, 27); cout << "NO HUBO CAMBIOS EN LA RESERVA.";
    } else {
        remove("CRUCEROS_temp.dat");
        gotoxy(10, 5); cout << "NO SE ENCONTRO RESERVA CON ESE NUMERO.";
    }
    getch();
    
}//Fin de la Funcion Modificar


void eliminarReserva() {
    system("CLS");
    marco();

    char nroReservaBuscada[20];
    gotoxy(10, 3); cout << "INGRESE EL NUMERO DE RESERVA A ELIMINAR: ";
    cin.ignore();
    cin.getline(nroReservaBuscada, 20);

    Reserva res;
    bool encontrado = false;

    FILE *fOriginal = fopen("CRUCEROS.dat", "rb");
    if (!fOriginal) {
        gotoxy(10, 5); cout << "Error abriendo archivo de reservas.";
        getch();
        return;
    }

    // First, find and show the reservation
    while (fread(&res, sizeof(Reserva), 1, fOriginal)) {
        if (strcmp(res.numero_reserva, nroReservaBuscada) == 0) {
            encontrado = true;
            break;
        }
    }
    fclose(fOriginal);

    if (encontrado) {
        mostrarReserva(res); // Show the full details first

        gotoxy(3, 26); cout << "ESTA SEGURO QUE DESEA ELIMINAR ESTA RESERVA? (S/N): ";
        char confirmacion = getch();

        if (confirmacion == 'S' || confirmacion == 's') {
            // Re-open files to perform deletion
            fOriginal = fopen("CRUCEROS.dat", "rb");
            FILE *fTemp = fopen("CRUCEROS_temp.dat", "wb");
            if (!fOriginal || !fTemp) {
                 gotoxy(10, 5); cout << "Error abriendo archivos para eliminar."; getch(); return;
            }

            Reserva temp_res;
            while (fread(&temp_res, sizeof(Reserva), 1, fOriginal)) {
                if (strcmp(temp_res.numero_reserva, nroReservaBuscada) != 0) {
                    fwrite(&temp_res, sizeof(Reserva), 1, fTemp);
                }
            }
            fclose(fOriginal);
            fclose(fTemp);

            remove("CRUCEROS.dat");
            rename("CRUCEROS_temp.dat", "CRUCEROS.dat");

            system("CLS");
            marco();
            gotoxy(10, 15); cout << "RESERVA ELIMINADA EXITOSAMENTE.";

        } else {
            system("CLS");
            marco();
            gotoxy(10, 15); cout << "ELIMINACION CANCELADA POR EL USUARIO.";
        }
    } else {
        system("CLS");
        marco();
        gotoxy(10, 15); cout << "NO SE ENCONTRO RESERVA CON ESE NUMERO.";
    }

    gotoxy(10, 17); cout << "Presione una tecla para continuar...";
    getch();
}


void cancelarReactivar() {
    system("CLS");
    marco();

    FILE *fOriginal = fopen("CRUCEROS.dat", "rb+");
    if (!fOriginal) {
        gotoxy(10, 5); cout << "Error al abrir el archivo de reservas.";
        getch();
        return;
    }

    char nroReservaBuscada[20];
    bool encontrada = false;
    long int posicion = 0;

    gotoxy(10, 3); cout << "INGRESE EL NUMERO DE RESERVA A CANCELAR/REACTIVAR: ";
    cin.ignore();
    cin.getline(nroReservaBuscada, 20);

    Reserva res;
    while (fread(&res, sizeof(Reserva), 1, fOriginal)) {
        if (strcmp(res.numero_reserva, nroReservaBuscada) == 0) {
            encontrada = true;
            system("CLS");
            marco();

            gotoxy(10, 3); cout << "RESERVA ENCONTRADA:";
            gotoxy(10, 5); cout << "Numero: " << res.numero_reserva;
            gotoxy(10, 6); cout << "Solicitante: " << res.soli.nombre;
            gotoxy(10, 7); cout << "Estado actual: " << (res.activa ? "ACTIVA" : "CANCELADA");

            gotoxy(10, 9); cout << "Que desea hacer con esta reserva?";
            gotoxy(10, 10); cout << "1. " << (res.activa ? "Cancelar" : "Reactivar");
            gotoxy(10, 11); cout << "2. Dejar como esta";

            int opcion = validar_numero(1, 2, "Opcion: ", 10, 13);

            if (opcion == 1) {
                res.activa = !res.activa;
                fseek(fOriginal, posicion, SEEK_SET);
                fwrite(&res, sizeof(Reserva), 1, fOriginal);
                gotoxy(10, 15); cout << "Estado de la reserva actualizado a: " << (res.activa ? "ACTIVA" : "CANCELADA");
            } else {
                gotoxy(10, 15); cout << "No se realizaron cambios en la reserva.";
            }

            gotoxy(10, 17); cout << "Presione una tecla para continuar...";
            getch();
            break;
        }
        posicion = ftell(fOriginal);
    }

    fclose(fOriginal);

    if (!encontrada) {
        gotoxy(10, 5); cout << "No se encontro ninguna reserva con el numero: " << nroReservaBuscada;
        gotoxy(10, 7); cout << "Presione una tecla para continuar...";
        getch();
    }
}

void borrarLinea(int x, int y) {
    gotoxy(x, y);
    cout << "                                                                                  ";
}

void mostrarReservaSimple(Reserva r) {
    printf("Nro: %s | Destino: %s | Pasajeros: %d | Ref: %.2f EUR | Estado: %s",
       r.numero_reserva, r.destino, r.num_pasajeros,
       r.precio_total, r.activa ? "Activa" : "Cancelada");
}

//Funciones Bryan

void reportes() {
    int op;
    do {
        system("CLS");
        marco();
		gotoxy(45, 3); cout << "REPORTES - OCEANO AZUL";
        gotoxy(40, 6); cout << "1. Consulta por Linea de Crucero";
        gotoxy(40, 8); cout << "2. Viajes por Temporada";
        gotoxy(40, 10); cout << "3. Cancelaciones por Edad";
        gotoxy(40, 12); cout << "4. Revision de Capacidad";
        gotoxy(40, 14); cout << "0. Volver al menu principal";
        op = validar_numero(0,4,"Opcion: ", 40, 17);

        switch(op) {
            case 1: reporteLineaCrucero(); break;
            case 2: reporteViajesTemporada(); break;
            case 3: CancelacionesPorEdadDestino(); break;
            case 4: revisionCapacidadCabina(); break;
            case 0: return;
        }

    } while(op!=0);
}

void reporteLineaCrucero() {
    setlocale(LC_ALL, "spanish");
    system("CLS");
    marco();
    gotoxy(45, 3); cout << "REPORTE POR LINEA DE CRUCERO";
    
    char linea[50];
    gotoxy(3, 6); cout << "Ingrese la Línea de Crucero: ";
    fflush(stdin);
    gets(linea);
    
    int orden, moneda;
    float tasa = 1.0; 
    
    gotoxy(3, 8); cout << "Ordenar por:";
    gotoxy(3, 9); cout << "1. Monto Ascendente";
    gotoxy(3, 10); cout << "2. Monto Descendente";
    gotoxy(3, 11); cout << "Opción: ";

    gotoxy(3, 15); cout << "Moneda:";
    gotoxy(3, 16); cout << "1. Euros (EUR)";
    gotoxy(3, 17); cout << "2. Dólares (USD)";
    gotoxy(3, 18); cout << "3. Bolívares (BS)";
    gotoxy(3, 19); cout << "Opción: ";

    // Validar opción de orden
    do {
        borrarLinea(3, 11); // Borrar la línea anterior
        gotoxy(3, 11); cout << "Opción: ";
        cin >> orden;
        if (orden < 1 || orden > 2) {
            gotoxy(3, 13); cout << "Opción inválida. Por favor, ingrese una opción válida.";
            getch();
            borrarLinea(3, 13); // Borrar el mensaje de error
        }
    } while (orden < 1 || orden > 2);
    
    // Validar opción de moneda
    do {
        borrarLinea(3, 19); // Borrar la línea anterior
        gotoxy(3, 19); cout << "Opción: ";
        cin >> moneda;
        if (moneda < 1 || moneda > 3) {
            gotoxy(3, 21); cout << "Opción inválida. Por favor, ingrese una opción válida.";
            getch();
            borrarLinea(3, 21); // Borrar el mensaje de error
        }
    } while (moneda < 1 || moneda > 3);
    
    // Validar tasa de cambio si se selecciona USD o BS
    if (moneda > 1) {
        do {
            borrarLinea(3, 23); // Borrar la línea anterior
            gotoxy(3, 23); cout << "Ingrese tasa de cambio (1 EUR = ?): ";
            cin >> tasa;
            if (tasa <= 0) {
                gotoxy(3, 25); cout << "Tasa de cambio inválida. Por favor, ingrese un valor positivo.";
                getch();
                borrarLinea(3, 25); // Borrar el mensaje de error
            }
        } while (tasa <= 0);
    }
    
    // Mostrar la tasa de cambio en la parte superior derecha
    gotoxy(100, 3); 
    if (moneda == 2) {
        cout << "Tasa : " << tasa << " USD";
    } else if (moneda == 3) {
        cout << "Tasa : " << tasa << " BS";
    }
    
    FILE *arch = fopen("CRUCEROS.dat", "rb");
    if (arch == NULL) {
        gotoxy(3, 27); cout << "ERROR: No se pudo abrir el archivo de datos.";
        getch();
        return;
    }
    
    Reserva reservas[100];
    int cont = 0;
    float total = 0;
    Reserva temp;
    
    while (fread(&temp, sizeof(Reserva), 1, arch) == 1) {
        if (strcmp(temp.linea_crucero, linea) == 0) {
            reservas[cont++] = temp;
            total += temp.precio_total;
        }
    }
    fclose(arch);
    
    if (cont == 0) {
        gotoxy(3, 27); cout << "No se encontraron reservas para esta línea.";
        getch();
        return;
    }

    for (int i = 0; i < cont - 1; i++) {
        for (int j = i + 1; j < cont; j++) {
            if ((orden == 1 && reservas[i].precio_total > reservas[j].precio_total) ||
                (orden == 2 && reservas[i].precio_total < reservas[j].precio_total)) {
                Reserva aux = reservas[i];
                reservas[i] = reservas[j];
                reservas[j] = aux;
            }
        }
    }

    system("CLS");
    marco();
    gotoxy(45, 3); cout << "REPORTE POR LINEA DE CRUCERO";
    gotoxy(100, 3); 
    if (moneda == 2) {
        cout << "Tasa : " << tasa << " USD";
    } else if (moneda == 3) {
        cout << "Tasa : " << tasa << " BS";
    }
    
    int y = 6;
    for (int i = 0; i < cont; i++) {
        float monto = reservas[i].precio_total;
        if (moneda == 2 || moneda == 3) monto *= tasa;
        
        gotoxy(3, y++);
        mostrarReservaSimple(reservas[i]);
        printf(" | Monto: %.2f %s", monto, moneda == 1 ? "EUR" : (moneda == 2 ? "USD" : "BS"));
 
        if (y >= 28) {
            gotoxy(3, 29); cout << "Presione una tecla para continuar...";
            getch();
            system("CLS");
            marco();
            gotoxy(45, 3); cout << "REPORTE POR LINEA DE CRUCERO";
            gotoxy(100, 3); 
            if (moneda == 2) {
                cout << "Tasa : " << tasa << " USD";
            } else if (moneda == 3) {
                cout << "Tasa : " << tasa << " BS";
            }
            y = 6;
        }
    }
    
    gotoxy(3, y++); cout << "---------------------------------------";
    gotoxy(3, y++); cout << "TOTAL RESERVAS: " << cont;
    gotoxy(3, y++); printf("MONTO TOTAL: %.2f %s", total * (moneda == 1 ? 1 : tasa), moneda == 1 ? "EUR" : (moneda == 2 ? "USD" : "BS"));
    gotoxy(3, y++); cout << "Presione una tecla para continuar...";
    getch();
}

void mostrar2(int pos1, int pos2, int desde, int hasta, Fecha fecha) {
    int op;
    for(op = desde; op <= hasta; op++, pos2++) {
        gotoxy(pos1, pos2);
        switch(op) {
            case 1: cout << "Mes: " << fecha.mes; break;
            case 2: cout << "Dia: " << fecha.dia; break;
            case 3: cout << "Ano: " << fecha.anio; break;
            default: ;
        }
    }
}

void reporteViajesTemporada() {
    setlocale(LC_ALL, "spanish");
    Fecha fechaInicio, fechaFin;
    int y_pos = 6;
    long totalInicio, totalFin;

    // FECHA INICIAL 
    system("CLS");
    marco();
    gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
    gotoxy(3, y_pos++); cout << "FECHA INICIAL DEL RANGO:";
    
    // Validar mes
    fechaInicio.mes = validar_numero(1, 12, "  Mes (1-12): ", 3, y_pos++);
    mostrar2(3, y_pos-1, 30, 1, fechaInicio);
    
    system("CLS");
    marco();
    gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
    gotoxy(3, 6); cout << "FECHA INICIAL DEL RANGO:";
    gotoxy(3, 7); cout << "  Mes (1-12): " << fechaInicio.mes;
    
    // Validar día según mes
    int maxDia;
    if (fechaInicio.mes == 4 || fechaInicio.mes == 6 || fechaInicio.mes == 9 || fechaInicio.mes == 11) {
        maxDia = 30;
        fechaInicio.dia = validar_numero(1, 30, "  Día (1-30): ", 3, 8);
    } else if (fechaInicio.mes == 2) {
        maxDia = 28;
        fechaInicio.dia = validar_numero(1, 28, "  Día (1-28): ", 3, 8);
    } else {
        maxDia = 31;
        fechaInicio.dia = validar_numero(1, 31, "  Día (1-31): ", 3, 8);
    }
    mostrar2(3, 8, 30, 2, fechaInicio);
    
    system("CLS");
    marco();
    gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
    gotoxy(3, 6); cout << "FECHA INICIAL DEL RANGO:";
    gotoxy(3, 7); cout << "  Mes (1-12): " << fechaInicio.mes;
    gotoxy(3, 8); cout << "  Día (1-" << maxDia << "): " << fechaInicio.dia;
    
    // Validar año
    fechaInicio.anio = validar_numero(2024, 2100, "  Año (2024-2100): ", 3, 9);
    mostrar2(3, 9, 30, 3, fechaInicio);
    totalInicio = fechaInicio.anio * 365 + fechaInicio.mes * 30 + fechaInicio.dia;

    // FECHA FINAL 
    do {
        system("CLS");
        marco();
        gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
        y_pos = 6;
        gotoxy(3, y_pos++); cout << "FECHA FINAL DEL RANGO (posterior a " 
                                << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio << "):";
        
        // Validar mes
        fechaFin.mes = validar_numero(1, 12, "  Mes (1-12): ", 3, y_pos++);
        mostrar2(3, y_pos-1, 30, 1, fechaFin);
        
        system("CLS");
        marco();
        gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
        gotoxy(3, 6); cout << "FECHA FINAL DEL RANGO (posterior a " 
                                << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio << "):";
        gotoxy(3, 7); cout << "  Mes (1-12): " << fechaFin.mes;
        
        // Validar día según mes
        if (fechaFin.mes == 4 || fechaFin.mes == 6 || fechaFin.mes == 9 || fechaFin.mes == 11) {
            maxDia = 30;
            fechaFin.dia = validar_numero(1, 30, "  Día (1-30): ", 3, 8);
        } else if (fechaFin.mes == 2) {
            maxDia = 28;
            fechaFin.dia = validar_numero(1, 28, "  Día (1-28): ", 3, 8);
        } else {
            maxDia = 31;
            fechaFin.dia = validar_numero(1, 31, "  Día (1-31): ", 3, 8);
        }
        mostrar2(3, 8, 30, 2, fechaFin);
        
        system("CLS");
        marco();
        gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
        gotoxy(3, 6); cout << "FECHA FINAL DEL RANGO (posterior a " 
                                << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio << "):";
        gotoxy(3, 7); cout << "  Mes (1-12): " << fechaFin.mes;
        gotoxy(3, 8); cout << "  Día (1-" << maxDia << "): " << fechaFin.dia;
        
        // Validar año
        fechaFin.anio = validar_numero(2024, 2100, "  Año (2024-2100): ", 3, 9);
        mostrar2(3, 9, 30, 3, fechaFin);
        totalFin = fechaFin.anio * 365 + fechaFin.mes * 30 + fechaFin.dia;
        
        if (totalFin < totalInicio) {
            gotoxy(3, 11); cout << "¡ERROR! La fecha final debe ser posterior a la inicial";
            getch();
        }
    } while (totalFin < totalInicio);

    // FILTRADO POR ESTADO 
    system("CLS");
    marco();
    gotoxy(35, 3); cout << "REPORTE POR TEMPORADA (FECHAS DE SALIDA)";
    y_pos = 6;
    gotoxy(3, y_pos++); cout << "FILTRAR POR ESTADO:";
    gotoxy(3, y_pos++); cout << "1. Todas las reservas";
    gotoxy(3, y_pos++); cout << "2. Solo activas";
    gotoxy(3, y_pos++); cout << "3. Solo canceladas";
    int opcionEstado = validar_numero(1, 3, "Opción: ", 3, y_pos++);

    // MOSTRAR RESULTADOS
    system("CLS");
    marco();
    gotoxy(35, 3); cout << "RESERVAS ENTRE " 
                       << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio 
                       << " Y "
                       << fechaFin.dia << "/" << fechaFin.mes << "/" << fechaFin.anio;

    // Encabezados
    gotoxy(3, 6); cout << "NRO RESERVA";
    gotoxy(20, 6); cout << "FECHA SALIDA";
    gotoxy(35, 6); cout << "LINEA CRUCERO";
    gotoxy(60, 6); cout << "COD. VIAJE";
    gotoxy(75, 6); cout << "PASAJEROS";
    gotoxy(90, 6); cout << "ESTADO";

    FILE *arch = fopen("CRUCEROS.dat", "rb");
    if (!arch) {
        gotoxy(3, 8); cout << "Error al abrir el archivo de reservas";
        getch();
        return;
    }

    Reserva temp;
    int totalReservas = 0, totalPasajeros = 0, y = 8;
    bool hayDatos = false;

    while (fread(&temp, sizeof(Reserva), 1, arch) == 1) {
        long totalFechaSalida = temp.fecha_salida.anio * 365 + temp.fecha_salida.mes * 30 + temp.fecha_salida.dia;
        bool enRango = (totalFechaSalida >= totalInicio) && (totalFechaSalida <= totalFin);
        bool estadoOk = (opcionEstado == 1) || 
                      (opcionEstado == 2 && temp.activa) || 
                      (opcionEstado == 3 && !temp.activa);

        if (enRango && estadoOk) {
            if (y >= 28) {
                gotoxy(50, 28); cout << "Presione una tecla para continuar...";
                getch();
                system("CLS");
                marco();
                gotoxy(35, 3); cout << "RESERVAS ENTRE " << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio << " Y " << fechaFin.dia << "/" << fechaFin.mes << "/" << fechaFin.anio;

                // Encabezados
                gotoxy(3, 6); cout << "NRO RESERVA";
                gotoxy(20, 6); cout << "FECHA SALIDA";
                gotoxy(35, 6); cout << "LINEA CRUCERO";
                gotoxy(60, 6); cout << "COD. VIAJE";
                gotoxy(75, 6); cout << "PASAJEROS";
                gotoxy(90, 6); cout << "ESTADO";
                y = 8;
            }
            hayDatos = true;
            totalReservas++;
            totalPasajeros += temp.num_pasajeros;

            gotoxy(3, y); cout << temp.numero_reserva;
            gotoxy(20, y); printf("%02d/%02d/%04d", temp.fecha_salida.dia, temp.fecha_salida.mes, temp.fecha_salida.anio);
            gotoxy(35, y); cout << temp.linea_crucero;
            gotoxy(60, y); cout << temp.codigo_viaje;
            gotoxy(78, y); cout << temp.num_pasajeros;
            gotoxy(90, y); cout << (temp.activa ? "Activa" : "Cancelada");
            y++;
            for (int i = 0; i < temp.num_pasajeros; i++) {
                if (y >= 28) {
                    gotoxy(3, 29); cout << "Presione una tecla para continuar...";
                    getch();
                    system("CLS");
                    marco();
                    gotoxy(35, 3); cout << "RESERVAS ENTRE " << fechaInicio.dia << "/" << fechaInicio.mes << "/" << fechaInicio.anio << " Y " << fechaFin.dia << "/" << fechaFin.mes << "/" << fechaFin.anio;

                    // Encabezados
                    gotoxy(3, 6); cout << "NRO RESERVA";
                    gotoxy(20, 6); cout << "FECHA SALIDA";
                    gotoxy(35, 6); cout << "LINEA CRUCERO";
                    gotoxy(60, 6); cout << "COD. VIAJE";
                    gotoxy(75, 6); cout << "PASAJEROS";
                    gotoxy(90, 6); cout << "ESTADO";
                    y = 8;
                }

                gotoxy(6, y); cout << "- Pasajero " << (i+1) << ": " << temp.pasajeros[i].nombre;
                y++;
            }
            y++;
            if (y >= 28) {
                gotoxy(3, 29); cout << "Presione una tecla para continuar...";
                getch();
                system("CLS");
                marco();
                y = 6;
            }
        }
    }
    fclose(arch);

    if (!hayDatos) {
        gotoxy(3, 10); cout << "No hay reservas en el rango especificado";
    } else {
        gotoxy(3, y+2); cout << "=== RESUMEN ===";
        gotoxy(3, y+3); cout << "Total reservas: " << totalReservas;
        gotoxy(3, y+4); cout << "Total pasajeros: " << totalPasajeros;
    }

    gotoxy(3, y+6); cout << "Presione una tecla para volver...";
    getch();
}

//Funciones de Fort
void CancelacionesPorEdadDestino() {
    FILE* archivo = fopen("CRUCEROS.dat", "rb");
    if (!archivo) {
        cout << "\nError al abrir archivo de reservas.";
        getch(); return;
    }

    char destino[50];
    int edad_min;
    char filtro;
    char cabinaFiltro[20];
    bool usarFiltro = false; 

    system("cls"); marco();
    gotoxy(30, 5); cout << "Destino del crucero: ";
    fflush(stdin); gets(destino);

    edad_min = validar_numero(0, 100, "Edad mínima para filtrar: ", 30, 7);

    fflush(stdin); 
    filtro = validar_dosletras("Desea filtrar por categoria de cabina? (S/N): ", 30, 9, "S", "N", "s", "n");
    
    if (filtro == 'S' || filtro == 's') {
        usarFiltro = true;
        gotoxy(30, 11); cout << "Categoria de cabina: ";
        gotoxy(30, 12); cout << "<1> Interior <2> Exterior <3> Balcon <4> Suite";
        int op = validar_numero(1, 4, "Opcion: ", 30, 13);
        switch(op) {
            case 1: strcpy(cabinaFiltro, "Interior"); break;
            case 2: strcpy(cabinaFiltro, "Exterior"); break;
            case 3: strcpy(cabinaFiltro, "Balcon"); break;
            case 4: strcpy(cabinaFiltro, "Suite"); break;
        }
        
    }

    int y = 15; 
    int mostrados = 0;
    Reserva r;
    
    system("cls"); marco();
    gotoxy(30, 3); cout << "CANCELACIONES EN DESTINO: " << destino;
    gotoxy(10, 5); cout << "Edad mínima: " << edad_min;
    if (usarFiltro) {
        gotoxy(10, 6); cout << "Filtro de cabina: " << cabinaFiltro;
        y = 8;
    } else {
        y = 6;
    }
    
    gotoxy(10, y++); cout << "--------------------------------------------------";
    
    while (fread(&r, sizeof(Reserva), 1, archivo)) {
        if (!r.activa && strcmp(r.destino, destino) == 0) {
            for (int i = 0; i < r.num_pasajeros; i++) {
                Pasajero p = r.pasajeros[i];
                if (p.edad >= edad_min && (!usarFiltro || strcmp(r.categoria_cabina, cabinaFiltro) == 0)) {
                    gotoxy(10, y++); cout << "Pasajero: " << p.nombre << ", Edad: " << p.edad << ", Género: " << p.genero;
                    gotoxy(10, y++); cout << "Camarote: " << p.tipo_camarote << ", Precio: " << p.precio_pasaje << " EUR";
                    gotoxy(10, y++); cout << "Categoria Cabina: " << r.categoria_cabina;
                    gotoxy(10, y++); cout << "--------------------------------------------------";
                    mostrados++;
                }
            }
        }
    }
    fclose(archivo);

    if (mostrados == 0) {
        gotoxy(10, y++); cout << "No se encontraron pasajeros cancelados con esos criterios.";
    }

    gotoxy(10, y++); cout << "Total de pasajeros mostrados: " << mostrados;
    gotoxy(10, y++); cout << "Presione una tecla para continuar...";
    getch();
}

void revisionCapacidadCabina() {
    FILE* archivo = fopen("CRUCEROS.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir archivo de reservas.";
        getch(); return;
    }

    char codBuscado[20];
    int capacidad;
    char moneda[20], aux;
    float tasa = 1.0;

    system("cls"); marco();
    gotoxy(35, 5); cout << "Ingrese codigo del viaje: ";
    fflush(stdin); gets(codBuscado);
    capacidad = validar_numero(0, 1000, "Capacidad maxima del viaje (Maximo 1000): ", 35, 6);
    gotoxy(20, 7); cout << "Moneda por defecto (EUR), si desea cambiarla ingrese <U> para dolar o <B> para bolivares";
    aux = validar_dosletras("Opcion: ", 35, 8, "U", "B", "s", "b");
    
    if (aux == 'U' || aux == 'u') {
        tasa = validar_float(0, 10000, "Tasa EUR -> USD (Maximo 10000): ", 35, 8);
        strcpy(moneda, "USD");
    } else if (aux == 'B' || aux == 'b') {
        tasa = validar_float(0, 10000, "Tasa EUR -> Bs (Maximo 10000): ", 35, 8);
        strcpy(moneda, "Bs");
    } else {
        tasa = 1.0;
        strcpy(moneda, "EUR");
    }

    struct Nodo {
        Reserva r;
        float monto;
    } lista[200];

    int totalPasajeros = 0, total = 0;
    Reserva r;

    while (fread(&r, sizeof(Reserva), 1, archivo)) {
        if (strcmp(r.codigo_viaje, codBuscado) == 0) {
            float monto = 0;
            for (int i = 0; i < r.num_pasajeros; i++) {
                monto += r.pasajeros[i].precio_pasaje;
            }
            lista[total].r = r;
            lista[total].monto = monto * tasa;
            totalPasajeros += r.num_pasajeros;
            total++;
        }
    }
    fclose(archivo);

    // Ordenar por fecha_reserva (simple bubble)
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            Fecha f1 = lista[i].r.fecha_reserva;
            Fecha f2 = lista[j].r.fecha_reserva;
            if (f1.anio > f2.anio || (f1.anio == f2.anio && f1.mes > f2.mes) ||
                (f1.anio == f2.anio && f1.mes == f2.mes && f1.dia > f2.dia)) {
                Nodo tmp = lista[i]; lista[i] = lista[j]; lista[j] = tmp;
            }
        }
    }

    system("cls"); marco();
    gotoxy(40, 3); cout << "REVISION DE CAPACIDAD - COD: " << codBuscado;
    int y = 5, acumulados = 0, rechazados = 0;
    float excesoMonto = 0;

    for (int i = 0; i < total; i++) {
        Reserva r = lista[i].r;
        float monto = lista[i].monto;
        bool entra = (acumulados + r.num_pasajeros <= capacidad);
        gotoxy(20, y++); cout << "Reserva #: " << r.numero_reserva << ", Destino: " << r.destino;
        gotoxy(20, y++); cout << "Pasajeros: " << r.num_pasajeros << ", Monto: " << monto << " " << moneda;
        gotoxy(20, y++); cout << "Fecha Reserva: " << r.fecha_reserva.dia << "/" << r.fecha_reserva.mes << "/" << r.fecha_reserva.anio;
        
        if (!entra) {
            gotoxy(20, y++); cout << "--> FUERA DE CUPO";
            excesoMonto += monto;
            rechazados += r.num_pasajeros;  // Contar pasajeros rechazados
        } else {
            acumulados += r.num_pasajeros;  // Contar pasajeros admitidos
        }
        y++;
    }

    gotoxy(20, y++); cout << "Pasajeros admitidos: " << acumulados;
    gotoxy(20, y++); cout << "Pasajeros rechazados: " << rechazados;  // Mostrar rechazados contados
    gotoxy(20, y++); cout << "Monto excedente: " << excesoMonto << " " << moneda;
    gotoxy(20, y++); cout << "Presione una tecla para continuar..."; getch();
}
