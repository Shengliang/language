import acc;

verbosityLevel = 3

# Caesar substitution cipher
#  shift n
#  mod n = 128  ASCII
#    https://www.asciitable.com/
class EncryptRecord:
    def __init__(self, shift_n, mod_n = 128):
        self.mod_n = mod_n
        self.shift_n = shift_n % mod_n

    def EncryptArray(self, arr):
        n = len(arr)
        cypher_arr = [ 0 for i in range(n) ]
        for i in range(n):
            cypher_arr[i] = (self.mod_n + ord(arr[i]) + self.shift_n) % self.mod_n    
            cypher_arr[i] = chr(cypher_arr[i])
        return cypher_arr

    def DecryptArray(self, cypher_arr):
        n = len(cypher_arr)
        arr = [ 0 for i in range(n) ]
        for i in range(n):
            arr[i] = (self.mod_n + ord(cypher_arr[i]) - self.shift_n) % self.mod_n
            arr[i] = chr(arr[i])
        return arr 

    def EncryptRecord(self, record):
        n = len(record)
        cypher_record = [ None for i in range(n) ]
        for i in range(n):
            cypher_record[i] = "".join(self.EncryptArray(list(record[i])))
        return cypher_record

    def DecryptRecord(self, cypher_record):
        n = len(cypher_record)
        record = [ None for i in range(n) ]
        for i in range(n):
            record[i] = "".join(self.DecryptArray(list(cypher_record[i])))
        return record


class DataRecord:
    def __init__(self, filename):
        self.fileName = filename
        self.LAST_NAME_IDX = 0
        self.FIRST_NAME_IDX = 1
        self.ID_IDX = 2
        self.UNAME_IDX = 3
        self.PASSWORD_IDX = 4

        self.userNameObj = acc.UserName()
        self.passwordObj = acc.Password()

        self.userDataEntered = False
        self.userPasswordEntered = False
        self.PasswordVerified = False
        self.usernameFoundFlag = False

        self.caesar = EncryptRecord(2, 128);

        # Curent record
        self.record = [ '' for i in range(5)]
        # record array
        self.records = []
        # Hash Table: map uname_idx_hmap to records array index
        # Use hash table to check if uname_idx_hmap exist or not.
        self.uname_idx_hmaps = {}

    def getLastName(self, record):
        return record[self.LAST_NAME_IDX]
    def setLastName(self,record,lname):
        record[self.LAST_NAME_IDX] = lname

    def getFirstName(self,record):
        return record[self.FIRST_NAME_IDX]
    def setFirstName(self,record,fname):
        record[self.FIRST_NAME_IDX] = fname

    def getID(self,record):
        return record[self.ID_IDX]
    def setID(self,record,id):
        record[self.ID_IDX] = id

    def getUName(self, record):
        return record[self.UNAME_IDX]
    def setUName(self, record, uname):
        record[self.UNAME_IDX] = uname

    def getPassword(self, record):
        return record[self.PASSWORD_IDX]
    def setPassword(self, record, passwd):
        record[self.PASSWORD_IDX] = passwd

    def InputUserData(self):
        self.userNameObj.InputUserData()
        self.setFirstName(self.record, self.userNameObj.firstNameEntered)
        self.setLastName(self.record, self.userNameObj.lastNameEntered)
        self.setID(self.record, self.userNameObj.idNumberEntered)
        self.setUName(self.record, self.userNameObj.unameComplete)
        if verbosityLevel >= 3:
            print(self.record)
        self.userDataEntered = True

    def InputPassword(self):
        self.setPassword(self.record, self.passwordObj.InputPassword())
        if verbosityLevel >= 3:
            print(self.record)
        self.userPasswordEntered = True

    # append a record to a file
    def AppendRecordToFile(self):
        file_handle = open(self.fileName, 'a+')
        record = self.caesar.EncryptRecord(self.record)
        file_handle.write(','.join(record))
        file_handle.write('\n')
        file_handle.close()

    def ReadRecordFromFile(self):
        self.records = []
        self.uname_idx_hmaps = {}

        read_file_handle = None
        # open file for read only, quit if open file error
        try:
            read_file_handle = open(self.fileName, 'r+')
        except IOError:
            return
       
        # read a line from file
        read_value = read_file_handle.readline()
        # remove white space and newline
        read_value = read_value.rstrip()
        if verbosityLevel >= 3:
            print("current read value = [", read_value, "]")
        i = 0
        while read_value != '':
            record = read_value.split(',')
            if len(record) != 5:
                continue
            self.records.append(record)
            uname = self.getUName(record)
            self.uname_idx_hmaps[uname] = i
            i = i + 1
            read_value = read_file_handle.readline()
            read_value = read_value.rstrip()
            if verbosityLevel >= 3:
                print("current read value = [", read_value, "]")
        read_file_handle.close()
        return

    def getRecordFromFile(self, uname):
        self.ReadRecordFromFile()
        if uname in self.uname_idx_hmaps:
            i = self.uname_idx_hmaps[uname]
            self.record = self.caesar.DecryptRecord(self.records[i])
            self.usernameFoundFlag = True

    def DisplayRecords(self):
        if not self.PasswordVerified:
            print("Password is not verified. Skip display.")
            # return
        self.ReadRecordFromFile()
        if verbosityLevel >= 3:
            print("display:", self.records)
        for r in self.records:
            record = self.caesar.DecryptRecord(r)
            print(",".join(record))

    def VerifyUserNameAndWriteToFile(self):
        if not self.userDataEntered or not self.userPasswordEntered:
            print("New record is incompleted. Nothing to save.")
            return

        uname = self.getUName(self.record)
        passwd = self.getPassword(self.record)
        self.ReadRecordFromFile()

        # Append "1" if seen duplciate user name
        while uname in self.uname_idx_hmaps:
            uname = uname + "1"
        self.setUName(self.record, uname)

        i = len(self.records)
        self.uname_idx_hmaps[uname] = i
        if verbosityLevel >= 3:
            print("Append:", self.record)
        self.records.append(self.record)
        self.AppendRecordToFile()

        # clear current record after append it to a file.
        self.userDataEntered = False
        self.userPasswordEntered = False
        self.record = [ '' for i in range(5)]

    def VerifyLogin(self):
        self.PasswordVerified = False
        self.ReadRecordFromFile()
        uname = input("login user name:").rstrip()
        passwd = input("login password:").rstrip()
        if verbosityLevel >= 3:
            print(uname, passwd)
        self.getRecordFromFile(uname)
        if not self.usernameFoundFlag:
            print("Record '" + uname + "' is not found.")
            return

        record_passwd = self.getPassword(self.record)
        if passwd == record_asswrd:
            print("Found valid user:", record)
            self.PasswordVerified = True
        else:
            print("Found '" + uname + "'; however, password does not match.")

    def WriteRecordsToFile(self):
        # delete records infile, overwrite records to the file
        file_handle = open(self.fileName, 'w+')
        for r in self.records:
            file_handle.write(','.join(r) + '\n')
        file_handle.close()
    
    def SortByLastName(self):
        self.ReadRecordFromFile()
        self.records.sort()
        self.WriteRecordsToFile()
        self.ReadRecordFromFile()



