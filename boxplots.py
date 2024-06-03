import matplotlib.pyplot as plt
import numpy as np
from scipy import stats


files = [
	"./generators/c++_mt19937/chi_square_results.txt",
	"./generators/c_stdlib_rand/chi_square_results.txt",
	"./generators/python_random/chi_square_results.txt",
	"./generators/python_numpy_random/chi_square_results.txt",
	"./generators/java_math_random/chi_square_results.txt",
	"./generators/java_util_random/chi_square_results.txt",
	"./generators/matlab_randi/chi_square_results.txt",
	"./generators/xorshift64/chi_square_results.txt",
	"./generators/xorshift64_star/chi_square_results.txt",
	"./generators/atmospheric_noise/chi_square_results.txt",
]

generators = [
	"C++ mt19937",
	"C stdlib rand",
	"Python random",
	"Numpy random",
	"Java Math.Random",
	"Java Util.Random",
	"MATLAB randi",
	"Xorshift 64",
	"Xorshift* 64",
	"Atmosphere",
]

p_values = {generator: [] for generator in generators}


for filename, generator in zip(files, generators):
	with open(filename, "r") as file:
		lines = file.readlines()
		file.close()

	for i, line in enumerate(lines):
		if (line.startswith("###")):
			continue
		components = line.split(", ")
		p_val = float(components[3])
		assert(p_val >= 0 and p_val <= 1)

		p_values[generator].append(p_val)


def five_number_summary(data):
	data = sorted(data)
	return [
		np.min(data),
		np.percentile(data, 25),
		np.median(data),
		np.percentile(data, 75),
		np.max(data),
	]


fig, ax = plt.subplots(figsize=(6.5, 9))
data = list(p_values.values())
ax.boxplot(
	data, 
	vert=False, 
	patch_artist=True, 
	boxprops=dict(facecolor='lightblue')
)
ax.set_yticklabels(generators)
plt.show()

