#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"

#define FIN  			"\033[0m"
#define BLANCO 			"\033[1m\033[37m"
#define AZUL 			"\033[1m\033[34m"
#define ROJO 			"\033[1m\033[31m"
#define VERDE           "\033[1m\033[32m"
#define MAGENTA 		"\033[1m\033[35m"
#define AMARILLO 		"\033[1m\033[33m"
#define SILVER          "\033[0m\033[37m"
#define GRIS            "\033[1m\033[30m"
#define SANGRIA 		"         "
#define LINEA 			"\n-------------------------------------------------\n"


#define ENSALADA 	'E'
#define HAMBURGUESA 'H'
#define PIZZA 		'P'
#define GUISO 		'G'

#define PRIMER_PERSONAJE_LETRA      'L'
#define SEGUNDO_PERSONAJE_LETRA     'G'

#define PRIMER_PERSONAJE 	"Legolas"
#define ENANO               "Gimli"
#define PRIMER_EQUIPO 		"los elfos"
#define SEGUNDO_PERSONAJE 	"Gimli"
#define SEGUNDO_EQUIPO 		"los enanos"

#define POR_DEFECTO (-1)
#define CARACTER_POR_DEFECTO '1'
#define PERSONALIZADO 0
#define CARACTER_PERSONALIZADO '0'

#define VALOR_NULO -1
#define CARACTER_NULO 'Z'

const int DIA_MES_MIN = 1;
const int DIA_MES_MAX = 30;
const int HORAS_SUENO_MIN = 0;
const int HORAS_SUENO_MAX = 12;
const int MUCHO_VIENTO = 75;
const int VIENTO_REGULAR = 50;
const int POCO_VIENTO = 25;
const int MUCHA_HUMEDAD = 75;
const int HUMEDAD_REGULAR = 50;
const int POCA_HUMEDAD = 25;
const int PUNTOS_PIE_DERECHO = 10;
const int PUNTOS_ENSALADA = 20;
const int PUNTOS_HAMBURGUESA = 15;
const int PUNTOS_PIZZA = 10;
const int PUNTOS_GUISO = 5;
const int PUNTOS_DORMIR_NORMAL = 10;
const int PUNTOS_DORMIR_MUCHO = 20;
const int MAX_PUNTOS_ANIMO_MALO = 20;
const int MAX_PUNTOS_ANIMO_REGULAR = 35;
const int MIN_DORMIR_NORMAL = 5;
const int MAX_DORMIR_NORMAL = 8;
const int MAX_DIA_MUCHO_VIENTO = 10;
const int MAX_DIA_VIENTO_REGULAR = 20;
const int CANT_OPC_PARENTESIS_MENSAJE = 5;
const int MAX_RANDOM = 12;
const char MANANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char MALO = 'M';
const char REGULAR = 'R';
const char BUENO = 'B';

/*Pre-condiciones: 
	"comparacion_1" debe ser menor a "comparacion_2".
Post-condiciones:
	la función retorna true si ese valor no está entre los dos valores a comparar.*/
bool ingreso_numero_es_incorrecto(int valor, int comparacion_1, int comparacion_2){

    return ((valor < comparacion_1) || (valor > comparacion_2));
}

/*Pre-condiciones: -.
Post-condiciones:
	la función retorna true si el primer parámetro ("letra") no es igual a ninguno de los dos valores a comparar.*/
bool ingreso_letra_es_incorrecto_2(char letra, char comparacion_1,  char comparacion_2){

    return ( (letra != comparacion_1) && (letra != comparacion_2) );
}

/*Pre-condiciones: -.
Post-condiciones:
	la función retorna true si el primer parámetro ("letra") no es igual a ninguno de los tres valores a comparar.*/
bool ingreso_letra_es_incorrecto_3(char letra,  char comparacion_1, char comparacion_2, char comparacion_3){

    return ( (letra != comparacion_1) && (letra != comparacion_2) && (letra != comparacion_3) );
}

/*Pre-condiciones: -.
Post-condiciones:
	la función retorna true si el primer parámetro ("letra") no es igual a ninguno de los cuatro valores a comparar.*/
