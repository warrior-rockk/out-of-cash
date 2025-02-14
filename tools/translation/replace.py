import csv
import argparse
import os

def reemplazar_texto_desde_csv(nombre_archivo, nombre_archivo_csv):
    """
    Reemplaza cadenas de texto en un archivo basándose en datos de un archivo CSV.

    Args:
        nombre_archivo: La ruta al archivo de texto que se va a modificar.
        nombre_archivo_csv: La ruta al archivo CSV que contiene las cadenas.
    """

    try:
        with open(nombre_archivo_csv, 'r', encoding='utf-8') as archivo_csv:
            lector_csv = csv.reader(archivo_csv)
            # Saltar la primera fila si contiene encabezados
            next(lector_csv, None)

            with open(nombre_archivo, 'r', encoding='latin_1') as archivo_texto:
                contenido = archivo_texto.read()

            for fila in lector_csv:
                if len(fila) >= 2:  # Asegurarse de que haya al menos dos columnas
                    if fila[-1]:    #Asegurarse de que la cadena de reemplazo no esta vacia
                        cadenas_a_buscar = fila[:-1]  # Todas las columnas excepto la última son cadenas a buscar
                        cadena_de_reemplazo = fila[-1]  # La última columna es la cadena de reemplazo

                        for cadena_original in cadenas_a_buscar:
                            contenido = contenido.replace(cadena_original, cadena_de_reemplazo)

            with open(nombre_archivo, 'w', encoding='utf-8') as archivo_texto:
                archivo_texto.write(contenido)

        print(f"Se han realizado reemplazos en '{nombre_archivo}' usando datos de '{nombre_archivo_csv}'")

    except FileNotFoundError:
        print(f"Error: No se encontró el archivo '{nombre_archivo}' o '{nombre_archivo_csv}'")
    except Exception as e:
        print(f"Error: Ocurrió un error: {e}")

# Argumentos de entrada
parser = argparse.ArgumentParser(description="Sustituye cadenas de texto entre comillas (ignorando las cadenas vacías) en base a un archivo CSV")
parser.add_argument("-f", "--file", help="Nombre del archivo a reemplazar las cadenas de texto")
parser.add_argument("-d", "--data", help="Nombre del archivo de datos con la relacion de cadenas a sustituir")
args = parser.parse_args()

# Llamada a funcion con argumentos de entrada
if args.file:
    if args.data:
        reemplazar_texto_desde_csv(args.file, args.data)
    else:
        reemplazar_texto_desde_csv(args.file, os.path.splitext(args.file)[0] + ".csv")
else:
    print(f"No se ha especificado archivo de entrada")