import time

def movimiento_valido(origen, destino):
    # Convertimos las letras (a-h) a numeros (1-8) para calcular distancias
    col_origen = ord(origen[0]) - ord('a') + 1
    fila_origen = int(origen[1])
    
    col_destino = ord(destino[0]) - ord('a') + 1
    fila_destino = int(destino[1])
    
    # Verificamos que no se salga del tablero 8x8
    if not (1 <= col_destino <= 8 and 1 <= fila_destino <= 8):
        return False
        
    # Calculamos la distancia absoluta recorrida en columnas y filas
    dx = abs(col_origen - col_destino)
    dy = abs(fila_origen - fila_destino)
    
    # El caballo se mueve en L: 2 casillas de un lado y 1 del otro
    return (dx == 1 and dy == 2) or (dx == 2 and dy == 1)

def validar_cadena(pos_inicial, cadena):
    movimientos = cadena.split()
    pos_actual = pos_inicial
    
    for i, mov in enumerate(movimientos):
        # Validar que empiece con K
        if mov[0] != 'K':
            print(f"INCORRECTO falla letra {mov[0]} no pertenece a un caballo.")
            return False
            
        destino = mov[1:]
        
        # Validar el movimiento 
        if movimiento_valido(pos_actual, destino):
            pos_actual = destino
        else:
            print(f"INCORRECTO falla en el movimiento {i + 1}.")
            return False
            
    print("movimiento CORRECTO.")
    return True

# --- PRUEBA Y MEDICIÓN DE TIEMPO ---
pos_inicial = "a2"
# Aquí va la cadena completa de 500 movimientos provista por el profesor
cadena_500 = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4"

inicio = time.time()
for _ in range(10):
    validar_cadena(pos_inicial, cadena_500)
fin = time.time()

print(f"\nTiempo de verificar 10 veces los 500 movimientos: {fin - inicio:.6f} segundos")