#!/usr/bin/env python
# -*- coding: utf-8 -*-
#____________developed by paco andres____________________
palabras={}
with open("quijote.txt","r") as f:

    for l in f.readlines():
      for pal in l.split(" "):
          if palabras.has_key(pal):
              palabras[pal]=palabras[pal]+1
          else:
            palabras[pal]=1

f.close()
if __name__ == "__main__":
  print (palabras)