bool ingreso_letra_es_incorrecto_4(char letra, char comparacion_1, char comparacion_2, char comparacion_3, char comparacion_4){

    return ( (letra != comparacion_1) && (letra != comparacion_2) && (letra != comparacion_3) && (letra != comparacion_4) );
}

/*Pre-condiciones: 
    -
Post-condiciones:
    la función devolverá si algún valor no es VALOR_NULO o CARACTER_NULO segun corresponda.*/
bool hubo_algun_ingreso(int dia, char momento, char pie_primer_personaje, char cena_primer_personaje, int horas_sueno_primer_personaje, char pie_segundo_personaje, char cena_segundo_personaje, int horas_sueno_segundo_personaje){

    return ( (dia != VALOR_NULO) || (momento != CARACTER_NULO)
        || (pie_primer_personaje != CARACTER_NULO) || (cena_primer_personaje != CARACTER_NULO) || (horas_sueno_primer_personaje != VALOR_NULO)
        || (pie_segundo_personaje != CARACTER_NULO) || (cena_segundo_personaje != CARACTER_NULO) || (horas_sueno_segundo_personaje != VALOR_NULO) ); 
}

/*Pre-condiciones:
    "viento" y "humedad" son PERSONALIZADO o POR_DEFECTO;
    "animo_legolas" y "animo_gimli" son CARACTER_PERSONALIZADO o CARACTER_POR_DEFECTO.
Post-condiciones: 
    la función devuelve si alguno de los valores no es PERSONALIZADO o CARACTER_PERSONALIZADO segun corresponda.*/
bool ingreso_algo(int viento, int humedad, char animo_gimli, char animo_legolas){

    return ( (viento != PERSONALIZADO) || (humedad != PERSONALIZADO) || (animo_gimli != CARACTER_PERSONALIZADO) || (animo_legolas != CARACTER_PERSONALIZADO) );
}

/*Pre-condiciones: -.
Post-condiciones:
	la función convierte en mayúscula "letra" si el mismo no lo estaba; si "letra" ya estaba en mayúscula, se devolverá el mismo valor*/
void mayusculizar_variable(char *letra){

    *letra = (char) toupper (*letra);
}

/*Pre-condiciones: 
    "numero" > 0 y "numero" < MAX_RANDOM.
Post-condiciones:
    la función muestra por pantalla un mensaje de error a partir del valor recibido*/
void mostrar_mensaje_error_general(int numero){
    
    switch (numero){
        case 0:
            printf("Ai ai, parece que lo que ingresó ");
            break;        
        case 1:
            printf("¡Paparruchas! Parece que lo que ingresó ");
            break;       
        case 2:
            printf("Recorcholis, flasheó feo, ¡nadie puede hacer eso! Lo que ingresó ");
            break;        
        case 3:
            printf("¡Por Elbereth y Lúthien la Furia!, eso que ingresó ");
            break;       
        case 4:
            printf("Nonono, usted tiene que arrepentirse de lo que dijo. Ingreso anterior ");
            break;
        case 5:
            printf("Le recomendamos revisar sus conocimientos en comprensión de textos, lo ingresado ");
            break;
        case 6:
            printf("¡Por la barba de Gandalf!, espero ahora ingrese correctamente los datos ya que ");
            break;       
        case 7:
            printf("Ingreso ");
            break;        
        case 8:
            printf("¡Por las barbas de las enanas! Se equivocó, ");
            break;
        case 9:
            printf("¡Serpientes y viboras! Ingreso ");
            break;          
        case 10:
            printf("¡Por el anillo! Ingrese lo que se le pide, ");
            break;          
        default:
            printf("Muy raro esto Willy, no sé que está sucediendo, mepa que ");
            break;
    }
}

/*Pre-condiciones: 
    "numero_random" > 0 y "numero_random" < MAX_RANDOM.
Post-condiciones:
    la función muestra por pantalla un mensaje de error a partir del segundo parámetro recibido, que incluye el valor del primer parámetro*/
void mostrar_numero_ingresado(int ingreso, int numero_random){

    if (numero_random <= CANT_OPC_PARENTESIS_MENSAJE)
        printf("('%i') no es válido, intente nuevamente. \n", ingreso);
    else
        printf("'%i' no es válido, intente nuevamente.\n", ingreso);
}

