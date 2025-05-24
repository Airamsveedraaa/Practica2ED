#include "GestorServidores.h"

Jugador crearJugador(cadena nombre, int id, bool activo, int latencia, long puntuacion, cadena pais)
{
    Jugador j;
    strcpy(j.nombreJugador, nombre);
    j.ID = id;
    j.activo = activo;
    j.latencia = latencia;
    j.puntuacion = puntuacion;
    strcpy(j.pais, pais);
    return j;
}

int menu()
{
    int opcion;
    do
    {
        CLS;
        cout<<"GESTOR DE SERVIDORES   v1.0"<<endl;
        cout<<"================================"<<endl;
        cout<<"1. Mostrar Servidor\n2. Crear Servidor\n3. Eliminar servidor\n4. ActivarServidor"<<endl;
        cout<<"5. Desactivar Servidor\n6. Programar mantenimiento de servidor\n7. Conectar jugador"<<endl;
        cout<<"8. Expulsar jugador\n9. Salir\n"<<endl;
        cout<<"Indique la opcion deseada: ";
        cin>>opcion;
        if(opcion<1 || opcion>9)
        {
            cout<<"Opcion no valida, intentelo de nuevo\n\n";
            PAUSE;
        }
    }
    while(opcion<1 || opcion>9);

    return opcion;
}

int main()
{
    srand(time(0));
    int opc;
    GestorServidores Gestor;
    do
    {
        opc = menu();

        switch(opc)
        {

        case 1:
        {
            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a mostrar (ALL para mostrar todos): " << endl;
            cin >> direccion;

            if(strcmp(direccion, "ALL") == 0)
            {
                if(Gestor.getNumServidores() > 0)
                {
                    Gestor.mostrarInformacionServidores(-1);
                }
                else
                {
                    cout << "No hay servidores para mostrar" << endl;
                }
            }
            else
            {
                int pos = Gestor.getPosicionServidor(direccion);

                if(pos == -1)
                {
                    cout << "No existe ningun servidor con esa direccion/hostname " << endl;
                }
                else
                {
                    Gestor.mostrarInformacionServidores(pos);
                }
            }
        }
        break;

        case 2:
        {
            cadena direccion;
            cadena nombreJuego;
            cadena Pais;
            int ID,MaxConectados,MaxEnEspera,Puerto;

            cout << "Introduzca los datos del servidor a desplegar: " << endl;
            cout << "Direccion/hostname: ";
            cin >> direccion;
            cout << "Nombre del juego que aloja el servidor: ";
            cin >> nombreJuego;
            cout << "ID: ";
            cin >> ID;
            cout << "Maximo de jugadores que podran conectarse: ";
            cin >> MaxConectados;
            cout << "Maximo de jugadores que podran estar en espera de conectarse: ";
            cin >> MaxEnEspera;
            cout << "Puerto de escucha: ";
            cin >> Puerto;
            cout << "Pais donde estara alojado el servidor: ";
            cin >> Pais;

            Gestor.desplegarServidor(direccion,nombreJuego,ID,MaxConectados,MaxEnEspera,Puerto,Pais);

        }
        break;

        case 3:
        {
            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a eliminar: " << endl;
            cin >> direccion;

            bool eliminado=Gestor.eliminarServidor(direccion);
            if(eliminado==false)
            {
                cout << "Servidor a eliminar no existente" << endl;
            }
            else
            {
                cout << "Servidor eliminado con exito" << endl;
            }

        }
        break;

        case 4:
        {

            cadena direccion;
            cout << "Introduzca la direccion/hostname del servidor a activar: " << endl;
            cin >> direccion;
            bool activado=Gestor.conectarServidor(direccion);
            if(activado==false)
            {
                cout << "Servidor ya activo" << endl;
            }
            else
                cout << "Servidor activado con exito" << endl;

        }
        break;

        case 5:
        {
            cadena direccion;
            cout << "Introduzca la direcciion/hostname del servidor a desactivar: " << endl;
            cin >> direccion;

            bool desactivado=Gestor.desconetarServidor(direccion);

            if(!desactivado)
            {
                cout << "Servidor a desactivar no existente" << endl;
            }
            else
                cout << "Servidor desactivado con exito" << endl;

        }
        break;

        case 6:
        {

            cadena direccion;
            cout << "Introduzca la direccion hostname del servidor a poner en mantenimiento: " << endl;
            cin >> direccion;

            bool mantenimiento=Gestor.realizarMantenimiento(direccion);

            if(mantenimiento)
            {
                cout << "Mantenimiento programado con exito" << endl;
            }
            else
            {
                cout << "El servidor a poner en mantenimiento esta activo o ya en mantenimiento, desactivelo primero" << endl;

            }

        }
        break;

        case 7:
        {
            cadena nombreJugador;
            cout << "Introduzca el nick del jugador a conectar: " << endl;
            cin >> nombreJugador;

            if(Gestor.jugadorConectado(nombreJugador))
            {
                cout << "Error, el jugador con nick " << nombreJugador << " ya se encuentra conectado al sistema" << endl;
            }

            else
            {
                int ID,latencia,puntuacion;
                cadena Pais;
                cadena nombreJuego;
                bool activo=true;
                cout << "El jugador no se encuentra conectado al sistema actualmente, introduzca los datos del jugador a conectar: ";
                cout << "ID: " << endl;
                cin >> ID;
                cout << "Pais desde el que se conecta al sistema: " << endl;
                cin >> Pais;
                cout << "Nombre del juego que va a jugar: " << endl;
                cin >> nombreJuego;
                latencia = 1 + rand() % 500;
                puntuacion= rand() % 100000;

                Jugador J1=crearJugador(nombreJugador,ID,activo,latencia,puntuacion,Pais);

                //intentar conectar al jugador

                cadena host;
                bool enEspera;
                bool conectado=Gestor.alojarJugador(J1,nombreJuego,host,enEspera);
                if(conectado && !enEspera)
                {
                    cout << "Jugador " << nombreJugador << " conectado con exito al servidor con direccion/hostname: " << host;
                }

                else if(!conectado && enEspera)
                {
                    cout << "Jugador " << nombreJugador << " conectado a la cola de espera del servidor " << host << " con exito";
                }
                else
                {
                    cout << "El Jugador no ha podido ser conectado a ningun servidor activo para el juego indicado por falta de espacio";
                }
            }

        }
        break;

        case 8:
        {

            cadena nick;
            cadena host;
            cout << "Introduzca el nick del jugador a expulsar: " << endl;
            cin >> nick;

            if(!Gestor.jugadorConectado(nick) && !Gestor.jugadorEnEspera(nick)){
                cout << "El jugador no se encuentra en el sistema" << endl;
            }

            else{
                    Gestor.expulsarJugador(nick,host);
                cout << "Jugador expulsado con exito del servidor: " << host << endl;
            }

        } break;

        case 9:
        {
            cout << "Saliendo del menu..." << endl;
        }
        break;
        default:
        {
            cout << "Opcion incorrecta" << endl;
        }
        }

        cout<<endl;
        PAUSE;
    }
    while(opc != 9);

    return 0;
}
