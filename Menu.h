#pragma once
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**************************** LIMITES ************************************************************/
#define MENU_LARGO_TITULO 100
#define MENU_CANT_MAX 20
#define MENU_LARGO_DESCRIPCION 1000


/**************************** ESTRUCTURAS ********************************************************/
typedef struct
{
   char titulo[MENU_LARGO_TITULO];
   int limiteOpciones;
   int codigos[MENU_CANT_MAX];
   char descripciones[MENU_LARGO_DESCRIPCION];
} eMenu;


/**************************** LISTADO DE DATOS ***************************************************/
/** \brief muestra en pantalla un tipo de dato menu
 *
 * \param menu  eMenu*: el menu a mostrar
 * \return void
 *
 */
void eMenu_mostrarMenu(eMenu* menu);
//-----------------------------------------------------------------------------------------------//


/**************************** ENTRADA DE DATOS ***************************************************/
/** \brief pide al usuario que elija una opcion de menu recibido como parametro
 *
 * \param menu  eMenu*: el menu de opciones a mostrar al usuario para pedir y validar la opcion seleccionada
 * \return int: el numero de opcion validada
 *
 */
int eMenu_pedirOpcion(eMenu* menu);
//-----------------------------------------------------------------------------------------------//

#endif // MENU_H_INCLUDED
