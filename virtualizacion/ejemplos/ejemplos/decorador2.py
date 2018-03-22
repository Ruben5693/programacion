#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
class logger(object):

    def __init__(self, fn):
        print ("Logger se instancia en la definicion de la funcion ")
        self.fn = fn
    def __call__(self, *args):
        # esta es la decoracion
        print ("La decoracion puede ejecutar tareas previas a la ejecucion de la funcion")
        for i, arg in enumerate(args):
            print ("arg %d:%d" % (i, arg)) #esto es interpolación de cadenas
        # nunca olvido ejecutar funcion decorada
        return self.fn(*args)



# Sumador va a sumar todos los argumentos enviandos, sin importar cuantos son.
@logger
def Sumador(*args):
    return sum([i for i in args])

# Ejecuto mi funcion decorada - La decoracion ya se instancio.
print ("Voy a Correr el Sumador")
print(Sumador(1,2,3,4))
print ("Funcion ejecutada")


if __name__ == "__main__":
  pass
