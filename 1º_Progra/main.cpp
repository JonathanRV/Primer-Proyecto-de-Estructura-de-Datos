#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>

/**
Brian Salazar Sanchez y Jonathan Rojas.
*/

/**
Los menus no estan completos.
*/

using namespace std;

//------------------------------DECLARACION DE METODOS------------------------------

void menuPrincipal();

void gruposGUI();
void insertarGrupoGUI();
void insertarEquipoGrupoGUI();
void imprimirEquiposGrupoGUI();

void equiposGUI();
void insertarEquipoGUI();
void insertarJugadorEquipoGUI();
void imprimirJugadoresEquipoGUI();


void jugadoresGUI();
void insertarJugadorGUI();
void imprimirJugadoresGUI();

void arbitrosGUI();
void insertarArbitroGUI();
void imprimirArbitrosGUI();

void consultasGUI();
void reportesGUI();

void estadiosGUI();
void insertarEstadioGUI();
void imprimirEstadiosGUI();

void partidosGUI();
void insertarPartidoGUI();
void insertarTarjetasPartidoGUI();
void insertarGolesPartidoGUI();
void imprimirUnPartidoGUI();
void imprimirPartidosGUI();
void finalizarGUI();

void consultasGUI();
void consulta_1GUI();
void consulta_2GUI();
void consulta_3GUI();
void consulta_4GUI();
void consulta_5GUI();
void consulta_6GUI();
void consulta_7GUI();
void consulta_8GUI();
void consulta_9GUI();

void reportesGUI();
void reporte_1GUI();
void reporte_2GUI();
void reporte_3GUI();
void reporte_4GUI();
void reporte_5GUI();
void reporte_6GUI();
void reporte_7GUI();

void ActualizarGUI();

//------------------------------STRUCT LISTAS---------------------------------------


struct listaGrupos{ //Lista doble para almacenar los 8 grupos.

    char letra;
    struct listaGrupos *sig;
    struct listaGrupos *ant;

    struct equipo *lisEquipos;

}*grupos;

struct listaSelecciones{ //Lista circular para almacenar las selecciones

    int pts = 0;
    string nombre;
    int mundialesParticipados;
    int finales;
    int mundialesGanados;
    int PG;
    int PP;
    int PE;
    int GF;
    int GC;
    int actualPG;
    int actualPP;
    int actualPE;
    int actualGF;
    int actualGC;
    int PJ = 0;
    string confederacion;

    bool estado = false;
    bool octavos = false;
    bool cuartos = false;
    bool semifinal = false;
    bool fin = false;
    bool campeon = false;

    struct listaSelecciones *sig;
    struct jugador *lisJugador;

}*selecciones;


struct listaJugadores{ //Lista Simple para almacenar los jugadores

    string nombre;
    string nacion;
    string posicion;
    string fechaNacimiento;
    string club;
    int cabeza;
    int golesMundiales;
    int mundiales;
    int golesActuales = 0;

    bool ordenadoGolead = false;
    bool ordenadoGoleadAux = false;

    struct listaJugadores *sig;

}*jugadores;


struct Partidos{ //Lista Simple para almacenar los Partidos

    string id;
    string fecha;
    string hora;
    int cantPersAsist;
    int golEqui1;
    int golEqui2;

    bool estado = false;

    struct Partidos *sig;

    struct partidosEquipos *listaPE1;
    struct partidosEquipos *listaPE2;
    struct partidosGoles *listaPG;
    struct partidosTarjetas *listaPT;
    struct partidosArbitros *listaArbi;
    struct partidosEstadios *listaEst;

}*listaPartidos;

struct listaArbitros{//Lista para almacenar a los Arbitros
    string nombre;
    string nacion;
    string tipo;
    int roja = 0;
    int amarilla = 0;

    struct listaArbitros *sig;
}*arbitros;


struct listaEstadios{ //Lista para almacenar a los Estadios
    string nombre;
    int capacidad;
    string sede;
    int inauguracion;
    string ubicacion;

    struct listaEstadios *sig;
}*estadios;


//---------------------------------STRUCT SUBLISTAS---------------------------------

struct jugador{        //Sublistas de Jugadores para Equipos
    struct listaJugadores *enlace;
    struct jugador *sig;
};

struct equipo{        //Sublistas de Equipos para Grupos
    struct listaSelecciones *enlace;
    struct equipo *sig;
};

struct partidosEquipos{        //Sublistas de Equipos para los Partidos
    struct listaSelecciones *enlace;
    struct partidosEquipos *sig;
};

struct partidosGoles{//Sublistas de Goles para Partidos

    int minuto;
    string forma;

    struct listaJugadores *enlace;
    struct partidosGoles *sig;
};

struct partidosTarjetas{//Sublistas de Tarjetas para los Partidos

    int minuto;
    string color;

    struct listaJugadores *enlace;
    struct partidosTarjetas *sig;
};

struct partidosArbitros{        //Sublistas de Arbitros para los Partidos
    struct listaArbitros *enlace;
    struct partidosArbitros *sig;
};


struct partidosEstadios{        //Sublistas de Estadios para los Partidos
    struct listaEstadios *enlace;
    struct partidosEstadios *sig;
};




//---------------------------------Metodos Grupos-----------------------------------


//Busca un grupo y devuelve TRUE si lo encuentra en la lista y False si no lo encuentra.
bool buscarGrupo(char sigla){

    if(grupos == NULL){
        cout << endl <<"NO EXISTEN GRUPOS"<< endl;
        }

    struct listaGrupos *temp = grupos;

    do{
        if(temp->letra  == sigla){
            return true;
            }
        temp = temp -> sig;


    }while(temp != grupos);
    return false;
}


//Inserta el grupo de forma ordenada
bool insertarGrupo_Ordenado(char sigla){

    struct listaGrupos *nn = new listaGrupos();
    nn->letra = sigla;

    nn->sig = NULL;

    if(sigla>'I'){
        return false;
    }

    if(grupos == NULL){
            grupos = nn;
            nn->sig = nn;
            nn->ant = nn;
            return true;
        }
    if (buscarGrupo(sigla)){
            return false;
        }

    else{
        struct listaGrupos *temp = grupos;

        while((temp->sig != grupos) && (temp->letra < sigla)){
            temp = temp -> sig;
        }

        if((temp == grupos) && (temp->letra > sigla)){

            struct listaGrupos*temp2 = grupos;

            while(temp2->sig != grupos){
                temp2 = temp2->sig;
            }

            nn->sig = temp;
            nn->ant = temp2;
            temp2->sig = nn;
            temp->ant = nn;
            grupos = nn;
            return true;
        }

        else if((temp -> sig == grupos) && (temp->letra < sigla)){
            temp->sig = nn;
            nn->ant = temp;
            nn->sig = grupos;
            grupos->ant = nn;
            return true;
        }

        else{
            struct listaGrupos *temp3 = temp->ant;
            temp3->sig = nn;
            nn-> ant= temp3;
            nn->sig = temp;
            temp->ant = nn;
            return true;
        }

    }
    return false;
}


//Busca un Equipo en Grupo para no agregarlo dos veces
struct listaSelecciones *existeSeleccionG(string nacion){

    struct listaSelecciones *temp = selecciones;

    if(selecciones == NULL){
        return NULL;
    }

    do{
        if((temp->nombre == nacion) and (temp->estado == false)){
            temp->estado = true;
            return temp;
            }
        temp = temp->sig;
    }while(temp != selecciones);
    return NULL;
}

//Busca un Grupo y retorna el nodo
struct listaGrupos *existeGrupo(char sigla){

    struct listaGrupos *temp = grupos;

    if(grupos == NULL){
        return NULL;
    }
    do{
        if(temp->letra == sigla){
            return temp;
            }
        temp = temp->sig;
    }while(temp != grupos);
    return NULL;
}


//Imprime los Equipos de un Grupo
void imprimirEquiposGrupo(char sigla){

    cout <<endl<< "---IMPRESION DE LISTA EQUIPOS DEL GRUPO "<<sigla<<" ----------"<<endl<<endl;

    struct listaGrupos *temp = existeGrupo(sigla);

    if(temp == NULL){
        return;
    }
    struct equipo *temp2 = temp->lisEquipos;
    if(temp != NULL){
        while(temp != NULL){
            if(temp->letra==sigla){
                if(temp->lisEquipos != NULL){
                    while(temp2 != NULL){
                        cout<<temp2->enlace->nombre<<endl;
                        temp2 = temp2->sig;
                    }
                }
                return;
            }
            temp = temp->sig;
        }
    }
}

//Imprime la lista de Grupos
void imprimirGrupos(){

    cout <<endl<<endl<< "---IMPRESION DE LISTA GRUPOS---"<< endl<<endl;

    struct listaGrupos *temp = grupos;

    if(grupos == NULL){
        cout << "NO EXISTE GRUPOS" <<endl << endl;
        return;
    }
    else{
        do{
            cout <<"NOMBRE: "<< temp->letra <<endl;
            temp = temp -> sig;
        }
        while(temp != grupos);
    }
}


//---------------------------------Metodos Equipos----------------------------------

//Busca una Seleccion y devuelve TRUE si lo encuentra en la lista y False si no lo encuentra
bool buscarSeleccion(string nombre){

    if(selecciones == NULL){
        cout<<endl<<"NO EXISTEN SELECCIONES"<<endl;
        }

    struct listaSelecciones *temp = selecciones;

    do{
        if(temp->nombre  == nombre){
            return true;
            }
        temp = temp -> sig;


    }while(temp != selecciones);

    return false;

}

//Inserta Selecciones de forma ordenada por nombre
bool insertarSeleccion_Ordenado(string nombre, int mundialesParticipados, int finales, int mundialesGanados, int PG, int PP, int PE, int GF, int GC, string confederacion){

    struct listaSelecciones *nn = new listaSelecciones();

    nn -> nombre = nombre;
    nn -> mundialesParticipados = mundialesParticipados;
    nn -> finales = finales;
    nn -> mundialesGanados = mundialesGanados;
    nn -> PG = PG;
    nn -> PP = PP;
    nn -> PE = PE;
    nn -> GF = GF;
    nn -> GC = GC;

    nn -> actualPG = 0;
    nn -> actualPP = 0;
    nn -> actualPE = 0;
    nn -> actualGF = 0;
    nn -> actualGC = 0;

    nn -> confederacion = confederacion;


    if (selecciones == NULL){
        selecciones = nn;
        selecciones->sig = nn;
        return true;
    }
    else if (buscarSeleccion(nombre)){
        return false;
    }
    else{
        struct listaSelecciones *temp = selecciones;
        struct listaSelecciones *temp3 = selecciones;

        while((temp->sig != selecciones) && (temp->nombre < nombre)){
            temp3 = temp;
            temp = temp -> sig;
        }


        if((temp == selecciones) && (temp->nombre > nombre)){
            struct listaSelecciones *temp2 = selecciones;

            while(temp2->sig != selecciones){
                temp2 = temp2->sig;
            }
            nn->sig = temp;
            temp2->sig = nn;
            selecciones = nn;
            return true;
        }

        else if((temp -> sig == selecciones) && (temp->nombre < nombre)){
            temp->sig = nn;
            nn->sig = selecciones;
            return true;
        }

        else{
            nn->sig = temp3->sig;
            temp3->sig = nn;
            return true;
        }
    }
    return false;
}

//Busca un Equipo y retorna el nodo.
struct listaSelecciones *existeSeleccion(string nacion){

    struct listaSelecciones *temp = selecciones;

    if(selecciones == NULL){
        return NULL;
    }

    do{
        if(temp->nombre == nacion){
            return temp;
            }
        temp = temp->sig;
    }while(temp != selecciones);
    return NULL;
}

//Busca un Equipo en Grupo si existe retorna TRUE de lo contrario retorna FALSE
bool buscarEquipoGrupo(string nacion){


    struct listaGrupos *temp2 = grupos;
    struct equipo *temp3 = temp2->lisEquipos;

    if(temp2 != NULL){
        while(temp3 != NULL){
            if(temp3->enlace->nombre == nacion){
                return true;
            }
            temp3 = temp3 -> sig;
        }
        return false;
    }
    return false;
}

