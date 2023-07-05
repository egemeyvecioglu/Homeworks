import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import sawtooth

#Part A
def fourier_coeff(signal, period, n, t):

    w_0 = 2*np.pi/period
    coeffs = np.zeros(n+1, dtype=complex)

    coeffs[0] = np.mean(signal)

    for k in range(1, n+1):
        cos_k = 0
        sin_k = 0
        for m in range(0, len(t)):
            cos_k += signal[m] * np.cos(k * w_0 * t[m])
            sin_k += signal[m] * np.sin(k * w_0 * t[m])
        cos_k = 2* cos_k / period
        sin_k /= 2* sin_k / period
        coeffs[k] = cos_k - 1j * sin_k

    return coeffs

#Part B
def fourier_approx(coeffs, period, n, t):
    w_0 = 2*np.pi/period
    approximated_signal = np.zeros_like(t, dtype=complex)


    for m in range(0, len(t)):
        for k in range(0, n+1):
            approximated_signal[m] +=  coeffs[k] * np.exp(1j * k * w_0 * t[m])
    return approximated_signal

# Part C
t = np.linspace(-0.5, 0.5, 1000, endpoint=False)
s = np.where(t < 0, -1, 1)

n_values = [1, 5, 10, 50, 999]
fig = plt.figure(figsize=(8, 8))

for i, n in enumerate(n_values):
    coeffs = fourier_coeff(s, 1, n, t)
    approximated_signal = fourier_approx(coeffs, 1, n, t)
    plt.subplot(len(n_values), 1, i+1)
    plt.plot(t, s, label="Original")
    plt.plot(t, approximated_signal, label="n={}".format(n))
    plt.legend()
    plt.xlabel('n')
    plt.ylabel('s[n]')
    plt.xlim(-0.8, 0.6)
plt.suptitle('Approximation of square wave function using Fourier Series coefficients')
plt.show()

fig.savefig('q7-partc.pdf', bbox_inches='tight')

#Part D
sawtooth_wave = sawtooth(2 * np.pi * t)
n_values = [1, 5, 10, 50, 100]

fig = plt.figure(figsize=(8, 8))

for i, n in enumerate(n_values):
    coeffs = fourier_coeff(sawtooth_wave, 1, n, t)
    approximated_signal = fourier_approx(coeffs, 1, n, t)
    
    plt.subplot(len(n_values), 1, i+1)
    plt.plot(t, sawtooth_wave, label="Original")
    plt.plot(t, approximated_signal, label="n={}".format(n))
    plt.legend(loc='upper right')
    plt.xlim(-0.6, 0.8)
    plt.xlabel('n')
    plt.ylabel('s[n]')

plt.suptitle('Approximation of sawtooth wave using Fourier Series coefficients')
plt.show()

fig.savefig('q7-partd.pdf', bbox_inches='tight')
