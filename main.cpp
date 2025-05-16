/*#include "GestorServidores.h"

Jugador crearJugador(const char* nombre, int id, bool activo, int latencia, long puntuacion, const char* pais) {
    Jugador j;
    strcpy(j.nombreJugador, nombre);
    j.ID = id;
    j.activo = activo;
    j.latencia = latencia;
    j.puntuacion = puntuacion;
    strcpy(j.pais, pais);
    return j;
}

void pruebaServidor()
{
    cout << "===== INICIO DE PRUEBAS DE SERVIDOR =====" << endl;

    // Crear un servidor
    Servidor s("10.0.0.1", "JuegoPrueba", 100, 3, 2, 3000, "Argentina");

    // Mostrar estado inicial
    cout << "\n--- Estado Inicial ---" << endl;
    s.mostrarInformacion();

    // Activar servidor
    cout << "\nActivando servidor..." << endl;
    if (s.activar()) cout << "Servidor activado correctamente." << endl;
    else cout << "El servidor ya estaba activo." << endl;

    // Crear jugadores
    Jugador j1 = crearJugador("Ana", 1, true, 40, 1500, "Colombia");
    Jugador j2 = crearJugador("Luis", 2, true, 35, 1300, "Chile");
    Jugador j3 = crearJugador("Pedro", 3, true, 30, 1600, "Peru");
    Jugador j4 = crearJugador("Maria", 4, true, 50, 1100, "Ecuador");
    Jugador j5 = crearJugador("Jose", 5, true, 45, 1250, "Mexico");

    // Conectar jugadores
    cout << "\nConectando jugadores:" << endl;
    cout << "Ana: " << (s.conectarJugador(j1) ? "OK" : "Fallo") << endl;
    cout << "Luis: " << (s.conectarJugador(j2) ? "OK" : "Fallo") << endl;
    cout << "Pedro: " << (s.conectarJugador(j3) ? "OK" : "Fallo") << endl;

    // Jugadores en espera
    cout << "\nPoniendo jugadores en espera:" << endl;
    cout << "Maria: " << (s.ponerJugadorEnEspera(j4) ? "OK" : "Fallo") << endl;
    cout << "Jose: " << (s.ponerJugadorEnEspera(j5) ? "OK" : "Fallo") << endl;

    // Mostrar jugadores conectados
    cout << "\n--- Jugadores Conectados ---" << endl;
    s.mostrarJugadoresConectados();

    // Mostrar jugadores en espera
    cout << "\n--- Jugadores en Espera ---" << endl;
    s.mostrarJugadoresEnEspera();

    // Expulsar un jugador
    cout << "\nExpulsando a Luis..." << endl;
    if (s.expulsarJugador("Luis")) cout << "Luis expulsado correctamente." << endl;
    else cout << "No se encontro a Luis." << endl;

    // Mostrar despues de expulsion
    cout << "\n--- Jugadores Conectados Luego de Expulsion ---" << endl;
    s.mostrarJugadoresConectados();

    cout << "\n--- Jugadores en Espera Luego de Expulsion ---" << endl;
    s.mostrarJugadoresEnEspera();

    // Exportar jugadores conectados
    Jugador conectados[3];
    s.exportarJugadoresConectados(conectados);
    cout << "\nExportando jugadores conectados..." << endl;
    for (int i = 0; i < s.getNumJugadoresConectados(); i++) {
        cout << "- " << conectados[i].nombreJugador << endl;
    }

    // Exportar jugadores en espera
    Jugador enEspera[2];
    s.exportarJugadoresEnEspera(enEspera);
    cout << "\nExportando jugadores en espera..." << endl;
    for (int i = 0; i < s.getNumJugadoresEnEspera(); i++) {
        cout << "- " << enEspera[i].nombreJugador << endl;
    }

    // Pruebas de los nuevos métodos
cout << "\n--- Pruebas de los nuevos métodos ---" << endl;

// Primero mostrar estado actual
cout << "\nEstado actual:" << endl;
cout << "Conectados: Ana, Pedro" << endl;
cout << "En espera: Maria, Jose" << endl;

// Prueba PerteneceLista
cout << "\nProbando PerteneceLista:" << endl;
cout << "Ana (conectada): " << (s.PerteneceLista("Ana") ? "Sí" : "No") << endl;
cout << "Pedro (conectado): " << (s.PerteneceLista("Pedro") ? "Sí" : "No") << endl;
cout << "Maria (en espera): " << (s.PerteneceLista("Maria") ? "Sí" : "No") << endl;
cout << "Jose (en espera): " << (s.PerteneceLista("Jose") ? "Sí" : "No") << endl;
cout << "Juan (inexistente): " << (s.PerteneceLista("Juan") ? "Sí" : "No") << endl;

// Prueba PerteneceCola
cout << "\nProbando PerteneceCola:" << endl;
cout << "Ana (conectada): " << (s.PerteneceCola("Ana") ? "Sí" : "No") << endl;
cout << "Pedro (conectado): " << (s.PerteneceCola("Pedro") ? "Sí" : "No") << endl;
cout << "Maria (en espera): " << (s.PerteneceCola("Maria") ? "Sí" : "No") << endl;
cout << "Jose (en espera): " << (s.PerteneceCola("Jose") ? "Sí" : "No") << endl;
cout << "Juan (inexistente): " << (s.PerteneceCola("Juan") ? "Sí" : "No") << endl;
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
    int opc;

    do
    {
        opc = menu();

        switch(opc)
        {

        case 1:
        {
            pruebaServidor();
        } break;

        case 2:
        {

        } break;

        case 3:
        {

        } break;

        case 4:
        {

        } break;

        case 5:
        {

        } break;

        case 6:
        {

        } break;

        case 7:
        {

        } break;

        case 8:
        {

        } break;

        }//fin switch

        cout<<endl;
        PAUSE;
    }
    while(opc != 9);

    return 0;
}
*/


