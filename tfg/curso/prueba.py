#devuelve el elemento mayor de la lista
def p1():
    from functools import reduce
    items= list(range(203))
    print(reduce(lambda a, b: a if a>b else b, items))



#devuelve los elementos pares de la lista
def p2():
    items=range(100)
    for x in filter(lambda x: x % 2 == 0, items):
        print(x)

#devuelve los dias de la semana que tengan mas de 6 caracteres
def p3():
    lista = ["lunes","martes","miercoles","jueves","viernes","sabado","domingo"]
    for x in filter(lambda x: len(x)>6,lista):
        print(x)
#devuelve un diccionario con el numero de veces que aparece cada palabra de la cadena
def frec_palabras(cadena):
    frecuenciaPalab = []
    for p in cadena.split(" "):
        frecuenciaPalab.append(cadena.count(p))
    return dict(zip(cadena.split(" "),frecuenciaPalab))

#frec=frec_palabras("python para todos esto es una prueba es una prueba")
#print(frec)

def traspuesta(m):
    return list(zip(*m)) # el operador * desempaqueta una lista
matriz = [[1, 2, 3, 4],
[5, 6, 7, 8],
[9, 10, 11, 12]]
print(traspuesta(matriz))
