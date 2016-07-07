# ref: https://docs.python.org/2/tutorial/datastructures.html

# stack: last-in, first-out
stack = [3, 4, 5]
stack.append(6)
stack.append(7)
print stack.pop()
def is_even(x):
  return x & 1 == 0
def is_odd(x):
  return x & 1 == 1
print filter(is_even, stack)
print filter(is_odd, stack)

s = [x**2 for x in stack]
print s

# queue: first-in, first-out
from collections import deque
queue = deque(["Eric", "John", "Michael"])
queue.append("Terry")
queue.append("Graham")
print queue.popleft()
s = [len(str) for str in queue]
print s

# List comprehensions
print [(x,y) for x in [1,2,3] for y in ['a','b', 'C'] if is_odd(x) and y.islower()]

# set comprehensions
a = {x for x in 'abracadabra' if x not in 'abc'}
print a

matrix=[
[1,2,3,4],
[5,6,7,8],
[9,10,11,12],
]

# transpose matrix
print [[row[i] for row in matrix] for i in range(4)]
print zip(*matrix)

# tuples
p1 = 24, 'Bob'
p2 = 24, 'Alice'
p3 = 23, 'David'
v = [p1, p2, p3]
print v
print sorted(set(v))

# dictionaries
dic = {'k1':'v1', 'k2':'v2', 'k3':'v3'}
for k, v in dic.iteritems():
  print k, v 
p1 = {'name': 'Bob', 'age': 24}
p2 = {'name': 'Alice', 'age': 24}
p3 = {'name': 'David', 'age': 23}
v = [p1, p2, p3]
for i,v in enumerate(v):
  print i, v['name'], v['age']

# looping
for i,v in enumerate(['tic', 'tac', 'toe']):
  print i, v
