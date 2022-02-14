Se aprovecha las bibliotecas ya definidas para la version 17 de C++, especificamente de std::filesystem, para poder leer los recursos del sistema, determinar si se trata de una carpeta o un archivo.

Limitantes de la implementacion:
 - Si se envia una ruta que no sea una carpeta, se imprimira { }
 - Solo se revisan archivos y carpetas, no se procesan links simbolicos
 - Para su compilacion se requiere de al menos la version 17 C++
 - Se requieren permisos de escritura donde se encuentra el ejecutable para que pueda generar el archivo de salida dir.json
 - No se muestra nada en pantalla, solo se genera un archivo de salida