//Inserta un Equipo a un Grupo.
bool insertarEquipoGrupo(string nacion, char sigla){

    int cont = 0;

    if((existeSeleccionG(nacion) == NULL) or (existeGrupo(sigla) == NULL)){
        return false;
    }

    struct listaGrupos *temp = existeGrupo(sigla);
    struct listaSelecciones * temp2 = existeSeleccion(nacion);

    struct equipo *nn = new equipo();
    nn->enlace = temp2;



    struct equipo *temp3 = temp->lisEquipos;

    while(temp3 != NULL){
            cont+=1;
            temp3 = temp3->sig;
    }

    if(cont < 4){
        if((temp != NULL) && (temp2 != NULL)){
            if(buscarEquipoGrupo(nacion) == false){
                struct equipo *nn= new equipo();

                nn->enlace = temp2;
                nn->sig = NULL;

                if(temp->lisEquipos == NULL){
                    temp->lisEquipos = nn;
                    nn->sig = NULL;
                }
                else{
                    struct equipo *temp3 = temp->lisEquipos;

                    while(temp3->sig != NULL){
                        temp3 = temp3->sig;
                    }
                    temp3->sig = nn;
                    nn->sig = NULL;
                }
                return true;
            }
            else{
                cout<<endl<<"**** EL EQUIPO YA EXISTE EN ESTE GRUPO"<<endl;
                return false;
            }
        }
    }
    else{
        cout<<endl<<"**** EL GRUPO EXCEDE AL LIMITE DE EQUIPOS"<<endl<<endl;
        return false;
    }
    return false;
}

//Imprime los Jugadores de un Equipo
void imprimirJugadoresEquipo(string nacion){

    cout <<endl<< "---IMPRESION DE LISTA JUGADORES DEL EQUIPO---"<<endl<<endl;

    struct listaSelecciones *temp = existeSeleccion(nacion);
    struct jugador *temp2 = temp->lisJugador;

    if(temp->sig != selecciones){
        while(temp->sig != selecciones){
            if(temp->nombre==nacion){
                while(temp2 != NULL){
                    cout<<temp2->enlace->nombre<<endl;
                    temp2 = temp2->sig;
                }
            }
            temp = temp -> sig;
        }
    }
}

//Imprime la lista de Seleccion
void imprimirSeleccion(){

    cout <<endl<< "---IMPRESION DE LISTA SELECCIONES---"<< endl<<endl;

    struct listaSelecciones *temp = selecciones;

    do{
        cout <<" -- Nombre Seleccion: "<< temp -> nombre <<endl;
        temp = temp -> sig;
    }while(temp != selecciones);

}


//----------------------Metodos Jugadores---------------------------------------


//Busca un jugador y devuelve TRUE si lo encuentra en la lista y False si no lo encuentra.
bool buscarJugador(string nombre){

    struct listaJugadores *temp = jugadores;

    if(jugadores == NULL){
        return false;
    }

    while(temp != NULL){
        if(temp->nombre  == nombre){
            return true;
            }
        temp = temp->sig;
    }
    return false;
}

//Inserta un jugador a la lista Jugadores
bool insertarJugadores(string nombre, string nacion, string posicion, string fechaNacimiento, string club, int golesMundiales, int mundiales){//Inserta Jugadores Ordenadamente

    if(buscarJugador(nombre)){
        cout<<endl<<"El jugador ya se encuentra insertado"<<endl;
        return false;
    }
    struct listaJugadores *nn = new listaJugadores();

    nn->nombre = nombre;
    nn->nacion = nacion;
    nn->posicion = posicion;
    nn->fechaNacimiento = fechaNacimiento;
    nn->club = club;
    nn->golesMundiales = golesMundiales;
    nn->mundiales = mundiales;

    if(jugadores==NULL){
        jugadores = nn;
        return true;
    }

    else{

        struct listaJugadores *temp = jugadores;
        struct listaJugadores *temp2 = jugadores;

        while((temp!=NULL) && (temp->nombre < nombre)){
            temp2 = temp;
            temp = temp->sig;
        }
        if(temp == NULL){
            temp2 -> sig = nn;
            nn -> sig = NULL;
            return true;
        }
        else if((temp == jugadores) && (temp->nombre > nombre)){
            nn->sig = temp;
            jugadores = nn;
            return true;
        }

        else{
            nn->sig = temp;
            temp2->sig = nn;
            return true;
        }
    }
    return false;
}

//Busca un Jugador y retorna un nodo.
struct listaJugadores *existeJugador(string nombreJU, string nacion){

    struct listaJugadores *temp = jugadores;

    while(temp->sig != NULL){
        if((temp->nombre == nombreJU) and (temp->nacion == nacion)){
            return temp;
            }
        temp = temp->sig;
    }
    return NULL;
}

//Busca un Jugador y si existe retorna TRUE de lo contrario retorna FALSE
bool buscarJugadorEquipo(string nacion, string nombreJU){

    struct listaSelecciones *temp2 = existeSeleccion(nacion);

    struct jugador *temp3 = temp2->lisJugador;

    if(temp2 != selecciones){
        while(temp3 != NULL){
            if((temp3->enlace->nombre ==  nombreJU) and (temp3->enlace->nacion ==  nacion)){
                return true;
            }
            temp3 = temp3 -> sig;
        }
        return false;
    }
    return false;
}

//Inserta un Jugador a un Equipo
bool insertarJugadorEquipo(string nacion, string nombreJU){

    int cont = 0;

    struct listaSelecciones * temp = existeSeleccion(nacion);
    struct listaJugadores *temp2 = existeJugador(nombreJU,nacion);

    struct jugador *nn = new jugador();
    nn->enlace = temp2;

    if((existeSeleccion(nacion) == NULL) || (existeJugador(nombreJU,nacion) == NULL)){
        return false;
    }
    struct jugador *temp3 = temp->lisJugador;


    while(temp3 != NULL){
            cont+=1;
            temp3 = temp3->sig;
    }
    if(cont < 22){
        if((temp->sig != selecciones) && (temp2 != NULL)){

            if(buscarJugadorEquipo(nacion, nombreJU) == false){

                struct jugador *nn= new jugador();

                nn->enlace = temp2;
                nn->sig = NULL;

                if(temp->lisJugador == NULL){
                    temp->lisJugador = nn;
                    nn->sig = NULL;
                }
                else{
                    struct jugador *temp3 = temp->lisJugador;
                    while(temp3->sig != NULL){
                        temp3 = temp3->sig;
                    }
                    temp3->sig = nn;
                    nn->sig = NULL;
                }
                return true;
            }
            else{
                cout<<endl<<"**** EL JUGADOR YA EXISTE EN ESTE EQUIPO"<<endl;
                return false;
            }
        }
    }
    else{
        cout<<endl<<"**** EL EQUIPO EXCEDE AL LIMITE DE JUGADORES"<<endl<<endl;
        return false;
    }
    return false;
}

//Imprime la lista de Jugadores
void imprimirJugadores(){

    cout <<endl<< "---IMPRESION DE LISTA JUGADORES---"<<endl<<endl;

    struct listaJugadores *temp = jugadores;

    while(temp != NULL){
        cout <<" -- Nombre: "<< temp -> nombre <<endl;
        temp = temp -> sig;
    }
}


//----------------------------Metodos Arbitros---------------------------------------


//Busca un arbitro y devuelve TRUE si lo encuentra en la lista y False si no lo encuentra.
bool buscarArbitro(string nombre){

    struct listaArbitros *temp = arbitros;

    if(arbitros == NULL){
        return false;
    }

    while(temp != NULL){
        if(temp->nombre  == nombre){
            return true;
            }
        temp = temp->sig;
    }
    return false;
}


//Inserta Arbitros Ordenadamente
bool insertarArbitro(string nombre, string nacion, string tipo){

    if(buscarArbitro(nombre)){
        cout<<endl<<"El Arbitro ya se encuentra insertado"<<endl;
        return false;
    }
    struct listaArbitros *nn = new listaArbitros();

    nn->nombre = nombre;
    nn->nacion = nacion;
    nn->tipo = tipo;

    if(arbitros==NULL){
        arbitros= nn;
        return true;
    }

    else{

        struct listaArbitros *temp = arbitros;
        struct listaArbitros *temp2 = arbitros;

        while((temp!=NULL) && (temp->nombre < nombre)){
            temp2 = temp;
            temp = temp->sig;
        }
        if(temp == NULL){
            temp2 -> sig = nn;
            nn -> sig = NULL;
            return true;
        }
        else if((temp == arbitros) && (temp->nombre > nombre)){
            nn->sig = temp;
            arbitros = nn;
            return true;
        }

        else{
            nn->sig = temp;
            temp2->sig = nn;
            return true;
        }
    }
    return false;
}

//Busca un Arbitro y retorna el nodo
struct listaArbitros *existeArbitro(string nombre){

    struct listaArbitros *temp = arbitros;

    if(arbitros == NULL){
        return NULL;
    }
    while(temp->sig != arbitros){
        if(temp->nombre == nombre){
            return temp;
            }
        temp = temp->sig;
    }
    return NULL;
}

//Imprime la lista de Arbitros
void imprimirArbitros(){

    cout <<endl<< "---IMPRESION DE LISTA ARBITROS---"<<endl<<endl;

    struct listaArbitros *temp = arbitros;

    while(temp != NULL){
        cout <<" -- Nombre: "<< temp -> nombre <<endl;
        temp = temp -> sig;
    }
}

//--------------------------------Metodos Estadio-----------------------------------------

//Busca un Estadio y si lo encuentra retorna false o de lo contrario retorna true
bool buscarEstadio(string nombre, string sede){

    struct listaEstadios *temp = estadios;

    if(estadios == NULL){
        return false;
    }
    while(temp->sig !=NULL){
        if((temp->nombre == nombre) and (temp->sede == sede)){
            return true;
        }
        temp = temp->sig;
    }
    return false;

}

//Inserta  un Estadio a la lista de Estadios
bool insertarEstadio(string nombre, int capacidad, string sede, int inauguracion, string ubicacion){

    struct listaEstadios *nn = new listaEstadios();

    nn->nombre = nombre;
    nn->capacidad = capacidad;
    nn->sede = sede;
    nn->inauguracion = inauguracion;
    nn->ubicacion = ubicacion;
    nn->sig = NULL;

    struct listaEstadios *temp = estadios;

    if(buscarEstadio(nombre, sede)){
        return false;
    }

    else if(estadios == NULL){
        estadios = nn;
        return true;
    }

    else{
        while(temp->sig != NULL){
            temp = temp->sig;
        }
        temp->sig = nn;
        return true;
    }
    return false;
}

//Imprime la lista de Estadios
void imprimirEstadios(){

    struct listaEstadios *temp = estadios;

    while(temp != NULL){
        cout<<"Estadio: "<<temp->nombre<<endl;
        temp = temp->sig;
    }

}


//Busca un Estadio y retorna el nodo
struct listaEstadios *existeEstadio(string nombre){

    struct listaEstadios *temp = estadios;

    if(estadios == NULL){
        return NULL;
    }
    while(temp->sig != estadios){
        if(temp->nombre == nombre){
            return temp;
            }
        temp = temp->sig;
    }
    return NULL;
}



//--------------------------------Metodos de Partidos-------------------------------------

//Busca un Partido y si lo encuentra retorna false o de lo contrario retorna true
bool buscarPartido(string id){

    struct Partidos *temp = listaPartidos;

    if(listaPartidos == NULL){
        return false;
    }
    while(temp->sig !=NULL){
        if(temp->id == id){
            return true;
        }
        temp = temp->sig;
    }
    return false;

}

