# %% Imports
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from ode_helpers import state_plotter

# %% Define derivative function
def f(t, y, c):
    dydt = [c[0] * y[0]]
    return dydt

# %% Define time spans, initial values, and constants
tspan = np.linspace(0, 3, 25)
yinit = [10]
c = [1.02]

# %% Solve differential equation
sol = solve_ivp(lambda t, y: f(t, y, c),
                [tspan[0], tspan[-1]], yinit, t_eval=tspan, rtol = 1e-5)

# %% Plot states
state_plotter(sol.t, sol.y, 1)
