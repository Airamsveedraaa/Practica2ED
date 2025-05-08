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

    Servidor* servidorActual=new Servidor(dS,nJ,i,mxL,mxC,p,lG); //Objeto inicializado

//Comprobaciones

    if(servidorActual==NULL)
    {
        exito=false; //no hay memoria para alojar mas servidores
    }

    else
    {
        Servidor* serverAux=primerServidor;
        cadena s;
        while(serverAux!=NULL && exito)
        {
            if(serverAux->getId()==i)
            {
                exito=false; //mismo ID
            }
            else
            {
                serverAux->getNombreJuego(s);
                if(strcmp(s,nJ)==0)
                {
                    exito=false;  //mismo Juego
                }
            }
            serverAux=serverAux->getSiguienteServidor();
        }
    }

    if(exito)
    {

        if(primerServidor==NULL)
        {
            primerServidor=servidorActual;
            servidorActual->setSiguienteServidor(NULL);
            //se inserta en la primera posicion
        }
        else
        {
            cadena p;
            primerServidor->getLocalizacionGeografica(p);
            if(strcmp(lG,p)<0)
            {
                servidorActual->setSiguienteServidor(primerServidor);
                primerServidor=servidorActual;
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
                    if(strcmp(lG,localA)<0)
                    {
                        servidorActual->setSiguienteServidor(actual);
                        anterior->setSiguienteServidor(servidorActual);
                        actual=NULL;
                        SvInsertado=true; //servidor insertado en posicion intermedia
                    }
                    else
                    {
                        anterior=actual;
                        actual=actual->getSiguienteServidor();
                    }
                }
                if(!SvInsertado)
                {
                    anterior->setSiguienteServidor(servidorActual);
                    servidorActual->setSiguienteServidor(NULL);
                    //servidor insertado al final si no se ha insertado antes
                }

            }
        }

        numServidores++;

    }
    return exito;
}


Servidor* GestorServidores::getPrimerServidor()
{

    return primerServidor;

}

