#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include "defendiendo_torres.h"

#define CANT_NIVELES 				4
#define MAX_NOMBRE_ARCHIVO 			50
#define MAX_CAMINO					200
#define MAX_FILAS					30
#define MAX_COLUMNAS 				30
#define MAX_LONGITUD_CAMINO 		200
#define MAX_NOMBRE_PUNTO_CARDINAL	20
#define MAX_ARGUMENTO				40
#define MAX_NOMBRE					40
#define MAX_TEXTO					40

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_CREAR_CONFIGURACION;
    argumentos[POSICION_ARCHIVO_TEXTO] contiene el archivo de texto donde se guardará la configuración creada.
Post-condiciones: 
    la función creará la configuración y modificará el valor del puntero recibido según se pudo crear la configuracion o no.*/
void ejecutar_comando_crear_configuracion(char* argumentos[], bool *se_pudo);

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_CREAR_CAMINO;
    argumentos[POSICION_ARCHIVO_TEXTO] contiene el archivo de texto donde se guardará el camino creado.
Post-condiciones: 
    la función creará los caminos y modificará el valor del puntero recibido según se pudo crear la configuracion o no.*/
void ejecutar_comando_crear_camino(char* argumentos[], bool *se_pudo);

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_JUGAR;
    argumentos con sus posiciones con valores válidos;
    "cantidad_parametros" es mayor o igual a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_JUGAR_MAX.
Post-condiciones: 
    la función desarrollará el juego y modificará el valor del puntero recibido según pudo hacerlo o no.*/
void ejecutar_comando_jugar(int cantidad_parametros, char* argumentos[], bool *se_pudo);

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_GRABACION;
    argumentos con sus posiciones con valores válidos;
    "cantidad_parametros" es mayor o igual a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX.
Post-condiciones: 
    la función desarrollará el juego del archivo ingresado y modificará el valor del puntero recibido según pudo hacerlo o no.*/
void ejecutar_comando_ver_grabacion(int cantidad_parametros, char* argumentos[], bool *se_pudo);

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_RANKING;
    argumentos con sus posiciones con valores válidos;
    "cantidad_parametros" es mayor o igual a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX.
Post-condiciones: 
    la función mostrará el ranking y modificará el valor del puntero recibido según pudo hacerlo o no.*/
void ejecutar_comando_ver_ranking(int cantidad_parametros, char* argumentos[], bool *se_pudo);

#endif /* __DEFENDIENDO_TORRES_H__ */
