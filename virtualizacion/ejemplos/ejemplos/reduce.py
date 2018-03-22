#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________

#r = filter(func, seq)
def esprimo(numero):
    if numero<=2:
      return False
    for p in range(2, numero):
        if (numero % p) == 0:
            return False
    return True
suma=lambda x,y:x+y
values=[x for x in range(500) if esprimo(x)]

sumaprimos=reduce(suma,values)

if __name__ == "__main__":
  print (values)    
  print (sumaprimos)
