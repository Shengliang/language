# GNode represent a object as a node in a Graph.
# A GNode has links (or pointers) that link to other GNodes. 

class GNode(object):
	"""GNode Class"""
	def __init__(self, id, name):
		#print "Class __init__"
		self.properties = {'id':id, 'name':name }
		self.links = []

	def info(self):
		#print "Type: %s " % type(self)
		for k,v in self.properties.iteritems():
			if type(v) == type(1):
				print "%20s=%d " % (k,v)
			elif type(v) == type('string'):
				print "%20s=%s " % (k,v)
			else :
				print "%20s=%s " % (k,type(v))

		for item in self.links:
			item.info()
		return

	def html(self):
		#print "Type: %s " % type(self)
		s = ''
		for k,v in self.properties.iteritems():
			if type(v) == type(1):
				s += str(v)
				s += ' '
			elif type(v) == type('string'):
				s += v
			else :
				s += type(v)

		o = '<li>' +  s  + '</li>\n'
		o += '<ol>\n'
		for item in self.links:
			o += item.html()
		o += '</ol>\n'
		return o

	def property(self, key, val=None):
		if not (val is None):
			self.properties[key] = val
		return self.properties[key]

	def add(self, obj):
		self.links.append(obj)

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
			if type(pa) == PA:
				total_scores += pa.score()
		self.property('grade', total_scores)
	pass

class Class(GNode):
	"""Class Type"""
	pass

id = 4357
name = "Embedded Firmware"
c = Class(id, name)

s1 = Student(1, "Alice")
s2 = Student(2, "Bob")

pa1 = PA(1, "Script Language")
pa2 = PA(2, "C Language")

# Adds two assignments to student s1
s1.add(pa1)
s1.add(pa2)

# Adds 1 assignment to student s2
s2.add(pa1)

# Add two students to class c
c.add(s1)
c.add(s2)
for s in c.links:
   for pa in s.links:
       pa.score(100)

for s in c.links:
	s.grade()

o = c.html()
print "Content-type: text/html\n\n"

print "<html><head>Class Grade</head>\n";
print "<body>\n";
print "<ol>\n" + o + "</ol>\n"
print "</body>\n";
print "</html>\n";