#include "GestorServidores.h"
#include <iostream>
#include <cstring>

using namespace std;

Jugador crearJugador(const char* nombre, int id, bool activo, int latencia, long puntuacion, const char* pais)
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

void testGestorServidores()
{
    GestorServidores gestor;

    // 1. Crear y desplegar tres servidores
    cout << "\n== TEST 1: Despliegue de servidores ==" << endl;
    gestor.desplegarServidor("192.168.0.1", "JuegoA", 1, 2, 1, 3000, "España");
    gestor.desplegarServidor("192.168.0.2", "JuegoB", 2, 2, 1, 3001, "Chile");
    gestor.desplegarServidor("192.168.0.3", "JuegoC", 3, 2, 1, 3002, "México");

    cout << "Servidores desplegados: " << gestor.getNumServidores() << " (esperado: 3)\n";

    // 2. Activar un servidor
    cout << "\n== TEST 2: Activación de servidor ==" << endl;
    gestor.conectarServidor("192.168.0.2");
    bool activado = gestor.conectarServidor("192.168.0.2");
    cout << "Servidor 192.168.0.2 activado: " << (activado ? "Sí ✅" : "No ❌") << endl;

    // 3. Alojamiento de jugadores (JuegoB)
    cout << "\n== TEST 3: Alojamiento de jugadores en JuegoB ==" << endl;
    bool enEspera;
    cadena host;
    for (int i = 1; i <= 4; i++)
    {
        string nombre = "Jugador" + to_string(i);
        Jugador j = crearJugador(nombre.c_str(), i, true, 30 + i, 1000 + i, "AR");
        bool conectado = gestor.alojarJugador(j, "JuegoB", host, enEspera);

        cout << "  - " << nombre << ": ";
        if (conectado)
        {
            cout << "Conectado ✅ al servidor: " << host << endl;
        }
        else if (enEspera)
        {
            cout << "En espera 🕓 en el servidor: " << host << endl;
        }
        else
        {
            cout << "Rechazado ❌" << endl;
        }
    }

    // 4. Verificar estado de los jugadores
    cout << "\n== TEST 4: Comprobación de estado de jugadores ==" << endl;
    cout << "¿Jugador1 conectado? " << (gestor.jugadorConectado("Jugador1") ? "Sí ✅" : "No ❌") << endl;
    cout << "¿Jugador4 en espera? " << (gestor.jugadorEnEspera("Jugador4") ? "Sí ✅" : "No ❌") << endl;

    // 5. Expulsión de jugadores
    cout << "\n== TEST 5: Expulsión de jugadores ==" << endl;
    cadena expulsadoDe;

    bool expulsado1 = gestor.expulsarJugador("Jugador1", expulsadoDe);
    cout << "Jugador1 expulsado de: " << (expulsado1 ? expulsadoDe : "N/A") << " → "
         << (expulsado1 ? "✅" : "❌") << endl;

    cout << "¿Jugador1 sigue conectado? " << (gestor.jugadorConectado("Jugador1") ? "Sí ❌" : "No ✅") << endl;
    cout << "¿Jugador3 ahora conectado? " << (gestor.jugadorConectado("Jugador3") ? "Sí ✅" : "No ❌") << endl;

    bool expulsado2 = gestor.expulsarJugador("Jugador4", expulsadoDe);
    cout << "Jugador4 expulsado de cola: " << (expulsado2 ? expulsadoDe : "N/A") << " → "
         << (expulsado2 ? "✅" : "❌") << endl;
    cout << "¿Jugador4 en espera? " << (gestor.jugadorEnEspera("Jugador4") ? "Sí ❌" : "No ✅") << endl;

    // 6. Eliminar servidor
    cout << "\n== TEST 6: Eliminación de servidor ==" << endl;
    bool eliminado = gestor.eliminarServidor("192.168.0.2");
    cout << "Servidor eliminado: " << (eliminado ? "Sí ✅" : "No ❌") << endl;
    cout << "Servidores restantes: " << gestor.getNumServidores() << " (esperado: 2)\n";

    // 7. Verificar estado tras eliminación
    cout << "¿Jugador2 sigue conectado? " << (gestor.jugadorConectado("Jugador2") ? "Sí ❌" : "No ✅") << endl;
    // 8. Expulsión de jugador inexistente
    cout << "\n== TEST 7: Expulsión de jugador inexistente ==" << endl;
    cadena dummy;
    bool expulsadoX = gestor.expulsarJugador("JugadorX", dummy);
    cout << "JugadorX expulsado: " << (expulsadoX ? "Sí ❌" : "No ✅") << endl;
}


int main()
{
    testGestorServidores();
    return 0;
}
