import re
import argparse
import os
from translate import Translator

def extraer_cadenas_con_comillas(archivo_entrada, archivo_salida):
    """
    Extrae las cadenas de texto entre comillas (incluyendo escapadas) de un archivo y las guarda en otro,
    ignorando las cadenas vacías.

    Args:
        archivo_entrada: La ruta al archivo de texto de entrada.
        archivo_salida: La ruta al archivo de texto de salida.   
    """
    #Creamos el objeto translator
    traductor = Translator(from_lang="es" , to_lang="en")

    try:
        with open(archivo_entrada, 'r', encoding='latin_1') as f_entrada, open(archivo_salida, 'w') as f_salida:
            print(f"Extrayendo y traduciendo las cadenas de texto...\n")
            count = 0
            #encabezado
            f_salida.write("sp;eng\n")

            for linea in f_entrada:
                # Encuentra todas las cadenas entre comillas (escapadas o no) en la línea actual
                cadenas = re.findall(r'"([^"\\]*(?:\\.[^"\\]*)*)"', linea)  
                for cadena in cadenas:
                    if cadena:  # Verifica si la cadena no está vacía
                        f_salida.write(cadena + ';' + traductor.translate(cadena) + '\n')
                        count = count + 1
                        print(f"Cadenas procesadas: {count}", end='\r')
    
            print(f"{count} cadenas extraídas en fichero {archivo_salida}")
                                
    except FileNotFoundError:
        print(f"Error: Uno o ambos archivos no fueron encontrados.")
    except Exception as e:
        print(f"Ocurrió un error: {e}")

# Argumentos de entrada
parser = argparse.ArgumentParser(description="Extrae cadenas de texto entre comillas (ignorando las cadenas vacías) y las guarda otro archivo")
parser.add_argument("-f", "--file", help="Nombre del archivo a extraer las cadenas de texto")
parser.add_argument("-o", "--output", help="Nombre del archivo destino donde depositar las cadenas extraídas")
args = parser.parse_args()

# Llamada a funcion con argumentos de entrada
if args.file:
    if args.output:
        extraer_cadenas_con_comillas(args.file, args.output)
    else:
        extraer_cadenas_con_comillas(args.file, os.path.splitext(args.file)[0] + ".csv")
else:
    print(f"No se ha especificado archivo de entrada")
