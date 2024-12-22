"""
Reverse-engineering my specific program gives:
    while a > 0:
        b = a%8
        b ^= 3
        c = a//(1<<b)
        a = a//(1<<3)
        b ^= c
        b ^= 5
        output.append(b%8)
"""
from z3 import *


opt = Optimize()
s = BitVec("s", 64)
a,b,c = s, 0, 0
for x in [2,4,1,3,7,5,0,3,4,3,1,5,5,5,3,0]:
    b = a % 8
    b = b ^ 3
    c = a / (1 << b)
    a = a / (1<<3)
    b = b ^ c
    b = b ^ 5
    opt.add((b%8) == x)
opt.add(a == 0)
opt.minimize(s)
opt.check() 
#gets stuck on opt.check() for some reason, but when i interrupt it continues and prints answer
print(opt.model())
