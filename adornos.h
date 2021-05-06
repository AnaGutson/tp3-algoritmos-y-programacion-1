#ifndef __ADORNOS_H__
#define __ADORNOS_H__

#define ESPACIADO     "        "
#define VERDE       "\033[1m\033[32m"
#define FIN         "\033[0m"
#define LINEA       "\n-------------------------------------------------\n"
#define AMARILLO    "\033[1m\033[33m"
#define BLANCO      "\033[1m\033[37m"
#define ROJO        "\033[1m\033[31m"
#define AZUL        "\033[1m\033[34m"
#define MAGENTA     "\033[1m\033[35m"
#define FONDO       "\033[1m\033[40m"

/*Pre-condiciones: 
    -.
Post-condiciones:
    la función mostrará la carga del juego.*/
void mostrar_carga_juego();

/*Pre-condiciones: 
    -.
Post-condiciones:
    la función mostrará la carga del TP2.*/
void mostrar_carga_inicio_TP2();

/*Pre-condiciones: 
    "nivel" debe ser 1, 2, 3 o 4.
Post-condiciones: 
    la función retorna un ascii art segun "nivel".*/
void mostrar_mensaje_nivel_actual (int nivel);

/*Pre-condiciones: 
    -   
Post-condiciones:
    la función mostrará un ascii art*/
void mostrar_mensaje_felicitaciones();   

/*Pre-condiciones: 
    -   
Post-condiciones:
    la función mostrará un ascii art*/
void mostrar_mensaje_juego_perdido(int nivel);
   
/*Pre-condiciones: 
    -   
Post-condiciones:
    la función mostrará un ascii art*/    
void mostrar_mensaje_juego_ganado();

#endif /* __ADORNOS_H__ */
