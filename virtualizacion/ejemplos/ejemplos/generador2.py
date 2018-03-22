#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
def fib():
    a,b =0,1
    while True:
        yield b
        a,b=b,a+b


f=fib()
print (f)
for i in range(100):
    print (next(f))
if __name__ == "__main__":
  pass
  # listas y diccionarios tienen generadores implicitos
