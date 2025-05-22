#include <iostream>
#include <string>
using namespace std;

// Constantes para los limites
const int MAX_CIUDADES = 10;
const int MAX_SALAS = 8;
const int MAX_ACTORES = 4;
const int MAX_TELEFONOS = 4;

// Estructura para Actor
struct Actor {
    string nombreArtistico;
    string nombreReal;
    int edad;
    char sexo; // 'M' o 'F'
};

// Estructura para Horario
struct Horario {
    bool dosCuatro;
    bool cuatroSeis;
    bool seisOcho;
    bool ochoDiez;
};

// Estructura para Pelicula
struct Pelicula {
    string nombre;
    string director;
    string genero;
    string censura;
    string productora;
    int duracionHoras;
    int duracionMinutos;
    Actor actores[MAX_ACTORES];
    int cantidadActores;
    Horario horarios;
    string diaInicio;
    string mesInicio;
    string diaFin;
    string mesFin;
};

// Estructura para Sala
struct Sala {
    Pelicula pelicula;
    int numeroSala;
};

// Estructura principal para Cine
struct Cine {
    string ciudad;
    string direccion;
    string telefonos[MAX_TELEFONOS];
    int cantidadTelefonos;
    bool tieneEstacionamiento;
    int puestosEstacionamiento;
    Sala salas[MAX_SALAS];
    int cantidadSalas;
};

// Funcion para validar entrada num√©rica
int validarNumero(int min, int max, string mensaje) {
    int numero;
    do {
        cout << mensaje;
        cin >> numero;
        if(numero < min || numero > max) {
            cout << "Error: Debe estar entre " << min << " y " << max << endl;
        }
    } while(numero < min || numero > max);
    return numero;
}

// Funcion para cargar actores
void cargarActores(Actor actores[], int &cantidad) {
    cantidad = validarNumero(1, MAX_ACTORES, "Cantidad de actores principales (1-4): ");
    
    for(int i = 0; i < cantidad; i++) {
        cout << "\nActor " << i+1 << ":\n";
        cout << "Nombre art√≠stico: ";
        cin.ignore();
        getline(cin, actores[i].nombreArtistico);
        
        cout << "Nombre real: ";
        getline(cin, actores[i].nombreReal);
        
        cout << "Edad: ";
        cin >> actores[i].edad;
        
        cout << "Sexo (M/F): ";
        cin >> actores[i].sexo;
    }
}

// Funcion para cargar horarios
void cargarHorarios(Horario &horarios) {
    char opcion;
    cout << "\nSeleccione horarios (2-4, 4-6, 6-8, 8-10):\n";
    
    cout << "øFuncion de 2 a 4? (s/n): ";
    cin >> opcion;
    horarios.dosCuatro = (tolower(opcion) == 's');
    
    cout << "øFuncion de 4 a 6? (s/n): ";
    cin >> opcion;
    horarios.cuatroSeis = (tolower(opcion) == 's');
    
    cout << "øFuncion de 6 a 8? (s/n): ";
    cin >> opcion;
    horarios.seisOcho = (tolower(opcion) == 's');
    
    cout << "øFuncion de 8 a 10? (s/n): ";
    cin >> opcion;
    horarios.ochoDiez = (tolower(opcion) == 's');
}

