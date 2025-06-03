#include <iostream>
#include <string>
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

// Prototipos de funciones, vayan agregandolas aqui?
void gotoxy(int x, int y);
void marco();
void incluir();
bool validarFecha(Fecha f);
bool validarFechasReserva(Fecha fechaReserva, Fecha fechaSalida);
bool validarHoraEmbarque(int horas, int minutos);
int buscarReserva(char numero[20], Reserva &res);
float calcularPrecioTotal(Reserva &r);
void consultar();
void mostrarReservaCompleta(Reserva res); // Para mostrar todos los detalles de una reserva

// Funcion principal
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
            case 2: consultar(); break;
            // case 3: modificar(); break;
            // case 4: eliminar(); break;
            // case 5: cancelarReactivar(); break;
            // case 6: reportes(); break;
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
}//Fin validar fecha

bool validarFechasReserva(Fecha fechaReserva, Fecha fechaSalida) { //No usada
    if (fechaSalida.anio < fechaReserva.anio) return false;
    else if (fechaSalida.mes < fechaReserva.mes) return false;
    else if (fechaSalida.dia <= fechaReserva.dia) return false;
    return true;
}//Fin validar fecha reserva

bool validarHoraEmbarque(int horas, int minutos) { //No usada
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
}//Fin validar numero

char validar_genero(int pos1, int pos2){
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
 
}//Fin Validar Genero

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
		case 4: cout << "G?nero (M/F) : " << nueva.soli.genero; break;
		case 5: cout << "El solicitante viaja?: "<< nueva.soli.viaja; break;
		case 6: cout << "Puerto de salida: " << nueva.puerto_salida; break;
		case 7: cout << "Destino: " << nueva.destino; break;
		case 8: cout << "C?digo de viaje: " << nueva.codigo_viaje; break;
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
																			//Posicion en el arreglo.
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
		case 3: cout << "G?nero: " << nueva.pasajeros[npasajero].genero; break;
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
	bool condicion;
	system("CLS");
    marco();
    gotoxy(40, 12); cout << "INGRESANDO NUEVA RESERVA....";
    gotoxy(40, 14); cout << "N?mero de reserva: ";
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
        gets(nueva.destino); gotoxy(3,8); cout << "L?nea de crucero: ";
        fflush(stdin);
        gets(nueva.linea_crucero);
        gotoxy(3,9); cout << "C?digo de viaje: ";
        fflush(stdin);
        gets(nueva.codigo_viaje);
		gotoxy(3, 10); cout << "Seleccione una opcion de Categoria de cabina:(1-4):"; //PREGUNTAR SI ES POR PASAJERO.
        gotoxy(3, 11); cout << "<1>Interior";
        gotoxy(3, 12); cout << "<2>Exterior";
        gotoxy(3, 13); cout << "<3>Balc?n.";
        gotoxy(3, 14); cout << "<4>Suite";
		int op;
        op=validar_numero(1,4,"Opcion: ",3,15);
        switch(op) {
            case 1: strcpy(nueva.categoria_cabina, "Interior"); break;
            case 2: strcpy(nueva.categoria_cabina, "Exterior"); break;
            case 3: strcpy(nueva.categoria_cabina, "Balc?n"); break;
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
    
}//Fin de Incluir


