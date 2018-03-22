from tablero import Tablero

def pedirNum(j):
    columna=input("Columna jugador " +str(j)+"\n")
    return columna
def numJugadores():
    return int(input("Numero de jugadores\n"))

def crearTablero():
    fila= int(input("Inserte el numero de filas\n"))
    columna= int(input("Inserte el numero de columna\n"))
    return Tablero(fila,columna,numJugadores())

def iniciarJuego():
    print("bienvenido a n-raya".upper())
    t=crearTablero()
    while True:
        print(t)
        while not t.insertar(pedirNum(t.jugador)):
            None
        if t.comprobarGanador():
            print(t)
            print("Gana el jugador "+str(t.jugador)+"\n")
            break
        t.cambiarJugador()
    print("Fin del juego\n")
iniciarJuego()
