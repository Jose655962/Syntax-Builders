import time

from caballo import verificar, COLUMNAS

REPETICIONES = 10      # lo que pide el enunciado
REPETICIONES_100 = 100 # por el "n=100" del encabezado

# 1) Leer la cadena
with open("cadena.txt", "r") as f:
    movimientos = f.read().split()

print(f"Movimientos leídos: {len(movimientos)}")

# 2) El PDF no dice la casilla inicial: probamos las 64 y vemos cuáles dan CORRECTO
casillas_validas = []
for c in COLUMNAS:
    for r in "12345678":
        if verificar(c + r, movimientos) == "movimiento CORRECTO":
            casillas_validas.append(c + r)

print("Casillas iniciales que dan CORRECTO:", casillas_validas)

if not casillas_validas:
    print("Ninguna casilla funciona: revisa que cadena.txt esté bien copiada.")
    raise SystemExit

inicio = casillas_validas[0]

# 3) Medir el tiempo
def medir(veces):
    tiempos = []
    for _ in range(veces):
        t0 = time.perf_counter()
        resultado = verificar(inicio, movimientos)
        t1 = time.perf_counter()
        tiempos.append(t1 - t0)
    return tiempos, resultado

t10, resultado = medir(REPETICIONES)
t100, _ = medir(REPETICIONES_100)

# 4) Escribir resultados.txt
with open("resultados.txt", "w") as out:
    out.write("EJERCICIO 1 - Lenguaje: Python\n")
    out.write(f"Casilla inicial usada: {inicio}\n")
    out.write(f"Movimientos verificados: {len(movimientos)}\n")
    out.write(f"Resultado: {resultado}\n\n")

    out.write(f"--- {REPETICIONES} repeticiones ---\n")
    for i, t in enumerate(t10, start=1):
        out.write(f"Corrida {i}: {t:.9f} s\n")
    out.write(f"Total: {sum(t10):.9f} s\n")
    out.write(f"Promedio: {sum(t10)/len(t10):.9f} s\n\n")

    out.write(f"--- {REPETICIONES_100} repeticiones ---\n")
    out.write(f"Total: {sum(t100):.9f} s\n")
    out.write(f"Promedio: {sum(t100)/len(t100):.9f} s\n")

print("Listo: se escribió resultados.txt")