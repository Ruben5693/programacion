f=open("quijote.txt","r")
print f.read(6)
lines=f.readlines()
for i in range(10):
    print lines[i]
