verbosityLevel = 2

class Menu:
    def __init__(self):
        self.menuChoiceString = ''
        self.menuChoiceInt = -1
        self.validateMenuChoice = False
    
        # Hash Table: 1 to 8 options
        self.option = {}
        self.option[1] = "Enter User Data"
        self.option[2] = "Validate Entered Password"
        self.option[3] = "Write Current User Record to a file (1 & 2 required)"
        self.option[4] = "Display all user records from a file"
        self.option[5] = "login with user name and password"
        self.option[6] = "sort records by last name"
        self.option[7] = "Exit Program"
    
    def DisplayMenu(self):
        for i in range(1,8):
            print(i, self.option[i])
        print("\n")
    
    def GetMenuInput(self):
        self.DisplayMenu()
        self.menuChoiceString = input ("Pick a Menu Option 1-7: ")
        self.ValidateMenuInput()
        return self.menuChoiceInt
    
    def ValidateMenuInput(self):
        if verbosityLevel > 2:
            print("Time to validate menu input")
            print("validateMenuChoice= ", self.validateMenuChoice)
        self.validateMenuChoice = False
        while self.validateMenuChoice == False:
            try:
                print("Trying to convert input to an Integer")
                self.menuChoiceInt = int(self.menuChoiceString)
            except TypeError:
                print("You must pick a number!")
                self.menuChoiceString = input("Pick a Menu Option 1-7: ")
            except ValueError:
                print("You must pick a number!")
                self.menuChoiceString = input("Pick a Menu Option 1-7: ")
            else:
                self.validateMenuChoice = True
    
            if  self.menuChoiceInt < 1 or self.menuChoiceInt > 7:
                print("You need to choose a number between 1 - 7")
                self.validateMenuChoice = False
                self.menuChoiceString = input("Pick a Menu Option 1-7: ")
            else:
                print("The menu option chosen is valid")
                break
