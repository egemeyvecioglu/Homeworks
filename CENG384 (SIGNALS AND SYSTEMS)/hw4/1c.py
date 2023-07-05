import numpy as np

t = np.linspace(-5, 10, 1000)
y =  -2 * np.exp(-t) + 3 * np.exp(-2*t)
y = y * (t >= 0)

import matplotlib.pyplot as plt
figure = plt.figure()

plt.plot(t, y)
plt.xlim(-5, 10)
plt.xlabel('t')
plt.ylabel('y')
plt.title('y = (-2 * exp(-t) + 3 * exp(-2*t)) * u(t)')
plt.grid(True)
plt.show()

#save figure as pdf
figure.savefig('1c.pdf', format='pdf')