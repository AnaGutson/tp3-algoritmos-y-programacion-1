#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"
#include "animos.h"
#include "comandos.h"

#define MAX_LARGO_ARGUMENTO	100

#define POSICION_COMANDO_PRINCIPAL	1
#define POSICION_ARGUMENTO_1		2
#define POSICION_ARGUMENTO_2		3
#define COMANDO_MAX_ARGUMENTOS		4	

#define COMANDO_CREAR_CONFIGURACION 				"crear_configuracion"
#define CANT_ARGUMENTOS_CREAR_CONFIGURACION			3

#define COMANDO_CREAR_CAMINO 						"crear_camino"
#define CANT_ARGUMENTOS_CREAR_CAMINO				3

#define COMANDO_JUGAR 								"jugar"
#define CANT_ARGUMENTOS_COMANDO_JUGAR_MAX			4
#define PRIMER_ARGUMENTO_JUGAR						"config="
#define SEGUNDO_ARGUMENTO_JUGAR						"grabacion="

#define COMANDO_VER_GRABACION 						"poneme_la_repe"
#define CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX	4
#define PRIMER_ARGUMENTO_VER_GRABACION				"grabacion="
#define SEGUNDO_ARGUMENTO_VER_GRABACION				"velocidad="

#define COMANDO_VER_RANKING 						"ranking"
#define CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX		4
#define PRIMER_ARGUMENTO_VER_RANKING				"listar="
#define SEGUNDO_ARGUMENTO_VER_RANKING				"config="

#define COMANDO_SIN_ARGUMENTOS 		2
#define CANT_MINIMA_ARGUMENTOS		1
#define VELOCIDAD_DEFAULT_GRABACION 1

#define CARACTER_VACIO		'\0'

#define LEER 		"r"
#define ESCRIBIR 	"w"

#define FIN         "\033[0m"
#define BLANCO      "\033[1m\033[37m"
#define ROJO		"\033[1m\033[31m"
#define AZUL 		"\033[1m\033[34m"
#define MAGENTA 	"\033[1m\033[35m"

//															VALIDACIONES

/*Pre-condiciones:
	"comando" debe ser COMANDO_JUGAR, COMANDO_VER_GRABACION o COMANDO_VER_RANKING.
Post-condiciones:
	la función modifica el valor de "comparacion_1" y "comparacion_2" segun el comando recibido.*/
