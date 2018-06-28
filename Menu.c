/**************************** INCLUSION DE LIBRERIAS PERSONALES **********************************/
#include "Menu.h"
#include "General.h"

/**************************** INCLUSION DE LIBRERIAS ESTANDAR ************************************/
#include <stdio.h>



/**************************** LISTADO DE DATOS ***************************************************/
void eMenu_mostrarMenu(eMenu* menu)
{
   imprimirTitulo(menu->titulo);
   imprimirEnPantalla("\n");
   imprimirEnPantalla(menu->descripciones);
   imprimirEnPantalla("\n");
}
//-----------------------------------------------------------------------------------------------//


/**************************** ENTRADA DE DATOS ***************************************************/
int eMenu_pedirOpcion(eMenu* menu)
{
   int retorno;
   int i;

   eMenu_mostrarMenu(menu);
   printf("\nElija un n£mero de opci¢n del men£: ");
   scanf("%d", &retorno);


   while(buscarEnArrayInt(menu->codigos, menu->limiteOpciones, retorno) == -1)
   {
      eMenu_mostrarMenu(menu);
      //armo lista de opciones en el renglón por si el usuario se equivoca muchas veces
      //y el menú queda fuera de vista
      for(i = 0 ; i < menu->limiteOpciones ; i++)
      {
         if(i == 0)
         {
            printf("\nOpci¢n %d no v lida.\nElija una opci¢n de men£ de la lista\n(%d", retorno, menu->codigos[i]);
         }
         else
         {
            if(i < (menu->limiteOpciones)-1)
            {
               printf("-%d", menu->codigos[i]);
            }
            else
            {
               printf("-%d): ", menu->codigos[i]);
            }
         }
      }//for
      fflush(stdin);
      scanf("%d", &retorno);
   }

   return retorno;
}
//-----------------------------------------------------------------------------------------------//
