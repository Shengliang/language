import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

def plot():
    fig, ax = plt.subplots(figsize=(8, 5))
    # set the x-spine
    ax.spines['left'].set_position('zero')

    # turn off the right spine/ticks
    ax.spines['right'].set_color('none')
    ax.yaxis.tick_left()

    # set the y-spine
    ax.spines['bottom'].set_position('zero')

    # turn off the top spine/ticks
    ax.spines['top'].set_color('none')
    ax.xaxis.tick_bottom()


def model(t, z):
  y, v = z
  dy_dt = v
  dv_dt = - g
  dz_dt = [dy_dt, dv_dt]
  return dz_dt

def yFunc(v):
  v0 = v
  t = np.linspace(0, 10, 100)
  t_span = (t[0], t[-1])
  y0 = 0
  y0 = [y0, v0]
  sol = solve_ivp(model, t_span, y0, t_eval=t)
  return sol

plot()
g  = 9.8
v_guess = [35, 55, 75]
color = ['red', 'blue', 'green']
for i in range(len(v_guess)):
  sol = yFunc(v_guess[i])
  t = sol.t
  y = sol.y[0, :]
  plt.plot(t, y, ls=':', color=color[i], lw=3, label='v = %0.2f'%v_guess[i])
plt.xlabel('$t$', fontsize=14)
plt.ylabel('$y(t)$', fontsize=14)
plt.axvline(x = 10, ls='--', color='black')
plt.legend(loc='best')
plt.show()





