import numpy as np
import matplotlib.pyplot as plt

from scipy.integrate import solve_ivp
sol = solve_ivp(lambda t, y: t-y, [0, 15], [2], rtol = 1e-5)

plt.plot(sol.t, sol.y[0], 'k--s')
plt.show()
