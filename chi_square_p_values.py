import scipy.stats as stats


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


for filename in files:
	with open(filename, "r") as file:
		lines = file.readlines()
		file.close()

	print(f"Successfully read {filename}")
	for i, line in enumerate(lines):
		if line.startswith("###"):
			continue
		components = line.split(", ")
		k, xi, df = int(components[0]), float(components[1]), int(components[2])
		assert(df == 2**k - 1)
		
		p_val = stats.chi2.sf(xi, df)
		new_line = ", ".join([f"{k}", f"{xi:.8f}", f"{df}", f"{p_val:.8f}"]) + "\n"
		lines[i] = new_line

	print(f"Computed p-values for {filename}")
	with open(filename, "w") as file:
		file.writelines(lines)
		file.close()
	print(f"Successfully wrote to {filename}")

