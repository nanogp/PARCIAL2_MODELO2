/**************************** INCLUSION DE EMPTYRIAS PERSONALES **********************************/
#include "General.h"
#include "Menu.h"
#include "ArrayList.h"
#include "Archivo.h"
#include "MailingList.h"


/**************************** INCLUSION DE EMPTYRIAS ESTANDAR ************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int returnAux = CHECK_POINTER;
   eMenu menuPrincipal = {/*titulo del menu*/{"PARCIAL 2, MODELO 2"},
                          /*cantidad de opciones*/8,
                          /*codigos*/{1,2,3,4,5,6,7,
                                      0},
                          /*descripciones*/"\n  1. CARGAR DESTINATARIOS"
                                           "\n  2. CARGAR LISTA NEGRA"
                                           "\n  3. DEPURAR"
                                           "\n  4. LISTAR"
                                           "\n  5. lista 1"
                                           "\n  6. lista 2"
                                           "\n  7. lista 3"
                                           "\n  0. Salir Del Programa"};
    int opcion;
    char salirDelPrograma = 'N';

    //ARRAYS DE ESTRUCTURAS
    ArrayList* destinatarios = al_newArrayList();
    ArrayList* blacklist = al_newArrayList();
    ArrayList* depurados = al_newArrayList();

    if(destinatarios == NULL || blacklist == NULL || depurados == NULL)
    {
        salirDelPrograma = 'S';
    }

    while(salirDelPrograma == 'N')
    {
        ejecutarEnConsola(LIMPIAR_PANTALLA);
        opcion = eMenu_pedirOpcion(&menuPrincipal);
        switch(opcion)
        {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                eEmail_gestionListar(depurados);
                break;
            case 5:
                eEmail_gestionListar(destinatarios);
                break;
            case 6:
                eEmail_gestionListar(blacklist);
                break;
            case 7:
                eEmail_gestionListar(depurados);
                break;
            case 8:

                break;
            case 9:

                break;
            case 10:

                break;
            case 11:

                break;
            case 0:
                salirDelPrograma = pedirConfirmacion("Confirma que desea salir del programa?");
                returnAux = OK;
                break;
        }

    }
    return returnAux;
}
