
class Person:
    def __init__(self,name,age):
        self.name=name
        self.age=age

    def __lt__(self,other):
        return (self.age == other.age) and (self.name < other.name) or (self.age < other.age)


persons=[ Person("Alice", 31),  Person("Bob", 12), Person("David", 31) ]
results=sorted(persons);

for p in persons:
  print p.age, " ", p.name

for p in results:
  print p.age, " ", p.name

class ListNode(object):
   def __init__(self, val=None, next=None):
       self.val = val
       self.next = next



bucket = [ [ListNode(), None] for i in range (101) ]
persons=[ Person("Alice", i) for i in range(1,101) ];
persons+=[ Person("Bob", i) for i in range(1,101) ];

input = ListNode()
curr = input
for p in persons:
   curr.next = ListNode(p)
   curr = curr.next

curr = input.next
while curr:
  p = curr.val
  curr = curr.next
  n = bucket[p.age]
  if n[1]:
    n[1].next = ListNode(p);
    n[1] = n[1].next
  else:
    n[1] = ListNode(p);
    n[0].next = n[1]

ans = [ListNode(), None]
for b in bucket:
   c = b[0].next
   if c :
       if ans[1]:
          ans[1].next = c
          ans[1] = b[1]
       else:
          ans = b

h = ans[0].next
while h:
  print h.val.age, " ", h.val.name
  h = h.next
