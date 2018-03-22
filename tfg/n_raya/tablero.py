class Tablero:
    def __init__(self, a, b,num):
        self.tab =[ ]
        for fila in range(a):
            self.tab.append(self.crearLista(b))
        self.dim = (a,b)
        self.jugador=1
        self.numj=num
        self.cont=[ ]
        for f in range(num):
            self.cont.append(0)

    def crearLista(self,b):
        tab = [ ]
        for fila in range(b):
            tab.append(0)
        return tab

    def __str__(self):
        a=""
        for fila in self.tab:
            a=a+str(fila[0:self.dim[1]])+"\n"
        return a

    def insertar(self,columna):
        for fila in range(self.dim[0]):
            if self.tab[self.dim[0]-fila-1][columna] == 0:
                self.tab[self.dim[0]-fila-1][columna]=self.jugador
                self.cont[self.jugador-1]=self.cont[self.jugador-1]+1
                return True
        return False

    def comprobarGanador(self):
        for fila in self.cont:
            if fila==3:
                return True
            else:
                return False

    def cambiarJugador(self):
        if self.jugador == self.numj:
            self.jugador=1
        else:
            self.jugador=self.jugador+1

    def iniciar(self):
        for fila in self.tab:
            for columna in range(self.dim[0]):
                fila.insert(columna,0)
