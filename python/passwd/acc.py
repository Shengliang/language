verbosityLevel = 3

class UserName:
   def __init__(self):
       self.firstNameEntered = None
       self.lastNameEntered = None
       self.idNumberEntered = None
       self.unameComplete = None

   def InputFirstName(self):
       self.firstNameEntered = input("What is your first name? ")

   def InputLastName(self):
       self.lastNameEntered = input("What is your last name? ")

   def InputStudentID(self):
       self.idNumberEntered = input("What is your student id number?")
   
   def InputUserData(self):
       self.InputFirstName()
       self.InputLastName()
       self.InputStudentID()
       self.CreateUserName()

   # Generate user name: fff + lll + iii
   def CreateUserName(self):
       if self.firstNameEntered and self.lastNameEntered and self.idNumberEntered:
           self.unameComplete = self.firstNameEntered[0:3] + self.lastNameEntered[0:3] + self.idNumberEntered[-3:]
           print("User name is:", self.unameComplete)
       else:
           print("User name is not valid.")


class Password:
    def __init__(self):
        self.passwordEntered = "null password"
        self.has_upper = False
        self.has_lower = False
        self.has_num = False
    
    def isValid(self):
        self.has_upper = False
        self.has_lower = False
        self.has_num = False
        for c in self.passwordEntered:
            if c.isupper():
                self.has_upper = True
            if c.islower():
                self.has_lower = True
            if c.isnumeric():
                self.has_num = True
        passwdLen = len(self.passwordEntered)
        if verbosityLevel > 2:
            if not self.has_upper:
                print("missing upper case.")
            if not self.has_lower:
                print("missing lower case.")
            if not self.has_num:
                print("missing numbers.")
            if passwdLen < 7:
                print("Password length is too short.")
        return passwdLen >= 7 and self.has_upper and self.has_lower and self.has_num

    def InputPassword(self):
        done = False
        self.passwordEntered = "null password"
        while not done:
            self.passwordEntered = input("Enter a password:")
            if self.isValid():
                done = True
        return self.passwordEntered
