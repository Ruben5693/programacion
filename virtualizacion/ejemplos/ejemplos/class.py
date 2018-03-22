#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
class Circle(object):
    PI = 3.14
    def __init__(self, radius):
        self.radius = radius
    def perimeter(self):
        return 2 * self.PI * self.radius
def f1(a,b=5,*args,**kargs):
    print a
    print (kargs)
    print (args)
    return b

if __name__ == "__main__":
  print (f1("lll",(1,2,1),kk=11,pepe="ddd"))
