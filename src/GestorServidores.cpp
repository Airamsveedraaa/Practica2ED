#include "GestorServidores.h"

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

    numServidores=0;

}


int GestorServidores::getNumServidores()
{

    return numServidores;

}


bool GestorServidores::desplegarServidor(cadena dS, cadena nJ, int i, int mxL, int mxC, int p, cadena lG)
{

    bool exito=true; //condicion de parada y salida

    Servidor servidorActual(dS, nJ, i, mxL, mxC, p, lG); //Objeto inicializado

//Comprobaciones

    if(servidorActual.getSiguienteServidor()==NULL)
    {
        exito=false; //no hay memoria para alojar mas servidores
    }



return exito;
}