/*Pre-condiciones: 
    "numero_random" > 0 y "numero_random" < MAX_RANDOM.
Post-condiciones:
    la función muestra por pantalla un mensaje de error a partir del segundo parámetro recibido, que incluye el valor del primer parámetro*/
void mostrar_letra_ingresada(char ingreso, int numero_random){

    if (numero_random <=CANT_OPC_PARENTESIS_MENSAJE)
        printf("('%c') no es válido, intente nuevamente. \n", ingreso);
    else
        printf("'%c' no es válido, intente nuevamente.\n", ingreso);
}

/*Pre-condiciones: -.
Post-condiciones:
	la función muestra por pantalla un mensaje de error random con "ingreso*/
void mostrar_error_letra(char ingreso){
	int numero_random; 

	numero_random = rand()%MAX_RANDOM;
	printf(ROJO);
	mostrar_mensaje_error_general(numero_random);
	mostrar_letra_ingresada(ingreso, numero_random);
	printf(FIN);
}

/*Pre-condiciones: -.
Post-condiciones:
	la función muestra por pantalla un mensaje de error random con "ingreso"*/
void mostrar_error_numero(int ingreso){
	int numero_random;

	numero_random = rand()%MAX_RANDOM;
	printf(ROJO);
	mostrar_mensaje_error_general(numero_random);
	mostrar_numero_ingresado(ingreso, numero_random);
	printf(FIN);
}

/*Pre-condiciones: -.
Post-condiciones:
	la función muestra un saludo en élfico y español.*/
void presentarme(){

    printf(BLANCO "Alasse undómë usuario, ¿man vinyr colalyë? Necesito hacerle un par de preguntas y me parece una falta de respeto no presentarme antes. Mi nombre es Ana Gabriela Gutson, con su ayuda representaré la batalla del Abismo de Helm siendo los participantes" PRIMER_EQUIPO ", liderados por " PRIMER_PERSONAJE ", y " SEGUNDO_EQUIPO ", liderados por " SEGUNDO_PERSONAJE ", y deseo asegurarme de que todo salga de maravilla.\n" MAGENTA);
}

/*Pre-condiciones: -.
Post-condiciones:
	la función modica el valor de la posición recibida por un valor numérico entre DIA_MES_MIN y DIA_MES_MAX*/
void obtener_el_dia(int *dia){
    int cont = 0;

    do {

        if (cont > 0) mostrar_error_numero (*dia);
        printf(BLANCO "Para empezar necesito saber qué día del mes es hoy (indique un numero del "VERDE"%i"BLANCO" al "VERDE"%i"BLANCO" ya que en el universo del Sr. de los Anillos no existen los meses con días fuera de este rango). \n" MAGENTA, DIA_MES_MIN, DIA_MES_MAX);
        scanf(" %i", dia);
        cont++;
    }
    while(ingreso_numero_es_incorrecto(*dia, DIA_MES_MIN, DIA_MES_MAX));
    printf(BLANCO "Qué espléndido. " MAGENTA);    
}

/*Pre-condiciones: -.
Post-condiciones:
	la función modica el valor de la posición recibida por un valor que puede ser MANANA, TARDE o NOCHE*/
void obtener_el_momento(char *momento){
    int cont = 0;
    
    do{

        if (cont > 0) mostrar_error_letra (*momento);
        printf(BLANCO "Ahora debe ingresar en que momento del día nos encontramos: si estamos en la mañana ingrese "VERDE"'%c'"BLANCO" (supongo que hasta el mediodía aplica), si estamos en la tarde ingrese "VERDE"'%c'"BLANCO" (y esto será hasta las 19:00hs más o menos) y si es de noche (fijese si está todo oscuro afuera) ingrese "VERDE"'%c'"BLANCO". \n" MAGENTA, MANANA, TARDE, NOCHE);
        scanf(" %c", momento);
        mayusculizar_variable(momento);
        cont++;
    }
    while(ingreso_letra_es_incorrecto_3(*momento, MANANA, TARDE, NOCHE));
}

/*Pre-condiciones:
	"i" debe estar entre 0 y 1.
Post-condiciones:
	la función mostrará sobre quién serán las preguntas.*/
