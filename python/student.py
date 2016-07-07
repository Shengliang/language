# ref: https://h3manth.com/content/python-objects-json-string
import json
class Student:
    def __init__(self,name,email,contact,skills):
        self.email=email
        self.contact=contact
        self.name=name
        self.skills=[skills]

james=Student("James","j@j.com","+1 (778)999-0007","Python")
 
print json.dumps(vars(james),sort_keys=True, indent=4)
 
