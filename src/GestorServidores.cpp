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
        }
        numServidores++;

    }

    return exito;
}


Servidor* GestorServidores::getPrimerServidor()
{

    return primerServidor;

}

