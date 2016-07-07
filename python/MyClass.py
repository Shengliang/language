import json
import csv
import pickle 
import sys
import string

# GNode represent a object as a node in a Graph.
# A GNode has links (or pointers) that link to other GNodes. 

class GNode(object):
	"""GNode Class"""
	def __init__(self, name):
		self.properties = {
                   'name':name,
                }
	        self.links = []	

	def property(self, key, val=None):
		if not (val is None):
			self.properties[key] = val
		return self.properties[key]

	def add_link(self, obj):
		self.links.append(obj)

	def vars(self):
	   self.property('type', type(self).__name__)
	   if len(self.links) > 0 :
		self.property('links', [ item.vars() for item in self.links])
   	   return self.properties

class PA(GNode):
	"""Programming Assignment"""
	def score(self, n=None):
		return self.property('score', n)
	pass

class Student(GNode):
	"""Student Type"""
	def grade(self):
		total_scores = 0
		for pa in self.links:
			total_scores += pa.score()
		self.property('grade', total_scores)
	pass

class Class(GNode):
	"""Class Type"""
	pass

name = "4357 Embedded Firmware"
c = Class(name)
s1 = Student("Alice")
s2 = Student("Bob")

pa1 = PA("python")
pa2 = PA("C")

# Adds two assignments to student s1
s1.add_link(pa1)
s1.add_link(pa2)

# Adds 1 assignment to student s2
s2.add_link(pa1)

# Add two students to class c
c.add_link(s1)
c.add_link(s2)
for s in c.links:
   for pa in s.links:
       pa.score(100)

for s in c.links:
	s.grade()

prefix=c.property("name")
prefix=string.replace(prefix, " ", "_")
filename = prefix + ".json"
with open(filename, 'w') as fout:
    json.dump(c.vars(),fout, sort_keys=True, indent=4)
    fout.close()

with open(filename, 'r') as fin:
   x = json.load(fin)
   print "-" * 80
   json.dump(x, sys.stdout, sort_keys=False, indent=4)
   fin.close()

print "-" * 80
print "ref: http://www.diveintopython3.net/serializing.html"
fname = prefix + ".pickle"
with open(fname, 'wb') as fout:
    pickle.dump(c,fout)
    fout.close()

with open(fname, 'rb') as fin:
    x = pickle.load(fin)
    json.dump(x.vars(), sys.stdout, sort_keys=True, indent=4)
    fin.close()

