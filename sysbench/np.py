import numpy as np
import matplotlib.pyplot as plt

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter

# Create a random number generator with a fixed seed for reproducibility
rng = np.random.default_rng(19680801)

def func_normal():
    # s = np.random.normal(0, 0.1, 1000)
    mean_val = 100
    std_val = 10
    s = np.random.normal(mean_val, std_val, 1000)
    print("mean:", abs(mean_val - np.mean(s)))
    print("variance:", abs(std_val - np.std(s, ddof=1)))
    a = [ int(x) if x < 100 else int(200-x) for x in s ]
    print(a)
    s = a
    count, bins, ignored = plt.hist(s, 100, density=True)
    sigma = std_val
    mu = mean_val
    plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) * np.exp( - (bins - mu)**2 / (2 * sigma**2) ),
             linewidth=2, color='r')
    plt.show()

def ex1():
	N_points = 1000
	n_bins = 10
	# Generate two normal distributions
	dist1 = rng.standard_normal(N_points)
	dist2 = [ int(x) for x in 20 * rng.standard_normal(N_points) + 50]
	fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True)
	# We can set the number of bins with the *bins* keyword argument.
	print(dist2)
	axs[0].hist(dist1, bins=n_bins)
	axs[1].hist(dist2, bins=n_bins)
	plt.show()

ex1()
# func_normal()
