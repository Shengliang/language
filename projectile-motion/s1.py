# Importing modules
from numpy import *
from pylab import *

g=9.8

α=float(input("Enter the angle in degrees\n"))
# converting angle in radians
α=radians(α)

# Initial velocity of projectile
u=float(input("Enter initial velocity in m/s \n"))

# Evaluating Range
R=u**2*sin(2*α)/g

# Evaluating max height
h=u**2*(sin(α))**2/(2*g)

# Creating array of x with 50 points
x=linspace(0, R, 20)

# Solving for y
y=x*tan(α)-(1/2)*(g*x**2)/(u**2*(cos(α))**2 )
# Data plotting

figure(1,dpi=300)
plot(x,y,'r-',linewidth=3)
xlabel('x')
ylabel('y')
ylim(0, h+0.05)
savefig('proj.jpg')
show()

print(f"{'S. No.':^10}{'x':^10}{'y':^10}")
for i in range(len(x)):
   print(f"{i+1:^10}{round(x[i],3):^10}{round(y[i],3):^10}")
