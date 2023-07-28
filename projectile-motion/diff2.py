# %% Imports
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# %% Define independent function and derivative function
def x(t):
    return np.cos(3 * t)

def f(t, y, c):
    dydt = x(t) - y / 4
    return dydt

# %% Define time spans, initial values, and constants
tspan = np.linspace(0, 15, 1000)
yinit = [-1]
c = []

# %% Solve differential equation
sol = solve_ivp(lambda t, y: f(t, y, c),
                [tspan[0], tspan[-1]], yinit, t_eval=tspan, rtol = 1e-5)

# %% Plot independent and dependent variable
# Note that sol.y[0] is needed to extract a 1-D array
plt.figure(1)
plt.clf()
fig, ax = plt.subplots(num=1)
ax.plot(sol.t, x(sol.t), 'k-', label='Input')
ax.plot(sol.t, sol.y[0], 'k--', label='Output')
ax.legend(loc='best')
plt.show()
