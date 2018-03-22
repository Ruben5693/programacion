diccionario = dict(Bermejo="subnormal",Ruben="El mejoh")
for valor in diccionario.keys():
    print(valor)

diccionario_2 = {"Bermejo":"subnormal"},{"Ruben":"El mejoh"}

for valor in diccionario.values():
    print(valor)

for valor in diccionario.items():
    print(valor[::-2])


m=[[1,2,3],[4,5,6],[7,8,9]]
t=zip(*m)
print(m)
print(t)
#L=list()
#A=filter(lambda x,y:True if x>y:False,L)
