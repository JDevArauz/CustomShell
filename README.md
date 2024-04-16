# CustomShell

Este es un programa sencillo que permite ejecutar comandos internos en Linux mediante una consola personalizada de comandos.

## Antecedentes

Se trata de un programa diseñado para emular un Shell, utilizando las llamadas al sistema de manejo de procesos fork, wait, exec. Su funcionalidad principal es ejecutar cualquier comando del sistema operativo o lanzar otro programa. También puede ejecutar en modo tanda "&", admitir pipes "|", redireccionamiento de entrada "<", y salida ">". Automáticamente busca programas en los directorios /bin, /usr/bin y en el directorio actual.

## Puntos que abarca este proyecto

### Funciones principales

- **Prompt personalizado:** Muestra el login, el hostname y la carpeta actual.
- **Cambio de directorio:** Permite cambiar de directorio utilizando comandos como 'cd' o 'cd..'.
- **Evitar killall:** Evita que se mate al shell con killall desde el mismo shell.
- **Prevención de detención con CTRL+C:** No permite detenerse con CTRL+C y envía un mensaje indicando que se debe teclear "exit" para salir.

### Funciones secundarias

- **Admite varios pipes "|".**
- **Admite redirección a fichero "> fichero".**
- **Admite anexión a fichero ">> fichero".**
- **Admite entrada desde fichero "< fichero".**
- **Admite pasar comandos a segundo plano "&".**
- **Admite caracteres comodín ('*' y '?').**
- **Admite envío de señales a los comandos lanzados:** Pasa la señal SIGINT (Ctrl+C) a los procesos hijos.
