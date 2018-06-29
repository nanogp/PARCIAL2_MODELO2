/**************************** INCLUSION DE EMPTYRIAS EMAILALES **********************************/
#include "ArrayList.h"
#include "MailingList.h"
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
   eEmail* newEmail;

   newEmail = (eEmail*)malloc(sizeof(eEmail));
   if(newEmail != NULL)
   {
      newEmail->print     = eEmail_printOne;

      //getters
      newEmail->getUser   = eEmail_getUser;
      newEmail->getEmail  = eEmail_getEmail;

      //setters
      newEmail->setUser   = eEmail_setUser;
      newEmail->setEmail  = eEmail_setEmail;
   }

   return newEmail;
}
//-----------------------------------------------------------------------------------------------//
eEmail* eEmail_newParam(char* user,
                        char* email)
{
    eEmail* newEmail;

    newEmail = eEmail_new();

    if(newEmail != NULL)
   {
      newEmail->setUser(newEmail, user);
      newEmail->setEmail(newEmail, email);
   }

    return newEmail;
}
//-----------------------------------------------------------------------------------------------//


/**************************** BUSQUEDA ***********************************************************/
int eEmail_listIsEmpty(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this != NULL)
   {
      returnAux = this->isEmpty(this);
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

      if(returnAux)
      {
         imprimirEnPantalla(EMAIL_MSJ_EMPTY_LIST);
      }
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
eEmail* eEmail_getByEmail(ArrayList* this, char* email)
{
   eEmail* oneEmail;
   eEmail* returnEmail = NULL;

   for(int i=0; i<this->len(this) ; i++)
   {
      oneEmail = this->get(this, i);

      if(!strcmp(oneEmail->getEmail(oneEmail), email))
      {
         returnEmail = oneEmail;
         break;
      }
   }
   return returnEmail;
}
//-----------------------------------------------------------------------------------------------//


/**************************** LISTADO DE DATOS ***************************************************/
int eEmail_printOne(void* this, char* mask)
{
   int returnAux = 0;

   if(this != NULL)
   {
      printf(mask,
            ((eEmail*)this)->getUser(this),
            ((eEmail*)this)->getEmail(this));
      returnAux = 1;
   }

   return returnAux;
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
//      this->print(this, EMAIL_PAGESIZE, eEmail_printOne,EMAIL_PRINT_MASK_CABECERA,EMAIL_PRINT_MASK);

      for(int i=0 ; i<this->len(this) ; i++)
      {
         eEmail_printOne(this->get(this,i), EMAIL_PRINT_MASK);
      }

   }
   pausa();
}
//-----------------------------------------------------------------------------------------------//
void eEmail_gestionOrdenar(ArrayList* this)
{
   limpiarPantallaYMostrarTitulo(EMAIL_ORDEN_TITULO);

   if(!eEmail_listIsEmptyLegend(this))
   {
      eEmail_sortByEmail(this);
      imprimirEnPantalla(EMAIL_MSJ_ORDEN_OK);
   }
   pausa();
}
//-----------------------------------------------------------------------------------------------//





/**************************** CARGAR ARCHIVO *****************************************************/
#define EMAIL_MASCARA_ARCHIVO "%[^,],%[^\n]\n"
#define CAMPOS_A_LEER 2

int eEmail_gestionCargarArchivo(ArrayList* this)
{
   int returnAux = CHECK_POINTER;
   eEmail* registro = eEmail_new();
   char* user = constructorString(100);
   char* email = constructorString(100);
   int cantCamposLeidos;
   int huboErrorAddRegistro;
   int leidosOk = 0;
   int leidosError = 0;
   FILE* pFile;
   char* ruta;

   if(registro != NULL && user != NULL && email != NULL)
   {
      returnAux = OK;

      ruta = constructorStringParametrizado("\nIngrese ruta de archivo: ", "\nReingrese ruta de archivo: ", 255);

      pFile = fopen(ruta, "r");

      if(pFile == NULL)
      {
         printf("\nNo pudo abrirse el archivo %s ", ruta);
      }
      else
      {
         if(!this->isEmpty(this))
         {
            //limpio lista si no esta vacia
            this->clear(this);
         }

         cantCamposLeidos = fscanf(pFile, EMAIL_MASCARA_ARCHIVO, user, email);

         while(!feof(pFile))
         {
            if(feof(pFile))
            {
               break;
            }

            if(cantCamposLeidos == CAMPOS_A_LEER)
            {
               huboErrorAddRegistro = 0;
               huboErrorAddRegistro += registro->setUser(registro, user);
               huboErrorAddRegistro += registro->setEmail(registro, email);
               printf("\n%s | %s", user, email);

               if(!huboErrorAddRegistro)
               {
                  this->add(this, registro);
                  leidosOk++;
               }
               else
               {
                  leidosError++;
               }
            }
            else
            {
               leidosError++;
            }

            cantCamposLeidos = fscanf(pFile, EMAIL_MASCARA_ARCHIVO, user, email);
         }

         printf("\nSe leyo un archivo desde la ruta %s", ruta);
         printf("\nSe cargaron %d registros.", leidosOk);
         if(!leidosError)
         {
            printf("\nHubo errores con %d registros.", leidosError);
         }
      }
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//

/**************************** DESTINATARIOS ******************************************************/
#define EMAIL_CARGA_DESTINATARIOS_TITULO "CARGA ARCHIVO DESTINATARIOS"

int eEmail_gestionCargarDestinatarios(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this != NULL)
   {
      returnAux = OK;

      limpiarPantallaYMostrarTitulo(EMAIL_CARGA_DESTINATARIOS_TITULO);

      returnAux = eEmail_gestionCargarArchivo(this);
      eEmail_sortByEmail(this);

      pausa();
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** BLACKLIST **********************************************************/
#define EMAIL_CARGA_BLACKLIST_TITULO "CARGA ARCHIVO BLACKLIST"

int eEmail_gestionCargarBlacklist(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this != NULL)
   {
      returnAux = OK;

      limpiarPantallaYMostrarTitulo(EMAIL_CARGA_BLACKLIST_TITULO);

      returnAux = eEmail_gestionCargarArchivo(this);
      eEmail_sortByEmail(this);

      pausa();
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//


/**************************** ORDENAMIENTO *******************************************************/
int eEmail_compareByUser(void* pA,void* pB)
{
   return strcmp(((eEmail*)pA)->user, ((eEmail*)pB)->user);
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
int eEmail_compareByEmail(void* pA,void* pB)
{
   return strcmp(((eEmail*)pA)->user, ((eEmail*)pB)->user);
}
//-----------------------------------------------------------------------------------------------//
int eEmail_sortByEmail(ArrayList* this)
{
   int returnAux = CHECK_POINTER;

   if(this!=NULL)
   {
      returnAux = OK;
      this->sort(this, eEmail_compareByEmail, EMAIL_ORDEN_ASC);
   }

   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
