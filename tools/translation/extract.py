import re

def extraer_cadenas_con_comillas(archivo_entrada, archivo_salida):
    """
    Extrae las cadenas de texto entre comillas de un archivo y las guarda en otro.

    Args:
        archivo_entrada: La ruta al archivo de texto de entrada.
        archivo_salida: La ruta al archivo de texto de salida.
    """

    try:
        with open(archivo_entrada, 'r') as f_entrada, open(archivo_salida, 'w') as f_salida:
            for linea in f_entrada:
                # Encuentra todas las cadenas entre comillas en la línea actual
                cadenas = re.findall(r'"([^"]*)"', linea)  
                for cadena in cadenas:
                    f_salida.write(cadena + '\n')
    except FileNotFoundError:
        print(f"Error: Uno o ambos archivos no fueron encontrados.")
    except Exception as e:
        print(f"Ocurrió un error: {e}")

# Ejemplo de uso:
archivo_entrada = 'room01.c'  # Reemplaza con la ruta a tu archivo de entrada
archivo_salida = 'salida.txt'  # Reemplaza con la ruta donde quieres guardar las cadenas

extraer_cadenas_con_comillas(archivo_entrada, archivo_salida)
