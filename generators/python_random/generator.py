import random
import struct


BITSTRING_SIZE = 16_000_000


with open("randomness.txt", "wb") as f:
	for _ in range(int(BITSTRING_SIZE / 4)):
		r = random.randint(0, 2**32 - 1)
		b = struct.pack('>I', r)
		f.write(b)

