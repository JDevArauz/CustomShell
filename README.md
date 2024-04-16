# CustomShell
Este es un programa sencillo que permite ejecutar comandos internos en linux mediante una consola personalizada de comandos.
ANTECEDENTES: Realizar un programa para emular un Shell, utilizando las llamadas al sistema de manejo de procesos fork, wait, exec, que permita ejecutar cualquier comando del sistema operativo o ejecutar otro programa, lanzar en modo tanda '&' y que admita pipe '|', así como redireccionamiento de entrada '<' y salida '>'. Se buscarán los programas automáticamente en los directorios /bin, /usr/bin y en el directorio actual.

## Puntos que abacarca este proyecto: 
Funciones principales:
• Prompt personalizado: muestra el login, el hostname y la carpeta actual.
• Cambio de directorio con todas las opciones posibles (según las del Bash como el 'cd' o 'cd..')  
• Evita que se mate al shell con killall desde él mismo.
• No permitir detener con CTRL+C y enviar un mensaje indicando que debe teclear “exit” para salir. 

Funciones secundarias:
• Admite varios pipes "|".
• Admite redirección a fichero "> fichero".
• Admite anexión a fichero ">> fichero".
• Admite entrada desde fichero "< fichero".
• Admite pasar comandos a segundo plano "&".
• Admite caracteres comodín (* y ?) 
• Admite envío de señales a los comandos lanzados (pasa señal SIGINT, de Ctrl+C, a los hijos)  
