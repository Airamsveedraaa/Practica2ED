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

Servidor::~Servidor(){



}

int Servidor::getId(){

return id;

}

void Servidor::getDireccionServidor(cadena dS){

strcpy(dS,direccionServidor);

}


void Servidor::setSiguienteServidor(Servidor *pS){

siguienteServidor=pS;

}

Servidor* Servidor::getSiguienteServidor(){

return siguienteServidor;

}