// Funcion para cargar pel√≠culas
void cargarPelicula(Pelicula &pelicula) {
    cout << "\nNombre de la pelicula: ";
    cin.ignore();
    getline(cin, pelicula.nombre);
    
    cout << "Director: ";
    getline(cin, pelicula.director);
    
    cout << "Genero: ";
    getline(cin, pelicula.genero);
    
    cout << "Censura: ";
    getline(cin, pelicula.censura);
    
    cout << "Empresa productora: ";
    getline(cin, pelicula.productora);
    
    cout << "Duracion (horas): ";
    cin >> pelicula.duracionHoras;
    
    cout << "Duracion (minutos): ";
    cin >> pelicula.duracionMinutos;
    
    cargarActores(pelicula.actores, pelicula.cantidadActores);
    cargarHorarios(pelicula.horarios);
    
    cout << "Dia de inicio: ";
    cin >> pelicula.diaInicio;
    
    cout << "Mes de inicio: ";
    cin >> pelicula.mesInicio;
    
    cout << "Dia de fin: ";
    cin >> pelicula.diaFin;
    
    cout << "Mes de fin: ";
    cin >> pelicula.mesFin;
}
// Funcion para cargar cines
void cargarCines(Cine cines[]) {
    for(int i = 0; i < MAX_CIUDADES; i++) {
        cout << "\n=== CINE " << i+1 << " ===\n";
        
        cout << "Ciudad: ";
        getline(cin, cines[i].ciudad);
        
        cout << "Direccion: ";
        getline(cin, cines[i].direccion);
        
        cines[i].cantidadTelefonos = validarNumero(1, MAX_TELEFONOS, "Cantidad de telefonos (1-4): ");
        for(int j = 0; j < cines[i].cantidadTelefonos; j++) {
            cout << "Telefono " << j+1 << ": ";
            getline(cin, cines[i].telefonos[j]);
        }
        
        char tieneEst;
        cout << "øTiene estacionamiento? (s/n): ";
        cin >> tieneEst;
        cines[i].tieneEstacionamiento = (tolower(tieneEst) == 's');
        
        if(cines[i].tieneEstacionamiento) {
            cout << "Puestos de estacionamiento: ";
            cin >> cines[i].puestosEstacionamiento;
        }
        
        cines[i].cantidadSalas = validarNumero(2, MAX_SALAS, "Cantidad de salas (2-8): ");
        for(int j = 0; j < cines[i].cantidadSalas; j++) {
            cout << "\nSALA " << j+1 << ":\n";
            cines[i].salas[j].numeroSala = j+1;
            cargarPelicula(cines[i].salas[j].pelicula);
        }
    }
}

// Funcion para mostrar datos
void mostrarDatos(const Cine cines[]) {
    for(int i = 0; i < MAX_CIUDADES; i++) {
        cout << "\n=== CINE: " << cines[i].ciudad << " ===";
        cout << "\nDireccion: " << cines[i].direccion;
        cout << "\nTelefonos: ";
        for(int j = 0; j < cines[i].cantidadTelefonos; j++) {
            cout << cines[i].telefonos[j] << " ";
        }
        
        cout << "\nEstacionamiento: " << (cines[i].tieneEstacionamiento ? "Si" : "No");
        if(cines[i].tieneEstacionamiento) {
            cout << " (" << cines[i].puestosEstacionamiento << " puestos)";
        }
        
        cout << "\n\nSalas:";
        for(int j = 0; j < cines[i].cantidadSalas; j++) {
            cout << "\n\nSala " << cines[i].salas[j].numeroSala << ":";
            cout << "\nPelicula: " << cines[i].salas[j].pelicula.nombre;
            cout << "\nDirector: " << cines[i].salas[j].pelicula.director;
            cout << "\nGenero: " << cines[i].salas[j].pelicula.genero;
            cout << "\nDuracion: " << cines[i].salas[j].pelicula.duracionHoras << "h " 
                 << cines[i].salas[j].pelicula.duracionMinutos << "m";
            cout << "\nDesde: " << cines[i].salas[j].pelicula.diaInicio << "/" 
                 << cines[i].salas[j].pelicula.mesInicio << " hasta " 
                 << cines[i].salas[j].pelicula.diaFin << "/" 
                 << cines[i].salas[j].pelicula.mesFin;
        }
        cout << "\n=================================\n";
    }
}

void mostrarUltimasFunciones(const Cine cines[], string ciudadBuscar, string generoBuscar) {
    bool encontrado = false;
    
    for(int i = 0; i < MAX_CIUDADES; i++) {
        if(cines[i].ciudad == ciudadBuscar) {
            cout << "\n=== ULTIMAS FUNCIONES EN " << ciudadBuscar << " (Genero: " << generoBuscar << ") ===\n";
            
            for(int j = 0; j < cines[i].cantidadSalas; j++) {
                if(cines[i].salas[j].pelicula.genero == generoBuscar) {
                    cout << "\nSala " << cines[i].salas[j].numeroSala << ": " 
                         << cines[i].salas[j].pelicula.nombre << "\n";
                    
                    cout << "Horarios: ";
                    if(cines[i].salas[j].pelicula.horarios.ochoDiez) {
                        cout << "8-10pm (Ultima funcion)";
                    } else if(cines[i].salas[j].pelicula.horarios.seisOcho) {
                        cout << "6-8pm";
                    } else if(cines[i].salas[j].pelicula.horarios.cuatroSeis) {
                        cout << "4-6pm";
                    } else if(cines[i].salas[j].pelicula.horarios.dosCuatro) {
                        cout << "2-4pm";
                    }
                    cout << "\n";
                    encontrado = true;
                }
            }
            break;
        }
    }
    
    if(!encontrado) {
        cout << "No se encontraron funciones para ese genero en la ciudad especificada.\n";
    }
}