//Inserta un Partido a la lista de Partidos
bool insertarPartido(string id, string fecha, string hora, string equi1, string equi2, string estadio, string albi1, string albi2, string albi3, string albi4, int cantPersAsist){

    struct Partidos *nP = new Partidos();

    nP->id = id;
    nP->fecha = fecha;
    nP->hora = hora;
    nP->cantPersAsist = cantPersAsist;
    nP->sig = NULL;
    nP->golEqui1 = 0;
    nP->golEqui2 = 0;

    struct Partidos *temp = listaPartidos;

    struct listaSelecciones *tempEqui1 = existeSeleccion(equi1);
    struct listaSelecciones *tempEqui2 = existeSeleccion(equi2);

    struct listaEstadios *tempEst = existeEstadio(estadio);

    struct listaArbitros *tempArb1 = existeArbitro(albi1);
    struct listaArbitros *tempArb2 = existeArbitro(albi2);
    struct listaArbitros *tempArb3 = existeArbitro(albi3);
    struct listaArbitros *tempArb4 = existeArbitro(albi4);

    struct partidosEquipos *nE1 = new partidosEquipos();
    nE1->enlace = tempEqui1;
    nE1->sig = NULL;

    struct partidosEquipos *nE2 = new partidosEquipos();
    nE2->enlace = tempEqui2;
    nE2->sig = NULL;

    struct partidosEstadios *nEs = new partidosEstadios();
    nEs->enlace = tempEst;
    nEs->sig = NULL;

    struct partidosArbitros *nA1 = new partidosArbitros();
    nA1->enlace = tempArb1;
    nA1->sig = NULL;

    struct partidosArbitros *nA2 = new partidosArbitros();
    nA2->enlace = tempArb2;
    nA2->sig = NULL;

    struct partidosArbitros *nA3 = new partidosArbitros();
    nA3->enlace = tempArb3;
    nA3->sig = NULL;

    struct partidosArbitros *nA4 = new partidosArbitros();
    nA4->enlace = tempArb4;
    nA4->sig = NULL;

    if((existeSeleccion(equi1) == NULL) or (existeSeleccion(equi2) == NULL) or (existeEstadio(estadio)== NULL) or (existeArbitro(albi1) == NULL) or (existeArbitro(albi2) == NULL) or (existeArbitro(albi3) == NULL) or (existeArbitro(albi4) == NULL)){
        return false;
    }

    else if(buscarPartido(id) == true){
        return false;
    }

    else if(listaPartidos == NULL){
        listaPartidos = nP;

        nP->listaPE1 = nE1;
        nP->listaPE2 = nE2;

        nP->listaEst = nEs;

        nP->listaArbi = nA1;
        nP->listaArbi = nA2;
        nP->listaArbi = nA3;
        nP->listaArbi = nA4;
        return true;
    }

    else{
        while(temp->sig != NULL){
            temp = temp->sig;
        }
        temp->sig = nP;

        nP->listaPE1 = nE1;
        nP->listaPE2 = nE2;

        nP->listaEst = nEs;

        nP->listaArbi = nA1;
        nP->listaArbi = nA2;
        nP->listaArbi = nA3;
        nP->listaArbi = nA4;
        return true;
    }
    return false;
}

//Busca un Partido y retorna el nodo
struct Partidos *existePartido(string id){

    struct Partidos *temp = listaPartidos;

    if(listaPartidos == NULL){
        return NULL;
    }
    while(temp != NULL){
        if(temp->id == id){
            return temp;
            }
        temp = temp->sig;
    }
    return NULL;
}

//Inserta Tarjetas a un Partidos
bool insertarTarjetasPartidos(string idPart, string nombreJu, string nacionJu, string color, int minuto){

    string fecha;
    struct Partidos *tempPar = existePartido(idPart);
    struct listaJugadores *tempJug = existeJugador(nombreJu, nacionJu);

    struct partidosTarjetas *nT = new partidosTarjetas();

    nT->color = color;
    nT->minuto = minuto;
    nT->enlace = tempJug;
    nT->sig = NULL;

    if((tempPar == NULL) or (tempJug == NULL)){
        return false;
    }

    else if(tempPar->estado == true){
        return false;
    }

    else if((tempPar->listaPE1->enlace->nombre == nacionJu) or (tempPar->listaPE2->enlace->nombre == nacionJu)){

        if(tempPar->listaPT == NULL){
            tempPar->listaPT = nT;

            if((nT->color == "Amarilla") or (nT->color == "amarilla")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    struct partidosArbitros *tempParArb = tempPar->listaArbi;
                    while(tempParArb != NULL){
                        if(tempParArb->enlace->tipo == "Central"){
                            tempParArb->enlace->amarilla++;
                        }
                        tempParArb = tempParArb->sig;
                    }
                }
            }
            else if((nT->color == "Roja") or (nT->color == "roja")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    struct partidosArbitros *tempParArb = tempPar->listaArbi;
                    while(tempParArb != NULL){
                        if(tempParArb->enlace->tipo == "Central"){
                            tempParArb->enlace->roja++;
                        }
                        tempParArb = tempParArb->sig;
                    }
                }
            }
            return true;
        }
        else{
            struct partidosTarjetas *tempParTar = tempPar->listaPT;

            while(tempParTar->sig != NULL){
                tempParTar = tempParTar->sig;
            }
            tempParTar->sig = nT;

            if((nT->color == "Amarilla") or (nT->color == "amarilla")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    struct partidosArbitros *tempParArb = tempPar->listaArbi;
                    while(tempParArb != NULL){
                        if(tempParArb->enlace->tipo == "Central"){
                            tempParArb->enlace->amarilla++;
                        }
                        tempParArb = tempParArb->sig;
                    }
                }
            }
            else if((nT->color == "Roja") or (nT->color == "roja")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    struct partidosArbitros *tempParArb = tempPar->listaArbi;
                    while(tempParArb != NULL){
                        if(tempParArb->enlace->tipo == "Central"){
                            tempParArb->enlace->roja++;
                        }
                        tempParArb = tempParArb->sig;
                    }
                }
            }
            return true;
        }

    }
    else{
        cout<<endl<<endl<<"-----------LOS DATOS NO CONCUERDAN CON EL PARTIDO--------"<<endl<<endl;
        return false;
    }
}

//Inserta Goles a un Partidos
bool insertarGolesPartidos(string idPart, string nombreJu, string nacionJu, string forma, int minuto){

    string fecha;

    struct Partidos *tempPar = existePartido(idPart);
    struct listaJugadores *tempJug = existeJugador(nombreJu, nacionJu);

    struct partidosTarjetas *tempParTar = tempPar->listaPT;

    struct partidosGoles *nG = new partidosGoles();

    nG->forma = forma;
    nG->minuto = minuto;
    nG->enlace = tempJug;
    nG->sig = NULL;

    if((tempPar == NULL) or (tempJug == NULL)){
        return false;
    }
    else if(tempPar->estado == true){
        return false;
    }
    while(tempParTar != NULL){
        if(tempParTar->enlace->nombre == nombreJu){
            if((tempParTar->color == "Roja") and (tempParTar->minuto < minuto)){
                cout<<endl<<endl<<"EL JUGADOR A SIDO EXPULSADO"<<endl;
                return false;
            }
        }
        tempParTar = tempParTar->sig;
    }
    if((tempPar->listaPE1->enlace->nombre == nacionJu) or (tempPar->listaPE2->enlace->nombre == nacionJu)){

        if(tempPar->listaPG == NULL){
            tempPar->listaPG = nG;
            if((tempPar->listaPG->forma == "Cabeza") or (tempPar->listaPG->forma == "cabeza")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    tempJug->cabeza++;
                    tempJug->golesActuales++;
                }
            }
            else if((tempPar->listaPG->forma != "Cabeza") or (tempPar->listaPG->forma != "cabeza")){
                tempJug->golesActuales++;
            }
            return true;
        }
        else{
            struct partidosGoles *tempParGol = tempPar->listaPG;

            while(tempParGol->sig != NULL){
                tempParGol = tempParGol->sig;
            }
            tempParGol->sig = nG;
            if((tempParGol->forma == "Cabeza") or (tempParGol->forma == "cabeza")){
                fecha = tempPar->fecha;
                string fecha1;
                int j = 0;
                for(int i = 0; i < fecha.length(); i++){
                    if(fecha[i] == '/'){
                        j++;
                    }
                    else if(j == 2){
                        fecha1 += fecha[i];
                    }
                }
                if(fecha1 == "2014"){
                    tempJug->cabeza++;
                    tempJug->golesActuales++;
                }
            }
            else if((tempPar->listaPG->forma != "Cabeza") or (tempPar->listaPG->forma != "cabeza")){
                tempJug->golesActuales++;
            }
            return true;
        }

    }
    else{
        cout<<endl<<endl<<"-----------LOS DATOS NO CONCUERDAN CON EL PARTIDO--------"<<endl<<endl;
        return false;
    }
}


//Imprime la lista de Partidos
void imprimirPartidos(){

    struct Partidos *temp = listaPartidos;




    while(temp != NULL){
        struct partidosTarjetas *tempParTar  = temp->listaPT;
        struct partidosGoles *tempParGol = temp->listaPG;
        struct partidosArbitros *tempParArb = temp->listaArbi;
        cout<<endl<<endl<<endl<<"---------------------------------------------"<<endl<<endl;
        cout<<"        "<<temp->listaPE1->enlace->nombre<<" vrs "<<temp->listaPE2->enlace->nombre<<"        "<<endl;
        cout<<endl<<"Id: "<<temp->id<<endl;
        cout<<"Fecha: "<<temp->fecha<<endl;
        cout<<"Hora: "<<temp->hora<<endl;
        cout<<endl<<"Tarjetas: "<<endl<<endl;
        while(tempParTar != NULL){
            cout<<tempParTar->color<<" al Jugador "<<tempParTar->enlace->nombre<<" en el minuto "<<tempParTar->minuto<<endl;
            tempParTar = tempParTar->sig;
        }
        cout<<endl<<"Goles: "<<endl<<endl;
        while(tempParGol != NULL){
            cout<<"Gol de "<<tempParGol->forma<<" del Jugador "<<tempParGol->enlace->nombre<<" en el minuto "<<tempParGol->minuto<<endl;
            tempParGol = tempParGol->sig;
        }
        temp = temp->sig;
    }
}

//Imprime la Infromacion de un Partido X
void imprimirUnPartido(string idPart){

    struct Partidos *temp = existePartido(idPart);

    if(temp == NULL){
        cout<<endl<<endl<<"EL PARTIDO NO SE ENCUENTRA REGISTRADO"<<endl<<endl;
        return;
    }

    struct partidosTarjetas *tempParTar  = temp->listaPT;
    struct partidosGoles *tempParGol = temp->listaPG;

    cout<<endl<<endl<<endl<<"---------------------------------------------"<<endl<<endl;
    cout<<"        "<<temp->listaPE1->enlace->nombre<<" vrs "<<temp->listaPE2->enlace->nombre<<"        "<<endl;
    cout<<endl<<"Id: "<<temp->id<<endl;
    cout<<"Fecha: "<<temp->fecha<<endl;
    cout<<"Hora: "<<temp->hora<<endl;
    cout<<endl<<"Tarjetas: "<<endl<<endl;
    while(tempParTar != NULL){
        cout<<tempParTar->color<<" al Jugador "<<tempParTar->enlace->nombre<<" en el minuto "<<tempParTar->minuto<<endl;
        tempParTar = tempParTar->sig;
    }
    cout<<endl<<"Goles: "<<endl<<endl;
    while(tempParGol != NULL){
        cout<<"Gol de "<<tempParGol->forma<<" del Jugador "<<tempParGol->enlace->nombre<<" en el minuto "<<tempParGol->minuto<<endl;
        tempParGol = tempParGol->sig;
    }

}


void finalizar(string idPart){

    struct Partidos *tempPart = existePartido(idPart);

    if(tempPart != NULL){
        tempPart->estado = true;
    }
    else if(tempPart == NULL){
        cout <<endl<<endl<<"--- EL PARTIDO NO EXISTE ---"<<endl;
    }
}


