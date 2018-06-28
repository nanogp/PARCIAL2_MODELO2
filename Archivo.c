/**************************** INCLUSION DE LIBRERIAS PERSONALES **********************************/
#include "Archivo.h"

/**************************** INCLUSION DE LIBRERIAS ESTANDAR ************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************** GESTION ARCHIVO TEXTO ********************************************/
FILE* eArchivoTexto_abrir(char* nombreArchivo)
{
   FILE* pArchivo;

   pArchivo = fopen(nombreArchivo, ARCHIVO_TEXTO_LECTURA);

   return pArchivo;
}
//-----------------------------------------------------------------------------------------------//
void eArchivoTexto_cerrar(FILE* pArchivo)
{
   fclose(pArchivo);
}
//-----------------------------------------------------------------------------------------------//
