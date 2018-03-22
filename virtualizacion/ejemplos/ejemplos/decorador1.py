#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
def logger(fn):
 	# Este wrapper lo usas para atrapar los parametros de la funcion decorada
    def wrapper(*args):

        # esta es la funcionalidad de la decoracion
        for i, arg in enumerate(args):
            print ("arg %d:%d" % (i, arg))
        # no se debe olvidar ejecutar la funcion que se esta decorando.
        return fn(*args)
    return wrapper

# Sumador va a sumar todos los argumentos enviandos, sin importar cuantos son.
@logger
def Sumador(*args):
    return sum([i for i in args])

print(Sumador(1,2,3,4))


if __name__ == "__main__":
  pass
