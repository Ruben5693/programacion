#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
toys = ['Buzz', 'Rex', 'Bo', 'Hamm', 'Slink', ]
len_map1 = {}
for toy in toys:
    len_map1[toy] = len(toy)

len_map = {toy: len(toy) for toy in toys}
if __name__ == "__main__":
  print (len_map1)
  print (len_map)
  edad=18
  a="mayor" if edad>20 else "nemor"
  print(a)
