#include "GestorServidores.h"
#include "Servidor.h"

GestorServidores::GestorServidores()
{

    primerServidor=NULL; //inicializo al primer puntero ¿?

    numServidores=0; //al inicio 0 elementos efectivos

}

GestorServidores::~GestorServidores()
{

    Servidor* servidorActual= primerServidor;

    while(servidorActual!=NULL)
    {
        Servidor* siguiente=servidorActual->getSiguienteServidor();
        delete servidorActual;
        servidorActual=siguiente;
    }
    primerServidor=NULL;
    numServidores=0;

}


int GestorServidores::getNumServidores()
{

    return numServidores;

}


bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG)
{

//creamos objeto y variable booleana
    bool exito=true;

    Servidor* ServidorActual=new Servidor(dS,nJ,i,mxL,mxC,p,lG); //Servidor a desplegar

    if(ServidorActual==NULL)
    {
        exito=false; //no hay memoria para añadir el servidor
    }

    else
    {
        //comprobaciones
        Servidor* Actual=primerServidor; //Servidor auxiliar para movernos entre nodos
        cadena nomJ;
        while(Actual!=NULL)
        {
            Actual->getNombreJuego(nomJ);
            if(Actual->getId()==i)
            {
                exito=false; //mismo id
            }
            else if(strcmp(nomJ,nJ)==0)
            {
                exito=false; //mismo nombre de juego
            }

            Actual=Actual->getSiguienteServidor();
        }
        if(exito)
        {
            //quiere decir que podemos desplegar

            //caso 1, al inicio de la lista
            if(primerServidor==NULL)
            {
                ServidorActual->setSiguienteServidor(primerServidor);
                primerServidor=ServidorActual;

            }
            else
            {
                cadena p;
                primerServidor->getLocalizacionGeografica(p);
                if(strcmp(p,lG)<0)
                {
                    ServidorActual->setSiguienteServidor(primerServidor);
                    primerServidor=ServidorActual;
                }
                else
                {
                    Servidor* anterior=primerServidor;
                    Servidor* actual=primerServidor->getSiguienteServidor();
                    bool SvInsertado=false;
                    while(actual!=NULL && !SvInsertado)
                    {
                        cadena localA;
                        actual->getLocalizacionGeografica(localA);
                        if(strcmp(localA,lG)<0)
                        {
                            ServidorActual->setSiguienteServidor(actual);
                            anterior->setSiguienteServidor(ServidorActual);
                            actual=NULL;
                            SvInsertado=true;
                        }
                        else
                        {
                            anterior=actual;
                            actual=actual->getSiguienteServidor();
                        }
                    }
                    if(!SvInsertado)
                    {
                        anterior->setSiguienteServidor(ServidorActual);
                        ServidorActual->setSiguienteServidor(NULL);
                    }
                }
            }
        numServidores++;
        }

    }

    return exito;
}

//DESCONECTAR SERVIDOR AQUI


bool GestorServidores::conectarServidor(cadena dS)
{

    bool exito;
    if(primerServidor==NULL)
    {
        exito=false; //error, no hay servidores
    }

    else
    {
        //buscar servidor coincidente para activarlo
        Servidor* ServerAux=primerServidor; //Servidor auxiliar para recorrer y encontrar posicion en donde activar
        while(ServerAux!=NULL)
        {
            cadena dir;
            ServerAux->getDireccionServidor(dir);
            if(strcmp(dir,dS)==0)
            {
                //Posicion encontrada, activamos server
                exito=ServerAux->activar();
            }
            ServerAux=ServerAux->getSiguienteServidor();
        }
    }

    return exito;
}


bool GestorServidores::realizarMantenimiento(cadena dS)
{

    bool exito;
    if(primerServidor==NULL)
    {
        exito=false; //error, no hay servidores
    }

    else
    {
        //buscar servidor coincidente para activarlo
        Servidor* ServerAux=primerServidor; //Servidor auxiliar para recorrer y encontrar posicion en donde realizar mantenimiento
        while(ServerAux!=NULL)
        {
            cadena dir;
            ServerAux->getDireccionServidor(dir);
            if(strcmp(dir,dS)==0)
            {
                //Posicion encontrada, activamos server
                exito=ServerAux->ponerEnMantenimiento();
            }
            ServerAux=ServerAux->getSiguienteServidor();
        }
    }

    return exito;
}


