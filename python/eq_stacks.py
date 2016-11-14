#!/bin/python3

import sys
from bisect import bisect_left

def getS(h):
    s=0
    sarr=[]
    for e in h:
       s+=e
       sarr.append(s)
    return sarr
    
n1,n2,n3 = input().strip().split(' ')
n = [int(n1),int(n2),int(n3)]
h1 = [int(h1_temp) for h1_temp in input().strip().split(' ')]
h2 = [int(h2_temp) for h2_temp in input().strip().split(' ')]
h3 = [int(h3_temp) for h3_temp in input().strip().split(' ')]

h1.reverse()
h2.reverse()
h3.reverse()
s1 = getS(h1)
s2 = getS(h2)
s3 = getS(h3)

s=[s1,s2,s3]
lens=[len(s1), len(s2), len(s3)]
ml=min(lens)
il=lens.index(ml)
s[il].reverse()
for x in s[il]:
    cnt=0  
    for i in range(3):
       if i!=il:
          if x in s[i]:
               cnt+=1
    if cnt==2:
       print(x)
       break
