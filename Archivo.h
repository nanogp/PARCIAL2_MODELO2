#pragma once
#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

/**************************** INCLUSION DE LIBRERIAS ESTANDAR ************************************/
#include <stdio.h>

/**************************** LIMITES ************************************************************/
#define ARCHIVO_HTML_LARGO_NAME 255

/**************************** CONSTANTES *********************************************************/
#define ARCHIVO_TEXTO_NAME "data.csv"
#define ARCHIVO_TEXTO_LECTURA "r"
#define ARCHIVO_TEXTO_ESCRITURA "w"

/**************************** GESTION ARCHIVO TEXTO ********************************************/
FILE* eArchivoTexto_abrir(char* nombreArchivo);
//-----------------------------------------------------------------------------------------------//
void eArchivoTexto_cerrar(FILE* pArchivo);
//-----------------------------------------------------------------------------------------------//
#endif // ARCHIVO_H_INCLUDED
