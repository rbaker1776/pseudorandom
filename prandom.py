import scipy.stats as stats
import random
import math
import numpy as np


def bitstring(length: int, flag: str="random") -> str:
	if flag == "random":
		return "".join([str(random.randint(0,1)) for _ in range(length)])
	elif set(flag).issubset({"0", "1"}):
		return (flag * (length // len(flag) + 1))[:length]
		

def substring_distribution(b: str, k: int) -> list:
	dist = [0] * 2**k
	for i in range(len(b) - k + 1):
		dist[int(b[i:i+k], 2)] += 1
	return dist


def p_random_dist(dist: list) -> float:
	total = sum(dist)
	N = len(dist)
	E = [total / N] * N

	chi_square = sum((o - e)**2 / e for o, e in zip(dist, E))
	df = N - 1

	return stats.chi2.sf(chi_square, df)


def random_substr_dist(b: str) -> list:
	return [p_random_dist(substring_distribution(b, k)) for k in range(1, math.floor(math.log(len(b), 2)))]


def p_random(b: str) -> float:
	return np.prod(random_substr_dist(b))


b = bitstring(100000, "0101000111000011100110110110111001111111111011111101010010111100101010110100101000101001011001101001010101001010100101001001010111010010101001101001010101010101010101001010101010010101010101010010101010101011001010101001010101010010101010101010101010010101010100101010100101001001010010100101001010100100101000111100101010100010010001")
print(p_random(b))
print(p_random(bitstring(len(b))))

