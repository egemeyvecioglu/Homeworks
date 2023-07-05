import matplotlib.pyplot as plt
import numpy as np

x = [-4,-3,-2,-1,0,1,2,3,4,5,6,7]
y = 3 * [1/4, 1/4*np.exp(-3j*np.pi/2), 1/4*np.exp(-6j*np.pi/2), 1/4*np.exp(-6j*np.pi/2)] 



#plotting the magnitude and phase of the coefficients
mag_coeffs = np.abs(y)

phase_coeffs = np.angle(y)


fig, axs = plt.subplots(2, 1, figsize=(8, 6))

axs[0].stem(x, mag_coeffs, 'o')
axs[0].set_ylabel('Magnitude')
axs[0].set_title('Magnitude plot |a$_{k}$|')

axs[1].stem(x, phase_coeffs, 'o')
axs[1].set_ylabel('Phase (radians)')
axs[1].set_title('Phase plot <a$_{k}$')

plt.show()
#save as pdf image
fig.savefig('q6b.pdf', bbox_inches='tight')