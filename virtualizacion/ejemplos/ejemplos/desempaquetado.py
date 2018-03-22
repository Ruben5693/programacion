#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
toys = ['Buzz', 'Rex', 'Bo', 'Hamm', 'Slink', ]

def division(a, b):
    quotient = a // b
    remainder = a % b
    return quotient, remainder

if __name__ == "__main__":
  q,r=division(10,3)
  print("el cociente es %d y el resto %d" % (q,r))
  a,b=division(20,4)
  a,b=b,a
  print (a,b)

  k,*l=toys
  print (k,l)