void mostrar_mensaje_inicial(char *color, char *personaje){

    printf(BLANCO "Ahora le haré preguntas sobre %s%s\n", color, personaje);
}

/*Pre-condiciones: -.
Post-condiciones:
	la función modica el valor de la posición recibida por un valor que puede ser PIE_DERECHO o PIE_IZQUIERDO*/
void obtener_pie(char *pie){
    int cont = 0;
    
    do{

        if (cont > 0) mostrar_error_letra (*pie);
        printf(BLANCO "¿Con qué pie se levantó?: si fue el derecho ingrese "VERDE"'%c'"BLANCO" y si fue el izquierdo ingrese "VERDE"'%c'"BLANCO". \n" MAGENTA, PIE_DERECHO, PIE_IZQUIERDO);
        scanf(" %c", pie);
        mayusculizar_variable(pie);
        cont++;
    }
    while(ingreso_letra_es_incorrecto_2(*pie, PIE_DERECHO, PIE_IZQUIERDO));
}

/*Pre-condiciones: -.
Post-condiciones:
	la función modica el valor de la posición recibida por un valor que puede ser ENSALADA, HAMBURGUESA, PIZZA o GUISO*/
void obtener_cena(char *cena){
    int cont = 0;

    do {

        if (cont > 0) mostrar_error_letra(*cena);
        printf(BLANCO "También necesito saber qué cenó la noche anterior: para ensalada ingrese "VERDE"'%c'"BLANCO", para hamburguesa ingrese "VERDE"'%c'"BLANCO", para pizza ingrese "VERDE"'%c'"BLANCO" y para guiso ingrese "VERDE"'%c'"BLANCO". \n" MAGENTA, ENSALADA, HAMBURGUESA, PIZZA, GUISO);
        scanf(" %c", cena);
        mayusculizar_variable(cena);
        cont++;    
    }
    while(ingreso_letra_es_incorrecto_4(*cena, ENSALADA, HAMBURGUESA, PIZZA, GUISO));
}

/*Pre-condiciones: -.
Post-condiciones:
	la función modica el valor de la posición recibida por un valor numérico el cual está entre HORAS_SUENO_MIN y HORAS_SUENO_MAX*/
void obtener_horas_sueno(int *horas){
    int cont = 0;

    do {

        if (cont > 0)
            mostrar_error_numero(*horas);
        printf(BLANCO "Por último, necesito saber cuántas horas durmió (ingrese un número del "VERDE"%i"BLANCO" al "VERDE"%i"BLANCO"). \n" MAGENTA, HORAS_SUENO_MIN, HORAS_SUENO_MAX);
        scanf(" %i", horas);
        cont++;
    }
    while(ingreso_numero_es_incorrecto(*horas, HORAS_SUENO_MIN, HORAS_SUENO_MAX));  
}

/*Pre-condiciones: 
	"pie" debe ser PIE_DERECHO o PIE_IZQUIERDO.
Post-condiciones:
	la función modica el valor de la posición recibida, entre un mínimo y máximo posible, a partir del valor del segundo parámetro ("pie").*/
void calcular_puntos_pie(int *puntos, char pie){

	if (pie == PIE_DERECHO)
        *puntos += PUNTOS_PIE_DERECHO;
}

/*Pre-condiciones: 
	"cena" debe ser ENSALADA, HAMBURGUESA, PIZZA O GUISO.
Post-condiciones: 
	la función modica el valor de la posición recibida, entre un mínimo y máximo posible, a partir del valor del segundo parámetro ("cena").*/
void calcular_puntos_cena(int *puntos, char cena){

	switch (cena){
        case ENSALADA:
            *puntos += PUNTOS_ENSALADA;
            break;
        case HAMBURGUESA:
            *puntos += PUNTOS_HAMBURGUESA;
            break;
        case PIZZA:
            *puntos += PUNTOS_PIZZA;
            break;
        case GUISO:
            *puntos += PUNTOS_GUISO;
            break;
    }
}

/*Pre-condiciones: 
	"horas" debe estar entre HORAS_SUENO_MIN y HORAS_SUENO_MAX.
Post-condiciones:
	la función modica el valor de la posición recibida, entre un mínimo y máximo posible, a partir del valor del segundo parámetro ("horas").*/
