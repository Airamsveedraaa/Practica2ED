#include "Servidor.h"

Servidor::Servidor(cadena dS, cadena nJ,int i, int mxL, int mxC, int p, cadena lG)
{

    strcpy(direccionServidor,dS);
    strcpy(nombreJuego,nJ);
    id=i;
    maxJugadoresConectados=mxL;
    maxJugadoresEnEspera=mxC;
    puerto=p;
    strcpy(localizacionGeografica,lG);
    strcpy(estado,"INACTIVO");
    siguienteServidor=NULL;

}

Servidor::~Servidor()
{



}

int Servidor::getId()
{

    return id;

}

void Servidor::getDireccionServidor(cadena dS)
{

    strcpy(dS,direccionServidor);

}


void Servidor::setSiguienteServidor(Servidor *pS)
{

    siguienteServidor=pS;

}

Servidor* Servidor::getSiguienteServidor()
{

    return siguienteServidor;

}

bool Servidor::conectarJugador(Jugador j)
{

    bool exito=true; //valor a devolver en la funcion

    int longi=jugadoresConectados.longitud();
    int i=1;

    if(longi==maxJugadoresConectados)
    {
        exito=false;
    }
    else
    {
        while(jugadoresConectados.observar(i).puntuacion < j.puntuacion && i<longi)
        {
            i++;
        }

        jugadoresConectados.insertar(i,j);

    }

    return exito; //pendiente

}

bool Servidor::ponerJugadorEnEspera(Jugador j)
{

    bool exito=true;
    int longi=jugadoresEnEspera.longitud();

    if(longi!=maxJugadoresConectados || longi==maxJugadoresEnEspera)
    {
        exito=false;
    }
    else
    {
        jugadoresEnEspera.encolar(j);
    }

    return exito;

}

void Servidor::mostrarJugadoresConectados()
{

    int i=1;
    int longi=jugadoresConectados.longitud();

    cout << "Datos de los jugadores conectados: ";
    while(i<=longi)
    {
        cout << jugadoresConectados.observar(i).nombreJugador
             << "\n" << jugadoresConectados.observar(i).ID
             << "\n" << jugadoresConectados.observar(i).latencia
             << "\n" << jugadoresConectados.observar(i).puntuacion
             << "\n" << jugadoresConectados.observar(i).pais << endl;
    }

}

void Servidor::mostrarJugadoresEnEspera()
{

    cola Caux;

    if(jugadoresEnEspera.esvacia())
    {
        cout << "No hay jugadores en espera actualmente" << endl;
    }
    else
    {
        cout << "Datos de los jugadores en cola : ";
        while(!jugadoresEnEspera.esvacia())
        {
            cout << jugadoresEnEspera.primero().nombreJugador
                 << "\n" << jugadoresEnEspera.primero().ID
                 << "\n" << jugadoresEnEspera.primero().latencia
                 << "\n" << jugadoresEnEspera.primero().puntuacion
                 << "\n" << jugadoresEnEspera.primero().pais << endl;
            Caux.encolar(jugadoresEnEspera.primero());
            jugadoresEnEspera.desencolar();
        }
        while(!Caux.esvacia())  //restablezco orden original de la cola
        {
            jugadoresEnEspera.encolar(Caux.primero());
            Caux.desencolar();
        }
    }

}

bool Servidor::estaActivo(){

return (strcmp(estado,"ACTIVO")==0);

}

