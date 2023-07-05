import matplotlib.pyplot as plt
import numpy as np

w0 = 2*np.pi

mag_b_2 = np.sqrt(1/(4 + 16 * w0**2))
mag_b_1 = np.sqrt(5/(4 + 4 * w0**2))
mag_b_0 = 1
mag_b1 = np.sqrt(5/(4 + 4 * w0**2))
mag_b2 = np.sqrt(1/(4 + 16 * w0**2))

phase_b_2 = np.arctan(-1) + np.arctan(2*w0)
phase_b_1 = np.arctan(1/2) + np.arctan(w0)
phase_b_0 = 0
phase_b1 =np.arctan(-1/2) + np.arctan(-w0)
phase_b2 = np.arctan(1) + np.arctan(-2*w0)

#print everything above
print('Magnitude of b_2: ', mag_b_2)
print('Phase of b_2: ', phase_b_2)
print()
print('Magnitude of b_1: ', mag_b_1)
print('Phase of b_1: ', phase_b_1)
print()
print('Magnitude of b_0: ', mag_b_0)
print('Phase of b_0: ', phase_b_0)
print()
print('Magnitude of b1: ', mag_b1)
print('Phase of b1: ', phase_b1)
print()
print('Magnitude of b2: ', mag_b2)
print('Phase of b2: ', phase_b2)

#pring phases in terms of pi
print()
print('Phase of b_2 in terms of pi: ', phase_b_2/np.pi)
print('Phase of b_1 in terms of pi: ', phase_b_1/np.pi)
print('Phase of b_0 in terms of pi: ', phase_b_0/np.pi)
print('Phase of b1 in terms of pi: ', phase_b1/np.pi)
print('Phase of b2 in terms of pi: ', phase_b2/np.pi)



fig, axs = plt.subplots(2, 1, figsize=(8, 6))

axs[0].stem(['b$_{-2}$', 'b$_{-1}$', 'b$_0$', 'b$_1$', 'b$_2$'],
           [ mag_b_2, mag_b_1, mag_b_0, mag_b1, mag_b2 ])
axs[0].set_ylabel('Magnitude')
axs[0].set_title('Magnitude plot |b$_{k}$|')

axs[1].stem(['b$_{-2}$', 'b$_{-1}$', 'b$_0$', 'b$_1$', 'b$_2$'],
            [phase_b_2, phase_b_1, phase_b_0, phase_b1, phase_b2])
axs[1].set_ylabel('Phase (radians)')
axs[1].set_title('Phase plot <b$_{k}$')

plt.show()
#save as pdf image
fig.savefig('q4c.pdf', bbox_inches='tight')