void calcular_puntos_sueno(int *puntos, int horas){

	if ((horas >= MIN_DORMIR_NORMAL) && (horas <= MAX_DORMIR_NORMAL))
		*puntos += PUNTOS_DORMIR_NORMAL;
    else if (horas > MAX_DORMIR_NORMAL)
    	*puntos += PUNTOS_DORMIR_MUCHO;
}

/*Pre-condiciones: 
    "pie" debe ser PIE_DERECHO o PIE_IZQUIERDO;
    "cena" debe ser ENSALADA, HAMBURGUESA, PIZZA O GUISO;
    "horas" debe estar entre HORAS_SUENO_MIN y HORAS_SUENO_MAX.
Post-condiciones: 
    la función retorna la cantidad de puntos, entre un mínimo y máximo posible, con base en los parámetros recibidos.*/
int puntos_total_obtenidos(char pie, char cena, int horas){
    int puntos = 0;

    calcular_puntos_pie(&puntos, pie);
    calcular_puntos_cena(&puntos, cena);
    calcular_puntos_sueno(&puntos, horas);

    return puntos;
}

/*Pre-condiciones:
	"puntos" debe ser positivo y menor al máximo posible.
Post-condiciones:
	la función modica el valor de la posición recibida con BUENO, MALO o REGULAR con base en el valor del primer parámetro.*/
void determinar_animo(int puntos, char *animo){
	
    if (puntos <= MAX_PUNTOS_ANIMO_MALO)
        *animo = MALO;
    else if (puntos <= MAX_PUNTOS_ANIMO_REGULAR)
        *animo = REGULAR;
    else
        *animo = BUENO;    
}

/*Pre-condiciones:
    "pie" debe ser PIE_DERECHO o PIE_IZQUIERDO;
    "cena" debe ser ENSALADA, HAMBURGUESA, PIZZA o GUISO;
    "horas_sueno" debe estar entre HORAS_SUENO_MIN y HORAS_SUENO_MAX.
Post-condiciones:
    la función devuelve un animo que puede ser BUENO, MALO o REGULAR*/
char animo_personaje(char pie, char cena, int horas_sueno){
    int puntos = 0;
    char animo;

    puntos = puntos_total_obtenidos(pie, cena, horas_sueno);
    determinar_animo(puntos, &animo);

    return animo;
}

/*Pre-condiciones: 
	"letra_personaje" debe ser PRIMER_PERSONAJE_LETRA o SEGUNDO_PERSONAJE_LETRA.
Post-condiciones:
	la función mostrará un mensaje con el nombre de un personaje que puede ser PRIMER_PERSONAJE o SEGUNDO_PERSONAJE, el cuál dependerá del valor recibido.*/
void mostrar_mensaje_final(char letra_personaje){

	if (letra_personaje == PRIMER_PERSONAJE_LETRA)
        printf(BLANCO "Hooray! Terminamos de ingresar los datos de " PRIMER_PERSONAJE". " BLANCO);
	else 
        printf(BLANCO "Hurrah! Finalizamos los ingresos, felicitaciones.\n" BLANCO);
}

/*Pre-condiciones: 
    "pie" deben ser CARACTER_NULO, PIE_DERECHO o PIE_IZQUIERDO,
    "cena" deben ser CARACTER_NULO, ENSALADA, HAMBURGUESA, PIZZA o GUISO,
    "horas" deben estar entre HORAS_SUENO_MIN y HORAS_SUENO_MAX, o ser VALOR_NULO.
    Alguno de los tres valores debe ser diferente de CARACTER_NULO o VALOR_NULO segun corresponda.
Post-condiciones:
    la función muestra un mensaje con todos los valores recibidos, si son diferentes a CARACTER_NULO o VALOR_NULO segun corresponda.*/
void mostrar_datos_animo_personaje(char pie, char cena, int horas, char* color, char* personaje_nombre){

    printf("·" BLANCO "Ánimo de %s%s"FIN ": \n", color, personaje_nombre);
    if (pie != CARACTER_NULO)
        printf(SANGRIA "■ " BLANCO "Pie con el que se levantó: " VERDE "%c. \n" FIN, pie);
    if (cena != CARACTER_NULO)
        printf(SANGRIA "■ " BLANCO "Cena de la noche anterior: " VERDE "%c. \n" FIN, cena);
    if (horas != VALOR_NULO)
        printf(SANGRIA "■ " BLANCO "Cantidad de horas que durmió: " VERDE "%i. \n" FIN, horas);
}

