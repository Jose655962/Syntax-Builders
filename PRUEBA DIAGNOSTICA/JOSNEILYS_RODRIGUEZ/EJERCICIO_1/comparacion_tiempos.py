import time

def validar_movimientos(ak, n, c):
    col_actual = ord(ak[0]) - ord('a')
    fila_actual = int(ak[1]) - 1
    movs = c.split()
    for i, mov in enumerate(movs):
        if i >= n: break
        if mov[0] != 'K': return False
        col_siguiente = ord(mov[1]) - ord('a')
        fila_siguiente = int(mov[2]) - 1
        dx, dy = abs(col_siguiente - col_actual), abs(fila_siguiente - fila_actual)
        if not ((dx == 1 and dy == 2) or (dx == 2 and dy == 1)): return False
        col_actual, fila_actual = col_siguiente, fila_siguiente
    return True

def test_1():
    c_500 = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8"
    inicio = time.time()
    for _ in range(10): validar_movimientos("a2", 500, c_500)
    return time.time() - inicio

def test_2():
    inicio = time.time()
    coef = [1] * 101
    for i in range(1, 101):
        for j in range(i - 1, 0, -1): coef[j] += coef[j - 1]
    return time.time() - inicio

with open("tiempos_python.txt", "w") as f:
    f.write(f"Tiempo Python (Caballo - 10 veces 500 movs): {test_1():.6f} seg\n")
    f.write(f"Tiempo Python (Pascal n=100): {test_2():.6f} seg\n")