//Actualiza todos los resultados de los Partidos
void Actualizar(){


    struct Partidos *tempPart = listaPartidos;

    if(tempPart == NULL){
        cout<<endl<<endl<<"LA LISTA PARTIDOS ESTA VACIA"<<endl<<endl;
    }


    while(tempPart != NULL){

        struct partidosGoles *tempPartGol = tempPart->listaPG;
        while(tempPartGol != NULL){

            if((tempPartGol->enlace->nacion == tempPart->listaPE2->enlace->nombre) and (tempPartGol->forma == "Autogol")){
                tempPart->golEqui1++;
            }
            else if((tempPartGol->enlace->nacion == tempPart->listaPE1->enlace->nombre) and (tempPartGol->forma == "Autogol")){
                 tempPart->golEqui2++;
            }
            else if(tempPartGol->enlace->nacion == tempPart->listaPE2->enlace->nombre){
                 tempPart->golEqui2++;
            }
            else if(tempPartGol->enlace->nacion == tempPart->listaPE1->enlace->nombre){
                 tempPart->golEqui1++;
            }
            tempPartGol = tempPartGol->sig;
        }

        if(tempPart->listaPG != NULL){
            int pts = 0;
            int pts1 = 0;

            if(tempPart->golEqui1 > tempPart->golEqui2){
                tempPart->listaPE1->enlace->actualPG ++ ;
                pts = tempPart->listaPE1->enlace->actualPG * 3;
                tempPart->listaPE1->enlace->pts += pts;
                tempPart->listaPE2->enlace->actualPP ++;
                pts = 0;
            }
            else if(tempPart->golEqui1 == tempPart->golEqui2){
                tempPart->listaPE1->enlace->actualPE ++;
                tempPart->listaPE2->enlace->actualPE ++;
                pts = tempPart->listaPE1->enlace->actualPE * 1;
                tempPart->listaPE1->enlace->pts += pts;
                pts1 = tempPart->listaPE2->enlace->actualPE * 1;
                tempPart->listaPE2->enlace->pts += pts1;
                pts = 0;
                pts1 = 0;
            }
            else if(tempPart->golEqui1 < tempPart->golEqui2){
                tempPart->listaPE1->enlace->actualPP ++;
                tempPart->listaPE2->enlace->actualPG ++;
                pts = tempPart->listaPE2->enlace->actualPG * 3;
                tempPart->listaPE2->enlace->pts += pts;
                pts = 0;
            }
            tempPart->listaPE1->enlace->actualGF += tempPart->golEqui1;
            tempPart->listaPE2->enlace->actualGF += tempPart->golEqui2;

            tempPart->listaPE1->enlace->actualGC += tempPart->golEqui2;
            tempPart->listaPE2->enlace->actualGC += tempPart->golEqui1;

            tempPart->listaPE1->enlace->PJ++;
            tempPart->listaPE2->enlace->PJ++;
        }
        else if((tempPart->estado == true) and (tempPart->listaPG == NULL)){
            int pts = 0;
            int pts1 = 0;
            tempPart->listaPE1->enlace->PJ++;
            tempPart->listaPE2->enlace->PJ++;
            tempPart->golEqui1 = 0;
            tempPart->golEqui1 = 0;
            tempPart->listaPE1->enlace->actualPE ++;
            tempPart->listaPE2->enlace->actualPE ++;
            pts = tempPart->listaPE1->enlace->actualPE * 1;
            tempPart->listaPE1->enlace->pts += pts;
            pts1 = tempPart->listaPE2->enlace->actualPE * 1;
            tempPart->listaPE2->enlace->pts += pts1;
            pts = 0;
            pts1 = 0;
        }
        tempPart = tempPart->sig;
    }
}
//Actualiza los Octavos de final.
void ActualizarOctavos(){

    struct listaGrupos *tempG = grupos;


    if(tempG == NULL){
        cout<<endl<<endl<<"NO EXISTEN GRUPOS"<<endl<<endl;
        return;
    }

    struct equipo *tempGruEquiAux = tempG->lisEquipos;
    struct equipo *tempGruEquiAux1 = tempG->lisEquipos;
    struct equipo *tempGruEquiAux2 = tempG->lisEquipos;

    do{
        struct equipo *tempGruEqui = tempG->lisEquipos;

        while(tempGruEqui != NULL){
            if(tempGruEqui->enlace->pts >= tempGruEquiAux->enlace->pts){
                tempGruEquiAux1 = tempGruEquiAux;
                tempGruEquiAux = tempGruEqui;
            }
            else if(tempGruEqui->enlace->pts == tempGruEquiAux1->enlace->pts){
                tempGruEquiAux1 = tempGruEqui;
            }
            tempGruEqui = tempGruEqui->sig;
        }
        tempGruEquiAux->enlace->octavos = true;
        tempGruEquiAux1->enlace->octavos = true;
        cout<<"***************** "<<tempG->letra<<" *******************"<<endl;
        cout<<tempGruEquiAux->enlace->nombre<<endl;
        cout<<tempGruEquiAux1->enlace->nombre<<endl<<endl;
        tempGruEquiAux = tempGruEquiAux2;
        tempGruEquiAux1 = tempGruEquiAux2;
        tempG = tempG->sig;

    }while(tempG != grupos);
}


//-------------------------------------Metodos de Consultas--------------------------------------------

//Imprime el resultado de un Partido X
void  consulta_1(string idPart){


    struct Partidos *tempPart = existePartido(idPart);

    if(tempPart == NULL){
        cout<<endl<<endl<<"EL PARTIDO NO EXISTE"<<endl<<endl;
    }
    cout<<endl<<endl<<tempPart->listaPE1->enlace->nombre<<" "<<tempPart->golEqui1<<" - "<<tempPart->golEqui2<<" "<<tempPart->listaPE2->enlace->nombre<<endl<<endl;
}

//Imprime el Jugador mas joven de un Equipo X
void consulta_2(string nombreEqui){

    string fecha;
    int edad = 0;
    int cont = 0;
    int ano = 0;
    int mes = 0;
    int dia = 0;
    int jugad = 0;
    int jugadAux = 0;
    int aux = 0;

    struct listaSelecciones *tempSele = existeSeleccion(nombreEqui);

    struct jugador *tempSeleJuga = tempSele->lisJugador;
    struct jugador *tempSeleJuga1 = tempSele->lisJugador;

    if(tempSele == NULL){
        cout<<endl<<endl<<"EL EQUIPO NO EXISTE"<<endl<<endl;
        return;
    }

    while(tempSeleJuga != NULL){
        fecha = tempSeleJuga->enlace->fechaNacimiento;
        for(int i = fecha.length()-1; i >= 0; i--,cont++){
            if(cont == 0){
                aux = fecha[i];
                aux-=48;
                edad += aux;
                aux = 0;
            }
            else if(cont == 1){
                aux = fecha[i];
                aux-=48;
                edad += (aux*10);
                aux = 0;
            }
            else if((fecha[i] == '/') and (cont == 2)){
                mes = edad;
                cont = -1;
                edad = 0;
            }
            else if(cont == 2){
                aux = fecha[i];
                aux-=48;
                edad += (aux*100);
            }

            else if((cont == 3) and (i == 6)){
                aux = fecha[i];
                aux-=48;
                edad += (aux*1000);
                aux = 0;
            }
            else if((fecha[i] == '/') and (cont == 4)){
                ano = edad;
                edad = 0;
                cont = -1;
            }
        }
        dia = edad;
        edad = 0;
        cont = 0;

        jugadAux = dia+(mes*31)+(ano*365);

        if(jugad <= jugadAux){
            jugad = jugadAux;
            tempSeleJuga1 = tempSeleJuga;
        }
        tempSeleJuga = tempSeleJuga->sig;
        jugadAux = 0;
    }
    cout<<endl<<endl<<"El Jugador mas joven del equipo "<<nombreEqui<<" es: "<<tempSeleJuga1->enlace->nombre<<endl<<endl;
}

//Imprime el Jugador mas viejo de un Equipo X
void consulta_3(string nombreEqui){

    string fecha;
    int edad = 0;
    int cont = 0;
    int ano = 0;
    int mes = 0;
    int dia = 0;
    int jugad = 0;
    int jugadAux = 0;
    int aux = 0;

    struct listaSelecciones *tempSele = existeSeleccion(nombreEqui);

    struct jugador *tempSeleJuga = tempSele->lisJugador;
    struct jugador *tempSeleJuga1 = tempSele->lisJugador;

    if(tempSele == NULL){
        cout<<endl<<endl<<"EL EQUIPO NO EXISTE"<<endl<<endl;
        return;
    }

    while(tempSeleJuga != NULL){
        fecha = tempSeleJuga->enlace->fechaNacimiento;
        for(int i = fecha.length()-1; i >= 0; i--,cont++){
            if(cont == 0){
                aux = fecha[i];
                aux-=48;
                edad += aux;
                aux = 0;
            }
            else if(cont == 1){
                aux = fecha[i];
                aux-=48;
                edad += (aux*10);
                aux = 0;
            }
            else if((fecha[i] == '/') and (cont == 2)){
                mes = edad;
                cont = -1;
                edad = 0;
            }
            else if(cont == 2){
                aux = fecha[i];
                aux-=48;
                edad += (aux*100);
            }

            else if((cont == 3) and (i == 6)){
                aux = fecha[i];
                aux-=48;
                edad += (aux*1000);
                aux = 0;
            }
            else if((fecha[i] == '/') and (cont == 4)){
                ano = edad;
                edad = 0;
                cont = -1;
            }
        }
        dia = edad;
        edad = 0;
        cont = 0;

        jugadAux = dia+(mes*31)+(ano*365);

        if(jugad == 0){
            jugad = jugadAux;
        }
        else if(jugad < jugadAux){
            jugadAux = 0;
        }
        else if(jugad > jugadAux){
            jugad = jugadAux;
            tempSeleJuga1 = tempSeleJuga;
        }
        tempSeleJuga = tempSeleJuga->sig;
        jugadAux = 0;
    }
    cout<<endl<<endl<<"El Jugador mas viejo del equipo "<<nombreEqui<<" es: "<<tempSeleJuga1->enlace->nombre<<endl<<endl;
}

//Retorna el gol más tempranero del mundial 2014.
void consulta_4(){

    string fecha;

    struct Partidos *tempPart = listaPartidos;
    struct Partidos *tempPart1 = listaPartidos;
    struct partidosGoles *tempPartGol1 = tempPart->listaPG;

    if(tempPart == NULL){
        cout<<endl<<endl<<"NO EXISTEN PARTIDOS, NI MENOS GOLES"<<endl<<endl;
        return;
    }

    while(tempPart != NULL){
        fecha = tempPart->fecha;
        string fecha1;
        int j = 0;
        for(int i = 0; i < fecha.length(); i++){
            if(fecha[i] == '/'){
                j++;
            }
            else if(j == 2){
                fecha1 += fecha[i];
            }
        }
        if(fecha1 == "2014"){
            struct partidosGoles *tempPartGol = tempPart->listaPG;

            while(tempPartGol != NULL){
                if(tempPartGol->minuto < tempPartGol1->minuto){
                    tempPartGol1 = tempPartGol;
                    tempPart1 = tempPart;
                }
                tempPartGol = tempPartGol->sig;
            }
        }
        tempPart = tempPart->sig;
    }

    cout<<endl<<endl<<"El Gol mas temprano fue en el minuto "<<tempPartGol1->minuto;
    cout<<" por "<<tempPartGol1->enlace->nombre<<endl<<"En el Partido "<<tempPart1->listaPE1->enlace->nombre;
    cout<<" vrs "<<tempPart1->listaPE2->enlace->nombre<<endl<<endl;
}

//Retorna la mayor goleada del mundial 2014.
void consulta_5(){

    string fecha;
    int marcadores = 0;
    int marcadores1 = 0;

    struct Partidos *tempPart = listaPartidos;
    struct Partidos *tempPart1 = listaPartidos;



    if(tempPart == NULL){
        cout<<endl<<endl<<"NO EXISTEN PARTIDOS, NI MENOS GOLES"<<endl<<endl;
        return;
    }

    while(tempPart != NULL){
        fecha = tempPart->fecha;
        string fecha1;
        int j = 0;
        for(int i = 0; i < fecha.length(); i++){
            if(fecha[i] == '/'){
                j++;
            }
            else if(j == 2){
                fecha1 += fecha[i];
            }
        }
        if(fecha1 == "2014"){

            marcadores = tempPart->golEqui1 - tempPart->golEqui2;

            if(marcadores < 0){
                marcadores = marcadores*-1;
            }
            if(marcadores > marcadores1){
                marcadores1 = marcadores;
                tempPart1 = tempPart;
            }
        }
        tempPart = tempPart->sig;
    }
    cout<<endl<<endl<<"La mayor Goleada fue en el Partido "<<tempPart1->listaPE1->enlace->nombre;
    cout<<" "<<tempPart1->golEqui1<<" vrs "<<tempPart1->golEqui2<<" "<<tempPart1->listaPE2->enlace->nombre;
    cout<<endl<<"El "<<tempPart1->fecha<<" a las "<<tempPart1->hora<<" en el Estadio ";
    cout<<tempPart1->listaEst->enlace->nombre<<endl<<endl;
}


//Retorna el Jugador que ha hecho mas goles de cabeza en el mundial 2014.
void consulta_6(){

    struct listaJugadores *tempJuga = jugadores;
    struct listaJugadores *tempJugaAux = jugadores;

    if(tempJuga == NULL){
        cout<<endl<<endl<<"NO EXISTEN JUGADORES"<<endl<<endl;
        return;
    }

    while(tempJuga != NULL){
        if(tempJuga->cabeza > tempJugaAux->cabeza){
            tempJugaAux = tempJuga;
        }
        tempJuga = tempJuga->sig;
    }
    cout<<endl<<endl<<"El Jugador con mas Goles de Cabeza es "<<tempJugaAux->nombre;
}


//Imprime el equipo que suma más goles en todos los mundiales incluyendo 2014.
void consulta_7(){


    int golTotal;
    int golTotal1;

    struct listaSelecciones *tempEqui = selecciones;

    struct listaSelecciones *tempEquiAux = selecciones;

    if(tempEqui == NULL){
        cout<<endl<<endl<<"NO EXISTEN JUGADORES"<<endl<<endl;
        return;
    }

    while(tempEqui->sig != selecciones){
        golTotal = tempEqui->actualGF + tempEqui->GF;
        struct listaSelecciones *tempEqui1 = selecciones;

        while(tempEqui1->sig != selecciones){
            golTotal1 = tempEqui1->actualGF + tempEqui1->GF;
            if(golTotal < golTotal1){
                tempEquiAux = tempEqui1;
            }
            tempEqui1 = tempEqui1->sig;
        }
        tempEqui = tempEqui->sig;
    }
    cout<<endl<<endl<<"El Equipo con mas Goles en la Historica  "<<tempEquiAux->nombre;
}

