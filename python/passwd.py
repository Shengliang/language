#from easygui import *

verbosity_level = 1
# Hash Table: 1 to 8 options
option = {}

# Generate user name: fff + lll + iii
def get_user_name(first_name, last_name, id_num):
    return first_name[0:3] + last_name[0:3] + id_num[-3:]

option[1] = "Enter user information"
def enter_user_info(record):
    first_name = input("What is your first name? ")
    last_name = input("What is your last name? ")
    id_number = input("What is your id number?")
    user_name = get_user_name(first_name, last_name, id_number)
    print("User name is:", user_name)
    # Record format: 0:last_name, 1:first_name, 2:id, 3:user_name, 4:password
    record[0] = last_name
    record[1] = first_name
    record[2] = id_number
    record[3] = user_name
    return

option[2] = "validate password"
def is_valid(passwd):
    if len(passwd) < 7:
        print("Password length is too short.")
        return False
    has_upper = False
    has_lower = False
    has_num = False
    for c in passwd:
        if c.isupper():
            has_upper = True
        if c.islower():
            has_lower = True
        if c.isnumeric():
            has_num = True
    if not has_upper:
        print("missing upper case.")
    if not has_lower:
        print("missing lower case.")
    if not has_num:
        print("missing numbers.")
    return has_upper and has_lower and has_num

def enter_valid_password():
    done = False
    passwd = None
    while not done:
        passwd = input("Enter a password:")
        v = is_valid(passwd)
        if v:
            done = True
    return passwd

option[3] = "write record to a file"
def read_records(file_name):
    # record array
    records = []
    # Hash Table: map user_name to records array index
    # Use hash table to check if user_name exist or not.
    user_names = {}
    read_file_handle = None
    # open file for read only, quit if open file error
    try:
        read_file_handle = open(file_name, 'r+')
    except IOError:
        return records, user_names

    # read a line from file
    read_value = read_file_handle.readline()
    # remove white space and newline
    read_value = read_value.rstrip()
    if verbosity_level >= 3:
        print("current read value = [", read_value, "]")
    i = 0
    while read_value != '':
        record = read_value.split(',')
        records.append(record)
        user_names[record[3]] = i
        i = i + 1
        read_value = read_file_handle.readline()
        read_value = read_value.rstrip()
        if verbosity_level >= 3:
            print("current read value = [", read_value, "]")
    read_file_handle.close()
    return records, user_names

def append_record(file_name, record):
    file_handle = open(file_name, 'a+')
    print(record)
    file_handle.write(','.join(record))
    file_handle.write('\n')
    file_handle.close()

def verify_user_name_and_append_record_to_file(file_name, record):
    (records, user_names) = read_records(file_name)
    user_name = record[3]
    passwd = record[4]
    if user_name == '' or passwd == '':
        print("No new record to save.")
        return
    while user_name in user_names:
        user_name = user_name + "1"
    i = len(records)
    user_names[user_name] = i
    record[3] = user_name
    records.append(record)
    append_record(file_name, record)
    # clear current record after append it to a file.
    for i in range(5):
        record[i] = ''

option[4] = "display records"
def display_records(file_name):
    (records, user_names) = read_records(file_name)
    if verbosity_level >= 3:
        print("display:", records)
    for r in records:
        print(",".join(r))

option[5] = "exit"

option[6] = "login with user name and password"
def verify_login(file_name):
    (records, user_names) = read_records(file_name)
    user_name = input("login user name:").rstrip()
    passwd = input("login password:").rstrip()
    if verbosity_level >= 3:
        print(records)
        print(user_names)
        print(user_name, passwd)
    if user_name in user_names:
        index = user_names[user_name]
        record = records[index]
        if verbosity_level >= 3:
            print(record)
        if len(record) == 5 and passwd == record[4]:
            print("Found user:", record)
        else:
            print("Record '" + user_name + "' found; however, password does not match.")
    else:
        print("Record '" + user_name + "' is not found.")

option[7] = "sort records by last name"
def sort_by_last_name(file_name):
    (records, user_names) = read_records(file_name)
    # python default sort on 1st element (last_name)
    records.sort()
    write_records(file_name, records)

def write_records(file_name, records):
    # delete records infile, overwrite records to the file
    file_handle = open(file_name, 'w+')
    for r in records:
        file_handle.write(','.join(r) + '\n')
    file_handle.close()


def menu(record):
    file_name = 'userData.txt'

    op = input("\n select an option:")
    if op == '1':
        enter_user_info(record)
        if verbosity_level >= 3:
            print(record)
    elif op == '2':
        passwd = enter_valid_password()
        # Record format: 0:last_name, 1:first_name, 2:id, 3:user_name, 4:password
        record[4] = passwd
        print(record)
    elif op == '3':
        print("curr:", record)
        verify_user_name_and_append_record_to_file(file_name, record)
        print("reset:", record)
    elif op == '4':
        display_records(file_name)
    elif op == '5':
        exit(0)
    elif op == '6':
        verify_login(file_name)
    elif op == '7': # sort by last name
        sort_by_last_name(file_name)
    else:
        pass
    return record

if __name__ == '__main__':
    record = ["" for i in range(5)]
    for i in range(1,8):
        print(i, option[i])
    print("\n")
    while True:
        record = menu(record)
