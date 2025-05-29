#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <locale.h>
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
	char viaja[2]; //si o no
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

// Prototipos de funciones, vayan agregandolas aquí
void gotoxy(int x, int y);
void marco();
void incluir();
bool validarFecha(Fecha f);
bool validarFechasReserva(Fecha fechaReserva, Fecha fechaSalida);
bool validarHoraEmbarque(int horas, int minutos);
int buscarReserva(char numero[20], Reserva &res);
float calcularPrecioTotal(Reserva &r);

// Función principal
int main() {
    setlocale(LC_ALL, "spanish");
    int op;
    
    do {
        system("CLS");
        marco();
        gotoxy(45, 3); cout << "OCEANO AZUL - SISTEMA DE RESERVAS";
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
            // case 2: consultar(); break;
            // case 3: modificar(); break;
            // case 4: eliminar(); break;
            // case 5: cancelarReactivar(); break;
            // case 6: reportes(); break;
        }
    } while(op != 0);
    
    return 0;
}

// Implementación de funciones
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Estética
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
}

bool validarFecha(Fecha f) { //No usada
    if (f.anio < 2023 || f.anio > 2100) return false;
    if (f.mes < 1 || f.mes > 12) return false;
    if (f.dia < 1 || f.dia > 31) return false;

    if ((f.mes == 4 || f.mes == 6 || f.mes == 9 || f.mes == 11) && f.dia > 30) {
        return false;
    }
    
    if (f.mes == 2 && f.dia > 28) {
        return false;
    }

    return true;
}

bool validarFechasReserva(Fecha fechaReserva, Fecha fechaSalida) { //No usada
    if (fechaSalida.anio < fechaReserva.anio) return false;
    else if (fechaSalida.mes < fechaReserva.mes) return false;
    else if (fechaSalida.dia <= fechaReserva.dia) return false;
    return true;
}

bool validarHoraEmbarque(int horas, int minutos) { //No usada
    if (horas < 0 || horas > 23) return false;
    if (minutos < 0 || minutos > 59) return false;
    return true;
}

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
}
float calcularPrecioTotal(Reserva &r) {
    float total = 0;
    for (int i = 0; i < r.num_pasajeros; i++) {
        total += r.pasajeros[i].precio_pasaje;
    }
    return total;
}

int validar_numero(int ini, int fin, string entrada, int pos1, int pos2) {
    int n, i=pos1, j=pos2, cont=0;
	do {
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
	}    while (n < ini || n > fin);
    return (n);
}
char validar_genero(int pos1, int pos2)
{
	char aux[2];
	int i=pos1, j=pos2;
	do{
		gotoxy(i, j);
		cout<<"Genero(M/F): ";
		fflush(stdin);
		gets(aux);
		if(strcmp(aux,"M")==0 || strcmp(aux,"m")==0 || strcmp(aux,"F")==0 || strcmp(aux,"f")==0) return(aux[0]);
		else{
   		system("cls");
			marco();
			i=10;
			j=10;
			gotoxy(i,j);
			cout<<"OPCION INVALIDA, PORFAVOR INTENTE DE NUEVO.";
			j=11;
		}
	}while(aux!="M"&& aux!="m"&& aux!="F" && aux!="f");
 
}

int validar_float(int ini, int fin, string entrada, int pos1, int pos2) {
    float n;
	int i=pos1, j=pos2, cont=0;
	do {
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
	}    while (n < ini || n > fin);
    return (n);
}
void mostrar(int pos1, int pos2, int desde, int hasta, Reserva nueva)
{
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
		case 4: cout << "Género (M/F) : " << nueva.soli.genero; break;
		case 5: cout << "El solicitante viaja?: "<< nueva.soli.viaja; break;
		case 6: cout << "Puerto de salida: " << nueva.puerto_salida; break;
		case 7: cout << "Destino: " << nueva.destino; break;
		case 8: cout << "Código de viaje: " << nueva.codigo_viaje; break;
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
}
																			//Posicion en el arreglo.