void mostrarPeliculasMasLargas(const Cine cines[]) {
    for(int i = 0; i < MAX_CIUDADES; i++) {
        int maxDuracion = 0;
        int indicePelicula = 0;
        
        // Buscar la pelicula mas larga en esta ciudad
        for(int j = 0; j < cines[i].cantidadSalas; j++) {
            int duracionTotal = cines[i].salas[j].pelicula.duracionHoras * 60 + 
                               cines[i].salas[j].pelicula.duracionMinutos;
            
            if(duracionTotal > maxDuracion) {
                maxDuracion = duracionTotal;
                indicePelicula = j;
            }
        }
        
        // Mostrar resultados
        cout << "\n=== " << cines[i].ciudad << " ===\n";
        cout << "Pelicula ma°s larga: " << cines[i].salas[indicePelicula].pelicula.nombre << "\n";
        cout << "Duracion: " << cines[i].salas[indicePelicula].pelicula.duracionHoras << "h " 
             << cines[i].salas[indicePelicula].pelicula.duracionMinutos << "m\n";
        cout << "Director: " << cines[i].salas[indicePelicula].pelicula.director << "\n";
    }
}

void peliculaMasProgramada(Cine cines[]) {
    struct PeliculaContador {
        string nombre;
        string director;
        int contador = 0;
    };
    
    PeliculaContador peliculas[100]; // Asumimos m·ximo 100 pelÌculas diferentes
    int totalPeliculas = 0;
    
    // Contar funciones por pelÌcula
    for(int i = 0; i < MAX_CIUDADES; i++) {
        for(int j = 0; j < cines[i].cantidadSalas; j++) {
        	
            string nombrePeli = cines[i].salas[j].pelicula.nombre;
            string directorPeli = cines[i].salas[j].pelicula.director;
            bool encontrada = false;
            
            // Buscar si ya tenemos esta pelÌcula registrada
            for(int k = 0; k < totalPeliculas; k++) {
            	
                if(peliculas[k].nombre == nombrePeli && peliculas[k].director == directorPeli) {
                    // Sumar los horarios de esta sala
                    if(cines[i].salas[j].pelicula.horarios.dosCuatro) peliculas[k].contador++;
                    if(cines[i].salas[j].pelicula.horarios.cuatroSeis) peliculas[k].contador++;
                    if(cines[i].salas[j].pelicula.horarios.seisOcho) peliculas[k].contador++;
                    if(cines[i].salas[j].pelicula.horarios.ochoDiez) peliculas[k].contador++;
                    encontrada = true;
                    break;
                }
            }
            
            // Si es una pelÌcula nueva, mostrar error
            if(!encontrada) {
                cout<<"Esta pelicula no fue encontrada, intentelo de nuevo\n"<<endl;break;
            }
        }
    }
    
    // Encontrar la pelÌcula con m·s funciones
    int maxContador = 0;
    int indiceMax = 0;
    for(int i = 0; i < totalPeliculas; i++) {
        if(peliculas[i].contador > maxContador) {
            maxContador = peliculas[i].contador;
            indiceMax = i;
        }
    }
    
    // Mostrar resultados
    cout << "\n=== PELiCULA MAS PROGRAMADA ===\n";
    cout << "Pelicula: " << peliculas[indiceMax].nombre << "\n";
    cout << "Director: " << peliculas[indiceMax].director << "\n";
    cout << "Total de funciones: " << peliculas[indiceMax].contador << "\n";
}

// Funcion principal
int main() {
    Cine cines[MAX_CIUDADES];
    cargarCines(cines);
    mostrarDatos(cines);
    
    // Ejemplo de uso para el apartado C
    string ciudad, genero;
    cout << "\nIngrese ciudad para buscar ultimas funciones: ";
    getline(cin, ciudad);
    cout << "Ingrese genero de pelÌcula: ";
    getline(cin, genero);
    mostrarUltimasFunciones(cines, ciudad, genero);
    
    // Apartado E
    mostrarPeliculasMasLargas(cines);
    
    // Apartado F
    peliculaMasProgramada(cines);
    
    return 0;
}