/*Pre-condiciones: 
	"dia" debe estar entre DIA_MES_MIN y DIA_MES_MAX,
	"momento" debe ser MANANA, TARDE O NOCHE,
	"pie_primer_personaje" y "pie_segundo_personaje" deben ser PIE_DERECHO o PIE_IZQUIERDO,
	"cena_primer_personaje" y "cena_segundo_personaje" deben ser ENSALADA, HAMBURGUESA, PIZZA o GUISO,
	"horas_sueno_primer_personaje" y "horas_sueno_segundo_personaje" deben estar entre HORAS_SUENO_MIN y HORAS_SUENO_MAX.
Post-condiciones:
	la función muestra un mensaje con todos los valores recibidos.*/
void mostrar_datos_ingresados(int dia, char momento, char pie_primer_personaje, char cena_primer_personaje, int horas_sueno_primer_personaje,
    char pie_segundo_personaje, char cena_segundo_personaje, int horas_sueno_segundo_personaje){
    
    if(hubo_algun_ingreso(dia, momento, pie_primer_personaje, cena_primer_personaje, horas_sueno_primer_personaje, pie_segundo_personaje, cena_segundo_personaje, horas_sueno_segundo_personaje)){
    
        printf(LINEA);
        printf(BLANCO "\nA continuación mostraré los datos ingresados:\n\n" FIN);
        if (dia != VALOR_NULO)
            printf("·" BLANCO "Día del mes: " VERDE "%i. \n" FIN, dia);

        if (momento != CARACTER_NULO)
            printf("·" BLANCO "Hora del día: " VERDE "%c. \n" FIN, momento);
        
        if (pie_primer_personaje != CARACTER_NULO || cena_primer_personaje != CARACTER_NULO || horas_sueno_primer_personaje != VALOR_NULO)
            mostrar_datos_animo_personaje(pie_primer_personaje, cena_primer_personaje, horas_sueno_primer_personaje, AZUL, PRIMER_PERSONAJE);            
        
        if (pie_segundo_personaje != CARACTER_NULO || cena_segundo_personaje != CARACTER_NULO || horas_sueno_segundo_personaje != VALOR_NULO)
            mostrar_datos_animo_personaje(pie_segundo_personaje, cena_segundo_personaje, horas_sueno_segundo_personaje, MAGENTA, SEGUNDO_PERSONAJE);

        printf(LINEA);
    }
}

/*Pre-condiciones:
	"dia" debe estar entre DIA_MES_MIN y DIA_MES_MAX.
Post-condiciones: 
	la función devuelve un valor que es MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO.*/
int viento_batalla(int dia){
	int viento;

	if (dia <= MAX_DIA_MUCHO_VIENTO)
        viento = MUCHO_VIENTO;
    else if (dia <= MAX_DIA_VIENTO_REGULAR)
        viento = VIENTO_REGULAR;
    else
        viento = POCO_VIENTO;

    return viento;
}

/*Pre-condiciones: 
	"momento" debe ser MANANA, TARDE o NOCHE.
Post-condiciones:
	la función devuelve un valor que es MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD.*/
int humedad_batalla(char momento){
	int humedad;
	
	if (momento == MANANA)
        humedad = MUCHA_HUMEDAD;
    else if (momento == TARDE)
        humedad = POCA_HUMEDAD;
    else
        humedad = HUMEDAD_REGULAR;

    return humedad;
}

/*Pre-condiciones: 
	"viento" debe ser MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO.
Post-condiciones:
	la función muestra un mensaje con las condiciones del viento partir del dato recibido.*/
void mostrar_informacion_viento(int viento){

    if (viento == MUCHO_VIENTO)
        printf("Un viento que despeina tanto a " PRIMER_EQUIPO " que no los deja ver nada, mientras que ");
    else if (viento == VIENTO_REGULAR)
        printf("Suficiente viento para despeinar a " PRIMER_EQUIPO " pero no tanto como para " SEGUNDO_PERSONAJE " y su tropa, mientras que ");
    else 
        printf("Poco viento, manteniendo tan perfecto como de costumbre al cabello de " PRIMER_EQUIPO " mientras que ");
}