void mostrar_pasajeros(int pos1, int pos2, int desde, int hasta, Reserva nueva, int npasajero)
{

	int op;
 	system("CLS");
 	marco();
	for(op=desde;op<=hasta;op++,pos2++)
	{
	gotoxy(pos1,pos2);
	switch(op){
		case 1: cout << "Nombre: " << nueva.pasajeros[npasajero].nombre; break;
		case 2: cout << "Edad: " << nueva.pasajeros[npasajero].edad; break;
		case 3: cout << "Género: " << nueva.pasajeros[npasajero].genero; break;
		case 4: cout << "Tipo de camarote: " << nueva.pasajeros[npasajero].tipo_camarote; break;
		case 5: cout << "Precio en euros:  " << nueva.pasajeros[npasajero].precio_pasaje; break;
		default: ;
		}
	}
}
void incluir()
{
	setlocale(LC_ALL, "spanish");
    Reserva nueva;
	char temp;
	int i, j, n, x, y = 7;
	bool condicion;
	system("CLS");
    marco();
    gotoxy(40, 12); cout << "INGRESANDO NUEVA RESERVA....";
    gotoxy(40, 14); cout << "Número de reserva: ";
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
        nueva.soli.edad=validar_numero(1,100,"Edad(1 al 100): ",3,8);
        //Carga y pregunta genero.
		mostrar(3,6,1,3,nueva);
		gotoxy(3,2); cout<< "Numero de reserva: "<<nueva.numero_reserva; //Encabezado
		temp=validar_genero(3,9);
		if (temp == 'm' || temp== 'M'){
		strcpy(nueva.soli.genero,"Masculino");}
        else strcpy(nueva.soli.genero,"Femenino");
        //Carga y pregunta si viaja.
		mostrar(3,6,1,4,nueva);
		gotoxy(3,10);
		cout<<"El solicitante viaja?: ";
  		gotoxy(3,11); cout<<"<1>Si.";
		gotoxy(3,12); cout<<"<2>No.";
		n=validar_numero(1,2,"Opcion: ",3,13);
		if(n==1) strcpy(nueva.soli.viaja,"Si");
		else strcpy(nueva.soli.viaja,"No");
		//Cargar para mostrar informacion completa.
		mostrar(3,6,1,5,nueva);
		gotoxy(3,2); cout<< "Numero de reserva: "<<nueva.numero_reserva;
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
        gets(nueva.destino); gotoxy(3,8); cout << "Línea de crucero: ";
        fflush(stdin);
        gets(nueva.linea_crucero);
        gotoxy(3,9); cout << "Código de viaje: ";
        fflush(stdin);
        gets(nueva.codigo_viaje);
		gotoxy(3, 10); cout << "Seleccione una opcion de Categoria de cabina:(1-4):"; //PREGUNTAR SI ES POR PASAJERO.
        gotoxy(3, 11); cout << "<1>Interior";
        gotoxy(3, 12); cout << "<2>Exterior";
        gotoxy(3, 13); cout << "<3>Balcón.";
        gotoxy(3, 14); cout << "<4>Suite";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,15);
        switch(op) {
            case 1: strcpy(nueva.categoria_cabina, "Interior"); break;
            case 2: strcpy(nueva.categoria_cabina, "Exterior"); break;
            case 3: strcpy(nueva.categoria_cabina, "Balcón"); break;
            case 4: strcpy(nueva.categoria_cabina, "Suite"); break;
        }
		gotoxy(40,2); cout<< "INFORMACION DEL VIAJE";
		mostrar(3,6,6,9,nueva);
		gotoxy(3,12); cout << "INFORMACION DEL VIAJE CARGADA.....";
		gotoxy(3,13); cout<< "Pulse una tecla para continuar."; getch();
        // Fecha de salida
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
		nueva.fecha_salida.anio = validar_numero(2025,2100,"Ano de la salida (2025-2100):",3,8);
		mostrar(3,6,10,12,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.embarque.hora=validar_numero(0,23,"Hora de embarque (Formato militar 0-23):",3,9);
		mostrar(3,6,10,13,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.embarque.minuto=validar_numero(0,59,"Minuto de embarque (0-59):",3,10);
		mostrar(3,6,10,14,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		//Fecha de reserva
		long int total_reserva, total_salida;
		total_salida= nueva.fecha_salida.anio*365 + nueva.fecha_salida.mes * 30 + nueva.fecha_salida.dia;
		do {
		nueva.fecha_reserva.mes=validar_numero(1,12,"Mes de reserva (1-12): ",3,10);
		mostrar(3,10,10,15,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		if(nueva.fecha_reserva.mes == 4 || nueva.fecha_reserva.mes == 6 || nueva.fecha_reserva.mes == 9 || nueva.fecha_reserva.mes == 11)nueva.fecha_reserva.dia=validar_numero(1,30,"Dia de reserva (1-30): ",3,7);
		else nueva.fecha_reserva.dia=validar_numero(1,30,"Dia de reserva (1-31): ",3,11);
		mostrar(3,10,10,16,nueva);
		gotoxy(40,2); cout<< "INFORMACION DE LAS FECHAS Y HORARIOS.";//Encabezado.
		nueva.fecha_reserva.anio = validar_numero(2025,2100,"Ano de la reserva (2025-2100):",3,12);

		total_reserva = nueva.fecha_reserva.dia * 365 + nueva.fecha_reserva.mes * 30 + nueva.fecha_reserva.dia ;
        if (total_reserva < total_salida) break;
		else{
			gotoxy(3,17);cout<<"Fecha de reserva posterior a la salida. Intentelo de nuevo.";
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
		if(strcmp(nueva.soli.viaja,"Si")== 0){nueva.num_pasajeros=validar_numero(1,3,"Numero de pasajeros adicionales (1-3): ",40,14)+1; condicion=true;}
			else {nueva.num_pasajeros=validar_numero(1,4,"Numero de pasajeros (1-4): ",40,14);condicion=false;}

		for (i=0; i < nueva.num_pasajeros; i++) {
            system("CLS");
            marco();
            gotoxy(40, 3);cout << "DATOS DEL PASAJERO " << i+1;//Encabezado.
			if(i==0 && condicion==true){
				strcpy(nueva.pasajeros[i].nombre,nueva.soli.nombre);
				nueva.pasajeros[i].edad=nueva.soli.edad;
				strcpy(nueva.pasajeros[i].genero,nueva.soli.genero);
				mostrar_pasajeros(3,6,1,3,nueva,0);
				gotoxy(40, 3);cout << "DATOS DEL PASAJERO " << i+1;//Encabezado.
				gotoxy(3, 9);cout << "Tipo de camarote: ";
            	fflush(stdin); gets(nueva.pasajeros[i].tipo_camarote);
            	nueva.pasajeros[i].precio_pasaje=validar_float(1,10000,"Precio pasaje (EUR): ",3,10);
			}
			else{
				gotoxy(3, 6); cout << "Nombre: ";
            	fflush(stdin); gets(nueva.pasajeros[i].nombre);
				nueva.pasajeros[i].edad=validar_float(1,100,"Edad(1 al 100): ",3,7);
				mostrar_pasajeros(3,6,1,2,nueva,i);
				gotoxy(40, 3);cout << "DATOS DEL PASAJERO " << i+1;//Encabezado.
           		temp=validar_genero(3,8);
				if (temp == 'm' || temp== 'M'){
				strcpy(nueva.pasajeros[i].genero,"Masculino");}
        		else strcpy(nueva.pasajeros[i].genero,"Femenino");
            	mostrar_pasajeros(3,6,1,3,nueva,i);
				gotoxy(40, 3); cout << "DATOS DEL PASAJERO " << i+1;//Encabezado.
            	gotoxy(3, 9);cout << "Tipo de camarote: ";
            	fflush(stdin); gets(nueva.pasajeros[i].tipo_camarote);
            	nueva.pasajeros[i].precio_pasaje=validar_float(1,10000,"Precio pasaje (EUR): ",3,10);
			}
        }
        // Calcular precio total
		if(condicion=true) nueva.num_pasajeros++;
		nueva.precio_total=0;
		for(i=0;i<nueva.num_pasajeros;i++)
		nueva.precio_total+=nueva.pasajeros[i].precio_pasaje;
        
        // Estado inicial
        nueva.activa = true;
        
        FILE *arch = fopen("CRUCEROS.dat", "ab");
        if (arch != NULL) {
            fwrite(&nueva, sizeof(Reserva), 1, arch);
            fclose(arch);
            gotoxy(3, 30);
            cout << "RESERVA REGISTRADA - TOTAL: " << nueva.precio_total << " EUR";
        } else {
            gotoxy(3, 30);
            cout << "ERROR AL GUARDAR LA RESERVA";
        }
    } else {
        gotoxy(3, 4);
        cout << "RESERVA YA EXISTENTE";
    	}
    getch();
}