void mostrarReserva(Reserva res) {
    system("CLS"); // Limpia la pantalla
    marco();       // Dibuja el marco
    int y = 3;

    gotoxy(35, y++); cout << "--- DETALLES DE LA RESERVA ---";
    y++;
    gotoxy(3, y++); cout << "Numero de Reserva: " << res.numero_reserva;
    gotoxy(3, y++); cout << "Estado: " << (res.activa ? "Activa" : "Cancelada");
    y++;
    gotoxy(3, y++); cout << "-- Solicitante --";
    gotoxy(5, y++); cout << "Nombre: " << res.soli.nombre;
    gotoxy(5, y++); cout << "Pasaporte: " << res.soli.pasaporte;
    gotoxy(5, y++); cout << "Edad: " << res.soli.edad;
    gotoxy(5, y++); cout << "Genero: " << res.soli.genero;
    gotoxy(5, y++); cout << "El solicitante viaja?: " << res.soli.viaja;
    y++;

    gotoxy(3, y++); cout << "-- Detalles del Viaje --";
    gotoxy(5, y++); cout << "Puerto de Salida: " << res.puerto_salida;
    gotoxy(5, y++); cout << "Destino: " << res.destino;
    gotoxy(5, y++); cout << "Linea de Crucero: " << res.linea_crucero;
    gotoxy(5, y++); cout << "Codigo de Viaje: " << res.codigo_viaje;
    gotoxy(5, y++); cout << "Categoria de Cabina: " << res.categoria_cabina;
    gotoxy(5, y++); cout << "Fecha de Salida: " << res.fecha_salida.dia << "/" << res.fecha_salida.mes << "/" << res.fecha_salida.anio;
    gotoxy(5, y++); cout << "Hora de Embarque: " << res.embarque.hora << ":" << res.embarque.minuto;
    gotoxy(5, y++); cout << "Fecha de Reserva: " << res.fecha_reserva.dia << "/" << res.fecha_reserva.mes << "/" << res.fecha_reserva.anio;
    y++;
    
    gotoxy(5, y++); cout << "-- Total --";
    gotoxy(5, y++); cout << "Precio Total: " << res.precio_total << " EUR";
    y++; 
    
    // NUEVO: Preguntar al usuario si quiere ver los pasajeros
    char respuesta;
    gotoxy(5, y++); cout << "--¿Desea ver la lista de pasajeros? (S/N): ";y++;
    respuesta = getch(); // Lee una tecla sin enter

    if (respuesta == 'S' || respuesta == 's') {
        gotoxy(3, y++); cout << "-- Pasajeros (" << res.num_pasajeros << ") --";y++;
        for (int i = 0; i < res.num_pasajeros; i++) {
            gotoxy(5, y++); cout << "  P" << i + 1 << ": " << res.pasajeros[i].nombre 
                                 << " (Edad: " << res.pasajeros[i].edad 
                                 << ", Genero: " << res.pasajeros[i].genero
                                 << ", Camarote: " << res.pasajeros[i].tipo_camarote 
                                 << ", EUR " << res.pasajeros[i].precio_pasaje << ")";
        }
    } else {
        gotoxy(5, y++); cout << "--(Pasajeros no mostrados)--";
    }
    y++
    gotoxy(3, y++); cout << "Presione una tecla para continuar...";
    y++;
    getch();
}//Fin de la funcion Mostrar Reserva


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
        gotoxy(40, 13); cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion_consulta;
        fflush(stdin); // Limpia el buffer de entrada, como en tu código original

        switch (opcion_consulta) {
            case 1: { // Buscar por Número de Reserva
                system("CLS"); 
                marco();
                gotoxy(35, 3); cout << "BUSCAR RESERVA POR NUMERO";
                gotoxy(3, 6); cout << "Ingrese el numero de reserva a buscar: ";
                gets(num_busqueda); 

                Reserva reserva_encontrada; // Variable para la función buscarReserva
                if (buscarReserva(num_busqueda, reserva_encontrada) == 1) {
                	
                    // Si se encuentra, llama a la función para mostrarla.
                    // mostrarReserva se encarga de limpiar pantalla, dibujar marco y pausar.
                    
                    mostrarReserva(reserva_encontrada);
                } else {
                    // Si no se encuentra, muestra un mensaje.
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
                gotoxy(3, 6); cout << "Ingrese el nombre del solicitante: ";
                gets(nombre_busqueda);

                archivo_cruceros = fopen("CRUCEROS.dat", "rb"); // Abrir en modo lectura binaria
                if (archivo_cruceros == NULL) {
                    gotoxy(3, 10); cout << "Error al abrir el archivo CRUCEROS.dat";
                    gotoxy(3, 12); cout << "Presione una tecla para continuar...";
                    getch();
                    break; 
                }

                bool alguna_encontrada = false;
                // Leer el archivo registro por registro
                while (fread(&reserva_leida, sizeof(Reserva), 1, archivo_cruceros) == 1) {
                    // Comparar el nombre del solicitante del registro actual con el buscado
                    if (strcmp(reserva_leida.soli.nombre, nombre_busqueda) == 0) {
                        alguna_encontrada = true;
                        mostrarReserva(reserva_leida); // Muestra y pausa
                        
                        // Después de presionar una tecla, el bucle continuará buscando más coincidencias.
                        // La pantalla se limpiará en la próxima llamada a mostrarReserva si hay otra.
                    }
                }
                fclose(archivo_cruceros); // Cerrar el archivo

                if (!alguna_encontrada) {
                    // Si no se encontró ninguna, mostrar mensaje.
                    // La pantalla ya estaría limpia por el system("CLS") inicial de este case.
                    // O si hubo llamadas a mostrarReservaSimple, la última limpió.
                    // Para asegurar, limpiamos y mostramos.
                    system("CLS");
                    marco();
                    gotoxy(3, 10); cout << "Ninguna reserva encontrada para el solicitante: " << nombre_busqueda;
                    gotoxy(3, 12); cout << "Presione una tecla para continuar...";
                    getch();
                } else {
                    // Si se encontraron una o más, después de la última pausa de mostrarReserva,
                    // podemos mostrar un mensaje final.
                    system("CLS");
                    marco();
                    gotoxy(35, 12); cout << "Fin de la busqueda para: " << nombre_busqueda << ".";
                    gotoxy(35, 14); cout << "Presione tecla para volver al menu de consulta...";
                    getch();
                }
                break;
            }
            case 0:
                // Opción para salir del submenú de consulta
                break;
            default:
                gotoxy(40, 15); cout << "Opcion no valida. Presione una tecla para intentar de nuevo...";
                getch();
                break;
        }
    } while (opcion_consulta != 0);
    
}//Fin de la Funcion consultar