//Imprime el árbitro que ha sacado más tarjetas amarillas en este mundial 2014.
void consulta_8(){

    struct listaArbitros *tempArb = arbitros;
    struct listaArbitros *tempArbAux = arbitros;

    if(tempArb == NULL){
        cout<<endl<<endl<<"NO EXISTEN ARBITROS"<<endl<<endl;
        return;
    }

    while(tempArb != NULL){
        if((tempArb->tipo == "Central") or (tempArb->tipo == "central")){
            if(tempArb->amarilla > tempArbAux->amarilla){
                tempArbAux = tempArb;
            }
        }
        tempArb = tempArb->sig;
    }
    cout<<endl<<endl<<"El Arbitro que ha sacado mas amarillas es "<<tempArbAux->nombre;
}


//-------------------------------------Metodos de Reportes--------------------------------------------

//Muestra la informacion de los estadios utilizados en el 2014
void reporte_1(){

    struct listaEstadios *tempEst = estadios;

    if(tempEst == NULL){
        cout<<endl<<endl<<"NO SE HAN UTILIZADO ESTADIOS EN EL 2014"<<endl<<endl;
        return;
    }

    while(tempEst != NULL){

        cout<<endl<<endl<<"*********** "<<tempEst->nombre<<" ***********";
        cout<<endl<<endl<<"Sede: "<<tempEst->sede;
        cout<<endl<<"Ubicacion: "<<tempEst->ubicacion;
        cout<<endl<<"Inauguracion: "<<tempEst->inauguracion;
        cout<<endl<<"Capacidad: "<<tempEst->capacidad;

        tempEst = tempEst->sig;
    }
}

//Muestra la informacion de los equipos con su respectiva lista de jugadores en el 2014.
void reporte_2(){

    struct listaSelecciones *tempEqui = selecciones;

    if(tempEqui == NULL){
        cout<<endl<<endl<<"NO SE HAN UTILIZADO LOS EQUIPOS EN EL 2014"<<endl<<endl;
        return;
    }
    do{
        if(tempEqui->estado == true){
            cout<<endl<<endl<<"********** "<<tempEqui->nombre<<" ************"<<endl;
            cout<<endl<<"Confederacion: "<<tempEqui->confederacion;
            cout<<endl<<"Mundiales a los que ha Participado: "<<tempEqui->mundialesParticipados;
            cout<<endl<<"Mundiales Ganados: "<<tempEqui->mundialesGanados<<endl;
            cout<<endl<<"       Lista Jugadores        "<<endl<<endl;
            struct jugador *tempEquiJuga = tempEqui->lisJugador;
            while(tempEquiJuga != NULL){
                cout<<endl<<tempEquiJuga->enlace->nombre;
                tempEquiJuga = tempEquiJuga->sig;
            }
        }
        tempEqui = tempEqui->sig;

    }while(tempEqui != selecciones);
}

//Muestra la informacion de los grupos con su respectiva lista de equipos en el 2014.
void reporte_3(){

    struct listaGrupos *tempGru = grupos;

    if(tempGru == NULL){
        cout<<endl<<endl<<"NO SE HAN REALIZADO LOS GRUPOS EN EL 2014"<<endl<<endl;
        return;
    }
    do{
        cout<<endl<<endl<<"********** "<<tempGru->letra<<" ************"<<endl;
        cout<<endl<<"       Lista Equipos        "<<endl<<endl;
        struct equipo *tempGruEqui = tempGru->lisEquipos;
        while(tempGruEqui != NULL){
            cout<<endl<<tempGruEqui->enlace->nombre;
            tempGruEqui = tempGruEqui->sig;
        }

    tempGru = tempGru->sig;

    }while(tempGru != grupos);
}

//Muestra los goleadores de forma ordenada del 2014 y los demas Mundiales.
void reporte_4(){

    struct listaJugadores *tempJug = jugadores;

    if(tempJug == NULL){
        cout<<endl<<endl<<"NO EXISTEN JUGADORES"<<endl<<endl;
        return;
    }

    cout<<endl<<"       Lista Goleadores       "<<endl<<endl;
    while(tempJug != NULL){
        struct listaJugadores *tempJugAux = jugadores;
        struct listaJugadores *tempJugAux1 = jugadores;
        struct listaJugadores *tempJugAux2 = jugadores;

        while(tempJugAux != NULL){
            if((tempJugAux->golesActuales >= tempJugAux1->golesActuales) and (tempJugAux->ordenadoGolead == false)){
                tempJugAux1 = tempJugAux;
            }
            else if((tempJugAux1->golesActuales == tempJugAux2->golesActuales) and (tempJugAux1->ordenadoGolead == true)){
                tempJugAux1 = tempJugAux;
            }
            tempJugAux = tempJugAux->sig;
        }
        tempJugAux1->ordenadoGolead = true;
        cout<<endl<<"Nombre: "<<tempJugAux1->nombre<<"  - Equipo: "<<tempJugAux1->nacion<<"  - Goles Actuales: "<<tempJugAux1->golesActuales;
        cout<<"  - Total Goles: "<<tempJugAux1->golesMundiales<<endl;
        tempJug = tempJug->sig;
    }
}

//Muestra la tabla de posiciones de los grupos 2014.
void reporte_5(){

    struct listaGrupos *tempGru = grupos;

    if(tempGru == NULL){
        cout<<endl<<endl<<"NO SE HAN REALIZADO LOS GRUPOS EN EL 2014"<<endl<<endl;
        return;
    }
    do{
        cout<<endl<<endl<<"********** "<<tempGru->letra<<" ************"<<endl;
        struct equipo *tempGruEqui = tempGru->lisEquipos;
        while(tempGruEqui != NULL){
            int GD = tempGruEqui->enlace->actualGF - tempGruEqui->enlace->actualGC;
            cout<<endl<<"Nombre: "<<tempGruEqui->enlace->nombre<<"  PJ: "<<tempGruEqui->enlace->PJ<<"  PG: "<<tempGruEqui->enlace->actualPG;
            cout<<"  PP: "<<tempGruEqui->enlace->actualPP<<"  PE: "<<tempGruEqui->enlace->actualPE;
            cout<<"  GF: "<<tempGruEqui->enlace->actualGF<<"  GC: "<<tempGruEqui->enlace->actualGC;
            cout<<"  GD: "<<GD<<"  PTS: "<<tempGruEqui->enlace->pts<<endl;
            tempGruEqui = tempGruEqui->sig;
        }

    tempGru = tempGru->sig;

    }while(tempGru != grupos);
}


//Muestra la tabla de posiciones historica de los equipos hasta el 2010.
void reporte_6(){

    struct listaSelecciones *tempEqui = selecciones;


    cout<<endl<<endl<<"********** Tabla de Posiciones Historica hasta 2010 ************"<<endl;
    do{
        if(tempEqui->estado == false){
            int GD = tempEqui->GF - tempEqui->GC;
            int PJ = tempEqui->PE+(tempEqui->PG/3);
            int pts = (tempEqui->PE*1)+(tempEqui->PG*3);
            cout<<endl<<"Nombre: "<<tempEqui->nombre<<"  PJ: "<<PJ<<"  PG: "<<tempEqui->PG;
            cout<<"  PP: "<<tempEqui->PP<<"  PE: "<<tempEqui->PE;
            cout<<"  GF: "<<tempEqui->GF<<"  GC: "<<tempEqui->GC;
            cout<<"  GD: "<<GD<<"  PTS: "<<pts<<endl;
        }
        tempEqui = tempEqui->sig;

    }while(tempEqui != selecciones);

}


//Muestra los goleadores de forma ordenada hasta el 2010.
void reporte_7(){

    struct listaJugadores *tempJug = jugadores;

    if(tempJug == NULL){
        cout<<endl<<endl<<"NO EXISTEN JUGADORES"<<endl<<endl;
        return;
    }

    cout<<endl<<"       Lista Goleadores       "<<endl<<endl;
    while(tempJug != NULL){
        struct listaJugadores *tempJugAux = jugadores;
        struct listaJugadores *tempJugAux1 = jugadores;
        struct listaJugadores *tempJugAux2 = jugadores;

        while(tempJugAux != NULL){
            if((tempJugAux->golesMundiales >= tempJugAux1->golesMundiales) and (tempJugAux->ordenadoGoleadAux == false)){
                tempJugAux1 = tempJugAux;
            }
            else if((tempJugAux1->golesMundiales == tempJugAux2->golesMundiales) and (tempJugAux1->ordenadoGoleadAux == true)){
                tempJugAux1 = tempJugAux;
            }
            tempJugAux = tempJugAux->sig;
        }
        tempJugAux1->ordenadoGoleadAux = true;
        cout<<endl<<"Nombre: "<<tempJugAux1->nombre<<"  - Equipo: "<<tempJugAux1->nacion;
        cout<<"  - Goles Mundiales: "<<tempJugAux1->golesMundiales<<endl;
        tempJug = tempJug->sig;
    }
}


//*************************************** METODOS INTERFAZ ****************************************






//-------------------------Metodos de Interfaz de Grupos---------------------------------


//Muestra la opciones relacionadas con grupos al usuario desde la Interfaz
void gruposGUI(){
    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU GRUPOS-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR GRUPO";
    cout <<endl<<"2. AGREGAR EQUIPO A UN GRUPO";
    cout <<endl<<"3. MOSTRAR LISTA DE EQUIPO DE UN GRUPO X";
    cout <<endl<<"4. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarGrupoGUI();
    }
    else if (x == '2'){
        insertarEquipoGrupoGUI();
    }
    else if (x == '3'){
        imprimirEquiposGrupoGUI();
    }
    else if (x == '4'){
        menuPrincipal();
    }
    else{
        gruposGUI();
    }
}


//Inserta un Grupo por medio de Interfaz
void insertarGrupoGUI(){

    system("cls");

    char sigla;
    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------------------------AGREGAR GRUPO-----------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL GRUPO: ";
        cin >> sigla;
        if (insertarGrupo_Ordenado(sigla) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL GRUPO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
    }
    gruposGUI();
}


//Inserta Equipo a un Grupo desde la Interfaz
void insertarEquipoGrupoGUI(){

    system("cls");

    string nombre;
    char sigla;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-------------------------AGREGAR EQUIPO A GRUPO---------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL GRUPO ";
        cin >> sigla;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin >> nombre;


        if (insertarEquipoGrupo(nombre,sigla) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL EQUIPO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    gruposGUI();
}


//Imprime los Equipos de un Grupo desde la Interfaz
void imprimirEquiposGrupoGUI(){
    system("cls");

    char sigla;
    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------LISTA DE EQUIPOS-----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL GRUPO: ";
        cin >> sigla;
        imprimirEquiposGrupo(sigla);
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    gruposGUI();
}


//----------------------------Metodos de Interfaz de Equipos------------------------------

//Muestra las opciones relacionadas a los equipos al usuario desde la Interfaz
void equiposGUI(){
    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU EQUIPO-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR EQUIPO";
    cout <<endl<<"2. AGREGAR JUGADOR AL UN EQUIPO";
    cout <<endl<<"3. MOSTRAR LISTA DE JUGADORES DE UN EQUIPO X";
    cout <<endl<<"4. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarEquipoGUI();
    }
    else if (x == '2'){
        insertarJugadorEquipoGUI();
    }
    else if (x == '3'){
        imprimirJugadoresEquipoGUI();
    }
    else if (x == '4'){
        menuPrincipal();
    }
    else{
        equiposGUI();
    }

}


