#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "comandos.h"
#include "utiles.h"
#include "animos.h"
#include "adornos.h"

#define AMARILLO 		"\033[1m\033[33m"
#define AZUL 			"\033[1m\033[34m"
#define BLANCO 			"\033[1m\033[37m"
#define GRIS	 		"\033[1m\033[30m"
#define MAGENTA 		"\033[1m\033[35m"
#define ROJO			"\033[1m\033[31m"
#define SILVER 			"\033[0m\033[37m"
#define VERDE_CLARO 	"\033[0m\033[32m"
#define VERDE_OSCURO 	"\033[1m\033[32m"
#define FIN 			"\033[0m"

#define MARGEN 			"         "

#define ESTE 			'E'
#define OESTE 			'O'
#define NORTE 			'N'
#define SUR 			'S'

#define ARRIBA 			'W'
#define IZQUIERDA 		'A'
#define ABAJO 			'S'
#define DERECHA 		'D'

#define NADA 			'N'
#define ENTRADA 		'E'
#define ENTRADA_1 		'1'
#define ENTRADA_2 		'2'
#define TORRE_1 		'3'
#define TORRE_2 		'4'
#define CAMINO_1 		'U'
#define CAMINO_2 		'D'
#define AMBOS_CAMINOS 	'C'
#define ELFO 			'L'
#define ENANO 			'G'

#define VERDADERO		1
#define FALSO			0

#define SI 				'S'
#define NO 				'N'

#define POSIBLE 		0
#define NO_POSIBLE 		-1

#define PERDIDO 		-1
#define JUGANDO 		0
#define GANADO 			1

#define POR_DEFECTO 				(-1)
#define CARACTER_POR_DEFECTO 		'1'
#define PERSONALIZADO 				0
#define CARACTER_PERSONALIZADO 		'0'

#define TEXTO_VALOR_DEFAULT 		"-1"
#define CARACTER_DEFAULT 			'A'
#define CARACTER_VACIO				'\0'

#define TEXTO_DEFAULT 				"Texto default"
#define NOMBRE_TEMPORAL				"archivo_ranking.csv"

#define NUMERO_TORRE_1 				1
#define NUMERO_TORRE_2 				2
#define NUMERO_CAMINO_1 			1
#define NUMERO_CAMINO_2 			2
#define VALOR_NULO 					0
#define VACIO 						0
#define VALOR_DEFAULT 				(-1)
#define DECENA 						10
#define DISTANCIA_ENTRADA			3
#define DISTANCIA_TORRES			3
#define DOS_CAMINOS 				2

#define POSICION_ARGUMENTO_PRINCIPAL 	1
#define POSICION_ARGUMENTO_1			2
#define POSICION_ARGUMENTO_2			3
#define POSICION_ARCHIVO_TEXTO	 		2

#define PUNTO 							'.'
#define EXTENSION_ARCHIVOS_TEXTO		".txt"
#define EXTENSION_ARCHIVOS_GRABACION    ".dat"
#define EXTENSION_ARCHIVOS_PUNTAJE		".csv"

#define TIEMPO_ENTRE_TURNOS 			5
#define TIEMPO_ENTRE_DEFENSORES 		2
#define TIEMPO_GENERAL			 		2
#define TIEMPO_FINALIZACION_NIVEL 		2

#define ENANOS_EXTRAS_INICIAL			10
#define ELFOS_EXTRAS_INICIAL			10
#define VIDA_INICIAL_TORRE_1			600
#define VIDA_INICIAL_TORRE_2			600
#define COSTO_ENANO_EXTRA_TORRE_1 		50
#define COSTO_ENANO_EXTRA_TORRE_2 		0
#define COSTO_ELFO_EXTRA_TORRE_1		0
#define COSTO_ELFO_EXTRA_TORRE_2		50
#define DEF_EXTRA_TORRE_1 				"ENANO"
#define DEF_EXTRA_TORRE_2 				"ELFO"

#define NIVEL_1 						1
#define TAMANIO_NIVEL_1 				15
#define CARDINAL_NIVEL_1 				ESTE
#define ENEMIGOS_NIVEL_1 				100
#define ELFOS_NIVEL_1 					0
#define ENANOS_NIVEL_1  				5
#define PODER_AGREGAR_ELFO_NIVEL_1		FALSO
#define PODER_AGREGAR_ENANO_NIVEL_1		VERDADERO
#define ENEMIGOS_DEFENSOR_EXTRA_NIVEL_1 25
#define CANT_CAMINOS_NIVEL_1			1
#define TORRE_NIVEL_1					TORRE_1

#define NIVEL_2 						2
#define TAMANIO_NIVEL_2 				15
#define CARDINAL_NIVEL_2 				OESTE
#define ENEMIGOS_NIVEL_2 				200
#define ELFOS_NIVEL_2 					5
#define ENANOS_NIVEL_2  				0
#define PODER_AGREGAR_ELFO_NIVEL_2		VERDADERO
#define PODER_AGREGAR_ENANO_NIVEL_2		FALSO
#define ENEMIGOS_DEFENSOR_EXTRA_NIVEL_2 50
#define CANT_CAMINOS_NIVEL_2			1
#define TORRE_NIVEL_2					TORRE_2

#define NIVEL_3 						3
#define TAMANIO_NIVEL_3			 		20
#define CARDINAL_NIVEL_3 				NORTE
#define ENEMIGOS_NIVEL_3 				300
#define ELFOS_NIVEL_3 					3
#define ENANOS_NIVEL_3  				3
#define PODER_AGREGAR_ELFO_NIVEL_3		VERDADERO
#define PODER_AGREGAR_ENANO_NIVEL_3		VERDADERO
#define ENEMIGOS_DEFENSOR_EXTRA_NIVEL_3 50
#define CANT_CAMINOS_NIVEL_3			2

#define NIVEL_4 						4
#define TAMANIO_NIVEL_4					20
#define CARDINAL_NIVEL_4 				SUR
#define ENEMIGOS_NIVEL_4 				500
#define ELFOS_NIVEL_4 					4
#define ENANOS_NIVEL_4  				4
#define PODER_AGREGAR_ELFO_NIVEL_4		VERDADERO
#define PODER_AGREGAR_ENANO_NIVEL_4		VERDADERO
#define ENEMIGOS_DEFENSOR_EXTRA_NIVEL_4 50
#define CANT_CAMINOS_NIVEL_4			2

#define VIDA_TORRES_MIN 					10
#define VIDA_TORRES_MAX 					1000000

#define DEFENSOR_DE_CADA_TIPO_INICIAL_MIN 	0
#define DEFENSOR_DE_CADA_TIPO_INICIAL_MAX 	15

#define DEFENSOR_EXTRA_MIN 					0
#define DEFENSOR_EXTRA_MAX 					15

#define PORCENTAJE_ATAQUE_MIN 				0
#define PORCENTAJE_ATAQUE_MAX 				100

#define COSTO_DEFENSOR_MIN 					1
#define COSTO_DEFENSOR_MAX 					1000000

#define VELOCIDAD_MIN 						0.1f
#define VELOCIDAD_MAX 						10
#define VELOCIDAD_GRABACION_DEFAULT 		1

#define LEER 		"r"
#define ESCRIBIR 	"w"

#define CANT_TURNOS_A_GRABAR_POR_REPETICION 1

#define ESPACIO_COSTADOS_CUADRO		8
#define ESPACIO_POR_CASILLA_CUADRO	3
#define ESPACIO 					" "
#define CANT_CASILLAS_CUADRO		10

#define FORMATO_CONFIGURACION_RESISTENCIA_TORRES 	"RESISTENCIA_TORRES=%i,%i\n"
#define FORMATO_CONFIGURACION_ENANOS_EXTRA 			"ENANOS_EXTRA=%i,%i,%i\n"
#define FORMATO_CONFIGURACION_ELFOS_EXTRA 			"ELFOS_EXTRA=%i,%i,%i\n"
#define FORMATO_CONFIGURACION_ENANOS_ANIMO 			"ENANOS_ANIMO=%i,%i\n"
#define FORMATO_CONFIGURACION_ELFOS_ANIMO 			"ELFOS_ANIMO=%i,%i\n"
#define FORMATO_CONFIGURACION_VELOCIDAD 			"VELOCIDAD=%f\n"
#define FORMATO_CONFIGURACION_CAMINOS 				"CAMINOS=%s\n"

#define FORMATO_DEFENSORES_INICIO_PRIMERA_PARTE		"%s_INICIO=%i"

#define COMANDO_CREAR_CONFIGURACION 				"crear_configuracion"
#define CANT_ARGUMENTOS_CREAR_CONFIGURACION			3

#define COMANDO_CREAR_CAMINO 						"crear_camino"
#define CANT_ARGUMENTOS_CREAR_CAMINO				3

#define COMANDO_JUGAR 								"jugar"
#define ARGUMENTO_JUGAR_CON_PARAMETROS_CANT_MIN 	3
#define CANT_ARGUMENTOS_COMANDO_JUGAR_MAX			4
#define PRIMER_ARGUMENTO_JUGAR						"config="
#define SEGUNDO_ARGUMENTO_JUGAR						"grabacion="

#define COMANDO_VER_GRABACION 						"poneme_la_repe"
#define CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX	4
#define PRIMER_ARGUMENTO_VER_GRABACION				"grabacion="
#define SEGUNDO_ARGUMENTO_VER_GRABACION				"velocidad="

#define COMANDO_VER_RANKING 						"ranking"
#define ARGUMENTO_VER_RANKING_CON_PARAMETROS_CANT_MIN 	3
#define CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX			4
#define PRIMER_ARGUMENTO_VER_RANKING				"listar="
#define SEGUNDO_ARGUMENTO_VER_RANKING				"config="

#define CARACTER_DELIMITADOR_ARGUMENTOS				'='

#define TERMINO_LECTURA 0




// 													FUNCIONES GENERALES 
/*Pre-condiciones:
	-
Post-condiciones:
	la función convierte en mayúscula "letra" si el mismo no lo estaba; si "letra" ya estaba en mayúscula, se devolverá el mismo valor*/
static void mayusculizar_letra(char *letra){

    *letra = (char) toupper (*letra);
}

/*Pre-condiciones: 
    "valor" positivo.
Post-condiciones: 
    la función devolverá la cantidad de digitos del valor.*/
static int cant_digitos(int valor){
	int digitos = 0;
	
	do{
		
		digitos++;
		valor/=DECENA;
	}while(valor != 0);
	
	return digitos;
}

/*Pre-condiciones: 
    "tope" positivo y menor al máximo de "vector".
Post-condiciones: 
    la función devolverá el vector con un CARACTER_VACIO en cada posicion.*/
void limpiar_vector_caracteres(char vector[], int tope){

	for (int i = 0; i < tope; i++)
		vector[i] = CARACTER_VACIO;
}

/*Pre-condiciones: 
    "largo" debe ser positivo.
Post-condiciones: 
    la función actualizará el valor de "resultado" segun los parámetros recibidos.*/
static void copiar_final(char original[MAX_ARGUMENTO], char resultado[MAX_ARGUMENTO], int i, size_t largo){
	int j = 0;

	limpiar_vector_caracteres(resultado, MAX_ARGUMENTO);
	while(i < largo){

		resultado[j] = original[i];
		i++;
		j++;
	}
}

/*Pre-condiciones: 
    "original" debe contener "delimitador".
Post-condiciones: 
    la función actualizará el valor de "resultado" segun los parámetros recibidos.*/
static void separar_y_obtener_final(char original[MAX_ARGUMENTO], char resultado[MAX_ARGUMENTO], char delimitador){
	int i = 0;
	bool encontrado = false;

	size_t largo = strlen(original);

	while( (i < largo) && !encontrado ){

		if(original[i] == delimitador){

			copiar_final(original, resultado, i+1, largo);
			encontrado = true;
		}
		i++;
	}
}

/*Pre-condiciones: 
    "original" debe contener "delimitador".
Post-condiciones: 
    la función actualizará el valor de "resultado" segun los parámetros recibidos.*/
void separar_y_obtener_primera_parte(char original[MAX_ARGUMENTO], char resultado[MAX_ARGUMENTO], char delimitador){
	size_t i = 0, largo;

	largo = strlen(original);
	limpiar_vector_caracteres(resultado, MAX_ARGUMENTO);

	while( (i < largo) && (original[i] != delimitador) ){

		resultado[i] = original[i];
		i++;
	}
}

/*Pre-condiciones: 
    "tope" debe ser > 0;
Post-condiciones: 
    la función retornará un valor entre 0 y tope.*/
static int generar_posicion(int tope){
	
	return (rand()%tope); 
}

/*Pre-condiciones: 
    "punto_cardinal" debe ser NORTE, SUR, ESTE u OESTE;
    "tope" debe ser positivo.
Post-condiciones: 
    la función modificará los valores de los punteros recibidos segun el punto cardinal.*/
void generar_entrada_y_torre_segun_pto_cardinal(char punto_cardinal, coordenada_t *entrada, coordenada_t *torre, int tope){
	
	switch(punto_cardinal){
		case ESTE:
			entrada->fil = generar_posicion(tope);
			entrada->col = tope - 1;
			torre->fil = generar_posicion(tope);
			torre->col = 0;
			break;
		case OESTE:
			entrada->fil = generar_posicion(tope);
			entrada->col = 0;
			torre->fil = generar_posicion(tope);
			torre->col = tope - 1;
			break;
		case NORTE:
			entrada->fil = 0;
			entrada->col = generar_posicion(tope);
			torre->fil = tope - 1;
			torre->col = generar_posicion(tope);
			break;
		case SUR:
			entrada->fil = tope - 1;
			entrada->col = generar_posicion(tope);
			torre->fil = 0;
			torre->col = generar_posicion(tope);
			break;
	}
}




//											OBTENER DATOS DE NIVELES
/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
Post-condiciones: 
    la función retorna "tamanio" que es TAMANIO_NIVEL_1, TAMANIO_NIVEL_2, TAMANIO_NIVEL_3 o TAMANIO_NIVEL_4.*/