/*Pre-condiciones: 
	"humedad" debe ser MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD.
Post-condiciones:
	la función muestra un mensaje con las condiciones de la humedad partir del dato recibido.*/
void mostrar_informacion_humedad(int humedad){
	
	if (humedad == MUCHA_HUMEDAD)
        printf("el frizz en el cabello de " SEGUNDO_EQUIPO " denota mucha humedad. ");
    else if (humedad == POCA_HUMEDAD)
        printf("la sequedad en la piel de " SEGUNDO_EQUIPO " denota poca humedad. ");
    else
        printf("la humedad es perfecta para este día de batalla. ");
}

/*Pre-condiciones:
	"animo_personaje" debe ser BUENO, REGULAR o MALO,
	"nombre_personaje" debe ser PRIMER_PERSONAJE o SEGUNDO_PERSONAJE.
Post-condiciones:
	la función muestra un mensaje con el animo del personaje partir de los datos recibidos.*/
void mostrar_animo_personaje (char animo_personaje, char *nombre_personaje){

	if (animo_personaje == MALO)
        printf("Tan malo parece el día de %s que las apuestas dicen que será una batalla dificil para él. ", nombre_personaje);
    else if (animo_personaje == REGULAR)
        printf("Un día normal para %s, acostumbrado a estar listo ante cualquier situación. ", nombre_personaje);
    else
        printf("Un gran día para %s, de la felicidad por batallar baila un rato con su tropa. ", nombre_personaje);
}

/*Pre-condiciones: 
    "viento" debe ser MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO,
    "humedad" debe ser MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD,
    "animo_primer_personaje" y "animo_segundo_personaje" deben ser BUENO, MALO o REGULAR.
Post-condiciones:
    la función muestra un mensaje con las condiciones para la batalla a partir de los datos recibidos.*/
void mostrar_condicion_batalla(int viento, int humedad, char animo_primer_personaje, char animo_segundo_personaje){

    printf(BLANCO "\nCondiciones para la batalla: " BLANCO);
    mostrar_informacion_viento(viento);
    mostrar_informacion_humedad(humedad);
    mostrar_animo_personaje(animo_primer_personaje, PRIMER_PERSONAJE);
    mostrar_animo_personaje(animo_segundo_personaje, SEGUNDO_PERSONAJE);
}

/*Pre-condiciones: 
	"viento" debe ser MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO,
	"humedad" debe ser MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD,
	"animo_primer_personaje" y "animo_segundo_personaje" deben ser BUENO, MALO o REGULAR.
Post-condiciones:
	la función muestra un mensaje con un resumen de la batalla.*/
void mostrar_resumen(int viento, int humedad, char animo_primer_personaje, char animo_segundo_personaje){

    printf("\nResumen: "VERDE"%i %i %c %c"BLANCO".\n" FIN, viento, humedad, animo_primer_personaje, animo_segundo_personaje);
}

/*Pre-condiciones: 
    "viento" debe ser MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO,
    "humedad" debe ser MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD,
    "animo_primer_personaje" y "animo_segundo_personaje" deben ser BUENO, MALO o REGULAR.
Post-condiciones:
    la función muestra un mensaje basándose en los datos recibidos.*/
void mostrar_resolucion(int viento, int humedad, char animo_primer_personaje, char animo_segundo_personaje){
    
    if (viento != PERSONALIZADO && humedad != PERSONALIZADO && animo_primer_personaje != CARACTER_PERSONALIZADO && animo_segundo_personaje != CARACTER_PERSONALIZADO){
    
        mostrar_condicion_batalla(viento, humedad, animo_primer_personaje, animo_segundo_personaje);
        mostrar_resumen(viento, humedad, animo_primer_personaje, animo_segundo_personaje);
    }

    printf(BLANCO"\n\nPresione enter para continuar\n"MAGENTA);
    while(getchar()!='\n');
    while(getchar()!='\n');
}

/*Pre-condiciones:
    -
Post-condiciones: 
    la función devuelve:
    - "*dia" que está entre DIA_MES_MIN y DIA_MES_MAX;
    - "*viento" que es MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO*/
