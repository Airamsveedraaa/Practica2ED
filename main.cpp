#include "Comun.h"
#include "GestorServidores.h"
#include "Servidor.h"
#include "TADCola.h"
#include "TADLista.h"
using namespace std;

int main()
{
    int opc;
    do
    {
        cout << "GESTOR DE SERVIDORES v1.0"
             << "\n-----------------------------------------------"
             << "\n-----------------------------------------------"
             << "\n1. Mostrar servidores"
             << "\n2. Crear servidor"
             << "\n3. Eliminar servidor"
             << "\n4. Activar servidor"
             << "\n5. Desactivar servidor"
             << "\n6. Programar mantenimiento del servidor"
             << "\n7. Conectar juador"
             << "\n8. Expulsar jugador"
             << "\n9. Salir"
             << "\n\n> Seleccione una opcion :" << endl;
        cin >> opc;
        system("cls");
        switch(opc)
        {

        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            cout << "Saliendo del menu..." << endl;
            break;
        default:
            break;
        }
    }while(opc!=9);
    return 0;
}
