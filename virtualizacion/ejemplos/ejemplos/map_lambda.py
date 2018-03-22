#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________

#r = map(func, seq)
fahrenheit = lambda T:((float(9)/5)*T + 32)
celsius = lambda T:(float(5)/9)*(T-32)



temp = (36.5, 37, 37.5,39)

F = map(lambda T:((float(9)/5)*T + 32), temp)
C = map(celsius, F)
if __name__ == "__main__":
  print (C)
  print (F)
