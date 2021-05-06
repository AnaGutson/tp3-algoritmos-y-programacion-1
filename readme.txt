Para crear un camino ingrese: crear_camino <nombre_archivo_en_donde_colocarlo>
    Ej: crear_camino camino.txt

Para crear una configuracion ingrese: crear_configuracion <nombre_archivo_en_donde_colocarla>
    Ej: crear_configuracion confi.txt

Para jugar: jugar config=<nombre_archivo_configuracion> grabacion=<nombre_archivo_en_donde_colocarla>
	-> los argumentos son opcionales.
    Ej: jugar config=confi.txt grabacion=version_final.dat

Para ver una partida grabada: poneme_la_repe grabacion=<nombre_archivo_grabacion> velocidad=<velocidad_entre_turnos>
	-> la velocidad es opcional, en caso de no colocarla se tomará velocidad '1' segundo'.
    Ej: poneme_la_repe grabacion=version_donde_gano.dat

Para ver el ranking de una configuracion: ranking listar=<cantidad_elementos_a_listar> config=<nombre_archivo_configuracion>
	-> los argumentos son opcionales.
    Ej: ranking config=confi.txt
