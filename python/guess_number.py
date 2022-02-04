import random

def read_integer(prompt):
    s = input(prompt)
    while not s.strip().isdigit():
        s = input(prompt)
    return int(s)

guessesTaken  = 0

def guess(start, end):
    global guessesTaken
    global num_of_tries
    rand_num = random.randint(start, end)
    print("random number:", rand_num)
    prompt = "Guess a number from {0} to {1}: ".format(start, end)
    ans = "You lose"
    while guessesTaken < num_of_tries:
        guessesTaken  = guessesTaken + 1
        x = read_integer(prompt)
        if not (x >= start and x <= end):
            prompt = "Not in range [{0},{1}] Guess a number from {0} to {1}:".format(start, end)
        elif x  < rand_num:
            prompt = "Guess a bigger number than {0} :".format(x)
        elif x > rand_num:
            prompt = "Guess a smaller number than {0} :".format(x) 
        else:
            ans = "You Win! You got it {0}.".format(x)
            break
    return ans

title = "Guess My Number Program 2"

print(title)

name = input("Enter your name ")

num_of_tries = read_integer("Max number of tries ")

start = read_integer("start value ")
end = read_integer("end value ")

ans = guess(start, end)
print(name)
print("{0} out of {1}".format(guessesTaken, num_of_tries))
print(ans)
