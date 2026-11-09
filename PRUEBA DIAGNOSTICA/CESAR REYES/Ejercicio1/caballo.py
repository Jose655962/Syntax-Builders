import time

COLUMNAS = "abcdefgh"

def verificar(inicio, movimientos):
    col = COLUMNAS.index(inicio[0])
    fila = int(inicio[1]) - 1

    for i, mov in enumerate(movimientos, start=1):
        if mov[0] != "K":
            return f"INCORRECTO falla letra {mov[0]} no pertenece a un caballo"
        if len(mov) != 3 or mov[1] not in COLUMNAS or mov[2] not in "12345678":
            return f"INCORRECTO falla en el movimiento {i}"

        nc = COLUMNAS.index(mov[1])
        nf = int(mov[2]) - 1
        dc, df = abs(nc - col), abs(nf - fila)

        if (dc, df) not in ((1, 2), (2, 1)):
            return f"INCORRECTO falla en el movimiento {i}"
        col, fila = nc, nf

    return "movimiento CORRECTO"

if __name__ == "__main__":
    # Pruebas con los ejemplos del enunciado
    pruebas = [
        ("a1", "Kc2 Kd4 Kb3 Kc5"),
        ("a1", "Kc2 Kd4 Kb4 Kc5"),
        ("a2", "Kc8 Ke4 Kf6 Ke8 Kg7"),
        ("a8", "Kb6 Kb7"),
        ("a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"),
        ("a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4"),
    ]
    for inicio, cadena in pruebas:
        print(inicio, cadena, "->", verificar(inicio, cadena.split()))