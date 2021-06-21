import numpy as np
from scipy import linalg

print("ex 5")

a = [[1, -1, -1, 0, 0], [0, 0, 1, -1, 0], [-5, -2, 0, 0, 0], [0, 2, 0, -3, 0], [0, 0, 0, 3, -1]]
b = [[0], [-2], [-10], [0], [0]]

x = np.dot(linalg.inv(a), b)

print(x)

print("\nex 6")

a = [[1, -1, -1], [-100, -100, 0], [0, 100, -100]]
b = [[0], [-7], [2]]

x = np.dot(linalg.inv(a), b)

print(x)