bool GestorServidores::eliminarServidor(cadena dS)
{

    bool exito=true;
    Servidor* ServerAux=primerServidor; //Servidor auxiliar para recorrer y encontrar posicion
    if(primerServidor==NULL)
    {

        exito=false; //no hay servidores
    }
    else
    {
        //buscar servidor coincidente para eliminarlo
        while(ServerAux->getSiguienteServidor()!=NULL)
        {
            cadena dir;
            ServerAux->getDireccionServidor(dir);
            if(strcmp(dir,dS)==0)
            {
                //Posicion encontrada, "eliminamos" server (mover posiciones)
                Servidor* anterior=ServerAux->getSiguienteServidor();
                ServerAux->setSiguienteServidor(anterior->getSiguienteServidor());
                delete anterior;
                numServidores--;
            }
            ServerAux=ServerAux->getSiguienteServidor();
        }


    }


    return exito;
}

//ALOJAR Y DESCONECTAR JUGADOR AQUI

bool GestorServidores::alojarJugador(Jugador j, cadena nomJuego, cadena host, bool &enEspera)
{
    bool Alojado=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL)
    {
        cadena nomJ;
        Aux->getNombreJuego(nomJ);
        if(strcmp(nomJ,nomJuego)==0)
        {
            if(Aux->estaActivo() && Aux->getMaxJugadoresConectados() > Aux->getNumJugadoresConectados())
            {
                Aux->conectarJugador(j);
                Aux->getDireccionServidor(host);
                Alojado=true;
                enEspera=false;
            }
            else if (Aux->getMaxJugadoresEnEspera() > Aux->getNumJugadoresEnEspera())
            {
                Aux->ponerJugadorEnEspera(j);
                Aux->getDireccionServidor(host);
                Alojado=false;
                enEspera=true;
            }
        }
        else
        {
            Alojado=false;
            enEspera=false;
        }
        Aux=Aux->getSiguienteServidor();
    }
    return Alojado;
}


int GestorServidores::getPosicionServidor(cadena dS)
{

    int p=1;
    bool encontrado=false;
    Servidor* Aux=primerServidor;
    while(p<=numServidores && !encontrado)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            encontrado=true;
        }
        else
            Aux=Aux->getSiguienteServidor();
        p++;
    }
    return p;
}

//MOSTRAR INFORMACION SERVIDORES AQUI

bool GestorServidores::jugadorConectado(cadena nJ,cadena dS)
{

    bool exito=false;
    bool PerteneceJ=false;
//primero, encontrar el servidor con dicha cadena ¿?
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            if(Aux->PerteneceLista(nJ))
                PerteneceJ=true;
        }
        Aux=Aux->getSiguienteServidor();
    }

    if(PerteneceJ)
    {
        exito=true;
    }
    return exito;
}

bool GestorServidores::jugadorEnEspera(cadena nJ, cadena dS)
{

    bool exito=false;
    bool PerteneceJ=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena aux;
        Aux->getDireccionServidor(aux);
        if(strcmp(aux,dS)==0)
        {
            if(Aux->PerteneceCola(nJ))
                PerteneceJ=true;
        }
        Aux=Aux->getSiguienteServidor();
    }
    if(PerteneceJ)
    {
        exito=true;
    }
    return exito;

}

bool GestorServidores::jugadorConectado(cadena nJ)
{

    bool exito=false;
    bool PerteneceJ=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena direcc;
        Aux->getDireccionServidor(direcc);
        if(Aux->PerteneceLista(nJ))
        {
            PerteneceJ=true;
        }
            Aux=Aux->getSiguienteServidor();
    }
    if(PerteneceJ)
    {
        exito=true;
    }

    return exito;
}


bool GestorServidores::jugadorEnEspera(cadena nJ)
{

    bool exito=false;
    Servidor* Aux=primerServidor;
    while(Aux!=NULL && !exito)
    {
        cadena direcc;
        Aux->getDireccionServidor(direcc);
        if(jugadorEnEspera(nJ,direcc))
        {
            exito=true;
        }
        else
            Aux=Aux->getSiguienteServidor();
    }

    return exito;


}


Servidor* GestorServidores::getPrimerServidor()
{

    return primerServidor;

}

Servidor* GestorServidores::getServidorP(int pos)
{

//¿? posible insertarlo ¿?


}

