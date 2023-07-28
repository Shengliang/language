# Importing modules
from numpy import *
from pylab import *

g=9.8

# Projectile Function
def Projectile_Plot(u,α):

   # for pronging legend
   αd=α

   # converting angle in radians
   α=radians(α)

   # Evaluating Range
   R=u**2*sin(2*α)/g

   # Evaluating max height
   h=u**2*(sin(α))**2/(2*g)

   # Creating array of x with 20 points
   x=linspace(0, R, 20)

   # Solving for y
   y=x*tan(α)-(1/2)*(g*x**2)/(u**2*(cos(α))**2 )

   # Data plotting
   figure(1,dpi=300)
   plot(x,y,'-',linewidth=2,label=f'α = {αd}')
   xlabel('x')
   ylabel('y')
   ylim(0, h+0.05)
   legend()
   savefig('proj2.jpg')


# Input data
# Initial velocity of projectile
u=float(input("Enter initial velocity in m/s \n"))
for i in range(15,75,5):
	Projectile_Plot(u,i)

show()
