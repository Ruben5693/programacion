#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
def my_gen():
    yield 2
    yield 1

for n in my_gen():
    print(n)
print list(my_gen())
g=my_gen()
print(next(g))
print(next(g))
if __name__ == "__main__":
  pass
