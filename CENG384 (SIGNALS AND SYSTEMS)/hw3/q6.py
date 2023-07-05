import matplotlib.pyplot as plt
import numpy as np

x = [0, 1, 2, 3]
y = [0, 1, 2, 1]

coeffs  = 4*[0]

T = 4
w_0 = 2*np.pi/T

my_exp = lambda k, n: np.exp(-1j * k * w_0 * n)

for n in range(0,4):
    for k in range(0,4):
        coeffs[n] += y[k] * my_exp(k, n)
    coeffs[n] /= T

fig = plt.figure(figsize=(8, 6))
x  = [-4,-3,-2,-1,0,1,2,3,4,5,6,7]
coeffs =  coeffs + coeffs + coeffs
print(coeffs)
plt.stem(x, coeffs, 'o')
plt.xlabel('k')
plt.ylabel('a$_{k}$')
plt.title('Fourier coefficients')
plt.grid()
plt.show()

fig.savefig('q6a.pdf', bbox_inches='tight')