//Inserta Equipos desde la Interfaz
void insertarEquipoGUI(){

    system("cls");

    string nombre;
    int mundialesParticipados;
    int finales;
    int mundialesGanados;
    int PG = 0;
    int PP = 0;
    int PE = 0;
    int GF = 0;
    int GC = 0;
    string confederacion;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------AGREGAR EQUIPO----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin >> nombre;
        cout <<endl<<"DIGITE LA CANTIDAD DE MUNDIALES QUE HA PARTICIPADO: ";
        cin >> mundialesParticipados;
        cout <<endl<<"DIGITE LA CANTIDAD DE FINALES QUE HA PARTICIPADO: ";
        cin >> finales;
        cout <<endl<<"DIGITE LA CANTIDAD DE MUNDIALES QUE HA GANADO: ";
        cin >> mundialesGanados;
        cout <<endl<<"DIGITE EL NOMBRE DEL LA CONFEDERACION: ";
        cin>>confederacion;


        if (insertarSeleccion_Ordenado(nombre, mundialesParticipados, finales, mundialesGanados,PG, PP, PE, GF, GC, confederacion) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL EQUIPO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    equiposGUI();
}

//Inserta un Jugador a un Equipo desde la Interfaz
void insertarJugadorEquipoGUI(){

    system("cls");

    string nombre;
    string nacion;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"---------------------------AGREGAR JUGADOR A EQUIPO---------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL JUGADOR: ";
        cin >> nombre;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin >> nacion;


        if (insertarJugadorEquipo(nacion, nombre) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL JUGADOR NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    equiposGUI();
}

//Imprime los Jugadores  de un Equipo por medio de la Interfaz
void imprimirJugadoresEquipoGUI(){
    system("cls");

    string nacion;
    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------LISTA DE JUGADORES-----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin >> nacion;
        imprimirJugadoresEquipo(nacion);
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    equiposGUI();
}


//---------------------------Metodos de Interfaz de Jugadores------------------------------

//Muestra las opciones relacionadas a los jugadores al usuario desde la Interfaz
void jugadoresGUI(){
    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU JUGADOR-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR JUGADOR";
    cout <<endl<<"2. IMPRIMIR JUGADORES";
    cout <<endl<<"3. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarJugadorGUI();
    }
    else if (x == '2'){
        imprimirJugadoresGUI();
    }
    else if (x == '3'){
        menuPrincipal();
    }
    else{
        jugadoresGUI();
    }

}


//Insertar un Jugador desde la Interfaz
void insertarJugadorGUI(){

    system("cls");

    string nombre;
    string nacion;
    string posicion;
    string fechaNacimiento;
    string club;
    int golesMundiales;
    int mundiales;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------AGREGAR JUGADOR-----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL JUGADOR: ";
        cin >> nombre;
        cout <<endl<<"DIGITE LA NACION DEL JUGADOR: ";
        cin >> nacion;
        cout <<endl<<"DIGITE LA POSICION DEL JUGADOR: ";
        cin >> posicion;
        cout <<endl<<"DIGITE EL AÑO DE NACIMIENTO: ";
        cin >> fechaNacimiento;
        cout <<endl<<"DIGITE EL CLUB ACTUAL DONDE JUEGA: ";
        cin>>club;
        cout <<endl<<"DIGITE LA CANTIDAD DE GOLES QUE HA REALIZADO DURANTE LOS MUNDIALES: ";
        cin>>golesMundiales;
        cout <<endl<<"DIGITE LA CANTIDAD DE MUNDIALES QUE HA PARTICIPADO: ";
        cin>>mundiales;


        if (insertarJugadores(nombre, nacion, posicion, fechaNacimiento, club, golesMundiales, mundiales) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL JUGADOR NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    jugadoresGUI();
}

//Imprime lista de Jugadores desde la Interfaz
void imprimirJugadoresGUI(){
    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------LISTA DE JUGADORES-----------------------------"<<endl;
        cout <<endl<<"PRESIONE UNA TECLA PARA IMPRIMIR JUGADORES: ";
        cin>>x;
        imprimirJugadores();
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    jugadoresGUI();
}



//-------------------------------Metodos Partidos de Interfaz-----------------------------------

//Muestra las opciones relacionadas con los partidos al Usuario
void partidosGUI(){

    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU PARTIDOS-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR PARTIDO";
    cout <<endl<<"2. INSERTAR TARJETAS A UN PARTIDO";
    cout <<endl<<"3. INSERTAR GOLES A UN PARTIDO";
    cout <<endl<<"4. IMPRIMIR UN PARTIDO X";
    cout <<endl<<"5. IMPRIMIR PARTIDOS";
    cout <<endl<<"6. FINALIZAR PARTIDO";
    cout <<endl<<"7. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarPartidoGUI();
    }
    else if (x == '2'){
        insertarTarjetasPartidoGUI();
    }
    else if (x == '3'){
        insertarGolesPartidoGUI();
    }
    else if (x == '4'){
        imprimirUnPartidoGUI();
    }
    else if (x == '5'){
        imprimirPartidosGUI();
    }
    else if (x == '6'){
        finalizarGUI();
    }
    else if (x == '7'){
        menuPrincipal();
    }
    else{
        partidosGUI();
    }

}

//Inserta un Partido desde la Interfaz
void insertarPartidoGUI(){

    system("cls");

    string id;
    string fecha;
    string hora;
    string equi1;
    string equi2;
    string estadio;
    string alb1;
    string alb2;
    string alb3;
    string alb4;
    int cantPersAsist;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"---------------------------AGREGAR PARTIDO--------------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin >> id;
        cout <<endl<<"DIGITE LA FECHA DEL PARTIDO, EJEMPLO (00/00/0000) : ";
        cin >> fecha;
        cout <<endl<<"DIGITE LA HORA DEL PARTIDO, EJEMPLO (00:00) : ";
        cin >> hora;

        cout <<endl<<endl<<"DIGITE LOS EQUIPOS: ";
        cout <<endl<<"DIGITE EL PRIMER EQUIPO: ";
        cin >> equi1;
        cout <<endl<<"DIGITE EL SEGUNDO EQUIPO: ";
        cin >> equi2;
        cout<<endl;

        cout <<endl<<"DIGITE EL ESTADIO: ";
        cin >> estadio;

        cout <<endl<<endl<<"DIGITE LOS ALBITROS: ";
        cout <<endl<<"DIGITE EL PRIMER ALBITRO: ";
        cin >> alb1;
        cout <<endl<<"DIGITE EL SEGUNDO ALBITRO: ";
        cin >> alb2;
        cout <<endl<<"DIGITE EL TERCER ALBITRO: ";
        cin >> alb3;
        cout <<endl<<"DIGITE EL CUATRO ALBITRO: ";
        cin >> alb4;

        cout<<endl;
        cout <<endl<<"DIGITE LA CANTIDAD DE PERSONAS QUE ASISTIRAN: ";
        cin >> cantPersAsist;



        if (insertarPartido(id, fecha, hora, equi1, equi2, estadio, alb1, alb2, alb3, alb4, cantPersAsist) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL PARTIDO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    partidosGUI();
}

//Inserta Tarjetas a un Partido desde la Interfaz
void insertarTarjetasPartidoGUI(){

    system("cls");

    string idPart;
    string nombreJu;
    string nacionJu;
    string color;
    int minuto;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------AGREGAR TARJETA A UN PARTIDO--------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin >> idPart;
        cout <<endl<<"DIGITE EL NOMBRE DEL JUGADOR : ";
        cin >> nombreJu;
        cout <<endl<<"DIGITE LA NACION DEL JUGADOR : ";
        cin >> nacionJu;
        cout <<endl<<"DIGITE EL TIPO DE TARJETA: ";
        cin >> color;
        cout <<endl<<"DIGITE EL MINUTO EN QUE SE MUESTRA LA TARJETA: ";
        cin >> minuto;

        if (insertarTarjetasPartidos(idPart, nombreJu, nacionJu, color, minuto) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADA LAS TARJETAS PORQUE NO CUMPLE CON LOS REQUISITOS!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    partidosGUI();
}


//Inserta Goles a un Partido desde la Interfaz
void insertarGolesPartidoGUI(){

    system("cls");

    string idPart;
    string nombreJu;
    string nacionJu;
    string forma;
    int minuto;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------AGREGAR TARJETA A UN PARTIDO--------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin >> idPart;
        cout <<endl<<"DIGITE EL NOMBRE DEL JUGADOR : ";
        cin >> nombreJu;
        cout <<endl<<"DIGITE LA NACION DEL JUGADOR : ";
        cin >> nacionJu;
        cout <<endl<<"DIGITE LA FORMA EN QUE HIZO EL GOL: ";
        cin >> forma;
        cout <<endl<<"DIGITE EL MINUTO EN QUE SE REALIZO EL GOL: ";
        cin >> minuto;

        if (insertarGolesPartidos(idPart, nombreJu, nacionJu, forma, minuto) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO EL GOL PORQUE NO CUMPLE CON LOS REQUISITOS!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    partidosGUI();
}

//Imprime la Informacion de un Partidos desde la Interfaz
void imprimirUnPartidoGUI(){

    system("cls");

    string idPart;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------LISTA DE PARTIDOS----------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin>>idPart;
        imprimirUnPartido(idPart);
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    partidosGUI();

}

//Imprime la lista de Partidos desde la Interfaz
void imprimirPartidosGUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------LISTA DE PARTIDOS----------------------"<<endl;
        cout <<endl<<"PRESIONE UNA TECLA PARA IMPRIMIR PARTIDOS: ";
        cin>>x;
        imprimirPartidos();
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    partidosGUI();

}

void finalizarGUI(){

    system("cls");

    string idPart;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------FINALIZAR UN PARTIDO X----------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin>>idPart;
        finalizar(idPart);
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    partidosGUI();

}


//-------------------------------Metodos Arbitro de Interfaz-----------------------------------


//Muestra las opciones relacionadas a Albitros al Usuario
void arbitrosGUI(){

    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU ARBITRO-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR ARBITRO";
    cout <<endl<<"2. IMPRIMIR ARBITROS";
    cout <<endl<<"3. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarArbitroGUI();
    }
    else if (x == '2'){
        imprimirArbitrosGUI();
    }
    else if (x == '3'){
        menuPrincipal();
    }
    else{
        arbitrosGUI();
    }

}


//Inserta un Arbitro desde la Interfaz
void insertarArbitroGUI(){

    system("cls");

    string nombre;
    string nacion;
    string tipo;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------AGREGAR ARBITRO-----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL ARBITRO: ";
        cin >> nombre;
        cout <<endl<<"DIGITE LA NACION DEL ARBITRO: ";
        cin >> nacion;
        cout <<endl<<"DIGITE LA POSICION DEL ARBITRO: ";
        cin >> tipo;


        if (insertarArbitro(nombre, nacion, tipo) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL ARBITRO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    arbitrosGUI();
}

//Imprime la lista de Arbitros desde la Interfaz
void imprimirArbitrosGUI(){
    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------LISTA DE JUGADORES-----------------------------"<<endl;
        cout <<endl<<"PRESIONE UNA TECLA PARA IMPRIMIR ARBITROS: ";
        cin>>x;
        imprimirArbitros();
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    arbitrosGUI();
}

//-------------------------------Metodos Estadio de Interfaz-----------------------------------

//Muestra la opciones relacionadas a Estadios al Usuario
void estadiosGUI(){

    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU ESTADIO-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. INSERTAR ESTADIO";
    cout <<endl<<"2. IMPRIMIR ESTADIOS";
    cout <<endl<<"3. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        insertarEstadioGUI();
    }
    else if (x == '2'){
        imprimirEstadiosGUI();
    }
    else if (x == '3'){
        menuPrincipal();
    }
    else{
        estadiosGUI();
    }

}

//Inserta un Estadio desde la Interfaz
void insertarEstadioGUI(){

    system("cls");

    string nombre;
    int canpacidad;
    string sede;
    int inauguracion;
    string ubicacion;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------AGREGAR ESTADIO-----------------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL ESTADIO: ";
        cin >> nombre;
        cout <<endl<<"DIGITE LA CAPACIDAD DE PERSONAS DEL ESTADIO: ";
        cin >> canpacidad;
        cout <<endl<<"DIGITE LA SEDE DEL ESTADIO: ";
        cin >> sede;
        cout <<endl<<"DIGITE LA FECHA DE INAUGURACION DEL ESTADIO: ";
        cin >> inauguracion;
        cout <<endl<<"DIGITE EL NOMBRE DE LA CIUDAD DONDE SE ENCUENTRA EL ESTADIO: ";
        cin >> ubicacion;


        if (insertarEstadio(nombre, canpacidad, sede, inauguracion, ubicacion) == true){
            cout <<endl<<"---> SE AGREGO CORRECTAMENTE!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }
        else{
            cout <<endl<<"---> LO SENTIMOS NO PUEDE SER AGREGADO PORQUE EL ESTADIO NO CUMPLE CON LOS REQUISITOS O YA ESTA REGISTRADO!!"<<endl;
            cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
            cin>>x;
        }

    }
    estadiosGUI();

}

//Imprime la lista de Estadios desde la Interfaz
void imprimirEstadiosGUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------------------------LISTA DE ESTADIOS-----------------------------"<<endl;
        cout <<endl<<"PRESIONE UNA TECLA PARA IMPRIMIR ESTADIOS: ";
        cin>>x;
        imprimirEstadios();
        cout <<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    estadiosGUI();

}


//-------------------------------Metodos Consulta de Interfaz-----------------------------------
void consultasGUI(){
    system("cls");

    string x;
    cout <<endl<<"-----------------------------MENU CONSULTA-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. RESULTADO DE UN PARTIDO X";
    cout <<endl<<"2. IMPRIMIR EL JUGADOR MAS JOVEN DE UN EQUIPO X";
    cout <<endl<<"3. IMPRIMIR EL JUGADOR MAS VIEJO DE UN EQUIPO X";
    cout <<endl<<"4. IMPRIME EL GOL MAS TEMPRANO DEL 2014";
    cout <<endl<<"5. IMPRIME LA MAYOR GOLEADA DE LOS PARTIDOS 2014";
    cout <<endl<<"6. IMPRIME EL JUGADOR QUE HA HECHO MAS GOLES DE CABEZA DEL MUNDIAL 2014";
    cout <<endl<<"7. IMPRIME EL EQUIPO QUE HA SUMADO MAS GOLES EN TODOS LOS MUNDIALES";
    cout <<endl<<"8. IMPRIME EL ARBITRO QUE HA SACADO MAS AMARILLAS EN EL 2014";
    cout <<endl<<"9. IMPRIME LOS EQUIPOS QUE AVANZARON A OCTAVOS DE FINAL EN EL 2014";
    cout <<endl<<"10. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == "1"){
        consulta_1GUI();
    }
    else if (x == "2"){
        consulta_2GUI();
    }
    else if (x == "3"){
        consulta_3GUI();
    }
    else if (x == "4"){
        consulta_4GUI();
    }
    else if (x == "5"){
        consulta_5GUI();
    }
    else if (x == "6"){
        consulta_6GUI();
    }
    else if (x == "7"){
        consulta_7GUI();
    }
    else if (x == "8"){
        consulta_8GUI();
    }
    else if (x == "9"){
        consulta_9GUI();
    }
    else if (x == "10"){
        menuPrincipal();
    }
    else{
        consultasGUI();
    }
}


