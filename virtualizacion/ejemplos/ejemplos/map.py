#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________

#r = map(func, seq)
def fahrenheit(T):
    return ((float(9)/5)*T + 32)
def celsius(T):
    return (float(5)/9)*(T-32)


temp = (36.5, 37, 37.5,39)

F = map(fahrenheit, temp)
C = map(celsius, F)
if __name__ == "__main__":
  print (C)
  print (F)