static int tamanio_tablero_segun_nivel(int nivel){
	int tamanio;

	switch (nivel){
		case NIVEL_1:
			tamanio = TAMANIO_NIVEL_1;
			break;
		case NIVEL_2:
			tamanio = TAMANIO_NIVEL_2;
			break;
		case NIVEL_3:
			tamanio = TAMANIO_NIVEL_3;
			break;
		case NIVEL_4:
			tamanio = TAMANIO_NIVEL_4;
			break;
	}

	return tamanio;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retorna un valor que puede ser CARDINAL_NIVEL_1, CARDINAL_NIVEL_2, CARDINAL_NIVEL_3 o CARDINAL_NIVEL_4.*/
static char punto_cardinal_segun_nivel(int nivel){
	char punto_cardinal;

	switch (nivel){
		case NIVEL_1:
			punto_cardinal = CARDINAL_NIVEL_1;
			break;	
		case NIVEL_2:
			punto_cardinal = CARDINAL_NIVEL_2;
			break;
		case NIVEL_3:
			punto_cardinal = CARDINAL_NIVEL_3;
			break;
		case NIVEL_4:
			punto_cardinal = CARDINAL_NIVEL_4;
			break;
	}

	return punto_cardinal;
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función modificará el valor de nombre[] según "nivel_actual".*/
static void obtener_nombre_punto_cardinal_segun_nivel(int nivel_actual, char nombre[MAX_NOMBRE_PUNTO_CARDINAL]){
	char punto_cardinal;

	punto_cardinal = punto_cardinal_segun_nivel(nivel_actual);
	switch (punto_cardinal){
		case ESTE: 
			strcpy(nombre, "ESTE");
			break;
		case OESTE:
			strcpy(nombre, "OESTE");
			break;
		case NORTE:
			strcpy(nombre, "NORTE");
			break;
		case SUR:
			strcpy(nombre, "SUR");
			break;
	}
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retorna un valor que puede ser CANT_CAMINOS_NIVEL_1, CANT_CAMINOS_NIVEL_2, CANT_CAMINOS_NIVEL_3 o CANT_CAMINOS_NIVEL_4.*/
int cantidad_caminos_segun_nivel(int nivel){
	int cantidad;

	switch(nivel){
		case NIVEL_1:
			cantidad = CANT_CAMINOS_NIVEL_1;
			break;
		case NIVEL_2:
			cantidad = CANT_CAMINOS_NIVEL_2;
			break;
		case NIVEL_3:
			cantidad = CANT_CAMINOS_NIVEL_3;
			break;
		case NIVEL_4:
			cantidad = CANT_CAMINOS_NIVEL_4;
			break;
	}

	return cantidad;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
Post-condiciones: 
    la función retorna un valor que puede ser ENEMIGOS_NIVEL_1, ENEMIGOS_NIVEL_2, ENEMIGOS_NIVEL_3 o ENEMIGOS_NIVEL_4.*/
int enemigos_nivel_actual(int nivel){
	int enemigos;

	switch (nivel){
		case NIVEL_1:
			enemigos = ENEMIGOS_NIVEL_1;
			break;		
		case NIVEL_2:
			enemigos = ENEMIGOS_NIVEL_2;
			break;
		case NIVEL_3:
			enemigos = ENEMIGOS_NIVEL_3;
			break;
		case NIVEL_4:
			enemigos = ENEMIGOS_NIVEL_4;
			break;
	}

	return enemigos;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retorna un valor que puede ser ENANOS_NIVEL_1, ENANOS_NIVEL_2, ENANOS_NIVEL_3 o ENANOS_NIVEL_4.*/
int cant_enanos(int nivel){
	int valor;
	
	switch(nivel){
		case NIVEL_1:
			valor = ENANOS_NIVEL_1;
			break;
		case NIVEL_2:
			valor = ENANOS_NIVEL_2;
			break;
		case NIVEL_3:
			valor = ENANOS_NIVEL_3;
			break;
		case NIVEL_4:
			valor = ENANOS_NIVEL_4;
			break;
	}

	return valor;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retorna un valor que puede ser ELFOS_NIVEL_1, ELFOS_NIVEL_2, ELFOS_NIVEL_3 o ELFOS_NIVEL_4.*/
int cant_elfos(int nivel){
	int valor;

	switch(nivel){
		case NIVEL_1:
			valor = ELFOS_NIVEL_1;
			break;
		case NIVEL_2:
			valor = ELFOS_NIVEL_2;
			break;
		case NIVEL_3:
			valor = ELFOS_NIVEL_3;
			break;
		case NIVEL_4:
			valor = ELFOS_NIVEL_4;
			break;
	}

	return valor;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retornará ENEMIGOS_DEFENSOR_EXTRA_NIVEL_1, ENEMIGOS_DEFENSOR_EXTRA_NIVEL_2, ENEMIGOS_DEFENSOR_EXTRA_NIVEL_3 o ENEMIGOS_DEFENSOR_EXTRA_NIVEL_4.*/
int enemigos_para_defensor_extra(int nivel){
	int enemigos_necesarios;
	
	switch (nivel){
		case NIVEL_1:
			enemigos_necesarios = ENEMIGOS_DEFENSOR_EXTRA_NIVEL_1; 
			break;
		case NIVEL_2:
			enemigos_necesarios = ENEMIGOS_DEFENSOR_EXTRA_NIVEL_2;
			break;
		case NIVEL_3:
			enemigos_necesarios = ENEMIGOS_DEFENSOR_EXTRA_NIVEL_3;
			break;
		case NIVEL_4:
			enemigos_necesarios = ENEMIGOS_DEFENSOR_EXTRA_NIVEL_4;
			break;
	}

	return enemigos_necesarios;
}

/*Pre-condiciones: 
    "nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retornará ENEMIGOS_NIVEL_1/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_1, ENEMIGOS_NIVEL_2/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_2, ENEMIGOS_NIVEL_3/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_3
    o ENEMIGOS_NIVEL_4/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_4.*/
int cant_def_extra_segun_nivel(int nivel){
	int cantidad;

	switch(nivel){
		case NIVEL_1:
			cantidad = ENEMIGOS_NIVEL_1/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_1;
			break;
		case NIVEL_2:
			cantidad = ENEMIGOS_NIVEL_2/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_2;
			break;
		case NIVEL_3:
			cantidad = ENEMIGOS_NIVEL_3/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_3;
			break;
		case NIVEL_4:
			cantidad = ENEMIGOS_NIVEL_4/ENEMIGOS_DEFENSOR_EXTRA_NIVEL_4;
			break;
	}

	return cantidad;
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retornará VERDADERO o no según nivel_actual*/
bool se_puede_agregar_elfo_segun_nivel(int nivel_actual){
	bool se_puede;
	
	switch (nivel_actual){
		case NIVEL_1:
			se_puede =  PODER_AGREGAR_ELFO_NIVEL_1;
			break;
		case NIVEL_2:
			se_puede =  PODER_AGREGAR_ELFO_NIVEL_2;
			break;
		case NIVEL_3:
			se_puede =  PODER_AGREGAR_ELFO_NIVEL_3;
			break;
		case NIVEL_4:
			se_puede =  PODER_AGREGAR_ELFO_NIVEL_4;
			break;
	}

	return se_puede;
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retornará VERDADERO o no según nivel_actual*/
bool se_puede_agregar_enano_segun_nivel(int nivel_actual){
	bool se_puede;
	
	switch (nivel_actual){
		case NIVEL_1:
			se_puede =  PODER_AGREGAR_ENANO_NIVEL_1;
			break;
		case NIVEL_2:
			se_puede =  PODER_AGREGAR_ENANO_NIVEL_2;
			break;
		case NIVEL_3:
			se_puede =  PODER_AGREGAR_ENANO_NIVEL_3;
			break;
		case NIVEL_4:
			se_puede =  PODER_AGREGAR_ENANO_NIVEL_4;
			break;
	}

	return se_puede;
}

/*Pre-condiciones: 
	"nivel" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
	"elfos_extra" y "enanos_extra" >= 0, y menores a ELFOS_EXTRA_INICIAL y ENANOS_EXTRA_INICIAL respectivamente.
Post-condiciones:
	la función devolverá VERDADERO si hay defensores según el nivel*/
bool hay_defensores_disponibles_seg_nivel(int nivel, int elfos_extra, int enanos_extra){
	bool hay;

	switch (nivel){
		case NIVEL_1:
			hay = enanos_extra > 0;
			break;
		case NIVEL_2:
			hay = elfos_extra > 0;
			break;
		case NIVEL_3:
			hay = enanos_extra > 0 || elfos_extra > 0;
			break;
		case NIVEL_4:
			hay = enanos_extra > 0 || elfos_extra > 0;
			break;
	}

	return hay;
}

/*Pre-condiciones: 
	"nivel" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
	"resistencia_torre_1" y "resistencia_torre_2" >= 0, y menores a VIDA_INICIAL_TORRE_1 y VIDA_INICIAL_TORRE_2 respectivamente.
Post-condiciones:
	la función devolverá VERDADERO según los parámetros recibidos*/
bool torres_con_suficiente_vida_seg_nivel(int nivel, torres_t torres){
	bool hay;

	switch(nivel){
		case NIVEL_1:
			hay = torres.resistencia_torre_1 > torres.costo_enanos_extra_torre_1 && torres.resistencia_torre_2 > torres.costo_enanos_extra_torre_2;
			break;
		case NIVEL_2:
			hay = torres.resistencia_torre_1 > torres.costo_elfos_extra_torre_1 && torres.resistencia_torre_2 > torres.costo_elfos_extra_torre_2;
			break;
		case NIVEL_3:
			hay = ( ( (torres.resistencia_torre_1 > torres.costo_enanos_extra_torre_1) && (torres.resistencia_torre_2 > torres.costo_enanos_extra_torre_2) )
				|| ( (torres.resistencia_torre_1 > torres.costo_elfos_extra_torre_1) && (torres.resistencia_torre_2 > torres.costo_elfos_extra_torre_2) ) );
			break;
		case NIVEL_4:
			hay = ( ( (torres.resistencia_torre_1 > torres.costo_enanos_extra_torre_1) && (torres.resistencia_torre_2 > torres.costo_enanos_extra_torre_2) )
				|| ( (torres.resistencia_torre_1 > torres.costo_elfos_extra_torre_1) && (torres.resistencia_torre_2 > torres.costo_elfos_extra_torre_2) ) );
			break;
	}

	return hay;
}

/*Pre-condiciones: 
	"nivel_actual" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones:
	la función actualizará "nombre" segun "nivel_actual"*/
void texto_comparar_nivel_segun_nivel(int nivel_actual, char nombre[MAX_NOMBRE]){
	
	switch (nivel_actual){
		case NIVEL_1: 
			strcpy(nombre, "NIVEL=1");
			break;
		case NIVEL_2:
			strcpy(nombre, "NIVEL=2");
			break;
		case NIVEL_3:
			strcpy(nombre, "NIVEL=3");
			break;
		case NIVEL_4:
			strcpy(nombre, "NIVEL=4");
			break;
	}
}





//												VALIDACIONES GENERALES

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función devolverá si los dos parámetros recibidos son iguales.*/
bool rutas_iguales(char ruta_archivo[MAX_NOMBRE_ARCHIVO], char ruta_archivo_camino[MAX_NOMBRE_ARCHIVO]){

	return (strcmp(ruta_archivo, ruta_archivo_camino) == 0);
}

/*Pre-condiciones: 
    "extension" debe ser EXTENSION_ARCHIVOS_TEXTO o EXTENSION_ARCHIVO_GRABACION.
Post-condiciones: 
    la función retorna si el nombre del archivo es igual a '."extension"'.*/
bool primera_parte_vacia(char nombre_archivo[MAX_NOMBRE_ARCHIVO], char extension[MAX_ARGUMENTO]){
	char comparacion[MAX_NOMBRE_ARCHIVO]={CARACTER_VACIO};
	
	comparacion[0] = PUNTO;
	strcat(comparacion, extension);

	return (strncmp(comparacion, nombre_archivo, strlen(comparacion)) == 0);
}

/*Pre-condiciones: 
    "extension" debe ser EXTENSION_ARCHIVOS_TEXTO o EXTENSION_ARCHIVO_GRABACION.
Post-condiciones: 
    la función retorna si la terminación del argumento es igual a "extension".*/
bool es_archivo_valido_segun_extension(char argumento[MAX_NOMBRE_ARCHIVO], char extension[MAX_ARGUMENTO]){
	size_t largo_archivo, largo_extension;
	bool valido = false;

	largo_archivo = strlen(argumento);
	largo_extension = strlen(extension);

	if(largo_archivo > largo_extension)
		valido = (strcmp(&argumento[largo_archivo-largo_extension], extension) == 0);

	return valido;
}

/*Pre-condiciones: 
	"extension" debe ser EXTENSION_ARCHIVOS_TEXTO o EXTENSION_ARCHIVOS_GRABACION.
Post-condiciones:
	la función retorna si el archivo es correcto.*/
bool nombre_archivo_ingresado_correcto(char ruta[MAX_NOMBRE_ARCHIVO], char extension[MAX_ARGUMENTO]){

	return( es_archivo_valido_segun_extension(ruta, extension) && !primera_parte_vacia(ruta, extension) );
}

/*Pre-condiciones: 
	"comparacion_1" debe ser menor a "comparacion_2".
Post-condiciones:
	la función retorna true si ese valor está entre los dos valores a comparar.*/
static bool ingreso_numero_es_correcto(int valor, int comparacion_1, int comparacion_2){

    return ((valor >= comparacion_1) && (valor <= comparacion_2));
}

/*Pre-condiciones: 
	"comparacion_1" debe ser menor a "comparacion_2".
Post-condiciones:
	la función retorna true si ese valor está entre los dos valores a comparar.*/
bool ingreso_numero_real_es_correcto(float valor, float comparacion_1, float comparacion_2){

    return ((valor >= comparacion_1) && (valor <= comparacion_2));
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función retornará VERDADERO si el primer parámetro ("letra") es igual a alguno de los dos valores a comparar.*/
bool ingreso_letra_es_correcto_2(char letra, char comparacion_1,  char comparacion_2){

    return ( (letra == comparacion_1) || (letra == comparacion_2) );
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función retorna true si el primer parámetro ("letra") es igual a alguno de los cuatro valores a comparar.*/
static bool ingreso_letra_es_correcto_4(char letra, char comparacion_1, char comparacion_2, char comparacion_3, char comparacion_4){

    return ( (letra == comparacion_1) || (letra == comparacion_2) || (letra == comparacion_3) || (letra == comparacion_4) );
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función retornará si el archivo se pudo abrir para leer.*/
static bool archivo_existe(char archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* archivo_nuevo;
	bool existe = true;

	archivo_nuevo = fopen(archivo, LEER);

	if(!archivo_nuevo)
		existe = false;
	else
		fclose(archivo_nuevo);
	
	return existe;
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función retorna si "nombre_archivo" es igual a TEXTO_VALOR_DEFAULT.*/
bool es_valor_default_string(char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	int comparacion;

	comparacion = strcmp(nombre_archivo, TEXTO_VALOR_DEFAULT);

	return (comparacion == 0);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función retornará VERDADERO si letra == CAMINO_1.*/
static bool hay_camino_en_matriz(char letra){

	return (letra == CAMINO_1);
}

/*Pre-condiciones: 
    "tope" debe ser positivo;
Post-condiciones: 
    la función retorna VERDADERO si "fila" está entre 0 y "tope".*/
static bool fila_valida(int fila, int tope){

	return ( (fila >= 0) && (fila < tope) );
}

/*Pre-condiciones: 
    "tope" debe ser positivo;
Post-condiciones: 
    la función retorna VERDADERO si "columna" está entre 0 y "tope".*/
static bool columna_valida(int columna, int tope){

	return ( (columna >= 0) && (columna < tope) );
}

/*Pre-condiciones: 
    "tope" debe ser positivo;
Post-condiciones: 
    la función retorna VERDADERO si "posicion.col" o "posicion.fil" están entre 0 y "tope".*/
static bool rango_valido(int tope, coordenada_t posicion){
	
	return( fila_valida(posicion.fil, tope) && columna_valida (posicion.col, tope) );
}

/*Pre-condiciones: 
	"sig_coordenada" debe tener campos válidos.
Post-condiciones:
	la función devolverá si hay alguna posicion de camino_1 con esa "fila" y "columna".*/
bool ya_hay_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t sig_coordenada, int tope){
	bool hay = false;
	int i = 0;

	while( (!hay) && (i < tope) ){

		if( (camino[i].fil == sig_coordenada.fil) && (camino[i].col == sig_coordenada.col) )
			hay = true;
		i++;
	}

	return hay;
}

/*Pre-condiciones: 
	"torre" debe tener campos válidos;
    "tope" debe ser positivo.
Post-condiciones: 
    la función retorna si alcanzó la torre.*/
bool alcanzo_torre(coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t torre, int tope){
	
	return ( (camino[tope-1].fil == torre.fil) && (camino[tope-1].col == torre.col) );
}

/*Pre-condiciones: 
	"numero_camino" debe ser CAMINO_1 o CAMINO_2;
    "numero_nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función retorna si hay una entrada en "sig_coordenada".*/
bool hay_entradas(nivel_caminos_t nivel, int numero_camino, coordenada_t sig_coordenada, int numero_nivel){
	bool respuesta = false;

	if( (numero_camino == NUMERO_CAMINO_1) && (cantidad_caminos_segun_nivel(numero_nivel) == DOS_CAMINOS) ){
		
		if( (nivel.entrada_2.fil == sig_coordenada.fil) && (nivel.entrada_2.col == sig_coordenada.col) )
			respuesta = true;
		else if( (nivel.torre_2.fil == sig_coordenada.fil) && (nivel.torre_2.col == sig_coordenada.col) )
			respuesta = true;
	} else if(numero_camino == NUMERO_CAMINO_2){
		
		if( (nivel.entrada_1.fil == sig_coordenada.fil) && (nivel.entrada_1.col == sig_coordenada.col) )
			respuesta = true;
		else if( (nivel.torre_1.fil == sig_coordenada.fil) && (nivel.torre_1.col == sig_coordenada.col) )
			respuesta = true;
	}

	return respuesta;
}

/*Pre-condiciones: 
    "tope" debe ser positivo y menor a "MAX_LONGITUD_CAMINO".
Post-condiciones: 
    la función retorna VERDADERO si "entrada" o "torre" son CAMINO en "camino[]".*/
bool hay_camino_en_entradas (coordenada_t camino[MAX_LONGITUD_CAMINO], int tope, coordenada_t entrada, coordenada_t torre){
	bool respuesta = false;

	for (int i = 0; i < tope; i++){

		if( (camino[i].fil == entrada.fil) && (camino[i].col == entrada.col) )
			respuesta = true;
		else if( (camino[i].fil == torre.fil) && (camino[i].col == torre.col) )
			respuesta = true;
	}

	return respuesta;
}








//											FUNCIONES PRIVADAS CREAR_CONFIGURACION


/*Pre-condiciones: 
    -
Post-condiciones: 
    la función devolverá si el valor ingresado es igual a VALOR_DEFAULT.*/
bool es_valor_default_numero(int valor_ingresado){

	return (valor_ingresado == VALOR_DEFAULT);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función devolverá si el valor ingresado es igual a VALOR_DEFAULT.*/
bool es_valor_default_numero_real(float valor_ingresado){

	return (valor_ingresado == VALOR_DEFAULT);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función devolverá si el valor ingresado es divisible por "divisor".*/
bool es_divisible(int valor_ingresado, int divisor){

	return (valor_ingresado%divisor == 0);
}

/*Pre-condiciones: 
    "torre" es TORRE_1 o TORRE_2.
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de resistencia para la torre que está entre VIDA_TORRES_MIN y VIDA_TORRES_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_resistencia_torre_individual(int *resistencia_torre, int torre){
	int cont = 0;

	do{
		if(cont > 0)
			printf(ROJO "\tError: la resistencia debe ser un valor entre "VERDE"'%i'"ROJO" y "VERDE"'%i'"ROJO", además de ser divisible por "VERDE"%i"ROJO". \n" FIN, VIDA_TORRES_MIN, VIDA_TORRES_MAX, CANT_CASILLAS_CUADRO);
		printf(BLANCO "\tResistencia torre %i: " FIN, torre);
		scanf(" %i", resistencia_torre);
    	cont++;
	} while( (!ingreso_numero_es_correcto(*resistencia_torre, VIDA_TORRES_MIN, VIDA_TORRES_MAX) || !es_divisible(*resistencia_torre, CANT_CASILLAS_CUADRO))
		&& !es_valor_default_numero(*resistencia_torre) );
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función actualizará el valor del puntero recibido según los valores ingresados.*/
void obtener_resistencia_torres(resistencia_torres_t *resistencia_torres){

	printf(AMARILLO "Resistencia de las torres: \n" FIN);
	obtener_resistencia_torre_individual(&(*resistencia_torres).torre_1, NUMERO_TORRE_1);
	obtener_resistencia_torre_individual(&(*resistencia_torres).torre_2, NUMERO_TORRE_2);
}

/*Pre-condiciones: 
    "nombre_tipo_defensor" es "ELFO" o "ENANO";
    "color" es MAGENTA o AZUL.
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de cantidad de defensores por cada nivel que esté entre DEFENSOR_DE_CADA_TIPO_INICIAL_MIN y DEFENSOR_DE_CADA_TIPO_INICIAL_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_defensores_por_nivel(char* nombre_tipo_defensor, char *color, int *cantidad){
	int cont = 0;
	
	do{

		if(cont > 0)
			printf(ROJO "\t\tError: la cantidad debe ser un valor entre "VERDE"'%i'"ROJO" y "VERDE"'%i'"ROJO"\n" FIN, DEFENSOR_DE_CADA_TIPO_INICIAL_MIN, DEFENSOR_DE_CADA_TIPO_INICIAL_MAX);
		printf(BLANCO "\t\tCantidad inicial defensor %s%s" FIN": ", color, nombre_tipo_defensor);
		scanf(" %i", cantidad);
		cont++;
	} while(!ingreso_numero_es_correcto(*cantidad, DEFENSOR_DE_CADA_TIPO_INICIAL_MIN, DEFENSOR_DE_CADA_TIPO_INICIAL_MAX) && !es_valor_default_numero(*cantidad));
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función actualizará el valor del puntero recibido según los valores ingresados.*/
void obtener_defensores_inicio(configuracion_t *configuracion){
	
	printf(AMARILLO "Defensores al inicio de cada nivel: \n" FIN);
	for (int i = 0; i < CANT_NIVELES; i++){
	
		printf(BLANCO "\tNIVEL: %i\n" FIN, i+1);
		obtener_defensores_por_nivel("ELFO", AZUL, &(configuracion->elfos.cant_inicial[i]));
		obtener_defensores_por_nivel("ENANO", MAGENTA, &(configuracion->enanos.cant_inicial[i]));
	}
}

/*Pre-condiciones: 
    "nombre_tipo_defensor" es "ELFO" o "ENANO";
    "color" es MAGENTA o AZUL.
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de cantidad de defensores extras por cada nivel DEFENSOR_EXTRA_MIN y DEFENSOR_EXTRA_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_cant_def_extras(char* nombre_tipo_defensor, char *color, int *cantidad){
	int cont = 0;
	
	do{

		if(cont > 0)
			printf(ROJO "\t\tError: la cantidad debe ser un valor entre "VERDE"'%i'"ROJO" y "VERDE"'%i'"ROJO"\n" FIN, DEFENSOR_EXTRA_MIN, DEFENSOR_EXTRA_MAX);
		printf(BLANCO"\t\tCantidad %s%s" BLANCO" extras: " FIN, color, nombre_tipo_defensor);
		scanf(" %i", cantidad);
		cont++;
	} while(!ingreso_numero_es_correcto(*cantidad, DEFENSOR_EXTRA_MIN, DEFENSOR_EXTRA_MAX) && !es_valor_default_numero(*cantidad));
}

/*Pre-condiciones: 
    "torre" es TORRE_1 o TORRE_2.
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de costo por defensor que esté entre COSTO_DEFENSOR_MIN y COSTO_DEFENSOR_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_costo_torres(int torre, int *costo){
	int cont = 0;

	do{

		if(cont > 0)
			printf(ROJO "\t\tError: la cantidad debe ser un valor entre "VERDE"'%i'"ROJO" y "VERDE"'%i'"ROJO"\n" FIN, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX);
		printf(BLANCO "\t\tCosto torre %i"FIN": ", torre);
		scanf(" %i", costo);
		cont++;
	} while(!ingreso_numero_es_correcto(*costo, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX) && !es_valor_default_numero(*costo));
}

/*Pre-condiciones: 
    "nombre_defensor" es "ELFOS" o "ENANOS";
    "color" es AZUL o MAGENTA.
Post-condiciones: 
    la función actualizará el valor del puntero recibido según los valores recibidos.*/
void obtener_valores_cada_def_extra(char* nombre_defensor, char* color, int *extras, int *costo_torre_1, int *costo_torre_2){

	printf(AZUL "\t%s: \n" FIN, nombre_defensor);
	obtener_cant_def_extras(nombre_defensor, color, extras);
	obtener_costo_torres(NUMERO_TORRE_1, costo_torre_1);
	obtener_costo_torres(NUMERO_TORRE_2, costo_torre_2);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función actualizará el valor del puntero recibido según los valores ingresados.*/
void obtener_valores_def_extras(defensores_t *elfos, defensores_t *enanos){

	printf(AMARILLO "Defensores extras: \n" FIN);
	obtener_valores_cada_def_extra("ELFOS", AZUL, &(elfos->extras), &(elfos->costo.torre_1), &(elfos->costo.torre_2));
	obtener_valores_cada_def_extra("ENANOS", MAGENTA, &(enanos->extras), &(enanos->costo.torre_1), &(enanos->costo.torre_2));
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de ataque por defensor que esté entre PORCENTAJE_ATAQUE_MIN y PORCENTAJE_ATAQUE_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_ataque_defensor(char* nombre_tipo_defensor, char *color, int *ataque, char* tipo_ataque){
	int cont = 0;
	
	printf(BLANCO "\tDefensor %s%s"FIN".\n", color, nombre_tipo_defensor);
	do{

		if(cont > 0)
			printf(ROJO "\t\tError: la cantidad debe ser un valor entre "VERDE"'%i'"ROJO" y "VERDE"'%i'"ROJO"\n" FIN, PORCENTAJE_ATAQUE_MIN, PORCENTAJE_ATAQUE_MAX);
		printf(BLANCO "\t\tPorcentaje ataque %s: " FIN, tipo_ataque);
		scanf(" %i", ataque);
		cont++;
	} while(!ingreso_numero_es_correcto(*ataque, PORCENTAJE_ATAQUE_MIN, PORCENTAJE_ATAQUE_MAX) && !es_valor_default_numero(*ataque));	
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función actualizará el valor del puntero recibido según los valores ingresados.*/
void obtener_porcentajes_ataques(animos_t *ataque_elfos, animos_t *ataque_enanos){

	printf(AMARILLO "Ataque de los defensores: \n" FIN);
	obtener_ataque_defensor("ELFO", AZUL, &(ataque_elfos->fallo), "fallido");
	obtener_ataque_defensor("ELFO", AZUL, &(ataque_elfos->critico), "critico");
	obtener_ataque_defensor("ENANO", MAGENTA, &(ataque_enanos->fallo), "fallido");
	obtener_ataque_defensor("ENANO", MAGENTA, &(ataque_enanos->critico), "critico");
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de velocidad que esté entre VELOCIDAD_MIN y VELOCIDAD_MAX o sea VALOR_POR_DEFECTO.*/
void obtener_velocidad(float *velocidad){
	int cont = 0;
	
	do{

		if(cont > 0)
			printf(ROJO "Error: la velocidad debe ser un valor entre "VERDE"'%f'"ROJO" y "VERDE"'%f'"ROJO"\n" FIN, VELOCIDAD_MIN, (float)VELOCIDAD_MAX);
		printf(BLANCO "Velocidad del juego: " FIN);
		scanf(" %f", velocidad);
		cont++;
	} while(!ingreso_numero_real_es_correcto(*velocidad, VELOCIDAD_MIN, VELOCIDAD_MAX) && !es_valor_default_numero_real(*velocidad));
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modificará el valor del puntero recibido con un valor válido de un archivo que exista o VALOR_POR_DEFECTO.*/
void obtener_ruta_camino(char camino[MAX_NOMBRE_ARCHIVO], char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	int cont = 0;

	do{
		
		if(cont > 0)
			printf(ROJO "Error: el nombre del archivo no es válido\n" FIN);
		printf(BLANCO "Ingrese ruta del archivo con el camino a usar: "FIN);
		scanf(" %s", camino);
		cont++;
	} while( !es_valor_default_string(camino)
		&& (!nombre_archivo_ingresado_correcto(camino, EXTENSION_ARCHIVOS_TEXTO) || rutas_iguales(camino, nombre_archivo)) );

	if(!archivo_existe(camino))
		printf("No se olvide de crear el archivo de caminos, ya que este no existe.\n");
}

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función modificará los valores del puntero recibido por los valores ingresados por el usuario.*/
void ingresar_configuracion(configuracion_t *configuracion, char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	
	printf(BLANCO "Ahora vamos a ingresar los datos personalizados. En caso que desee alguno por default, simplemente ingrese '%i' \n" FIN, VALOR_DEFAULT);

	obtener_resistencia_torres(&(*configuracion).resistencia_torres);
	obtener_defensores_inicio(configuracion);
	obtener_valores_def_extras(&(configuracion->elfos), &(configuracion->enanos));
	obtener_porcentajes_ataques(&(configuracion->elfos.animos), &(configuracion->enanos.animos));
	obtener_velocidad(&(configuracion->velocidad));
	obtener_ruta_camino(configuracion->ruta_archivo_camino, nombre_archivo);	
}

/*Pre-condiciones:
	"tipo_defensor" es "ELFOS" o "ENANOS".
	"archivo_configuracion" es un archivo válido.
	"defensor" contiene todos sus campos con valores válidos.
Post-condiciones:
	la función escribirá "defensor" en "archivo_configuracion".*/
void guardar_defensores_inicio_config(FILE* archivo_configuracion, char* tipo_defensor, defensores_t defensor){
	int i = 0;

	fprintf(archivo_configuracion, FORMATO_DEFENSORES_INICIO_PRIMERA_PARTE, tipo_defensor, defensor.cant_inicial[i]);
	i++;
	while(i< CANT_NIVELES){

		fprintf(archivo_configuracion, ",%i", defensor.cant_inicial[i]);
		i++;
	}
	fprintf(archivo_configuracion, "\n");
}

/*Pre-condiciones:
	"configuracion" contiene todos sus valores válidos.
	"nombre_archivo" es un nombre de archivo válido (con EXTENSION_ARCHIVO_TEXTO).
Post-condiciones:
	la función escribirá "configuracion" en "nombre_archivo".*/
void guardar_configuracion(configuracion_t configuracion, char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* archivo_configuracion;

	archivo_configuracion = fopen(nombre_archivo, ESCRIBIR);

	if(!archivo_configuracion)
		printf(ROJO"Error al intentar escribir en el archivo \n"FIN);
	else{

		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_RESISTENCIA_TORRES, configuracion.resistencia_torres.torre_1, configuracion.resistencia_torres.torre_2);
		guardar_defensores_inicio_config(archivo_configuracion, "ENANOS", configuracion.enanos);
		guardar_defensores_inicio_config(archivo_configuracion, "ELFOS", configuracion.elfos);
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_ENANOS_EXTRA, configuracion.enanos.extras, configuracion.enanos.costo.torre_1, configuracion.enanos.costo.torre_2);
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_ELFOS_EXTRA, configuracion.elfos.extras, configuracion.elfos.costo.torre_1, configuracion.elfos.costo.torre_2);
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_ENANOS_ANIMO, configuracion.enanos.animos.fallo, configuracion.enanos.animos.critico);
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_ELFOS_ANIMO, configuracion.elfos.animos.fallo, configuracion.elfos.animos.critico);	
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_VELOCIDAD, configuracion.velocidad);
		fprintf(archivo_configuracion, FORMATO_CONFIGURACION_CAMINOS, configuracion.ruta_archivo_camino);	
		
		fclose(archivo_configuracion);
	}
}







//													FUNCIONES PRIVADAS CREAR_CAMINO
//VALIDACIONES

/*Pre-condiciones: 
    "punto" debe ser NORTE o SUR.
Post-condiciones: 
    la función retorna VERDADERO si "columna_1" y "columna_2" no están colocadas válidamente según "punto" o si la distancia entre ellas es < constante.*/
bool estan_a_distancia_valida(int columna_1, int columna_2, char punto, int constante){
	bool respuesta;

	if(punto == NORTE)
		respuesta = ( (columna_1 <= columna_2) && ( abs(columna_1 - columna_2) >= constante ) );
	else
		respuesta = ( (columna_2 <= columna_1) && ( abs(columna_1 - columna_2) >= constante ) );

	return respuesta;
}


//										FUNCIONES PRIVADAS MOSTRAR_PARTE_VISUAL (CREAR_CAMINO)


/*Pre-condiciones: 
    "tamanio" positivo y menor a MAX_FILAS y MAX_COLUMNAS.
Post-condiciones: 
    la función retornará un valor a partir de "tamanio".*/
static int calcular_largo_tablero(int tamanio){
	int suma = ESPACIO_COSTADOS_CUADRO;

	for (int i = 0; i < tamanio; i++)
		suma += ESPACIO_POR_CASILLA_CUADRO; 
	suma += ESPACIO_COSTADOS_CUADRO;

	return suma;
}

/*Pre-condiciones: 
    "largo_total" positivo
Post-condiciones: 
    la función mostrará la linea superior del cuadro.*/
static void mostrar_linea_superior_cuadro(int largo_total){
	
	printf(MARGEN MARGEN MARGEN MARGEN MARGEN"█");
	for(int i = 0; i < largo_total; i++)
		printf("▀");
	printf("█\n" FIN);
}

/*Pre-condiciones: 
    "cant_espacios" positivo
Post-condiciones: 
    la función mostrará "cant_espacios" espacios*/
static void mostrar_espacio(int cant_espacios){
	
	for(int i = 0; i < cant_espacios; i++)
		printf(ESPACIO);
}

/*Pre-condiciones: 
    "largo_total" positivo;
Post-condiciones: 
    la función mostrará una linea del cuadro con espacios.*/
static void mostrar_linea_vacia_cuadro(int largo_total){
	
	printf(MARGEN MARGEN MARGEN MARGEN MARGEN"█");
	mostrar_espacio(largo_total);
	printf("█\n" FIN);
}

/*Pre-condiciones: 
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones: 
    la función mostrará una línea con la enumeración de las columnas del tablero.*/
static void mostrar_cant_columnas_cuadro(int tamanio_tablero){
	
	printf(BLANCO);
	for (int i = 0; i < tamanio_tablero; i ++){
	
		if(cant_digitos(i) < cant_digitos(DECENA))
			printf(" %i ", i);
		else
			printf(" %i", i);
	}
}

/*Pre-condiciones: 
    "largo_total" positivo;
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función mostrará una linea con el nivel actual.*/
static void mostrar_linea_nivel(int largo_total, int nivel_actual){
	int texto_total, espacio, resto, cant_sub_grupos = 2;
	char nombre_punto_cardinal[MAX_NOMBRE_PUNTO_CARDINAL] = {CARACTER_VACIO}, texto_1[] = "NIVEL ", texto_2[] = " - ";

	obtener_nombre_punto_cardinal_segun_nivel(nivel_actual, nombre_punto_cardinal);
	texto_total = (largo_total- (int) strlen(texto_1) - cant_digitos(nivel_actual) - (int) strlen(texto_2) - (int) strlen(nombre_punto_cardinal));
	espacio = texto_total/cant_sub_grupos;
	resto = texto_total%cant_sub_grupos;

	printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
	mostrar_espacio(espacio);
	printf(BLANCO "%s%i%s%s" FIN , texto_1, nivel_actual, texto_2, nombre_punto_cardinal);
	mostrar_espacio(espacio + resto);
	printf("█\n" FIN);
}

/*Pre-condiciones: 
    "largo_total" positivo;
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones: 
    la función mostrará una linea del cuadro con la enumeración de las columnas del tablero.*/
static void mostrar_linea_columnas(int largo_total, int tamanio_tablero){
	int espacio, resto, texto_total, cant_sub_grupos = 2;

	texto_total = largo_total - (tamanio_tablero*ESPACIO_POR_CASILLA_CUADRO);
	espacio = texto_total/cant_sub_grupos;
	resto = texto_total%cant_sub_grupos;
	printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
	mostrar_espacio(espacio +1);
	mostrar_cant_columnas_cuadro(tamanio_tablero);
	mostrar_espacio(espacio + resto -1);
	printf("█\n"FIN);
}

/*Pre-condiciones: 
    "largo_total" positivo;    
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones: 
    la función mostrará la linea superior del tablero.*/
static void mostrar_linea_superior_tablero(int largo_total, int tamanio_tablero){
	int texto_total, espacio, resto, cant_sub_grupos = 2;
	 
	texto_total = largo_total - (tamanio_tablero*ESPACIO_POR_CASILLA_CUADRO);
	espacio = texto_total/cant_sub_grupos;
	resto = texto_total%cant_sub_grupos;
	
	printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
	mostrar_espacio(espacio);
	printf("┌");
	for(int i = 0; i < tamanio_tablero*ESPACIO_POR_CASILLA_CUADRO; i++)
		printf("─");
	printf("┐");
	mostrar_espacio(espacio - 2 + resto);
	printf("█\n" FIN);
}

/*Pre-condiciones: 
    "largo_total" positivo;
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones: 
    la función mostrará el tablero del juego según los valores de la matriz.*/
static void mostrar_filas(int largo_total, int tamanio_tablero, char matriz_camino[MAX_FILAS][MAX_COLUMNAS]){
	int espacio, texto_total, resto, cant_sub_grupos = 2;
	char valor;

	for (int i = 0; i < tamanio_tablero; i++){
		
		texto_total = largo_total - (cant_digitos(i) + 2 + tamanio_tablero*ESPACIO_POR_CASILLA_CUADRO + 1);
		espacio = texto_total/cant_sub_grupos;
		resto = texto_total%cant_sub_grupos;

		printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
		mostrar_espacio(espacio);
		printf(BLANCO "%i │" FIN, i);
		
		for(int j = 0; j < tamanio_tablero; j++){

			valor = matriz_camino[i][j];
			switch(valor){
				case ENTRADA_1:
					printf(VERDE_OSCURO " E1"FIN);
					break;
				case ENTRADA_2:
					printf(VERDE_OSCURO " E2"FIN);
					break;
				case ENTRADA:
					printf(VERDE_OSCURO " E "FIN);
					break;	
				case TORRE_1:
					printf(VERDE_OSCURO " T1"FIN);
					break;
				case TORRE_2:
					printf(VERDE_OSCURO " T2"FIN);
					break;	
				case CAMINO_1:
					printf(AMARILLO" ■ "FIN);
					break;
				case CAMINO_2:
					printf(SILVER" ■ "FIN);
					break;
				case AMBOS_CAMINOS:
					printf(GRIS" ■ "FIN);
					break;
				case NADA:
					printf(VERDE_CLARO"',´"FIN);
					break;
			}
		}
		printf("│");
		mostrar_espacio(espacio + resto);
		printf("█\n" FIN);
	}

	printf(FIN);
}

/*Pre-condiciones: 
    "largo_total" positivo;
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones: 
    la función mostrará la linea inferior del tablero.*/
static void mostrar_linea_inferior_tablero(int largo_total, int tamanio_tablero){
 	int texto_total, espacio, resto, cant_sub_grupos = 2;

 	texto_total = (tamanio_tablero*ESPACIO_POR_CASILLA_CUADRO);
	espacio = (largo_total - texto_total)/cant_sub_grupos;
	resto = (largo_total - texto_total)%cant_sub_grupos;
	printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
	mostrar_espacio(espacio);
	printf("└");
	for(int i = 0; i < tamanio_tablero*3; i++)
		printf("─");
	printf("┘");
	mostrar_espacio(espacio - 2 + resto);
	printf("█\n" FIN);
}

/*Pre-condiciones: 
    "largo_total" positivo.
Post-condiciones: 
    la función mostrará la linea inferior del cuadro.*/
static void mostrar_linea_inferior_cuadro (int largo_total){

	printf(MARGEN MARGEN MARGEN MARGEN MARGEN "█");
	
	for(int i = 0; i < largo_total; i++)
		printf("▄");

	printf("█\n" FIN);
}

/*Pre-condiciones: 
	"i" es NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4;
	"nivel.tope_camino_1" es mayor a 0;
	"tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS.
Post-condiciones:
	la función mostrará el juego actual.*/
static void mostrar_parte_visual_crear_camino(nivel_caminos_t nivel, char matriz_camino[MAX_FILAS][MAX_COLUMNAS], int tamanio_tablero, int i){
	int largo_total = calcular_largo_tablero(tamanio_tablero);
	
	mostrar_linea_superior_cuadro(largo_total);
	mostrar_linea_nivel(largo_total, i);
	mostrar_linea_vacia_cuadro(largo_total);
	mostrar_linea_vacia_cuadro(largo_total);
	mostrar_linea_columnas(largo_total, tamanio_tablero);
	mostrar_linea_superior_tablero(largo_total, tamanio_tablero);
	mostrar_filas(largo_total, tamanio_tablero, matriz_camino);
	mostrar_linea_inferior_tablero(largo_total, tamanio_tablero);
	mostrar_linea_inferior_cuadro(largo_total);	
	printf(FIN); 
}


//OTRAS

/*Pre-condiciones: 
	"entrada_letra" es ENTRADA_1 o ENTRADA_2.
	"torre_letra" es TORRE_1 o TORRE_2.
Post-condiciones:
	la función modificará matriz_camino[][] según camino[] por "entrada" y "torre" .*/
void agregar_entrada_torre_matriz_coordenadas (char matriz_camino[MAX_FILAS][MAX_COLUMNAS], coordenada_t entrada_coord, coordenada_t torre_coord, char entrada_letra, char torre_letra){
	int fila_a_modificar, columna_a_modificar;

	fila_a_modificar = entrada_coord.fil;
	columna_a_modificar = entrada_coord.col;
	matriz_camino[fila_a_modificar][columna_a_modificar] = entrada_letra;
		
	fila_a_modificar = torre_coord.fil;
	columna_a_modificar = torre_coord.col;
	matriz_camino[fila_a_modificar][columna_a_modificar] = torre_letra;
}

/*Pre-condiciones: 
	"nivel" debe ser NIVEL_1 o NIVEL_2.
Post-condiciones:
	la función devolverá TORRE_NIVEL_1 o TORRE_NIVEL_2 según "nivel".*/
static char torre_segun_nivel_un_cam(int nivel){
	char respuesta;

	if(nivel == NIVEL_1)
		respuesta = TORRE_NIVEL_1;
	else if(nivel == NIVEL_2)
		respuesta = TORRE_NIVEL_2;

	return respuesta;
}

/*Pre-condiciones: 
    "tope" positivo y menor a MAX_FILAS y MAX_COLUMNAS.
    "letra" debe ser CAMINO_1 o CAMINO_2.
Post-condiciones: 
    la función modificará los valores de matriz[][] según vector[] y "es_segundo_camino" por "letra" o AMBOS_CAMINOS.*/
static void cambiar_matriz_segun_camino(char matriz[MAX_FILAS][MAX_COLUMNAS], coordenada_t vector[MAX_LONGITUD_CAMINO], int tope, char letra, bool es_segundo_camino){
	int fila_a_modificar = VALOR_DEFAULT, columna_a_modificar = VALOR_DEFAULT;
	
	if(es_segundo_camino){

		for (int i = 0; i < tope; i++){

			fila_a_modificar = vector[i].fil;
			columna_a_modificar = vector[i].col;
			
			if(hay_camino_en_matriz(matriz[fila_a_modificar][columna_a_modificar]))
				matriz[fila_a_modificar][columna_a_modificar] = AMBOS_CAMINOS;
			else
				matriz[fila_a_modificar][columna_a_modificar] = letra;
		}
	}
	else {

		for (int i = 0; i < tope; i++){

			fila_a_modificar = vector[i].fil;
			columna_a_modificar = vector[i].col;
			matriz[fila_a_modificar][columna_a_modificar] = letra;
		}
	}
}

/*Pre-condiciones: 
    "tamanio_tablero" positivo y menor a MAX_FILAS Y MAX_COLUMNAS;
Post-condiciones: 
    la función modifica las posiciones recibidas por VACIO.*/
static void inicializar_matriz(char matriz[MAX_FILAS][MAX_COLUMNAS], int tamanio_tablero, char letra){
	
	for (int fila = 0; fila < tamanio_tablero; fila++){
		
		for (int columna = 0; columna < tamanio_tablero; columna++)		
			matriz[fila][columna] = letra;
	}
}

/*Pre-condiciones: 
    "numero_nivel" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
Post-condiciones: 
    la función mostrará el cuadro con el camino que fue ingresado.*/
void mostrar_cuadro_crear_camino(nivel_caminos_t nivel, int numero_nivel){
	int tamanio_tablero;
	char matriz_camino[MAX_FILAS][MAX_COLUMNAS];

	tamanio_tablero = tamanio_tablero_segun_nivel(numero_nivel);
	inicializar_matriz(matriz_camino, tamanio_tablero, NADA);
	cambiar_matriz_segun_camino(matriz_camino, nivel.camino_1, nivel.tope_camino_1, CAMINO_1, false);
	
	if(cantidad_caminos_segun_nivel(numero_nivel) == DOS_CAMINOS){
	
		cambiar_matriz_segun_camino(matriz_camino, nivel.camino_2, nivel.tope_camino_2, CAMINO_2, true);
		agregar_entrada_torre_matriz_coordenadas(matriz_camino, nivel.entrada_1, nivel.torre_1, ENTRADA_1, TORRE_1);
		agregar_entrada_torre_matriz_coordenadas(matriz_camino, nivel.entrada_2, nivel.torre_2, ENTRADA_2, TORRE_2);
	}
	else
		agregar_entrada_torre_matriz_coordenadas(matriz_camino, nivel.entrada_1, nivel.torre_1, ENTRADA, torre_segun_nivel_un_cam(numero_nivel));
	
	mostrar_parte_visual_crear_camino(nivel, matriz_camino, tamanio_tablero, numero_nivel);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modificará el valor del puntero recibido.*/
void pedir_casilla_camino(char *letra){

	printf(BLANCO "Movimiento (arriba '%c', derecha '%c', abajo '%c', e izquierda '%c'):\n" FIN, ARRIBA, DERECHA, ABAJO, IZQUIERDA);
	scanf(" %c", letra);
}

/*Pre-condiciones: 
    "tope_obtenido" mayor o igual a 0;
Post-condiciones: 
    la función actualizará "camino_a_cambiar" y "*tope_a_cambiar".*/
void actualizar_camino_segun_casilla(coordenada_t camino_a_cambiar[MAX_LONGITUD_CAMINO], coordenada_t camino_obtenido[MAX_LONGITUD_CAMINO], int *tope_a_cambiar, int tope_obtenido){
	
	camino_a_cambiar[tope_obtenido].fil = camino_obtenido[tope_obtenido].fil;
	camino_a_cambiar[tope_obtenido].col = camino_obtenido[tope_obtenido].col;
	*tope_a_cambiar = tope_obtenido;
}

/*Pre-condiciones: 
    "*tope" mayor o igual a 0;
    "numero_camino" es CAMINO_1 o CAMINO_2.
Post-condiciones: 
    la función actualizará el camino segun cuál sea.*/
void agregar_casilla_camino(nivel_caminos_t *nivel, coordenada_t posicion_nueva, coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope, int numero_camino){
	
	camino[*tope].fil = posicion_nueva.fil;
	camino[*tope].col = posicion_nueva.col;
	(*tope)++;

	if(numero_camino == NUMERO_CAMINO_1)
		actualizar_camino_segun_casilla(nivel->camino_1, camino, &(nivel->tope_camino_1), *tope);
	else 
		actualizar_camino_segun_casilla(nivel->camino_2, camino, &(nivel->tope_camino_2), *tope);
}

/*Pre-condiciones: 
    "ultima_coordenada" debe tener sus campos válidos.
Post-condiciones: 
    la función actualizará el valor de "*sig_coordenada" según los valores recibidos.*/
void determinar_posicion_movimiento(char movimiento, coordenada_t ultima_coordenada, coordenada_t *sig_coordenada){
	
	switch(movimiento){
		case ARRIBA:
			sig_coordenada->fil = (ultima_coordenada.fil - 1);
			sig_coordenada->col = ultima_coordenada.col;
			break;
		case ABAJO:
			sig_coordenada->fil = (ultima_coordenada.fil + 1);
			sig_coordenada->col = ultima_coordenada.col;
			break;
		case DERECHA:
			sig_coordenada->fil = ultima_coordenada.fil;
			sig_coordenada->col = (ultima_coordenada.col + 1);
			break;
		case IZQUIERDA:
			sig_coordenada->fil = ultima_coordenada.fil;
			sig_coordenada->col = (ultima_coordenada.col - 1);
			break;
	}
}

/*Pre-condiciones: 
    "*cont" positivo;
    "tope" positivo;
    "tamanio_tablero" positivo y menor a MAX_FILAS y MAX_COLUMNAS;
    "numero_nivel" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4. 
Post-condiciones: 
    la función retornará un valor a partir de "tamanio".*/
void determinar_siguiente_movimiento_valido(nivel_caminos_t *nivel, coordenada_t camino[MAX_LONGITUD_CAMINO],
	int tope, coordenada_t *sig_coordenada, int tamanio_tablero, int numero_camino, int numero_nivel){
	char movimiento;
	int cont = 0;

	do{

		if(cont > 0)
			printf(ROJO "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones anteriormente mencionadas\n" FIN);
		pedir_casilla_camino(&movimiento);
		mayusculizar_letra(&movimiento);
		determinar_posicion_movimiento(movimiento, camino[tope - 1], sig_coordenada);
		(cont)++;
	} while( !ingreso_letra_es_correcto_4(movimiento, ARRIBA, ABAJO, DERECHA, IZQUIERDA)
		|| !rango_valido(tamanio_tablero, *sig_coordenada)
		|| ya_hay_camino(camino, *sig_coordenada, tope)
		|| hay_entradas(*nivel, numero_camino, *sig_coordenada, numero_nivel) );
}
		
/*Pre-condiciones: 
    "numero_camino" debe ser NUMERO_CAMINO_1 o NUMERO_CAMINO_2;
    "numero_nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
    "tope" debe ser positivo;
    "texto_camino" es "Camino: 1" o "Camino: 2".
Post-condiciones: 
    la función modifica el camino segun los valores ingresados*/
void ingresar_caminos(nivel_caminos_t *nivel, coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t entrada,
	coordenada_t torre, int numero_camino, int tope, int numero_nivel, int cant_caminos){
	int tamanio_tablero;
	coordenada_t sig_coordenada;
	
	tamanio_tablero = tamanio_tablero_segun_nivel(numero_nivel);
	
	agregar_casilla_camino(nivel, entrada, camino, &(tope), numero_camino);
	while(!alcanzo_torre(camino, torre, tope)){
		
		printf(BLANCO "Camino:"VERDE" %i"BLANCO"/%i\n\tLa entrada y la salida ya están marcadas, con color verde. Se encuentra parado en la entrada.\n" FIN, numero_camino, cant_caminos);
		mostrar_cuadro_crear_camino(*nivel, numero_nivel);
		determinar_siguiente_movimiento_valido(nivel, camino, tope, &sig_coordenada, tamanio_tablero, numero_camino, numero_nivel);
		agregar_casilla_camino(nivel, sig_coordenada, camino, &(tope), numero_camino);
		system("clear");
	}
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modifica todos los valores de las posiciones recibidas por VACIO*/
void limpiar_camino(coordenada_t vector[MAX_LONGITUD_CAMINO]){
	
	for (int i = 0; i < MAX_LONGITUD_CAMINO; i++){
	
		vector[i].fil = VACIO;
		vector[i].col = VACIO;
	}
}

/*Pre-condiciones:
	"cant_caminos" debe ser UN_CAMINO o DOS_CAMINOS;
	"punto_cardinal" es ESTE, OESTE, NORTE o SUR;
    "numero_nivel" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con los caminos generados.*/
void generar_entrada_torre_caminos(int cant_caminos, char punto_cardinal, nivel_caminos_t *nivel, int numero_nivel){
	int tamanio_tablero = tamanio_tablero_segun_nivel(numero_nivel);
	
	if(cant_caminos == DOS_CAMINOS){

		do{

			generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &(nivel->entrada_1), &(nivel->torre_1), tamanio_tablero);
			generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &(nivel->entrada_2), &(nivel->torre_2), tamanio_tablero);
		} while( ( !estan_a_distancia_valida(nivel->torre_1.col, nivel->torre_2.col, punto_cardinal, DISTANCIA_TORRES) )
			|| ( !estan_a_distancia_valida(nivel->entrada_1.col, nivel->entrada_2.col, punto_cardinal, DISTANCIA_ENTRADA) ) );	
	} else
		generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &(nivel->entrada_1), &(nivel->torre_1), tamanio_tablero);
}

/*Pre-condiciones: 
	"numero_nivel" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
	"cant_caminos" es UN_CAMINO o DOS_CAMINOS.
Post-condiciones: 
    la función modificará los valores del puntero recibido.*/
void inicializar_nivel_para_caminos(nivel_caminos_t *nivel, int numero_nivel, int cant_caminos){
	char punto_cardinal;
	
	punto_cardinal = punto_cardinal_segun_nivel(numero_nivel);
	
	nivel->tope_camino_1 = VALOR_NULO;
	nivel->tope_camino_2 = VALOR_NULO;
	limpiar_camino(nivel->camino_1);
	limpiar_camino(nivel->camino_2);
	generar_entrada_torre_caminos(cant_caminos, punto_cardinal, nivel, numero_nivel);
}

/*Pre-condiciones: 
	"*nivel_actual" debe ser NIVEL_SIN_INICIAR, NIVEL_1, NIVEL_2 o NIVEL_3.
Post-condiciones: 
    la función modificará el valor recibido y mostrará un mensaje.*/
void avanzar_nivel(int *nivel_actual){
	
	(*nivel_actual)++;
    mostrar_mensaje_nivel_actual(*nivel_actual);
}

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función mostrará un mensaje por pantalla.*/
void mensaje_segundo_camino(){

	printf(VERDE "Terminó de ingresar CAMINO 1\n" FIN);
	fflush(stdout);
	detener_el_tiempo(TIEMPO_GENERAL);
}

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función modificará los valores del puntero recibido por los valores ingresados por el usuario.*/
void obtener_caminos_niveles(nivel_caminos_t nivel[CANT_NIVELES]){
	int cant_caminos, numero_nivel = 0, pos;

	while(numero_nivel < CANT_NIVELES){
		
		avanzar_nivel(&numero_nivel);
		pos = numero_nivel - 1;
		cant_caminos = cantidad_caminos_segun_nivel(numero_nivel);
		inicializar_nivel_para_caminos(&nivel[pos], numero_nivel, cant_caminos);
		ingresar_caminos(&nivel[pos], nivel[pos].camino_1, nivel[pos].entrada_1, nivel[pos].torre_1,
			NUMERO_CAMINO_1, nivel[pos].tope_camino_1, numero_nivel, cant_caminos);
		if(cant_caminos == DOS_CAMINOS){

			mensaje_segundo_camino();
			ingresar_caminos(&nivel[pos], nivel[pos].camino_2, nivel[pos].entrada_2, nivel[pos].torre_2,
				NUMERO_CAMINO_2, nivel[pos].tope_camino_2, numero_nivel, cant_caminos);
		}
	}
}

/*Pre-condiciones:
	"tope" es positivo;
	"fila" y "columna" positivos y menores a MAX_FILAS y MAX_COLUMNAS; 
	"archivo_camino" está abierto.
Post-condiciones:
	la función escribirá las coordenadas de los caminos.*/
void escribir_coordenadas_caminos(int tope, FILE* archivo_camino, coordenada_t camino[MAX_LONGITUD_CAMINO]){

	for (int j = 0; j < tope; j++)
		fprintf(archivo_camino, "%i;%i\n", (camino[j].fil), (camino[j].col));		
}

/*Pre-condiciones:
	"nivel" contiene todos sus valores válidos.
	"nombre_archivo" es un nombre de archivo válido (con EXTENSION_ARCHIVO_TEXTO).
Post-condiciones:
	la función escribirá "nivel" en "nombre_archivo".*/
void guardar_camino(nivel_caminos_t nivel[CANT_NIVELES], char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	FILE* archivo_camino;
	
	archivo_camino = fopen(nombre_archivo, ESCRIBIR);
	if(!archivo_camino)
		printf(ROJO"Error al intentar escribir en el archivo \n"FIN);
	else{
		
		for (int i = 0; i < CANT_NIVELES; i++){
			
			fprintf(archivo_camino, "NIVEL=%i\n", i+1);
			fprintf(archivo_camino, "CAMINO=1\n");
			escribir_coordenadas_caminos(nivel[i].tope_camino_1, archivo_camino, nivel[i].camino_1);
			if(cantidad_caminos_segun_nivel(i + 1) == DOS_CAMINOS){

				fprintf(archivo_camino, "CAMINO=2\n");
				escribir_coordenadas_caminos(nivel[i].tope_camino_2, archivo_camino, nivel[i].camino_2);
			}
		}
		fclose(archivo_camino);
	}
}





//													FUNCIONES PRIVADAS JUGAR_JUEGO 
/*Pre-condiciones: 
    -
Post-condiciones: 
    la función devolverá VERDADERO si la respuesta del usuario es SI*/
bool querer_agregar_def_extra(){
	bool querer;
	char respuesta;

	printf("Tiene la posibilidad de agregar defensores extra a cambio de puntos de vida de su torre. ¿Desea hacerlo? ('%c' para sí, '%c' para no) \n", SI, NO);
	scanf(" %c", &respuesta);
	
	mayusculizar_letra(&respuesta);

	if(respuesta == SI)
		querer = true;
	else
		querer = false;

	return querer;
}

/*Pre-condiciones:
	"nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
	"enanos_extra" y "elfos_extra" >= 0 y menores a ELFOS_EXTRA_INICIAL y ENANOS_EXTRA_INCIAL;
	"vida_torre_1" y "vida_torre_2" > 0 y menores a VIDA_TORRE_1_INICIAL y VIDA_TORRE_2_INICIAL respectivamente.
Post-condiciones:
	la función modificará el valor de la posición recibida por ELFO o ENANO.*/
void determinar_tipo_de_def_a_agregar(char *tipo, int nivel_actual, int elfos_extra, int enanos_extra, int vida_torre_1, int vida_torre_2, torres_t torres){
	char defensor;
	int cont = 0;
	
	if( se_puede_agregar_elfo_segun_nivel(nivel_actual) && (elfos_extra > 0)
		&& (vida_torre_1 > torres.costo_elfos_extra_torre_1) && (vida_torre_2 > torres.costo_elfos_extra_torre_2)
		&& se_puede_agregar_enano_segun_nivel(nivel_actual) && (enanos_extra > 0)
		&& (vida_torre_1 > torres.costo_enanos_extra_torre_1) && (vida_torre_2 > torres.costo_enanos_extra_torre_2) ){

		do{

			if(cont > 0)
				printf(ROJO"Ingreso inválido\n" FIN);
			printf("¿Desea agregar un " AZUL "ELFO" FIN " (%c) o un " MAGENTA "ENANO "FIN"(%c)?\n" FIN, ELFO, ENANO);
			scanf(" %c", &defensor);
			mayusculizar_letra(&defensor);
        	cont++;
		} while(!ingreso_letra_es_correcto_2(defensor, ENANO, ELFO));
		*tipo = defensor;
	} else if( se_puede_agregar_elfo_segun_nivel(nivel_actual) && (elfos_extra > 0)
		&& (vida_torre_1 > torres.costo_elfos_extra_torre_1) && (vida_torre_2 > torres.costo_elfos_extra_torre_2) ){
		
		printf("Defensor" AZUL " ELFO \n" FIN);
		*tipo = ELFO;
	} else{
		
		printf("Defensor" MAGENTA " ENANO \n" FIN);
		*tipo = ENANO;
	}
}

//RESTO FUNCIONES
/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modifica los valores de las posiciones recibidas según ingreso.*/
void pedir_coordenadas(coordenada_t *posicion){

	printf("Indique numero fila:\n");
	scanf("%i", &(posicion->fil));
	printf("Indique numero columna:\n");
	scanf("%i", &(posicion->col));
}

/*Pre-condiciones: 
    "tope_obtenido" debe ser positivo y menor a "MAX_LONGITUD_CAMINO".
Post-condiciones: 
    la función modifica los valores en las posiciones recibidas con "camino_obtenido" según "tope_obtenido".*/
void cargar_camino(int *tope, int tope_obtenido, coordenada_t camino[MAX_LONGITUD_CAMINO], coordenada_t camino_obtenido[MAX_LONGITUD_CAMINO]){
	
	*tope = tope_obtenido;
	for (int i = 0; i < (*tope); i++)
		camino[i] = camino_obtenido[i];
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4;
    "tamanio_tablero" positivo y menor a MAX_FILAS y MAX_COLUMNAS;
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con los caminos generados.*/
void obtener_camino_segun_nivel_por_defecto(nivel_t *nivel, int nivel_actual, int tamanio_tablero){
	int tope_camino_1, tope_camino_2, cant_caminos;
	char punto_cardinal;
	coordenada_t camino_1[MAX_LONGITUD_CAMINO], entrada_1, torre_1;
	coordenada_t camino_2[MAX_LONGITUD_CAMINO], entrada_2, torre_2;

	punto_cardinal = punto_cardinal_segun_nivel(nivel_actual);
	cant_caminos = cantidad_caminos_segun_nivel(nivel_actual);

	if(cant_caminos == DOS_CAMINOS){

		do{

			generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &entrada_1, &torre_1, tamanio_tablero);
			generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &entrada_2, &torre_2, tamanio_tablero);
		} while( ( !estan_a_distancia_valida(torre_1.col, torre_2.col, punto_cardinal, DISTANCIA_TORRES) )
			|| ( !estan_a_distancia_valida(entrada_1.col, entrada_2.col, punto_cardinal, DISTANCIA_ENTRADA) ) );	
		do{

			obtener_camino(camino_1, &tope_camino_1, entrada_1, torre_1);
			obtener_camino(camino_2, &tope_camino_2, entrada_2, torre_2);
		} while( ( hay_camino_en_entradas(camino_1, tope_camino_1,entrada_2, torre_2) )
			|| ( hay_camino_en_entradas(camino_2, tope_camino_2, entrada_1, torre_1) ) );

		cargar_camino(&(nivel->tope_camino_2), tope_camino_2, nivel->camino_2, camino_2);
	} else{

		generar_entrada_y_torre_segun_pto_cardinal(punto_cardinal, &entrada_1, &torre_1, tamanio_tablero);
		obtener_camino(camino_1, &tope_camino_1, entrada_1, torre_1);
	}
	cargar_camino(&(nivel->tope_camino_1), tope_camino_1, nivel->camino_1, camino_1);
}

/*Pre-condiciones: 
    "tipo_defensor" debe ser ELFO o ENANO;
    "cantidad_defensores" debe ser mayor a 0;
    "tamanio_tablero" debe ser mayor a 0.
Post-condiciones: 
    la función modificara los valores de las posiciones recibidas.*/
void ingresar_defensores(juego_t *juego, char tipo_defensor, char* nombre_tipo_defensor, int cantidad_defensores, int tamanio_tablero, char *color, configuracion_t configuracion){
	int cont = 0;
	coordenada_t posicion_a_cambiar;

	for (int i = 0; i < cantidad_defensores; i++){
	
		do{

			if(cont > 0)
				printf(ROJO "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones anteriormente mencionadas\n" FIN);
			printf("Defensor %s%s "FIN"(%i/%i): \n", color, nombre_tipo_defensor, i+1, cantidad_defensores);
			pedir_coordenadas(&posicion_a_cambiar);
			cont++;
		} while( ( !rango_valido(tamanio_tablero, posicion_a_cambiar) )
			|| ( agregar_defensor(&(juego->nivel), posicion_a_cambiar, tipo_defensor) == NO_POSIBLE ) );
		system("clear");
		mostrar_juego(*juego, configuracion);
		cont = 0;
	}	
}

/*Pre-condiciones: 
    "juego.nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
    "tamanio_tablero" positivo.
Post-condiciones: 
    la función modificara los valores de las posiciones recibidas.*/
void cargar_defensores(juego_t *juego, int tamanio_tablero, configuracion_t configuracion){
	int cantidad_elfos, cantidad_enanos;

	if( !configuracion.es_por_defecto && (configuracion.elfos.cant_inicial[juego->nivel_actual - 1] != POR_DEFECTO) )
		cantidad_elfos = configuracion.elfos.cant_inicial[juego->nivel_actual - 1];
	else
		cantidad_elfos = cant_elfos(juego->nivel_actual);
	
	if( !configuracion.es_por_defecto && (configuracion.enanos.cant_inicial[juego->nivel_actual - 1] != POR_DEFECTO) )
		cantidad_enanos = configuracion.enanos.cant_inicial[juego->nivel_actual - 1];
	else
		cantidad_enanos = cant_enanos(juego->nivel_actual);
	
	mostrar_juego(*juego, configuracion);

	printf("\n Ahora vamos a colocar los defensores del nivel. Le recuerdo que los valores deben ser válidos y no pueden haber defensores donde hay camino u otros defensores. \n");
	ingresar_defensores(juego, ELFO, "ELFO", cantidad_elfos, tamanio_tablero, AZUL, configuracion);
	ingresar_defensores(juego, ENANO, "ENANO", cantidad_enanos, tamanio_tablero, MAGENTA, configuracion);

	printf(VERDE"Ingreso finalizado exitosamente\n"FIN);
	detener_el_tiempo(TIEMPO_ENTRE_DEFENSORES);
	system("clear");
}

/*Pre-condiciones: 
    "*archivo_camino" debe existir y ser un archivo válido.
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con el camino leído.*/
void extraer_camino_individual(FILE* archivo_camino, int *tope_camino_original, coordenada_t camino_original[MAX_LONGITUD_CAMINO]){
	int numero_camino, leidos, tope_camino = 0;
	coordenada_t camino[MAX_LONGITUD_CAMINO];
	
	leidos = fscanf(archivo_camino, "CAMINO=%i\n", &numero_camino);
	
	leidos = fscanf(archivo_camino, "%i;%i\n", &(camino[tope_camino].fil), &(camino[tope_camino].col));
	do {

		tope_camino++;
		leidos = fscanf(archivo_camino, "%i;%i\n", &(camino[tope_camino].fil), &(camino[tope_camino].col));
	} while(leidos == 2);
	cargar_camino(tope_camino_original, tope_camino, camino_original, camino);
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4;
    "*archivo_camino" debe existir y ser un archivo válido.
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con los caminos leidos.*/
void extraer_caminos_nivel_actual(nivel_t *nivel, int nivel_actual, FILE* archivo_camino){
	int cant_caminos;

	cant_caminos = cantidad_caminos_segun_nivel(nivel_actual);

	extraer_camino_individual(archivo_camino, &(nivel->tope_camino_1), nivel->camino_1);
	if(cant_caminos == DOS_CAMINOS)
		extraer_camino_individual(archivo_camino, &(nivel->tope_camino_2), nivel->camino_2);
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4;
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con los caminos leidos.*/
void leer_archivo_camino_nivel(nivel_t *nivel, int nivel_actual, char ruta_camino[MAX_NOMBRE_ARCHIVO]){
	int leidos;
	char texto_obtenido[MAX_TEXTO], texto_comparar[MAX_TEXTO];
	bool encontrado;
	FILE* archivo_camino;

	archivo_camino = fopen(ruta_camino, LEER);//Recién validé que se puedan leer
	
	texto_comparar_nivel_segun_nivel(nivel_actual, texto_comparar);
	leidos = fscanf(archivo_camino, "%[^\n]\n", texto_obtenido);		
	while(leidos != EOF && !encontrado){

		if(strncmp(texto_obtenido, texto_comparar, strlen(texto_comparar)) == 0){
			
			extraer_caminos_nivel_actual(nivel, nivel_actual, archivo_camino);
			encontrado = true;
		}
		leidos = fscanf(archivo_camino, "%[^\n]\n", texto_obtenido);		
	}
	fclose(archivo_camino);
}

/*Pre-condiciones: 
    "nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3, NIVEL_4;
    "tamanio_tablero" positivo y menor a MAX_FILAS y MAX_COLUMNAS;
Post-condiciones: 
    la función modificará las posiciones de "nivel" a partir de los datos obtenidos, con los caminos generados o leidos.*/
void obtener_camino_segun_nivel(nivel_t *nivel, int nivel_actual, int tamanio_tablero, bool es_por_defecto, bool hay_ruta, char ruta_archivo[MAX_NOMBRE_ARCHIVO]){

	if( es_por_defecto || !(hay_ruta) || !archivo_existe(ruta_archivo) )
		obtener_camino_segun_nivel_por_defecto(nivel, nivel_actual, tamanio_tablero);
	else
		leer_archivo_camino_nivel(nivel, nivel_actual, ruta_archivo);
}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función modificará los valores de las posiciones recibidas con VACIO y con los valores ingresados por el usuario.*/
void inicializar_nivel(juego_t *juego, configuracion_t configuracion){
	int tamanio_tablero;

	tamanio_tablero = tamanio_tablero_segun_nivel(juego->nivel_actual);
	
	juego->nivel.tope_camino_1 = VACIO;
	juego->nivel.tope_camino_2 = VACIO;
	juego->nivel.tope_defensores = VACIO;
	juego->nivel.tope_enemigos = VACIO;
	limpiar_camino(juego->nivel.camino_1);
	limpiar_camino(juego->nivel.camino_2);
	juego->nivel.max_enemigos_nivel = enemigos_nivel_actual(juego->nivel_actual);
    
    obtener_camino_segun_nivel(&(juego->nivel), juego->nivel_actual, tamanio_tablero, configuracion.es_por_defecto, configuracion.hay_ruta_camino, configuracion.ruta_archivo_camino);
	cargar_defensores(juego, tamanio_tablero, configuracion);
}

/*Pre-condiciones: 
    "torres->resistencia_torre_1" y "torres->resistencia_torre_2" mayores a 0;
    "defensor" es ENANO o ELFO.
Post-condiciones: 
    la función modificará el valor en la posición torres->resistencia_torre_1 o torres->resistencia_torre_2 según el defensor.*/
void restar_vida_torre_del_defensor(torres_t *torres, char defensor){
	
	if(defensor == ENANO){

		torres->resistencia_torre_1 -= torres->costo_enanos_extra_torre_1;
		torres->resistencia_torre_2 -= torres->costo_enanos_extra_torre_2;
	}
	else{

		torres->resistencia_torre_1 -= torres->costo_elfos_extra_torre_1;
		torres->resistencia_torre_2 -= torres->costo_elfos_extra_torre_2;
	}
}

/*Pre-condiciones: 
    "torres->enanos_extra" y "torres->elfos_extra" mayores o iguales a 0;
    "defensor" es ENANO o ELFO.
Post-condiciones: 
    la función modificará torres->enanos_extra o torres->elfos_extra según el defensor.*/
void restar_defensor_de_def_extras(torres_t *torres, char defensor){

	if(defensor == ENANO)
		(torres->enanos_extra)--;
	else
		(torres->elfos_extra)--;
}

/*Pre-condiciones: 
	"juego" estructura con valores válidos;
		"juego->nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4;
		"juego->torres.enanos_extra" y "juego->torres.elfos_extra" >= 0 y menores a ELFOS_EXTRA_INICIAL y ENANOS_EXTRA_INCIAL;
		"juego->torres.resistencia_torre_1" y "juego->torres.resistencia_torre_2" > 0 y menores a VIDA_TORRE_1_INICIAL y VIDA_TORRE_2_INICIAL respectivamente.
Post-condiciones:
	la función modificará los valores en "juego" según los valores ingresados por el usuario.*/
void agregar_def_extra(juego_t *juego){
	char tipo;
	coordenada_t posicion_a_cambiar;
	int cont = 0;
	int tamanio_tablero = tamanio_tablero_segun_nivel(juego->nivel_actual);

	determinar_tipo_de_def_a_agregar(&tipo, juego->nivel_actual, juego->torres.elfos_extra, juego->torres.enanos_extra,
		juego->torres.resistencia_torre_1, juego->torres.resistencia_torre_2, juego->torres);
	
	do{
		if(cont > 0)
			printf(ROJO "Ingreso incorrecto, vuelva a intentarlo siguiendo las instrucciones anteriormente mencionadas\n" FIN);
		pedir_coordenadas(&posicion_a_cambiar);
		cont++;
	} while(!rango_valido(tamanio_tablero, posicion_a_cambiar) || agregar_defensor(&(juego->nivel), posicion_a_cambiar, tipo) == NO_POSIBLE);
	restar_vida_torre_del_defensor(&(juego->torres), tipo);
	restar_defensor_de_def_extras(&(juego->torres), tipo);
}

/*Pre-condiciones:
	"cant_enemigos_def_extra" debe ser != 0.
Post-condiciones:
	la función modificará el valor de "juego" si es posible y el usuario así quiere.*/
void agregar_defensores_si_es_posible(juego_t *juego, int *cant_defensores_agregar_total, int cant_enemigos_def_extra){
	
	if( ((juego->nivel.tope_enemigos)%(cant_enemigos_def_extra) == 0) && (*cant_defensores_agregar_total != 0) ) {
			
	    (*cant_defensores_agregar_total)--;
	    if( hay_defensores_disponibles_seg_nivel(juego->nivel_actual, juego->torres.elfos_extra, juego->torres.enanos_extra)
	    	&& torres_con_suficiente_vida_seg_nivel(juego->nivel_actual, juego->torres)
	    	&& querer_agregar_def_extra() )
	    	agregar_def_extra(juego);
	}
}

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_RANKING;
    argumentos con sus posiciones con valores válidos;
    "cantidad_parametros" es mayor a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX.
Post-condiciones: 
    la función mostrará el ranking y modificará el valor del puntero recibido según se pudo crear la configuracion o no.*/
void determinar_existencia_archivo_configuracion(char argumento[MAX_ARGUMENTO], bool *configuracion_es_por_defecto, char ruta_configuracion[MAX_NOMBRE_ARCHIVO]){
	char supuesta_ruta[MAX_NOMBRE_ARCHIVO];

	separar_y_obtener_final(argumento, supuesta_ruta, CARACTER_DELIMITADOR_ARGUMENTOS);
	if(!archivo_existe(supuesta_ruta)){
	
		printf(ROJO"El archivo que ingresó no existe, así que se va a tomar la configuración default.\n"FIN);
		*configuracion_es_por_defecto = true;
		detener_el_tiempo(TIEMPO_GENERAL);
	}
	else{

		strcpy(ruta_configuracion, supuesta_ruta);
		*configuracion_es_por_defecto = false;	
	}
}

/*Pre-condiciones: 
	"cantidad_parametros" es mayor a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX.
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_RANKING.
    argumentos con sus posiciones con valores válidos.
Post-condiciones: 
    la función modificará el valor de "configuracion_es_por_defecto" y si este es false, modificará "ruta_configuracion".*/
void determinar_estado_configuracion(int cantidad_parametros, char* argumentos[], bool *configuracion_es_por_defecto, char ruta_configuracion[MAX_NOMBRE_ARCHIVO]){
	char argumento_1[MAX_ARGUMENTO], argumento_2[MAX_ARGUMENTO];
	
	*configuracion_es_por_defecto = true;
	if(cantidad_parametros >= ARGUMENTO_JUGAR_CON_PARAMETROS_CANT_MIN){
		
		strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
		if( ( strncmp(argumento_1, PRIMER_ARGUMENTO_JUGAR, strlen(PRIMER_ARGUMENTO_JUGAR)) == 0 ) )			
			determinar_existencia_archivo_configuracion(argumento_1, configuracion_es_por_defecto, ruta_configuracion);
		else if(cantidad_parametros == CANT_ARGUMENTOS_COMANDO_JUGAR_MAX){

			strcpy(argumento_2, argumentos[POSICION_ARGUMENTO_2]);
			determinar_existencia_archivo_configuracion(argumento_2, configuracion_es_por_defecto, ruta_configuracion);
		}
	}
}

/*Pre-condiciones: 
	"cantidad_parametros" es mayor a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX.
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_RANKING.
    argumentos con sus posiciones con valores válidos.
Post-condiciones: 
    la función devolverá si hay un valor a listar, y si lo hay, modificará el valor de "*cantidad".*/
bool hay_cantidad_a_listar(int cantidad_parametros, char* argumentos[], int *cantidad){
	char argumento_1[MAX_ARGUMENTO] = {CARACTER_VACIO}, argumento_2[MAX_ARGUMENTO] = {CARACTER_VACIO}, cantidad_texto[MAX_ARGUMENTO];
	bool hay_cantidad = false;

	strcpy(cantidad_texto, TEXTO_DEFAULT);
	if(cantidad_parametros >= ARGUMENTO_VER_RANKING_CON_PARAMETROS_CANT_MIN){

		strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
		if( ( strncmp(argumento_1, PRIMER_ARGUMENTO_VER_RANKING, strlen(PRIMER_ARGUMENTO_VER_RANKING)) == 0 ) )			
			separar_y_obtener_final(argumento_1, cantidad_texto, CARACTER_DELIMITADOR_ARGUMENTOS);
		else if(cantidad_parametros == CANT_ARGUMENTOS_COMANDO_VER_RANKING_MAX){

			strcpy(argumento_2, argumentos[POSICION_ARGUMENTO_2]);
			separar_y_obtener_final(argumento_2, cantidad_texto, CARACTER_DELIMITADOR_ARGUMENTOS);
		}
	}

	if(strcmp(cantidad_texto, TEXTO_DEFAULT) != 0){

		*cantidad = atoi(cantidad_texto);
		if(*cantidad != 0)
			hay_cantidad = true;
		else{
			
			printf(ROJO"La cantidad es inválida, se listará toda la lista.\n"FIN);
 			fflush(stdout);
			detener_el_tiempo(TIEMPO_GENERAL);
		}
	}

	return hay_cantidad;
}

/*Pre-condiciones: 
	"cantidad_parametros" es mayor a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_JUGAR_MAX.
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_JUGAR.
    argumentos con sus posiciones con valores válidos.
Post-condiciones: 
    la función modificará el valor de "se_graba" y si este es verdadero, modificará "ruta_grabacion".*/
void determinar_estado_grabacion(int cantidad_parametros, char* argumentos[], bool *se_graba, char ruta_grabacion[MAX_NOMBRE_ARCHIVO]){
	char argumento_1[MAX_ARGUMENTO];
	
	*se_graba = false;
	if(cantidad_parametros >= ARGUMENTO_JUGAR_CON_PARAMETROS_CANT_MIN){
		
		strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
		*se_graba = ( ( strncmp(argumento_1, SEGUNDO_ARGUMENTO_JUGAR, strlen(SEGUNDO_ARGUMENTO_JUGAR)) == 0 ) );
		if( (cantidad_parametros == CANT_ARGUMENTOS_COMANDO_JUGAR_MAX) && !(*se_graba) ){
		
			*se_graba = true;
			strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_2]);
		}
	}

	if(*se_graba)
		separar_y_obtener_final(argumento_1, ruta_grabacion, CARACTER_DELIMITADOR_ARGUMENTOS);
}

/*Pre-condiciones: 
	"*archivo_configuracion" debe existir y estar en modo LEER..
Post-condiciones: 
    la función modificará "*defensor" con los valores leídos.*/
void obtener_defensores_inicio_config(FILE* archivo_configuracion, defensores_t *defensor){
	int i = 0;

	fscanf(archivo_configuracion, "=%i", &(defensor->cant_inicial[i]));
	i++;
	while(i < CANT_NIVELES){

		fscanf(archivo_configuracion, ",%i", &(defensor->cant_inicial[i]));
		i++;
	}
	fscanf(archivo_configuracion, "\n");
}

/*Pre-condiciones: 
	"ruta_configuracion" debe existir y ser válida, con sus valores ingresados como se debe.
Post-condiciones: 
    la función modificará el valor de "*configuracion" con los valores del archivo leído.*/
void obtener_configuracion_personalizada(char ruta_configuracion[MAX_NOMBRE_ARCHIVO], configuracion_t *configuracion){
	int leidos;
	char texto[MAX_TEXTO];
	FILE* archivo_configuracion = fopen(ruta_configuracion, LEER);
	
	if(!archivo_configuracion){

		printf(ROJO"Error al intentar leer el archivo de configuracion, la configuracion será por defecto."FIN);
		configuracion->es_por_defecto = true;
		detener_el_tiempo(TIEMPO_GENERAL);
	} else{

		leidos = fscanf(archivo_configuracion, "%[^=]", texto);
		while(leidos != EOF){

			if(strcmp(texto, "RESISTENCIA_TORRES") == 0)
				leidos = fscanf(archivo_configuracion, "=%i,%i\n", &(configuracion->resistencia_torres.torre_1), &(configuracion->resistencia_torres.torre_2));
			else if(strcmp(texto, "ENANOS_INICIO") == 0)
				obtener_defensores_inicio_config(archivo_configuracion, &(configuracion->enanos));
			else if(strcmp(texto, "ELFOS_INICIO") == 0)
				obtener_defensores_inicio_config(archivo_configuracion, &(configuracion->elfos));
			else if(strcmp(texto, "ENANOS_EXTRA") == 0)
				leidos = fscanf(archivo_configuracion, "=%i,%i,%i\n", &(configuracion->enanos.extras), &(configuracion->enanos.costo.torre_1), &(configuracion->enanos.costo.torre_2));
			else if(strcmp(texto, "ELFOS_EXTRA") == 0)
				leidos = fscanf(archivo_configuracion, "=%i,%i,%i\n", &(configuracion->elfos.extras), &(configuracion->elfos.costo.torre_1), &(configuracion->elfos.costo.torre_2));
			else if(strcmp(texto, "ENANOS_ANIMO") == 0)
				leidos = fscanf(archivo_configuracion, "=%i,%i\n", &(configuracion->enanos.animos.fallo), &(configuracion->enanos.animos.critico));			
			else if(strcmp(texto, "ELFOS_ANIMO") == 0)			
				leidos = fscanf(archivo_configuracion, "=%i,%i\n", &(configuracion->elfos.animos.fallo), &(configuracion->elfos.animos.critico));	
			else if(strcmp(texto, "VELOCIDAD") == 0)			
				leidos = fscanf(archivo_configuracion, "=%f\n", &(configuracion->velocidad));
			else if(strcmp(texto, "CAMINOS") == 0)			
				leidos = fscanf(archivo_configuracion, "=%s\n", configuracion->ruta_archivo_camino);	

			leidos = fscanf(archivo_configuracion, "%[^=]", texto);
		}
		fclose(archivo_configuracion);

		if(!es_valor_default_string(configuracion->ruta_archivo_camino) && archivo_existe(configuracion->ruta_archivo_camino))
			configuracion->hay_ruta_camino = true;
		else
			configuracion->hay_ruta_camino = false;
	}
}

/*Pre-condiciones: 
	"elfos.fallo", "enanos.fallo", "elfos.critico" y "enanos.critico" deben ser POR_DEFECTO o PERSONALIZADO.
Post-condiciones: 
    la función modificará el valor de "*viento", "*humedad", "*animo_legolas" y "*animo_gimli" con POR_DEFECTO, CARACTER_POR_DEFECTO, PERSONALIZADO o CARACTER_PERSONALIZADO segun corresponda.*/
void determinar_preguntas_para_jugar(bool es_por_defecto, animos_t elfos, animos_t enanos, int *viento, int *humedad, char *animo_legolas, char *animo_gimli){

	*viento = POR_DEFECTO;
	*humedad = POR_DEFECTO;
	*animo_legolas = CARACTER_POR_DEFECTO;
	*animo_gimli = CARACTER_POR_DEFECTO;
		
	if(!es_por_defecto){
		
		if(elfos.fallo != POR_DEFECTO)
			*viento = PERSONALIZADO; 
		if(enanos.fallo != POR_DEFECTO)
			*humedad = PERSONALIZADO;
		if(elfos.critico != POR_DEFECTO)
			*animo_legolas = CARACTER_PERSONALIZADO;
		if(enanos.critico != POR_DEFECTO)
			*animo_gimli = CARACTER_PERSONALIZADO;
	}
}

/*Pre-condiciones: 
	"velocidad_config" debe ser o POR_DEFECTO o un valor entre VELOCIDAD_MIN o VELOCIDAD_MAX.
Post-condiciones: 
    la función modificará el valor de "*velocidad".*/
void determinar_velocidad_juego(float *velocidad, float velocidad_config, bool config_es_por_defecto){

	*velocidad = TIEMPO_ENTRE_TURNOS;

	if(!config_es_por_defecto && velocidad_config != POR_DEFECTO)
		*velocidad = velocidad_config;
}

/*Pre-condiciones: 
	"juego" debe ser una estructura con valores válidos:
		"juego.nivel_actual" debe ser NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
		"juego.max_enemigos_nivel" positivo y < MAX_ENEMIGOS.
		"juego->fallo_gimli", "juego->critico_gimli", "juego->fallo_legolas", "juego->critico_legolas" deben ser >= 0 y <= 100;
		"juego->torres" tiene que tener la resistencia de ambas torres > 0.
Post-condiciones:
	la función modificará "juego" según las jugadas realizadas (depende del azar mayormente) y mostrará información de cada turno jugado*/
void jugar_nivel(juego_t *juego, configuracion_t configuracion, bool se_graba, FILE* archivo_grabacion){
	int cant_enemigos_def_extra, cant_defensores_agregar_total;
	float velocidad;

	cant_enemigos_def_extra	= enemigos_para_defensor_extra(juego->nivel_actual);
    cant_defensores_agregar_total = cant_def_extra_segun_nivel(juego->nivel_actual);
	determinar_velocidad_juego(&velocidad, configuracion.velocidad, configuracion.es_por_defecto);
	while( ( estado_nivel(juego->nivel) == JUGANDO ) && ( estado_juego(*juego) == JUGANDO ) ){
    		
    	system("clear");
		if(archivo_grabacion)
			fwrite(juego, sizeof(juego_t), CANT_TURNOS_A_GRABAR_POR_REPETICION, archivo_grabacion);
		jugar_turno(juego);
		mostrar_juego(*juego, configuracion);
		detener_el_tiempo(velocidad);
		agregar_defensores_si_es_posible(juego, &cant_defensores_agregar_total, cant_enemigos_def_extra);
	}
	if(archivo_grabacion)
		fwrite(juego, sizeof(juego_t), CANT_TURNOS_A_GRABAR_POR_REPETICION, archivo_grabacion);
    
    detener_el_tiempo(TIEMPO_FINALIZACION_NIVEL);
}

/*Pre-condiciones: 
	"puntaje" debe ser positivo;
	"estado_juego(juego)" debe ser PERDIDO o GANADO.
Post-condiciones: 
    la función mostrará un ascii art, y el nombre y puntaje del jugador.*/
void mostrar_mensaje_finalizacion(juego_t juego, char nombre[MAX_NOMBRE], int puntaje){

	if(estado_juego(juego) == PERDIDO)
    	mostrar_mensaje_juego_perdido(juego.nivel_actual);
    else
    	mostrar_mensaje_juego_ganado();

    printf(BLANCO "Nombre: "VERDE"%s\n"BLANCO"Puntaje: "VERDE"%i\n" FIN, nombre, puntaje);    
}

/*Pre-condiciones:
	"puntaje_leido", "puntaje" positivos.
Post-condiciones:
	la funcióndevolverá si debería escribir el puntaje o no.*/
bool esta_desordenado(int puntaje_leido, int puntaje, char nombre_jugador_leido[MAX_NOMBRE], char nombre_jugador[MAX_NOMBRE]){
	bool desordenado = false;

	if(puntaje_leido < puntaje)
		desordenado = true;
	else if( (puntaje == puntaje_leido) && (strcmp(nombre_jugador_leido, nombre_jugador) >= 0) )
		desordenado = true;

	return desordenado;
}

/*Pre-condiciones:
	"tope_enemigos" positivo;
	"enemigos" con todos sus campos válidos.
Post-condiciones: 
    la función devolverá la cantidad de orcos muertos según en el último nivel jugado.*/
int cant_enemigos_muertos_nivel(int tope_enemigos, enemigo_t enemigos[MAX_ENEMIGOS]){
	int cont = 0;
	
	for (int i = 0; i < tope_enemigos; i++){

		if(enemigos[i].vida <= 0)
			cont++;
	}

	return cont;
}

/*Pre-condiciones:
	"defensor" con todos sus valores válidos.
Post-condiciones: 
    la función devolverá la cantidad de defensores al inicio totales.*/
int defensores_inicio_totales(defensores_t defensor){
	int cantidad = 0;

	for (int i = 0; i < CANT_NIVELES; i++)
		cantidad += defensor.cant_inicial[i];

	return cantidad;
}

/*Pre-condiciones:
	"juego" y "configuracion" con todos sus valores válidos.
		"juego.nivel_actual" es NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4.
Post-condiciones: 
    la función devolverá la cantidad de orcos muertos según el nivel.*/
int cant_enemigos_muertos_total(juego_t juego){
	int cantidad = 0;

	switch (juego.nivel_actual){
		case NIVEL_1:
			cantidad = cant_enemigos_muertos_nivel(juego.nivel.tope_enemigos, juego.nivel.enemigos);
			break;
		case NIVEL_2:
			cantidad = cant_enemigos_muertos_nivel(juego.nivel.tope_enemigos, juego.nivel.enemigos) + ENEMIGOS_NIVEL_1;
			break;
		case NIVEL_3:
			cantidad = cant_enemigos_muertos_nivel(juego.nivel.tope_enemigos, juego.nivel.enemigos) + ENEMIGOS_NIVEL_1 + ENEMIGOS_NIVEL_2;
			break;
		case NIVEL_4:
			cantidad = cant_enemigos_muertos_nivel(juego.nivel.tope_enemigos, juego.nivel.enemigos) + ENEMIGOS_NIVEL_1 + ENEMIGOS_NIVEL_2 + ENEMIGOS_NIVEL_3;
			break;
	}

	return cantidad;
}

/*Pre-condiciones:
	"juego" y "configuracion" con todos sus valores válidos.
Post-condiciones: 
    la función devolverá un puntaje calculado a partir de los parámetros ingresados.*/
int puntaje_obtenido(juego_t juego, configuracion_t configuracion){
	int puntaje;

	puntaje = cant_enemigos_muertos_total(juego) * 1000;
	puntaje /= (configuracion.resistencia_torres.torre_1 + configuracion.resistencia_torres.torre_2 + defensores_inicio_totales(configuracion.elfos)
		+ defensores_inicio_totales(configuracion.enanos)+ configuracion.enanos.extras + configuracion.elfos.extras);
	
	return puntaje;
}

/*Pre-condiciones:
	-
Post-condiciones: 
    la función modificará el nombre_archivo según los parámetros recibidos.*/
void obtener_nombre_archivo_puntajes(bool es_por_defecto, char ruta_archivo[MAX_NOMBRE_ARCHIVO], char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
	char resultado[MAX_NOMBRE_ARCHIVO];
	limpiar_vector_caracteres(nombre_archivo, MAX_NOMBRE_ARCHIVO);

	if(es_por_defecto)
		strcpy(nombre_archivo, COMANDO_VER_RANKING);
	else{

		strcpy(nombre_archivo, COMANDO_VER_RANKING"_");
		separar_y_obtener_primera_parte(ruta_archivo, resultado, PUNTO);
		strcat(nombre_archivo, resultado);
	}

	strcat(nombre_archivo, EXTENSION_ARCHIVOS_PUNTAJE);
}

void escribir_puntajes_segun_corresponda(FILE* archivo_desactualizado, FILE* archivo_actualizado, int puntaje, char nombre_jugador[MAX_NOMBRE]){
	int leidos, puntaje_leido;
	char nombre_jugador_leido[MAX_NOMBRE];
	bool falta_escribir = true;

	leidos = fscanf(archivo_desactualizado, "%[^;];%i\n", nombre_jugador_leido, &puntaje_leido);
	while(leidos != EOF){

		if( falta_escribir && esta_desordenado(puntaje_leido, puntaje, nombre_jugador_leido, nombre_jugador) ) {

			fprintf(archivo_actualizado, "%s;%i\n", nombre_jugador, puntaje);
			falta_escribir = false;	
		}
		fprintf(archivo_actualizado, "%s;%i\n", nombre_jugador_leido, puntaje_leido);
		leidos = fscanf(archivo_desactualizado, "%[^;];%i\n", nombre_jugador_leido, &puntaje_leido);
	}
	if(falta_escribir)
		fprintf(archivo_actualizado, "%s;%i\n", nombre_jugador, puntaje);	
}

/*Pre-condiciones:
	"configuracion" contiene todos sus valores válidos.
		"configuracion.archivo_grabacion" es un nombre de archivo válido.
Post-condiciones:
	la función escribirá "puntaje" en un archivo segun el nombre de la configuracion.*/
void guardar_puntaje(char nombre_jugador[MAX_NOMBRE], int puntaje, configuracion_t configuracion){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO], nombre_archivo_nuevo[MAX_NOMBRE_ARCHIVO] = {CARACTER_VACIO};
	FILE *archivo_puntajes_desactualizado, *archivo_puntajes_actualizado, *nuevo_archivo;

	obtener_nombre_archivo_puntajes(configuracion.es_por_defecto, configuracion.ruta_archivo, nombre_archivo);
	
	if(archivo_existe(nombre_archivo)){

		strcpy(nombre_archivo_nuevo, NOMBRE_TEMPORAL);
		archivo_puntajes_desactualizado = fopen(nombre_archivo, LEER);
		archivo_puntajes_actualizado = fopen(nombre_archivo_nuevo, ESCRIBIR);
		if(archivo_puntajes_actualizado && archivo_puntajes_actualizado){ //Sé que pudo leer archivo_puntajes_desactualizado, pero pregunto de nuevo por las dudas

			escribir_puntajes_segun_corresponda(archivo_puntajes_desactualizado, archivo_puntajes_actualizado, puntaje, nombre_jugador);
			fclose(archivo_puntajes_actualizado);
			fclose(archivo_puntajes_desactualizado);
			rename(nombre_archivo_nuevo, nombre_archivo);
		} else{
		
			printf(ROJO"No se ha podido escribir el puntaje."FIN);
			detener_el_tiempo(TIEMPO_GENERAL);
		}
	} else{
			
		nuevo_archivo = fopen(nombre_archivo, ESCRIBIR);
		if(nuevo_archivo){
			
			fprintf(nuevo_archivo, "%s;%i\n", nombre_jugador, puntaje);
			fclose(nuevo_archivo);
		} else{

			printf(ROJO"No se ha podido crear un nuevo archivo para guardar el puntaje."FIN);
			detener_el_tiempo(TIEMPO_GENERAL);
		}
	}
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función convierte en mayúscula el primer caracter de "nombre" si el mismo no lo estaba; si ya estaba en mayúscula, se devolverá el mismo valor*/
void mayusculizar_primer_letra(char nombre[MAX_NOMBRE]){

	mayusculizar_letra(&nombre[0]);
}

/*Pre-condiciones:
	-
Post-condiciones:
	la función actualizará el valor de "nombre" según el valor ingresado, con la primera letra mayúscula*/
void pedir_nombre(char nombre[MAX_NOMBRE]){

	printf(BLANCO "Para comenzar, por favor ingrese su nombre\n"MAGENTA);
    scanf(" %[^\n]", nombre);
    mayusculizar_primer_letra(nombre);
}

/*Pre-condiciones: 
	"constante" positiva.
Post-condiciones: 
    la función modificará "*valor_a_cambiar" si su valor es POR_DEFECTO.*/
void obtener_valor_inicial(int *valor_a_cambiar, int constante, int min, int max){

	if(*valor_a_cambiar == POR_DEFECTO || *valor_a_cambiar < min || *valor_a_cambiar > max)
		*valor_a_cambiar = constante;
}

/*Pre-condiciones: 
	"elfos_inicial" y "enanos_inicial" debe tener los valores leidos del archivo de configuracion, y sino tener POR_DEFECTO.
Post-condiciones: 
    la función modificará los valores de "configuracion" si su valor anterior era POR_DEFECTO.*/
void obtener_valor_inicial_defensores(int elfos_inicial[CANT_NIVELES], int enanos_inicial[CANT_NIVELES]){

	for(int i = 0; i < CANT_NIVELES; i++){

		obtener_valor_inicial(&elfos_inicial[i], cant_elfos(i+1), DEFENSOR_DE_CADA_TIPO_INICIAL_MIN, DEFENSOR_DE_CADA_TIPO_INICIAL_MAX);
		obtener_valor_inicial(&enanos_inicial[i], cant_enanos(i+1), DEFENSOR_DE_CADA_TIPO_INICIAL_MIN, DEFENSOR_DE_CADA_TIPO_INICIAL_MAX);
	}
}

/*Pre-condiciones: 
	"constante" positiva.
Post-condiciones: 
    la función modificará "*torre" si su valor está mal.*/
void solucionar_si_valor_erroneo(int *torre, int constante){

	if(!es_divisible(*torre, CANT_CASILLAS_CUADRO))
		*torre = constante;
}

/*Pre-condiciones: 
	"configuracion" debe tener los valores leidos del archivo de configuracion, y sino tener POR_DEFECTO.
Post-condiciones: 
    la función modificará los valores de "configuracion" si su valor anterior era POR_DEFECTO.*/
void actualizar_configuracion_actual(configuracion_t *configuracion){

	obtener_valor_inicial(&(configuracion->resistencia_torres.torre_1), VIDA_INICIAL_TORRE_1, VIDA_TORRES_MIN, VIDA_TORRES_MAX);
	solucionar_si_valor_erroneo(&(configuracion->resistencia_torres.torre_1), VIDA_INICIAL_TORRE_1);
	
	obtener_valor_inicial(&(configuracion->resistencia_torres.torre_2), VIDA_INICIAL_TORRE_2, VIDA_TORRES_MIN, VIDA_TORRES_MAX);
	solucionar_si_valor_erroneo(&(configuracion->resistencia_torres.torre_2), VIDA_INICIAL_TORRE_2);
	
	obtener_valor_inicial_defensores(configuracion->elfos.cant_inicial, configuracion->enanos.cant_inicial);
	obtener_valor_inicial(&(configuracion->elfos.extras), ELFOS_EXTRAS_INICIAL, DEFENSOR_EXTRA_MIN, DEFENSOR_EXTRA_MAX);
	obtener_valor_inicial(&(configuracion->enanos.extras), ENANOS_EXTRAS_INICIAL, DEFENSOR_EXTRA_MIN, DEFENSOR_EXTRA_MAX);
	obtener_valor_inicial(&(configuracion->elfos.costo.torre_1), COSTO_ELFO_EXTRA_TORRE_1, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX);
	obtener_valor_inicial(&(configuracion->elfos.costo.torre_2), COSTO_ELFO_EXTRA_TORRE_2, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX);
	obtener_valor_inicial(&(configuracion->enanos.costo.torre_1), COSTO_ENANO_EXTRA_TORRE_1, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX);
	obtener_valor_inicial(&(configuracion->enanos.costo.torre_2), COSTO_ENANO_EXTRA_TORRE_2, COSTO_DEFENSOR_MIN, COSTO_DEFENSOR_MAX);
}

/*Pre-condiciones: 
	"configuracion" debe tener sus campos válidos.
Post-condiciones:
	la función representará la épica batalla entre los orcos y el equipo de Gimli y Legolas.*/
void jugar_juego(configuracion_t configuracion){
	int viento = 0, humedad = 0, puntaje;
	char animo_legolas = CARACTER_DEFAULT, animo_gimli = CARACTER_DEFAULT, nombre_jugador[MAX_NOMBRE];
	juego_t juego;
	FILE* archivo_grabacion;
	srand ((unsigned)time(NULL));

	mostrar_carga_juego();
	pedir_nombre(nombre_jugador);
	determinar_preguntas_para_jugar(configuracion.es_por_defecto, configuracion.elfos.animos, configuracion.enanos.animos, &viento, &humedad, &animo_legolas, &animo_gimli);
	animos(&viento, &humedad, &animo_legolas, &animo_gimli);
	actualizar_configuracion_actual(&configuracion);
	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli, configuracion);
	mostrar_carga_inicio_TP2(juego);
    
    if(configuracion.se_graba)
    	archivo_grabacion = fopen(configuracion.ruta_archivo_grabacion, ESCRIBIR);
    do{
    	
    	avanzar_nivel(&(juego.nivel_actual));
    	inicializar_nivel(&juego, configuracion);
		jugar_nivel(&juego, configuracion, configuracion.se_graba, archivo_grabacion);
    	
    	if( (estado_nivel(juego.nivel) == GANADO) && (estado_juego(juego) == JUGANDO) )
    		mostrar_mensaje_felicitaciones();
    } while(estado_juego(juego) == JUGANDO);
	if(archivo_grabacion)
	   	fclose(archivo_grabacion);

	puntaje = puntaje_obtenido(juego, configuracion);
    guardar_puntaje(nombre_jugador, puntaje, configuracion);
    mostrar_mensaje_finalizacion(juego, nombre_jugador, puntaje);
}





//														FUNCIONES VER GRABACION

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función devolverá si alguno de los archivos ingresados tiene una extensión inválida.*/
bool rutas_correctas(bool es_por_defecto, char ruta_configuracion[MAX_NOMBRE_ARCHIVO], bool se_graba, char ruta_grabacion[MAX_NOMBRE_ARCHIVO]){
	bool correctas = true;

	if(!es_por_defecto && se_graba){

		correctas = ( nombre_archivo_ingresado_correcto(ruta_configuracion, EXTENSION_ARCHIVOS_TEXTO)
			&& nombre_archivo_ingresado_correcto(ruta_grabacion, EXTENSION_ARCHIVOS_GRABACION) );
	}
	else if(!es_por_defecto)
		correctas = nombre_archivo_ingresado_correcto(ruta_configuracion, EXTENSION_ARCHIVOS_TEXTO);
	else if(se_graba)
		correctas = nombre_archivo_ingresado_correcto(ruta_grabacion, EXTENSION_ARCHIVOS_GRABACION);

	return correctas;
}

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función modificará el valor de "*configuracion" con POR_DEFECTO.*/
void setear_configuracion_por_defecto(configuracion_t *configuracion){

	configuracion->resistencia_torres.torre_1 = POR_DEFECTO;
	configuracion->resistencia_torres.torre_2 = POR_DEFECTO;
	for(int i = 0; i < CANT_NIVELES; i++){

		configuracion->elfos.cant_inicial[i] = POR_DEFECTO;
		configuracion->enanos.cant_inicial[i] = POR_DEFECTO;
	}
	configuracion->elfos.extras = POR_DEFECTO;
	configuracion->enanos.extras = POR_DEFECTO;
	configuracion->elfos.costo.torre_1 = POR_DEFECTO;
	configuracion->elfos.costo.torre_2 = POR_DEFECTO;
	configuracion->enanos.costo.torre_1 = POR_DEFECTO;
	configuracion->enanos.costo.torre_2 = POR_DEFECTO;
}

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_GRABACION;
    argumentos con sus posiciones con valores válidos;
Post-condiciones: 
    la función actualizará "ruta_grabacion" con el archivo de grabación.*/
void determinar_archivo_grabacion(char* argumentos[], char ruta_grabacion[MAX_NOMBRE_ARCHIVO]){
	char argumento_1[MAX_ARGUMENTO], argumento_2[MAX_ARGUMENTO];
	
	strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
	if( ( strncmp(argumento_1, PRIMER_ARGUMENTO_VER_GRABACION, strlen(PRIMER_ARGUMENTO_VER_GRABACION)) == 0 ) )			
		separar_y_obtener_final(argumento_1, ruta_grabacion, CARACTER_DELIMITADOR_ARGUMENTOS);
	else{

		strcpy(argumento_2, argumentos[POSICION_ARGUMENTO_2]);
		separar_y_obtener_final(argumento_2, ruta_grabacion, CARACTER_DELIMITADOR_ARGUMENTOS);
	}
}

/*Pre-condiciones: 
    argumentos[POSICION_COMANDO_PRINCIPAL] = COMANDO_VER_GRABACION;
    argumentos con sus posiciones con valores válidos;
    "cantidad_parametros" es mayor o igual a CANT_MINIMA_ARGUMENTOS y menor a CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX.
Post-condiciones: 
    la función actualizará "velocidad_juego" con un valor >= VELOCIDAD_MIN.*/
void determinar_velocidad_a_mostrar(int cantidad_parametros, char* argumentos[], float *velocidad_juego){
	char argumento_1[MAX_ARGUMENTO] = {CARACTER_VACIO}, argumento_2[MAX_ARGUMENTO] = {CARACTER_VACIO}, velocidad_texto[MAX_ARGUMENTO];

	strcpy(velocidad_texto, TEXTO_DEFAULT);
	
	strcpy(argumento_1, argumentos[POSICION_ARGUMENTO_1]);
	if( ( strncmp(argumento_1, SEGUNDO_ARGUMENTO_VER_GRABACION, strlen(SEGUNDO_ARGUMENTO_VER_GRABACION)) == 0 ) )			
		separar_y_obtener_final(argumento_1, velocidad_texto, CARACTER_DELIMITADOR_ARGUMENTOS);
	else if(cantidad_parametros == CANT_ARGUMENTOS_COMANDO_VER_GRABACION_MAX){

		strcpy(argumento_2, argumentos[POSICION_ARGUMENTO_2]);
		separar_y_obtener_final(argumento_2, velocidad_texto, CARACTER_DELIMITADOR_ARGUMENTOS);
	}

	if(strcmp(velocidad_texto, TEXTO_DEFAULT) == 0)
		*velocidad_juego = VELOCIDAD_GRABACION_DEFAULT;
	else{

		*velocidad_juego = (float)atof(velocidad_texto);
		if(*velocidad_juego < VELOCIDAD_MIN)
			*velocidad_juego = VELOCIDAD_GRABACION_DEFAULT;
	}
}

/*Pre-condiciones: 
	-
Post-condiciones: 
    la función actualizará configuración con los valores default de ver grabación.*/
void inicializar_configuracion_personalizado_vacio(configuracion_t *configuracion){

	configuracion->es_por_defecto = true;
	configuracion->se_graba = false;
}

/*Pre-condiciones: 
	"juego" debe contener todos sus campos válidos:
		"juego.torres.resistencia_torre_1" y "juego.torres.resistencia_torre_2" deben ser válidos.
Post-condiciones: 
    la función actualizará "*configuración".*/
void establecer_valores_iniciales(juego_t juego, configuracion_t *configuracion){

	configuracion->resistencia_torres.torre_1 = juego.torres.resistencia_torre_1;
	configuracion->resistencia_torres.torre_2 = juego.torres.resistencia_torre_2;
	if( (juego.torres.resistencia_torre_1 != VIDA_INICIAL_TORRE_1) || (juego.torres.resistencia_torre_2 != VIDA_INICIAL_TORRE_2) )
		configuracion->es_por_defecto = false;
}




//													FUNCIONES PRIVADAS VER RANKING
/*Pre-condiciones:
	"contador" < "cantidad_total", ambos positivos.
	"leidos" positivo.
Post-condiciones: 
    la función devolverá si se puede listar o no segun los parámetros ingresados.*/
bool se_puede_listar(bool hay_valor, int contador, int cantidad_total, int leidos){
	bool se_puede = false;

	if( hay_valor && (contador < cantidad_total) && (leidos != EOF) )
		se_puede = true;
	else if( !hay_valor && (leidos != EOF) )
		se_puede = true;

	return se_puede;
}




//																COMANDOS

//Pre y post en comandos.h
void ejecutar_comando_crear_configuracion(char* argumentos[], bool *se_pudo){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	configuracion_t configuracion;
	
	strcpy(nombre_archivo, argumentos[POSICION_ARCHIVO_TEXTO]);
	if(!nombre_archivo_ingresado_correcto(nombre_archivo, EXTENSION_ARCHIVOS_TEXTO)){

		printf(ROJO"Ingrese un nombre para el archivo de texto (extensión: "EXTENSION_ARCHIVOS_TEXTO").\n");
		*se_pudo = false;
		return;
	}
	ingresar_configuracion(&configuracion, nombre_archivo);
	guardar_configuracion(configuracion, nombre_archivo);
	*se_pudo = true;
}

//Pre y post en comandos.h
void ejecutar_comando_crear_camino(char* argumentos[], bool *se_pudo){
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	nivel_caminos_t nivel[CANT_NIVELES];

	strcpy(nombre_archivo, argumentos[POSICION_ARCHIVO_TEXTO]);

	if(!nombre_archivo_ingresado_correcto(nombre_archivo, EXTENSION_ARCHIVOS_TEXTO)){

		printf(ROJO"Ingrese un nombre para el archivo de texto (extensión: "EXTENSION_ARCHIVOS_TEXTO").\n");
		*se_pudo = false;
		return;
	}
	obtener_caminos_niveles(nivel);
	guardar_camino(nivel, nombre_archivo);
	*se_pudo = true;
}

//Pre y post en comandos.h
void ejecutar_comando_ver_ranking(int cantidad_parametros, char* argumentos[], bool *se_pudo){
	configuracion_t configuracion;
	char nombre_archivo[MAX_NOMBRE_ARCHIVO];
	char nombre_jugador_leido[MAX_NOMBRE];
	int cantidad = 0, contador = 0, puntaje_leido, leidos; 
	bool hay_valor;
	FILE *archivo_puntajes;

	determinar_estado_configuracion(cantidad_parametros, argumentos, &(configuracion.es_por_defecto), configuracion.ruta_archivo);
	obtener_nombre_archivo_puntajes(configuracion.es_por_defecto, configuracion.ruta_archivo, nombre_archivo);	
	if(archivo_existe(nombre_archivo)){

		archivo_puntajes = fopen(nombre_archivo, LEER);
		hay_valor = hay_cantidad_a_listar(cantidad_parametros, argumentos, &cantidad);
		leidos = fscanf(archivo_puntajes, "%[^;];%i\n", nombre_jugador_leido, &puntaje_leido);
		do{

			contador++;
			printf(BLANCO"%i:\t"VERDE"%i\t"BLANCO"%s"FIN"\n", contador, puntaje_leido, nombre_jugador_leido);
			leidos = fscanf(archivo_puntajes, "%[^;];%i\n", nombre_jugador_leido, &puntaje_leido);
		}while(se_puede_listar(hay_valor, contador, cantidad, leidos));
		if(contador < cantidad)
			printf(BLANCO"Se listó el archivo entero: no quedan valores sin listar, se listaron sus %i elementos.\n", contador);	

		fclose(archivo_puntajes);
		*se_pudo = true;
	}
	else{

		printf(ROJO"No existe el archivo pedido. \n"FIN);
		*se_pudo = false;
		detener_el_tiempo(TIEMPO_GENERAL);
	}
}

//Pre y post en comandos.h
void ejecutar_comando_ver_grabacion(int cantidad_parametros, char* argumentos[], bool *se_pudo){
	juego_t juego;
	configuracion_t configuracion;
	char ruta_archivo_grabacion[MAX_NOMBRE_ARCHIVO];
	FILE* archivo_grabacion;
	float velocidad;
	size_t leidos;

	inicializar_configuracion_personalizado_vacio(&configuracion);
	determinar_archivo_grabacion(argumentos, ruta_archivo_grabacion);
	determinar_velocidad_a_mostrar(cantidad_parametros, argumentos, &velocidad);
	
	archivo_grabacion = fopen(ruta_archivo_grabacion, LEER);
    if(!archivo_grabacion){

    	printf(ROJO"El archivo de grabacion no existe.\n"FIN);
    	*se_pudo = false;
    	return;
    }
	leidos = fread(&juego, sizeof(juego_t), CANT_TURNOS_A_GRABAR_POR_REPETICION, archivo_grabacion);
	if(leidos != TERMINO_LECTURA){ //si el archivo no está vacio

		establecer_valores_iniciales(juego, &configuracion);
		do{

			system("clear");
			mostrar_juego(juego, configuracion);
			detener_el_tiempo(velocidad);
			leidos = fread(&juego, sizeof(juego_t), CANT_TURNOS_A_GRABAR_POR_REPETICION, archivo_grabacion);	
		}while(leidos != TERMINO_LECTURA);
		*se_pudo = true;
	}
	fclose(archivo_grabacion);
}

//Pre y post en comandos.h.
void ejecutar_comando_jugar(int cantidad_parametros, char* argumentos[], bool *se_pudo){
	configuracion_t configuracion;

	determinar_estado_configuracion(cantidad_parametros, argumentos, &(configuracion.es_por_defecto), configuracion.ruta_archivo);
	determinar_estado_grabacion(cantidad_parametros, argumentos, &(configuracion.se_graba), configuracion.ruta_archivo_grabacion);
	
	if( !rutas_correctas(configuracion.es_por_defecto, configuracion.ruta_archivo, configuracion.se_graba, configuracion.ruta_archivo_grabacion) ){

		printf(ROJO"Ingrese un nombre para el archivo de texto para la configuracion (extensión: "EXTENSION_ARCHIVOS_TEXTO") y/o un nombre para el archivo de grabación con extensión: "EXTENSION_ARCHIVOS_GRABACION"\n"FIN);
		*se_pudo = false;
		return;
	}
	if(!configuracion.es_por_defecto){
	
		obtener_configuracion_personalizada(configuracion.ruta_archivo, &configuracion);
		if( configuracion.hay_ruta_camino && rutas_iguales(configuracion.ruta_archivo, configuracion.ruta_archivo_camino) ){
			
			printf(ROJO"El nombre del archivo de camino no es válido.\n"FIN);
			*se_pudo = false;
			return;
		}
	}
	else
		setear_configuracion_por_defecto(&configuracion);
	
	jugar_juego(configuracion);
	*se_pudo = true;
}