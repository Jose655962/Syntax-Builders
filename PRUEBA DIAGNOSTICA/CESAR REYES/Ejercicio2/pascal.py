import time
from pathlib import Path

CARPETA = Path(__file__).parent


def generar_triangulo(n):
    filas = [[1]]
    for _ in range(n):
        previa = filas[-1]
        nueva = [1]
        for i in range(len(previa) - 1):
            nueva.append(previa[i] + previa[i + 1])
        nueva.append(1)
        filas.append(nueva)
    return filas


def polinomio_a_texto(coefs):
    n = len(coefs) - 1
    terminos = []
    for k, c in enumerate(coefs):
        grado = n - k
        if grado == 0:
            terminos.append(str(c))
        else:
            coef = "" if c == 1 else str(c)
            pot = "x" if grado == 1 else f"x^{grado}"
            terminos.append(coef + pot)
    return " + ".join(terminos)


def evaluar_por_pasos(coefs, x):
    n = len(coefs) - 1
    total = 0
    print(f"\nCalculo de f({x}) = ({x}+1)^{n} segun el polinomio:")
    for k, c in enumerate(coefs):
        grado = n - k
        valor = c * x ** grado
        total += valor
        print(f"  Paso {k + 1}: {c} * {x}^{grado} = {valor}   (acumulado = {total})")
    print(f"Resultado: f({x}) = {total}")
    print(f"Verificacion con ({x}+1)^{n} = {(x + 1) ** n}")
    return total


def medir_tiempo(n=100, repeticiones=10):
    tiempos = []
    for _ in range(repeticiones):
        t0 = time.perf_counter()
        generar_triangulo(n)
        tiempos.append(time.perf_counter() - t0)

    with open(CARPETA / "resultados_pascal_python.txt", "w") as out:
        out.write("EJERCICIO 2 - Lenguaje: Python\n")
        out.write(f"Se generan los polinomios (x+1)^k para k = 0..{n}\n\n")
        for i, t in enumerate(tiempos, start=1):
            out.write(f"Corrida {i}: {t:.9f} s\n")
        out.write(f"Total: {sum(tiempos):.9f} s\n")
        out.write(f"Promedio: {sum(tiempos) / len(tiempos):.9f} s\n")
    print(f"\nTiempo promedio (n={n}): {sum(tiempos) / len(tiempos):.9f} s")
    print("Se escribio resultados_pascal_python.txt")


if __name__ == "__main__":
    n = int(input("Ingrese n (entero no negativo): "))
    x = int(input("Ingrese x: "))

    triangulo = generar_triangulo(n)
    fila = triangulo[n]

    print(f"\nCoeficientes (fila {n}): {fila}")
    print(f"(x+1)^{n} = {polinomio_a_texto(fila)}")
    evaluar_por_pasos(fila, x)
    medir_tiempo(100, 10)