void obtener_argumentos_a_comparar_segun_comando(char comando[MAX_LARGO_ARGUMENTO], char comparacion_1[MAX_LARGO_ARGUMENTO], char comparacion_2[MAX_LARGO_ARGUMENTO]){
	
	if(strcmp(comando, COMANDO_JUGAR) == 0){

		strcpy(comparacion_1, PRIMER_ARGUMENTO_JUGAR);
		strcpy(comparacion_2, SEGUNDO_ARGUMENTO_JUGAR);
	}
	else if(strcmp(comando, COMANDO_VER_GRABACION) == 0){

		strcpy(comparacion_1, PRIMER_ARGUMENTO_VER_GRABACION);
		strcpy(comparacion_2, SEGUNDO_ARGUMENTO_VER_GRABACION);
	}else{

		strcpy(comparacion_1, PRIMER_ARGUMENTO_VER_RANKING);
		strcpy(comparacion_2, SEGUNDO_ARGUMENTO_VER_RANKING);
	}
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función retorna true si el primer argumento luego del comando es obligatorio.*/
bool primero_obligatorio(char comando[MAX_ARGUMENTO]){
	bool es_obligatorio = false;

	if(strcmp(comando, COMANDO_VER_GRABACION) == 0)
		es_obligatorio = true;

	return es_obligatorio;
}

/*Pre-condiciones:
	cantidad_argumentos_ingresados >= COMANDO_SIN_ARGUMENTOS y <= COMANDO_MAX_ARGUMENTOS;
Post-condiciones:
	la función retorna true si los argumentos ingresados corresponden al comando ingresado.*/
bool argumentos_comando_validos(int cantidad_argumentos_ingresados, char* argumentos[]){
	bool argumentos_validos = false, primer_argumento_obligatorio = false;
	char argumento_1[MAX_ARGUMENTO] = {CARACTER_VACIO}, argumento_2[MAX_ARGUMENTO] = {CARACTER_VACIO};
	char comparacion_1[MAX_ARGUMENTO] = {CARACTER_VACIO}, comparacion_2[MAX_ARGUMENTO] = {CARACTER_VACIO};	
	
	primer_argumento_obligatorio = primero_obligatorio(argumentos[POSICION_COMANDO_PRINCIPAL]);

	if( (cantidad_argumentos_ingresados == COMANDO_SIN_ARGUMENTOS) && primer_argumento_obligatorio )
		argumentos_validos = false;
	else if(cantidad_argumentos_ingresados == COMANDO_SIN_ARGUMENTOS)
		argumentos_validos = true;
	else{
		
		obtener_argumentos_a_comparar_segun_comando(argumentos[POSICION_COMANDO_PRINCIPAL], comparacion_1, comparacion_2);
		strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
		
		if(!primer_argumento_obligatorio)
			argumentos_validos = ( ( strncmp(argumento_1, comparacion_1, strlen(comparacion_1)) == 0 ) || ( strncmp(argumento_1, comparacion_2, strlen(comparacion_2)) == 0 ) );
		else
			argumentos_validos = strncmp(argumento_1, comparacion_1, strlen(comparacion_1)) == 0;
		
		if(cantidad_argumentos_ingresados == COMANDO_MAX_ARGUMENTOS){
			
			strcpy(argumento_2, argumentos[POSICION_ARGUMENTO_2]);
			argumentos_validos = ( ( ( strncmp(argumento_1, comparacion_1, strlen(comparacion_1)) == 0 ) && ( strncmp(argumento_2, comparacion_2, strlen(comparacion_2)) == 0 ) )
				|| ( ( strncmp(argumento_1, comparacion_2, strlen(comparacion_2)) == 0 ) && ( strncmp(argumento_2, comparacion_1, strlen(comparacion_1)) == 0) ) );
		}
	}

	return argumentos_validos;
}

/*Pre-condiciones:
	cantidad_argumentos_ingresados > CANT_MINIMA_ARGUMENTOS;
	comando_a_comparar es COMANDO_VER_GRABACION, COMANDO_JUGAR o COMANDO_VER_RANKING;
	cantidad_argumentos_comando es CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX, CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX o CANT_ARGUMENTOS_COMANDO_JUGAR_MAX segun corresponda.
Post-condiciones:
	la función retorna true si el comando ingresado es comando JUGAR, comando VER_RANKING o comando VER_GRABACION.*/
bool es_otro_comando(int cantidad_argumentos_ingresados, char* argumentos[], char comando_a_comparar[MAX_ARGUMENTO], int cantidad_argumentos_comando){

	return ( strcmp(argumentos[POSICION_COMANDO_PRINCIPAL], comando_a_comparar) == 0 
		&& (cantidad_argumentos_ingresados <= cantidad_argumentos_comando)
		&& argumentos_comando_validos(cantidad_argumentos_ingresados, argumentos) ); 
}

/*Pre-condiciones:
	cantidad_argumentos_ingresados > CANT_MINIMA_ARGUMENTOS;
	comando_a_comparar es COMANDO_CREAR_CONFIGURACION o COMANDO_CREAR_CAMINO;
	cantidad_argumentos_comando es CANT_ARGUMENTOS_CREAR_CONFIGURACION o CANT_ARGUMENTOS_CREAR_CAMINO segun corresponda.
Post-condiciones:
	la función retorna true si el comando ingresado es un comando de creación.*/
bool es_comando_crear(int cantidad_argumentos_ingresados, char* argumentos[], char comando_a_comparar[MAX_ARGUMENTO], int cantidad_argumentos_comando){

	return ( strcmp(argumentos[POSICION_COMANDO_PRINCIPAL], comando_a_comparar) == 0 
		&& (cantidad_argumentos_ingresados == cantidad_argumentos_comando)); 
}

/*Pre-condiciones:
	cantidad_argumentos > CANT_MINIMA_ARGUMENTOS.
Post-condiciones:
	la función retorna true si el comando ingresado es válido.*/
bool comando_es_valido(int cantidad_argumentos, char* argumentos[]){
	bool comando_valido = false;
	
	if(es_comando_crear(cantidad_argumentos, argumentos, COMANDO_CREAR_CONFIGURACION, CANT_ARGUMENTOS_CREAR_CONFIGURACION))
		comando_valido = true;

	else if(es_comando_crear(cantidad_argumentos, argumentos, COMANDO_CREAR_CAMINO, CANT_ARGUMENTOS_CREAR_CAMINO))
		comando_valido = true;

	else if(es_otro_comando(cantidad_argumentos, argumentos, COMANDO_VER_GRABACION, CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX))
		comando_valido = true;

	else if(es_otro_comando(cantidad_argumentos, argumentos, COMANDO_JUGAR, CANT_ARGUMENTOS_COMANDO_JUGAR_MAX))
		comando_valido = true;

	else if(es_otro_comando(cantidad_argumentos, argumentos, COMANDO_VER_RANKING, CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX))
		comando_valido = true;

	return comando_valido;
}

/*Pre-condiciones:
	cantidad_argumentos > 0.
Post-condiciones:
	la función retorna true si se ingreso una cantidad de argumentos válida.*/
bool hay_argumentos(int cantidad_argumentos){

	return (cantidad_argumentos > CANT_MINIMA_ARGUMENTOS);
}

/*Pre-condiciones:
	haber ingresado un comando invalido.
Post-condiciones:
	la función muestra los ingresos válidos a escribir.*/
void mostrar_opciones_comandos(){

	printf(ROJO "Comando inválido."BLANCO" Le recuerdo cuáles son los comandos válidos: \n");
	printf("\t-> Para crear un camino ingrese: "MAGENTA COMANDO_CREAR_CAMINO BLANCO" <nombre_archivo_en_donde_colocarlo>\n\n");
	printf("\t-> Para crear una configuracion ingrese: "MAGENTA COMANDO_CREAR_CONFIGURACION BLANCO" <nombre_archivo_en_donde_colocarla>\n\n");
	printf("\t-> Para jugar: "MAGENTA COMANDO_JUGAR" " AZUL PRIMER_ARGUMENTO_JUGAR BLANCO"<nombre_archivo_configuracion> "AZUL SEGUNDO_ARGUMENTO_JUGAR BLANCO"<nombre_archivo_en_donde_colocarla>\n");
	printf("\t\t-> los argumentos son opcionales.\n\n");
	printf("\t-> Para ver una partida grabada: "MAGENTA COMANDO_VER_GRABACION" "AZUL PRIMER_ARGUMENTO_VER_GRABACION BLANCO"<nombre_archivo_grabacion> "AZUL SEGUNDO_ARGUMENTO_VER_GRABACION BLANCO"<velocidad_entre_turnos>\n");
	printf("\t\t-> la velocidad es opcional, en caso de no colocarla se tomará velocidad '%i' segundo.\n\n", VELOCIDAD_DEFAULT_GRABACION);
	printf("\t-> Para ver el ranking de una configuracion: "MAGENTA COMANDO_VER_RANKING " " AZUL PRIMER_ARGUMENTO_VER_RANKING BLANCO"<cantidad_elementos_a_listar> "AZUL SEGUNDO_ARGUMENTO_VER_RANKING BLANCO"<nombre_archivo_configuracion>\n");
	printf("\t\t-> los argumentos son opcionales.\n"FIN);
}

/*Pre-condiciones:
	"cantidad_argumentos" > CANT_MINIMA_ARGUMENTOS, y es una cantidad válida.
Post-condiciones:
	la función ejecuta un comando y devuelve si pudo o no modicando el valor recibido por referencia "*se_pudo".*/
void ejecutar_comando(int cantidad_argumentos, char* argumentos[], bool* se_pudo){
	char comando[MAX_ARGUMENTO];

	system("clear");

	strcpy(comando, argumentos[POSICION_COMANDO_PRINCIPAL]);

	if(strcmp(comando, COMANDO_CREAR_CONFIGURACION) == 0)
		ejecutar_comando_crear_configuracion(argumentos, se_pudo);

	else if(strcmp(comando, COMANDO_CREAR_CAMINO) == 0)
		ejecutar_comando_crear_camino(argumentos, se_pudo);
	
	else if(strcmp(comando, COMANDO_JUGAR) == 0)
		ejecutar_comando_jugar(cantidad_argumentos, argumentos, se_pudo);
	
	else if(strcmp(comando, COMANDO_VER_RANKING) == 0)
		ejecutar_comando_ver_ranking(cantidad_argumentos, argumentos, se_pudo);
	
	else if(strcmp(comando, COMANDO_VER_GRABACION) == 0)
		ejecutar_comando_ver_grabacion(cantidad_argumentos, argumentos, se_pudo);
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función ejecutará el comando ingresado y en caso de no haber ingresado un comando válido, se mostrará un mensaje de ayuda.*/
int main(int cantidad_argumentos, char* argumentos[]){
	srand ((unsigned)time(NULL));
	bool se_pudo = false;

	system("clear");
	if( hay_argumentos(cantidad_argumentos) && comando_es_valido(cantidad_argumentos, argumentos) )
		ejecutar_comando(cantidad_argumentos, argumentos, &se_pudo);
	if(!se_pudo)
		mostrar_opciones_comandos();

	return 0;
}