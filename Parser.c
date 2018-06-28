/**************************** INCLUSION DE LIBRERIAS PERSONALES **********************************/
#include "Parser.h"
#include "ArrayList.h"
#include "Archivo.h"
/**************************** INCLUSION DE LIBRERIAS ESTANDAR ************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**************************** GESTION DE DATOS ***************************************************/
int charToIsEmpty(char* texto)
{
    int retorno = PERSON_OCCUPIED;

    if(stricmp(texto,TRUE) == 0)
    {
        retorno = PERSON_EMPTY;
    }
    else
    {
       retorno = PERSON_OCCUPIED;
    }

    return retorno;
}
//-----------------------------------------------------------------------------------------------//
int parserPerson(FILE* pFile, ArrayList* pArrayListPerson)
{
   int returnAux = -1;
   ePerson* auxEmpleado;
   char auxId[10];
   char auxName[PERSON_LARGO_NAME];
   char auxLastName[PERSON_LARGO_LAST_NAME];
   char auxIsEmpty[10];

   if(pArrayListPerson != NULL)
   {
      returnAux = 0;
      auxEmpleado = ePerson_new();

      //primera falsa lectura para saltear las cabeceras del archivo
      fscanf(pFile, PERSON_PARSE_MASK, auxId, auxName, auxLastName, auxIsEmpty);

      while(!feof(pFile))
      {
         auxEmpleado = ePerson_new();

         fscanf(pFile, PERSON_PARSE_MASK, auxId, auxName, auxLastName, auxIsEmpty);

         if(feof(pFile)) break; //por bug de fin de archivo que repite ultima lectura


         ePerson_setId(auxEmpleado, charToInt(auxId));
         ePerson_setName(auxEmpleado, auxName);
         ePerson_setLastName(auxEmpleado, auxLastName);
         ePerson_setIsEmpty(auxEmpleado, charToIsEmpty(auxIsEmpty));

         al_add(pArrayListPerson, auxEmpleado);

      }
   }
   return returnAux;
}
//-----------------------------------------------------------------------------------------------//
void ePerson_gestionParsear(ArrayList* this)
{
   FILE* pArchivo;
   int beforeCount;

   limpiarPantallaYMostrarTitulo(PERSON_PARSER_TITULO);

   pArchivo = eArchivoTexto_abrir(ARCHIVO_TEXTO_NOMBRE);
   if(pArchivo != NULL)
   {
      beforeCount = al_len(this);
      parserPerson(pArchivo, this);
      eArchivoTexto_cerrar(pArchivo);
      printf(PARSER_OK_MASK, al_len(this)-beforeCount);
   }
   else
   {
      imprimirEnPantalla("\nNo se pudo abrir el archivo");
   }
   pausa();

}
