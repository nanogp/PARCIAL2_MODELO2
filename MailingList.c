/**************************** INCLUSION DE EMPTYRIAS EMAILALES **********************************/
#include "ArrayList.h"
#include "Person.h"
#include "Menu.h"
/**************************** INCLUSION DE EMPTYRIAS ESTANDAR ************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**************************** GET ****************************************************************/
char* eEmail_getUser(eEmail* this)
{
    char* returnAux = NULL;
    if(this != NULL)
    {
        returnAux = this->user;
    }
    return returnAux;
}
//-----------------------------------------------------------------------------------------------//
char* eEmail_getEmail(eEmail* this)
{
    char* returnAux = NULL;
    if(this != NULL)
    {
        returnAux = this->email;
    }
    return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** SET ****************************************************************/
int eEmail_setUser(eEmail* this, char* user)
{
    int returnAux = CHECK_POINTER;
    if(this != NULL)
    {
        returnAux = OK;
        strcpy(this->user, user);
    }
    return returnAux;
}
//-----------------------------------------------------------------------------------------------//
int eEmail_setEmail(eEmail* this, char* email)
{
    int returnAux = CHECK_POINTER;
    if(this != NULL)
    {
        returnAux = OK;
        strcpy(this->email, email);
    }
    return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** CONSTRUCTORES ******************************************************/
eEmail* eEmail_new(void)
{
   eEmail* newPerson;

   newPerson = (eEmail*)malloc(sizeof(eEmail));
   if(newPerson != NULL)
   {
      newPerson->print            = eEmail_printOne;

       //getters
      newPerson->getUser          = eEmail_getUser;
      newPerson->getEmail         = eEmail_getEmail;

       //setters
      newPerson->setUser          = eEmail_setUser;
      newPerson->setEmail      = eEmail_setEmail;
   }

   return newPerson;
}
//-----------------------------------------------------------------------------------------------//
eEmail* eEmail_newParam(char* user,
                        char* email)
{
    eEmail* newPerson;

    newPerson = eEmail_new();

    if(newPerson != NULL)
   {
      newPerson->setUser(newPerson, user);
      newPerson->setEmail(newPerson, email);
   }

    return newPerson;
}
//-----------------------------------------------------------------------------------------------//


/**************************** BUSQUEDA ***********************************************************/
int eEmail_listIsEmpty(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this != NULL)
   {
      returnAux = this->isEmpty();
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
int eEmail_listIsEmptyLegend(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this != NULL)
   {
      returnAux = eEmail_listIsEmpty(this);

      if(returnAux == EMPTY)
      {
         imprimirEnPantalla(EMAIL_MSJ_EMPTY_LIST);
      }
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
eEmail* eEmail_getByEmail(ArrayList* this, int email)
{
   eEmail* oneEmail;
   eEmail* returnPerson = NULL;

   for(int i=0; i<this->len(this) ; i++)
   {
      oneEmail = this->get(this, i);

      if(oneEmail->getEmail(oneEmail) == email)
      {
         returnPerson = oneEmail;
         break;
      }
   }
   return returnPerson;
}
//-----------------------------------------------------------------------------------------------//


/**************************** LISTADO DE DATOS ***************************************************/
void eEmail_printOne(eEmail* this)
{
   printf(EMAIL_PRINT_MASK,
          this->getUser(this),
          this->getEmail(this));
}
//-----------------------------------------------------------------------------------------------//
int eEmail_printList(ArrayList* this, int pageSize)
{
   eEmail* oneEmail;
   int count = 0;

   imprimirEnPantalla(EMAIL_PRINT_MASK_CABECERA);

   for(int i=0 ; i<this->len(this) ; i++)
   {
      oneEmail = this->get(this,i);

      if(!eEmail_isEmpty(oneEmail))
      {
         oneEmail->print(oneEmail);
         count++;

         if(count%pageSize == 0)
         {
            pausa();
            imprimirEnPantalla(EMAIL_PRINT_MASK_CABECERA);
         }
      }
   }
   return count;
}
//-----------------------------------------------------------------------------------------------//



/**************************** GESTION DE DATOS ***************************************************/
void eEmail_delete(eEmail* this)
{
    free(this);
}
//-----------------------------------------------------------------------------------------------//
void eEmail_gestionListar(ArrayList* this)
{
   limpiarPantallaYMostrarTitulo(EMAIL_LISTADO_TITULO);

   if(!eEmail_listIsEmptyLegend(this))
   {
      eEmail_printList(this, EMAIL_PRINT_PAGESIZE);
   }
   pausa();
}
//-----------------------------------------------------------------------------------------------//
void eEmail_gestionListarDesdeHasta(ArrayList* this)
{
   int desde;
   int hasta;

   limpiarPantallaYMostrarTitulo(EMAIL_LISTADO_RANGO_TITULO);

   if(!eEmail_listIsEmptyLegend(this))
   {
      imprimirEnPantalla(EMAIL_LISTADO_RANGO_INGRESO);
      pedirRangoIntValido(EMAIL_MSJ_INGRESE_ID,
                          EMAIL_MSJ_REINGRESE_ID,
                          EMAIL_ID_MIN,
                          EMAIL_ID_MAX,
                          &desde,
                          &hasta);

      limpiarPantallaYMostrarTitulo(EMAIL_LISTADO_RANGO_TITULO);
      eEmail_printListFromTo(this, desde, hasta, EMAIL_PRINT_PAGESIZE);
   }
   pausa();
}
//-----------------------------------------------------------------------------------------------//
void eEmail_gestionOrdenar(ArrayList* this)
{
   limpiarPantallaYMostrarTitulo(EMAIL_ORDEN_TITULO);

   if(!eEmail_listIsEmptyLegend(this))
   {
      eEmail_sortByDni(this);
      //eEmail_sortByUser(this);
      imprimirEnPantalla(EMAIL_MSJ_ORDEN_OK);
   }
   pausa();
}
//-----------------------------------------------------------------------------------------------//



/**************************** ALTA ***************************************************************/
int eEmail_gestionAlta(ArrayList* this)
{
   int returnAux = CHECK_POINTER;
   eEmail* registro;
   char confirmacion;

   if(this != NULL)
   {
      returnAux = OK;
      limpiarPantallaYMostrarTitulo(EMAIL_ALTA_TITULO);

      registro = eEmail_askInput();

      if(!eEmail_getByDni(this, registro->getDni(registro)))
      {
        printf(EMAIL_MSJ_DNI_YA_EXISTE, registro->getDni(registro));
      }
      else
      {
         limpiarPantallaYMostrarTitulo(EMAIL_ALTA_TITULO);
         imprimirEnPantalla(EMAIL_PRINT_MASK_CABECERA);
         registro->print(registro);

         confirmacion = pedirConfirmacion(MSJ_CONFIRMA_CORRECTOS);

         if(confirmacion == 'S')
         {
           this->add(this, registro);
           eEmail_sortByDni(this);
           imprimirEnPantalla(EMAIL_MSJ_ALTA_OK);
         }
         else
         {
           imprimirEnPantalla(MSJ_CANCELO_GESTION);
         }
      }
      pausa();
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** BAJA DE REGISTRO ****************************************************/
int eEmail_gestionBaja(ArrayList* this)
{
   int returnAux = CHECK_POINTER;
   eEmail* oneEmail;
   char confirmacion;

   if(this != NULL)
   {
      returnAux = CHECK_IS_EMPTY;
      limpiarPantallaYMostrarTitulo(EMAIL_BAJA_TITULO);

      if(!eEmail_listIsEmptyLegend(this))
      {
         returnAux = OK;

         oneEmail = eEmail_getByAskId(this);

         limpiarPantallaYMostrarTitulo(EMAIL_BAJA_TITULO);
         imprimirEnPantalla(EMAIL_PRINT_MASK_CABECERA);
         oneEmail->print(oneEmail);

         confirmacion = pedirConfirmacion(EMAIL_MSJ_CONFIRMAR_BAJA);

         if(confirmacion == 'S')
         {
            oneEmail->setIsEmpty(oneEmail, EMAIL_EMPTY);
            imprimirEnPantalla(EMAIL_MSJ_BAJA_OK);
         }
         else
         {
            imprimirEnPantalla(MSJ_CANCELO_GESTION);
         }
      }

   }
   pausa();
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** ORDENAMIENTO *******************************************************/
int eEmail_compareByDni(void* pPersonA, void* pPersonB)
{
   int returnAux = 0;

   if(((eEmail*)pPersonA)->getDni(pPersonA) > ((eEmail*)pPersonB)->getDni(pPersonB))
   {
      returnAux = 1;
   }
   else if(((eEmail*)pPersonA)->getDni(pPersonA) < ((eEmail*)pPersonB)->getDni(pPersonB))
   {
      returnAux = -1;
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
int eEmail_compareByUser(void* pPersonA,void* pPersonB)
{
   return strcmp(((eEmail*)pPersonA)->user, ((eEmail*)pPersonB)->user);
}
//-----------------------------------------------------------------------------------------------//
int eEmail_sortByDni(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this!=NULL)
   {
      returnAux = OK;
      this->sort(this, eEmail_compareByDni, EMAIL_ORDEN_ASC);
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
int eEmail_sortByUser(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this!=NULL)
   {
      returnAux = OK;
      this->sort(this, eEmail_compareByUser, EMAIL_ORDEN_ASC);
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
