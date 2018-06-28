#pragma once
#ifndef EMAIL_H_INCLUDED
#define EMAIL_H_INCLUDED


/**************************** INCLUSION DE LIBRERIAS PERSONALES **********************************/
#include "ArrayList.h"
#include "General.h"
#include "Menu.h"

/**************************** CONSTANTES *********************************************************/
#define EMAIL_EMPTY EMPTY
#define EMAIL_OCCUPIED OCCUPIED
#define EMAIL_EMPTY_LEGEND "Vacio"
#define EMAIL_OCCUPIED_LEGEND "Ocupado"
#define TRUE "true"
#define FALSE "false"
#define EMAIL_PRINT_PAGESIZE 1000

/**************************** LIMITES ************************************************************/
#define EMAIL_LENGTH_NAME 51
#define EMAIL_LENGTH_LAST_NAME 51
#define EMAIL_ID_MIN 1
#define EMAIL_ID_MAX 1000000
#define EMAIL_DNI_MIN 1
#define EMAIL_DNI_MAX 1000000
#define EMAIL_STATS_MIN 1
#define EMAIL_STATS_MAX 1000000
#define EMAIL_LENGTH_RESERVAS 10

/**************************** MASCARAS ***********************************************************/
#define EMAIL_PRINT_MASK "\n%s \t\t %s"
#define EMAIL_PARSE_MASK "%[^,],%[^,],%[^\n]\n"
#define EMAIL_LISTADO_RECUENTO "\n%d registros."

/**************************** TITULOS ************************************************************/
#define EMAIL_ALTA_TITULO "ALTA DE EMAIL"
#define EMAIL_BAJA_TITULO "BAJA DE EMAIL"
#define EMAIL_MODIFICACION_TITULO "MODIFICACION DE EMAIL"
#define EMAIL_LISTADO_TITULO "LISTADO DE EMAILS"
#define EMAIL_LISTADO_RANGO_TITULO "LISTADO DE EMAILS POR RANGO"
#define EMAIL_PARSER_TITULO "PARSER ARCHIVO CSV DE EMAILS"
#define EMAIL_ORDEN_TITULO "ORDENAR LISTA DE EMAILS"

/**************************** MENSAJES INFO ******************************************************/
#define EMAIL_MSJ_ALTA_OK "\nLa Email se dio de alta"
#define EMAIL_MSJ_BAJA_OK "\nLa Email se dio de baja"
#define EMAIL_MSJ_MODIFICACION_SIN_CAMBIOS "\nNo hubo cambio alguno"
#define EMAIL_MSJ_MODIFICACION_OK "\nLa Email se modifico"
#define EMAIL_MSJ_REGISTRO_ACTUAL "\n\nREGISTRO DE EMAIL ACTUAL:\n----------------------------"
#define EMAIL_MSJ_REGISTRO_MODIFICADO "\n\nREGISTRO MODIFICADO:\n--------------------"
#define EMAIL_MSJ_ORDEN_OK "\n\nSe ordeno listado por nombre"
#define EMAIL_LISTADO_RANGO_INGRESO "\n\nSe deben ingresar los ID desde y hasta\n--------------------------------------"

/**************************** MENSAJES INPUT *****************************************************/
#define EMAIL_MSJ_CONFIRMAR_BAJA "Confirma que desea dar de baja dicha Email?"
#define EMAIL_MSJ_INGRESE_ID "\n\nIngrese el ID de Email: "
#define EMAIL_MSJ_INGRESE_DNI "\n\nIngrese el DNI de Email: "
#define EMAIL_MSJ_INGRESE_STATS "\n\nIngrese stats de Email: "
#define EMAIL_MSJ_INGRESE_NAME "\nIngrese Nombre: "
#define EMAIL_MSJ_INGRESE_LAST_NAME "\nIngrese Apellido: "

