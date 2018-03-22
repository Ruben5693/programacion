#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
class Circle(object):
    PI = 3.14
    def __init__(self, radius):
        self.radius = radius
    def perimeter(self):
        return 2 * self.PI * self.radius
    @property
    def radio(self):
        return self.radius
    @radio.setter    
    def radio(self,r):
        if r>0:
          self.radius=r

if __name__ == "__main__":
  c=Circle(1.2)
  print(c.perimeter())
  print (c.radio)
  c.radio=3.0
  print (c.radio)