//Imprime el resultado de un Partido X desde la Interfaz
void consulta_1GUI(){

    system("cls");

    string idPart;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------RESULTADO DE UN PARTIDO X----------------------"<<endl;
        cout <<endl<<"DIGITE EL ID DEL PARTIDO: ";
        cin>>idPart;
        consulta_1(idPart);
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el nombre del Jugador mas joven de un Equipo X desde la Interfaz.
void consulta_2GUI(){

    system("cls");

    string nombreEqui;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------JUGADOR MAS JOVEN----------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin>>nombreEqui;
        consulta_2(nombreEqui);
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el nombre del Jugador mas viejo de un Equipo X desde la Interfaz.
void consulta_3GUI(){

    system("cls");

    string nombreEqui;

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------JUGADOR MAS VIEJO----------------------"<<endl;
        cout <<endl<<"DIGITE EL NOMBRE DEL EQUIPO: ";
        cin>>nombreEqui;
        consulta_3(nombreEqui);
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el Gol mas temprano del 2014 desde la Interfaz.
void consulta_4GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------GOL MAS TEMPRANO----------------------"<<endl;
        consulta_4();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime la mayor goleada de los partidos 2014 desde la Interfaz.
void consulta_5GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------------MAYOR GOLEADA----------------------"<<endl;
        consulta_5();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el Jugador que ha hecho mas goles en el 2014 desde la Interfaz.
void consulta_6GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------JUGADOR QUE HA HECHO MAS GOLES DE CABEZA----------------"<<endl;
        consulta_6();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el equipo que suma más goles en todos los mundiales incluyendo 2014 desde la Interfaz.
void consulta_7GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------EQUIPO QUE HA HECHO MAS GOLES EN LOS MUNDIALES----------------"<<endl;
        consulta_7();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime el Arbitro que ha mostrado mas amarillas en el 2014 desde la Interfaz.
void consulta_8GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------------------ARBITRO QUE HA MOSTRADO MAS AMARILLAS EN EL 2014----------------"<<endl;
        consulta_8();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//Imprime los Equipos que avanzaron a octavos de final en el 2014 desde la Interfaz.
void consulta_9GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-------------EQUIPOS QUE AVANZARON A OCTAVOS DE FINAL 2014-----------"<<endl;
        ActualizarOctavos();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    consultasGUI();

}

//-------------------------------Metodos Reportes de Interfaz-----------------------------------

//Muestra las opciones de los reportes al usuario desde la Interfaz.
void reportesGUI(){
    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU REPORTES-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. IMPRIME LA INFORMACION DE LOS ESTADIOS UTILIZADOS EN EL 21014";
    cout <<endl<<"2. IMPRIME LOS EQUIPO CON SU INFORMACION Y LISTA DE JUGADORES 2014";
    cout <<endl<<"3. IMPRIME LOS GRUPOS CON SU INFORMACION Y LISTA DE EQUIPOS 2014";
    cout <<endl<<"4. MUESTRA LOS JUGADORES ORDENADOS POR GOLEO";
    cout <<endl<<"5. MUESTRA TABLA DE POSICIONES POR GRUPO 2014";
    cout <<endl<<"6. MUESTRA TABLA DE POSICIONES HISTORICA HASTA EL 2010";
    cout <<endl<<"7. IMPRIME EL EQUIPO QUE HA SUMADO MAS GOLES EN TODOS LOS MUNDIALES";
    cout <<endl<<"8. REGRESAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        reporte_1GUI();
    }
    else if (x == '2'){
        reporte_2GUI();
    }
    else if (x == '3'){
        reporte_3GUI();
    }
    else if (x == '4'){
        reporte_4GUI();
    }
    else if (x == '5'){
        reporte_5GUI();
    }
    else if (x == '6'){
        reporte_6GUI();
    }
    else if (x == '7'){
        reporte_7GUI();
    }
    else if (x == '8'){
        menuPrincipal();
    }
    else{
        reportesGUI();
    }
}

//Imprime la informacion de los Estadios que se han utlizados en el 2014 desde la Interfaz.
void reporte_1GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-------------ESTADIOS QUE SE UTILIZARON EN EL 2014-----------"<<endl;
        reporte_1();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}

//Imprime la informacion de los Equipos con sus lista de jugadores en el 2014 desde la Interfaz.
void reporte_2GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------INFORMACION DE EQUIPOS Y LISTA DE JUGADORES EL 2014--------"<<endl;
        reporte_2();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}

//Imprime la informacion de los Grupos con sus lista de Equipos en el 2014 desde la Interfaz.
void reporte_3GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------INFORMACION DE GRUPOS Y LISTA DE EQUIPOS EL 2014--------"<<endl;
        reporte_3();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}


//Muestra los jugadores ordenados por goleo desde la Interfaz.
void reporte_4GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------JUGADORES ORDENADOS POR GOLEO--------"<<endl;
        reporte_4();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}


//Muestra la tabla de posicion de los grupo 2014 desde la Interfaz.
void reporte_5GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------JUGADORES ORDENADOS POR GOLEO--------"<<endl;
        reporte_5();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}


//Muestra la tabla de posicion historica hasta el 2010 desde la Interfaz.
void reporte_6GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"-----------TABLA DE POSICIONES HISTORICA HASTA EL 2010-----------"<<endl;
        reporte_6();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}


//Muestra la tabla de posicion historica hasta el 2010 desde la Interfaz.
void reporte_7GUI(){

    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"------LISTA GOLEADORES ORDENADA POR GOLEO DE LOS MUNDIALES HASTA EL 2010------"<<endl;
        reporte_7();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    reportesGUI();

}


//-------------------------------Menu Principal Interfaz-----------------------------------

//Muestra todas las opciones que puede realizar el Usuario desde la Interfaz
void menuPrincipal(){
    system("cls");

    char x;
    cout <<endl<<"-----------------------------MENU PRINCIPAL-----------------------------"<<endl;
    cout <<endl<<"ELIJA UNA OPCION:";
    cout <<endl<<"1. TODO RELACIONADO A GRUPOS";
    cout <<endl<<"2. TODO RELACIONADO A EQUIPOS";
    cout <<endl<<"3. TODO RELACIONADO A JUGADORES";
    cout <<endl<<"4. TODO RELACIONADO A PARTIDOS";
    cout <<endl<<"5. TODO RELACIONADO A ESTADIO";
    cout <<endl<<"6. TODO RELACIONADO A ARBITRO";
    cout <<endl<<"7. CONSULTAS";
    cout <<endl<<"8. REPORTES";
    cout <<endl<<"9. ACTUALIZAR";
    cout <<endl<<"OPCION: ";
    cin >> x;

    if (x == '1'){
        gruposGUI();
    }
    else if (x == '2'){
        equiposGUI();
    }
    else if (x == '3'){
        jugadoresGUI();
    }
    else if (x == '4'){
        partidosGUI();
    }
    else if (x == '5'){
        estadiosGUI();
    }
    else if (x == '6'){
        arbitrosGUI();
    }
    else if (x == '7'){
        consultasGUI();
    }
    else if (x == '8'){
        reportesGUI();
    }
    else if (x == '9'){
        ActualizarGUI();
    }
    else{
        menuPrincipal();
    }
}


void ActualizarGUI(){
    system("cls");

    char x = '1';

    while(x=='1'){
        cout <<endl<<"--------------------------ACTUALIZADO----------------------------"<<endl;
        Actualizar();
        cout <<endl<<endl<<"---> PRESIONE UNA TECLA Y LUEGO ENTER PARA VOLVER <---"<<endl;
        cin>>x;
    }
    menuPrincipal();
}

