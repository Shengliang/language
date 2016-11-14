

def game(name):
   if name == 'Selina':
       print(name + " is the most awesome person in the entire history of awesome people!\n");
   elif name == 'Ella':
       print("Hi " +name +", why are you so dumb?\n");
   else:
       print("Hi " +name +", do I know you?\n");


game('Selina')
game('Sheng')
game('Ella')


def f2c(f):
    return (f-32)*5/9


def c2f(c):
    return (c*9/5+32)

def square(x):
    return x*x

def cube(x):
    return x**3


list = range(10)
print (list)


print (map(cube, list))
print (map(square, list))

abc = [ x**2 for x in range(10) ]
print(abc)

x = [c2f(100), f2c(c2f(100))]
print(x)

s="Selina"
print(s[0])
print(s[:2])
print(s[-2:])
