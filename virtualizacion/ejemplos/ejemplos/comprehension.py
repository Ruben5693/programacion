#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
fib = [1, 1, 2, 3, 5, 8, 13, 21]

even = []
even1 = []
for n in fib:
   if n % 2 == 0:
       even.append(n)

even1=[n for n in fib if n%2==0]
if __name__ == "__main__":
  print (even)
  print (even1)