/**************************** MENSAJES ERROR *****************************************************/
#define EMAIL_MSJ_ID_NO_EXISTE "\nEl ID de Email ingresado no existe"
#define EMAIL_MSJ_DNI_NO_EXISTE "\nEl DNI de Email ingresado no existe"
#define EMAIL_MSJ_DNI_YA_EXISTE "\nEl DNI %d ya existe en la lista"
#define EMAIL_MSJ_EMPTY_LIST "\n\nLa lista de Emails esta vacia o todos los registros se dieron de baja"
#define EMAIL_MSJ_NO_MAS_LUGAR "\nNo hay mas lugares disponibles para altas de Email"
#define EMAIL_MSJ_REINGRESE_ID "\nEl ID debe ser un numero mayor que cero. Reingrese un ID valido: "
#define EMAIL_MSJ_REINGRESE_DNI "\nEl DNI debe ser un numero mayor que EMAIL_DNI_MIN y menor que EMAIL_DNI_MAX. Reingrese un DNI valido:"
#define EMAIL_MSJ_REINGRESE_STATS "\nEl valor de stat debe ser un numero mayor que EMAIL_STATS_MIN y menor que EMAIL_STATS_MAX. Reingrese un stats valido:"
#define EMAIL_MSJ_REINGRESE_NAME "\nNombre no valido. Reingrese por favor hasta 50 caracteres: "
#define EMAIL_MSJ_REINGRESE_LAST_NAME "\nApellido no valido. Reingrese por favor hasta 50 caracteres: "

/**************************** LISTADOS ***********************************************************/
#define EMAIL_PRINT_MASK_CABECERA "\nID \t DNI \t NAME \t\t LAST_NAME \t\t ES VACIO\n-- \t ------ \t\t -------- \t\t --------"

/**************************** ORDENAMIENTO *******************************************************/
#define EMAIL_ORDEN_ASC 1
#define EMAIL_ORDEN_DESC 0

/**************************** ESTRUCTURAS ********************************************************/
struct
{
   char user[EMAIL_LENGTH_USER];
   char email[EMAIL_LENGTH_MAIL];

   void (*print)();

    //getters
   char* (*getUser)();
   char* (*getEmail)();

    //setters
   int (*setUser)();
   int (*setEmail)();

}typedef eEmail;

/**************************** GET ****************************************************************/
char* eEmail_getName(eEmail* this);
char* eEmail_getLastName(eEmail* this);

/**************************** SET ****************************************************************/
int eEmail_setName(eEmail* this, char* user);
int eEmail_setLastName(eEmail* this, char* email);

/**************************** CONSTRUCTORES ******************************************************/
eEmail* eEmail_new(void);
eEmail* eEmail_newParam(char* user,
                          char* email);

/**************************** BUSQUEDA ***********************************************************/
int eEmail_listIsEmpty(ArrayList* this)
int eEmail_listIsEmptyLegend(ArrayList* this);
eEmail* eEmail_getById(ArrayList* this, char* user);
eEmail* eEmail_getByDni(ArrayList* this, char* email);

/**************************** LISTADO DE DATOS ***************************************************/
void eEmail_printOne(eEmail* this);
int eEmail_printList(ArrayList* this, int pageSize);

/**************************** GESTION DE DATOS ***************************************************/
void eEmail_delete(eEmail* this);
void eEmail_gestionParse(ArrayList* this);
void eEmail_gestionListar(ArrayList* this);
void eEmail_gestionListarDesdeHasta(ArrayList* this);
void eEmail_gestionOrdenar(ArrayList* this);
int eEmail_gestionAlta(ArrayList* this);
int eEmail_gestionBaja(ArrayList* this);

/**************************** ORDENAMIENTO *******************************************************/
int eEmail_compareByUser(void* pEmailA, void* pEmailB);
int eEmail_compareByEmail(void* pEmailA, void* pEmailB);
int eEmail_sortByUser(ArrayList* this);
int eEmail_sortByEmail(ArrayList* this);