int main()
{
    insertarGrupo_Ordenado('A');
    insertarGrupo_Ordenado('B');
    insertarGrupo_Ordenado('C');
    insertarGrupo_Ordenado('D');
    insertarGrupo_Ordenado('E');
    insertarGrupo_Ordenado('F');
    insertarGrupo_Ordenado('G');
    insertarGrupo_Ordenado('H');


    insertarJugadores("Brian","Espana","Volante","10/10/1990","Saprissa",25,1);
    insertarJugadores("Agro","Espana","Delantero","17/02/1995","Manchester United",0,0);
    insertarJugadores("Maikol","Espana","Delantero","02/05/1983","LDA",0,0);
    insertarJugadores("Frank","Espana","Arquero","10/09/1993","Carmelita",0,0);
    insertarJugadores("Lolo","Espana","Volante","11/10/1989","Saprissa",25,1);
    insertarJugadores("Enano","Espana","Delantero","25/07/1993","Manchester United",0,0);
    insertarJugadores("Keneth","Espana","Delantero","11/09/1993","LDA",0,0);
    insertarJugadores("Franco","Espana","Arquero","10/05/1995","Carmelita",0,0);
    insertarJugadores("Villa","Espana","Volante","31/02/1989","Saprissa",25,1);
    insertarJugadores("Klose","Espana","Delantero","01/06/1993","Bayer",0,0);
    insertarJugadores("Ronaldo","Espana","Delantero","04/12/1991","LDA",0,0);
    insertarJugadores("Balotteli","Espana","Arquero","19/06/1981","Carmelita",0,0);

    insertarJugadores("Isac","Espana","Volante","26/09/1997","Saprissa",25,1);
    insertarJugadores("Carlos","Espana","Delantero","02/03/2000","LDA",0,0);
    insertarJugadores("Pedro","Espana","Arquero","19/06/1988","Carmelita",0,0);
    insertarJugadores("Diego","Espana","Volante","31/02/2000","Saprissa",25,1);
    insertarJugadores("Heiner","Espana","Delantero","21/06/1993","Manchester United",0,0);
    insertarJugadores("Tylor","Espana","Delantero","28/04/1994","LDA",0,0);
    insertarJugadores("Juan","Espana","Arquero","19/06/1992","Cartago",25,1);
    insertarJugadores("Santiago","Espana","Delantero","12/06/1990","BayeCarmelita",0,0);
    insertarJugadores("Olman","Espana","Volante","11/08/1993","Saprissa",0,0);
    insertarJugadores("Gabriel","Espana","Volante","19/03/1997","Saprissa",25,1);
    insertarJugadores("Yonathan","Espana","Delantero","10/04/1995","Bayer",0,0);

    insertarJugadores("Saul","Alemania","Delantero","19/07/1999","Bayer",0,0);
    insertarJugadores("Aron","Alemania","Delantero","19/07/1998","Bayer",0,0);
    insertarJugadores("Keylor","Alemania","Delantero","19/07/2000","Bayer",0,0);

    insertarJugadores("Abuelo","Argentina","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Juanito","Brazil","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Guardado","Mexico","Delantero","19/07/2000","Bayer",0,0);

    insertarJugadores("Honda","Japon","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Meireles","Portugal","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Palacios","Honduras","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Jhonson","USA","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Minor","Ghana","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Phil","Suiza","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Allan","Nigeria","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Sad","Rusia","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Ted","Camerun","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Forlan","Uruguay","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Drogba","CostaDeMarfil","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Cavanie","Italia","Delantero","19/07/2000","Bayer",0,0);
    insertarJugadores("Hank","Chile","Delantero","19/07/2000","Bayer",0,0);


    insertarSeleccion_Ordenado("Francia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("CostaRica",9,6,5,56,5,4,5,6,"CONCACAF");
    insertarSeleccion_Ordenado("Alemania",9,6,5,0,0,0,0,0,"UEFA");
    insertarSeleccion_Ordenado("Espana",9,6,5,0,0,0,0,0,"UEFA");
    insertarSeleccion_Ordenado("Brazil",9,6,5,56,5,4,7,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Italia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Holanda",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Ghana",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Mexico",9,6,5,56,5,4,5,6,"CONCACAF");
    insertarSeleccion_Ordenado("Argentina",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Uruguay",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Honduras",9,6,5,56,5,4,5,6,"CONCACAF");
    insertarSeleccion_Ordenado("Colombia",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Ecuador",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Grecia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Australia",9,6,5,56,5,4,5,6,"AFC");
    insertarSeleccion_Ordenado("Japon",9,6,5,56,5,4,5,6,"AFC");
    insertarSeleccion_Ordenado("Portugal",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("USA",9,6,5,56,5,4,5,6,"CONCACAF");
    insertarSeleccion_Ordenado("Korea",9,6,5,56,5,4,5,6,"AFC");
    insertarSeleccion_Ordenado("CostaDeMarfil",9,6,5,56,5,4,5,6,"África");
    insertarSeleccion_Ordenado("Chile",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Iran",9,6,5,56,5,4,5,6,"AFC");
    insertarSeleccion_Ordenado("Suiza",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Rusia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Bosnia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Inglaterra",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Camerun",9,6,5,56,5,4,5,6,"África");
    insertarSeleccion_Ordenado("Nigeria",9,6,5,56,5,4,5,6,"África");
    insertarSeleccion_Ordenado("Argelia",9,6,5,56,5,4,5,6,"África");
    insertarSeleccion_Ordenado("Croacia",9,6,5,56,5,4,5,6,"UEFA");
    insertarSeleccion_Ordenado("Belgica",9,6,5,56,5,4,5,6,"CONMEBOL");
    insertarSeleccion_Ordenado("Suecia",9,6,5,56,5,4,5,6,"CONMEBOL");


    insertarArbitro("Brian","CostaRica","Central");
    insertarArbitro("Jonathan","Alemania","Linea1");
    insertarArbitro("Enano","Espana","Cuarto");
    insertarArbitro("Agro","Brazil","Linea2");
    insertarArbitro("Santiago","Alemania","Central");

    insertarJugadorEquipo("Alemania","Saul");
    insertarJugadorEquipo("Alemania","Keylor");
    insertarJugadorEquipo("Alemania","Aron");

    insertarJugadorEquipo("Espana","Diego");
    insertarJugadorEquipo("Espana","Lolo");
    insertarJugadorEquipo("Espana","Maikol");
    insertarJugadorEquipo("Espana","Enano");
    insertarJugadorEquipo("Espana","Heiner");

    insertarJugadorEquipo("Espana","Tylor");
    insertarJugadorEquipo("Espana","Santiago");
    insertarJugadorEquipo("Espana","Olman");
    insertarJugadorEquipo("Espana","Juan");
    insertarJugadorEquipo("Espana","Gabriel");

    insertarJugadorEquipo("Espana","Yonathan");
    insertarJugadorEquipo("Espana","Ronaldo");
    insertarJugadorEquipo("Espana","Keneth");
    insertarJugadorEquipo("Espana","Klose");
    insertarJugadorEquipo("Espana","Pedro");

    insertarJugadorEquipo("Espana","Isac");
    insertarJugadorEquipo("Espana","Balotteli");
    insertarJugadorEquipo("Espana","Frank");
    insertarJugadorEquipo("Espana","Carlos");
    insertarJugadorEquipo("Espana","Franco");

    insertarJugadorEquipo("Espana","Villa");
    insertarJugadorEquipo("Argentina","Abuelo");
    insertarJugadorEquipo("Brazil","Juanito");
    insertarJugadorEquipo("Mexico","Guardado");
    insertarJugadorEquipo("Honduras","Palacios");
    insertarJugadorEquipo("Portugal","Ronaldo");
    insertarJugadorEquipo("Japon","Honda");

    insertarJugadorEquipo("Nigeria","Allan");
    insertarJugadorEquipo("USA","Jhonson");
    insertarJugadorEquipo("Rusia","Sad");
    insertarJugadorEquipo("Suiza","Phil");
    insertarJugadorEquipo("Camerun","Ted");
    insertarJugadorEquipo("Ghana","Minor");
    insertarJugadorEquipo("Uruguay","Forlan");
    insertarJugadorEquipo("CostaDeMarfil","Drogba");
    insertarJugadorEquipo("Italia","Cavanie");
    insertarJugadorEquipo("Chile","Hank");

    insertarEquipoGrupo("Mexico",'A');
    insertarEquipoGrupo("Argentina",'A');
    insertarEquipoGrupo("Uruguay",'A');
    insertarEquipoGrupo("Holanda",'A');

    insertarEquipoGrupo("Espana",'B');
    insertarEquipoGrupo("Alemania",'B');
    insertarEquipoGrupo("Brazil",'B');
    insertarEquipoGrupo("Francia",'B');

    insertarEquipoGrupo("Belgica",'C');
    insertarEquipoGrupo("Grecia",'C');
    insertarEquipoGrupo("Portugal",'C');
    insertarEquipoGrupo("Japon",'C');

    insertarEquipoGrupo("Korea",'D');
    insertarEquipoGrupo("USA",'D');
    insertarEquipoGrupo("Honduras",'D');
    insertarEquipoGrupo("Colombia",'D');

    insertarEquipoGrupo("Ghana",'E');
    insertarEquipoGrupo("Suecia",'E');
    insertarEquipoGrupo("CostaDeMarfil",'E');
    insertarEquipoGrupo("Ecuador",'E');

    insertarEquipoGrupo("Australia",'F');
    insertarEquipoGrupo("Italia",'F');
    insertarEquipoGrupo("Chile",'F');
    insertarEquipoGrupo("Iran",'F');

    insertarEquipoGrupo("Suiza",'G');
    insertarEquipoGrupo("Rusia",'G');
    insertarEquipoGrupo("Bosnia",'G');
    insertarEquipoGrupo("Inglaterra",'G');

    insertarEquipoGrupo("Camerun",'H');
    insertarEquipoGrupo("Nigeria",'H');
    insertarEquipoGrupo("Argelia",'H');
    insertarEquipoGrupo("Croacia",'H');


    insertarEstadio("RicardoSaprissa", 50000, "CostaRica",1961, "San Jose");
    insertarEstadio("FelloMeza", 50000, "CostaRica",1961, "Cartago");

    insertarPartido("1","16/04/2014","20:00", "Espana", "Alemania", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("2","16/04/2013","20:00", "Alemania", "Brazil", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("3","16/04/2013","20:00", "Brazil", "Espana", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("4","16/04/2013","20:00", "Alemania", "Francia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("5","16/04/2013","20:00", "Francia", "Brazil", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("6","16/04/2013","20:00", "Espana", "Francia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("7","16/04/2014","20:00", "Mexico", "Argentina", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("8","16/04/2014","20:00", "Argentina", "Uruguay", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("9","16/04/2014","20:00", "Holanda", "Mexico", "RicardoSaprissa", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("10","16/04/2014","20:00", "Uruguay", "Holanda", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("11","16/04/2014","20:00", "Mexico", "Uruguay", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("12","16/04/2014","20:00", "Argentina", "Holanda", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("13","16/04/2014","20:00", "Belgica", "Grecia", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("14","16/04/2013","20:00", "Grecia", "Portugal", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("15","16/04/2013","20:00", "Portugal", "Belgica", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("16","16/04/2013","20:00", "Japon", "Belgica", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("17","16/04/2013","20:00", "Grecia", "Japon", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("18","16/04/2013","20:00", "Japon", "Portugal", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("19","16/04/2014","20:00", "Korea", "USA", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("20","16/04/2014","20:00", "Honduras", "Colombia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("21","16/04/2014","20:00", "USA", "Colombia", "RicardoSaprissa", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("22","16/04/2014","20:00", "Honduras", "Korea", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("23","16/04/2014","20:00", "USA", "Honduras", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("24","16/04/2014","20:00", "Korea", "Colombia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("25","16/04/2014","20:00", "Ghana", "Suecia", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("26","16/04/2013","20:00", "CostaDeMarfil", "Ecuador", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("27","16/04/2013","20:00", "Ecuador", "Ghana", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("28","16/04/2013","20:00", "Ghana", "CostaDeMarfil", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("29","16/04/2013","20:00", "Suecia", "CostaDeMarfil", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("30","16/04/2013","20:00", "Ecuador", "Suecia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("31","16/04/2014","20:00", "Australia", "Italia", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("32","16/04/2014","20:00", "Australia", "Iran", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("33","16/04/2014","20:00", "Italia", "Iran", "RicardoSaprissa", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("34","16/04/2014","20:00", "Iran", "Chile", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("35","16/04/2014","20:00", "Australia", "Chile", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("36","16/04/2014","20:00", "Italia", "Chile", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("37","16/04/2014","20:00", "Suiza", "Rusia", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("38","16/04/2014","20:00", "Bosnia", "Inglaterra", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("39","16/04/2014","20:00", "Rusia", "Bosnia", "RicardoSaprissa", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("40","16/04/2014","20:00", "Inglaterra", "Suiza", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("41","16/04/2014","20:00", "Rusia", "Inglaterra", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("42","16/04/2014","20:00", "Bosnia", "Suiza", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);

    insertarPartido("43","16/04/2014","20:00", "Camerun", "Nigeria", "FelloMeza", "Jonathan", "Enano", "Agro", "Brian", 100000);
    insertarPartido("44","16/04/2014","20:00", "Argelia", "Croacia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("45","16/04/2014","20:00", "Croacia", "Camerun", "RicardoSaprissa", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("46","16/04/2014","20:00", "Nigeria", "Argelia", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("47","16/04/2014","20:00", "Argelia", "Camerun", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);
    insertarPartido("48","16/04/2014","20:00", "Croacia", "Nigeria", "FelloMeza", "Jonathan", "Enano", "Agro", "Santiago", 100000);


    insertarGolesPartidos("1", "Juan", "Espana", "Cabeza", 23);
    insertarGolesPartidos("2", "Saul", "Alemania", "TiroDirecto", 42);

    insertarGolesPartidos("8", "Abuelo", "Argentina", "TiroDirecto", 3);
    insertarGolesPartidos("10", "Forlan", "Uruguay", "TiroDirecto", 42);

    insertarGolesPartidos("14", "Ronaldo", "Portugal", "TiroDirecto", 2);
    insertarGolesPartidos("15", "Ronaldo", "Portugal", "TiroDirecto", 2);
    insertarGolesPartidos("17", "Honda", "Japon", "TiroDirecto", 3);

    insertarGolesPartidos("20", "Palacios", "Honduras", "TiroDirecto", 2);
    insertarGolesPartidos("21", "Jhonson", "USA", "TiroDirecto", 3);

    insertarGolesPartidos("25", "Minor", "Ghana", "TiroDirecto", 2);
    insertarGolesPartidos("26", "Drogba", "CostaDeMarfil", "TiroDirecto", 3);

    insertarGolesPartidos("33", "Cavanie", "Italia", "TiroDirecto", 2);
    insertarGolesPartidos("34", "Hank", "Chile", "TiroDirecto", 3);

    insertarGolesPartidos("40", "Phil", "Suiza", "TiroDirecto", 2);
    insertarGolesPartidos("41", "Sad", "Rusia", "TiroDirecto", 3);

    insertarGolesPartidos("45", "Ted", "Camerun", "TiroDirecto", 2);
    insertarGolesPartidos("46", "Allan", "Nigeria", "TiroDirecto", 3);
    insertarGolesPartidos("46", "Allan", "Nigeria", "TiroDirecto", 3);

    menuPrincipal();

    return 0;
}
