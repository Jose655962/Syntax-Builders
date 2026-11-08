import time

def generar_polinomio(n, x):
    # Memoria dinámica: la lista se ajusta al tamaño en Python automáticamente
    fila = [1]
    for i in range(1, n + 1):
        # Generar la siguiente fila del triángulo de Pascal basada en la anterior
        nueva_fila = [1]
        for j in range(1, len(fila)):
            nueva_fila.append(fila[j-1] + fila[j])
        nueva_fila.append(1)
        fila = nueva_fila

    if n <= 10: # Para no inundar la pantalla si n es 100
        # a) Mostrar polinomio
        terminos = []
        potencia_x = n
        for coef in fila:
            if potencia_x == 0:
                terminos.append(f"{coef}")
            elif potencia_x == 1:
                terminos.append(f"{coef}x")
            else:
                terminos.append(f"{coef}x^{potencia_x}")
            potencia_x -= 1
        print(f"Polinomio (x+1)^{n} = " + " + ".join(terminos))

        # b) Cálculo por pasos
        print(f"\nCalculando paso a paso para x = {x}:")
        potencia_x = n
        resultado_total = 0
        for coef in fila:
            valor_paso = coef * (x ** potencia_x)
            print(f"+ {coef} * ({x}^{potencia_x}) = {valor_paso}")
            resultado_total += valor_paso
            potencia_x -= 1
        print(f"Resultado final: {resultado_total}")

# --- MEDICIÓN DE TIEMPO n=100 ---
inicio = time.time()
generar_polinomio(100, 2)
fin = time.time()
print(f"\nTiempo de ejecución Python (n=100): {fin - inicio:.6f} segundos")