void obtener_viento(int *dia, int *viento){
    
    obtener_el_dia(dia);
    *viento = viento_batalla(*dia);
}

/*Pre-condiciones:
    -
Post-condiciones: 
    la función devuelve:
    - "*momento" que es MANANA, TARDE o NOCHE;
    - "*humedad" que es entre MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD.*/
void obtener_humedad(char *momento, int *humedad){

    obtener_el_momento(momento);
    *humedad = humedad_batalla(*momento);   
}

/*Pre-condiciones:
    -
Post-condiciones: 
    la función devuelve:
    - "*pie" que es DERECHO o IZQUIERDO;
    - "*cena" que es ENSALADA, GUISO, HAMBURGUESA o PIZZA;
    - "*horas_sueno" que es un valor entre HORAS_SUENO_MIN y HORAS_SUENO_MAX;
    . "*animo" es BUENO, MALO o REGULAR.*/
void obtener_datos_personaje(char *pie, char *cena, int *horas_sueno, char *animo){

    obtener_pie(pie);
    obtener_cena(cena);
    obtener_horas_sueno(horas_sueno);
    *animo = animo_personaje(*pie, *cena, *horas_sueno);
}

/*Pre-condiciones:
    -
Post-condiciones: 
    la función devuelve los valores de los punteros recibidos actualizados.*/
void limpiar_variables(char *pie, char *cena, int *horas_sueno){

    *pie = CARACTER_NULO;
    *cena = CARACTER_NULO;
    *horas_sueno = VALOR_NULO;
}

/*Pre-condiciones: 
    -
Post-condiciones:
    la función modificará, si es que el valor no es POR_DEFECTO o CARACTER_POR_DEFECTO según corresponda, el valor de las posiciones recibidas con los siguientes valores válidos:
    	"viento" debe ser MUCHO_VIENTO, VIENTO_REGULAR o POCO_VIENTO.
    	"humedad" debe ser MUCHA_HUMEDAD, HUMEDAD_REGULAR o POCA_HUMEDAD.
    	"animo_legolas" debe ser BUENO, MALO o REGULAR.
    	"animo_gimli" debe ser BUENO, MALO o REGULAR.*/
void animos (int *viento, int *humedad, char *animo_legolas, char *animo_gimli){
    char momento = CARACTER_NULO;
    char pie_primer_personaje = CARACTER_NULO, cena_primer_personaje = CARACTER_NULO;
    char pie_segundo_personaje = CARACTER_NULO, cena_segundo_personaje = CARACTER_NULO;
    int dia = VALOR_NULO, horas_sueno_primer_personaje = VALOR_NULO, horas_sueno_segundo_personaje = VALOR_NULO;
    
    presentarme();
    if (*viento == POR_DEFECTO)
        obtener_viento(&dia, viento);        
    if (*humedad == POR_DEFECTO)
        obtener_humedad(&momento, humedad);
    if (*animo_legolas == CARACTER_POR_DEFECTO){
        
        mostrar_mensaje_inicial(AZUL, PRIMER_PERSONAJE);
        obtener_datos_personaje(&pie_primer_personaje, &cena_primer_personaje, &horas_sueno_primer_personaje, animo_legolas);
        mostrar_mensaje_final(PRIMER_PERSONAJE_LETRA);
    }
    if (*animo_gimli == CARACTER_POR_DEFECTO){

        mostrar_mensaje_inicial(MAGENTA, SEGUNDO_PERSONAJE);
        obtener_datos_personaje(&pie_segundo_personaje, &cena_segundo_personaje, &horas_sueno_segundo_personaje, animo_gimli);
        mostrar_mensaje_final(SEGUNDO_PERSONAJE_LETRA);
    }
    
    system("clear");
    if (ingreso_algo(*viento, *humedad, *animo_gimli, *animo_legolas)){
        
        mostrar_datos_ingresados(dia, momento, pie_primer_personaje, cena_primer_personaje,
        	horas_sueno_primer_personaje, pie_segundo_personaje, cena_segundo_personaje, horas_sueno_segundo_personaje);
        mostrar_resolucion(*viento, *humedad, *animo_legolas, *animo_gimli);
    }
}