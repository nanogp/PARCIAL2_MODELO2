#pragma once
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED


/**************************** INCLUSION DE LIBRERIAS PERSONALES **********************************/
#include "General.h"
#include "ArrayList.h"

/**************************** INCLUSION DE LIBRERIAS ESTANDAR ************************************/
#include <stdio.h>

/**************************** MASCARAS ***********************************************************/
#define PARSER_OK_MASK "\n\nSe parsearon %d registros exitosamente."

/**************************** GESTION DE DATOS ***************************************************/
int charToIsEmpty(char* cadena);
//-----------------------------------------------------------------------------------------------//
int parserPerson(FILE* pFile, ArrayList* pArrayListPerson);
//-----------------------------------------------------------------------------------------------//
#endif // PARSER_H_INCLUDED
