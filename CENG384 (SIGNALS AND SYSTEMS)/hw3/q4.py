import matplotlib.pyplot as plt
import numpy as np

a_2 = 0.5 * np.exp(-1j*np.pi/4)
a_1 = 1 - 1/(2j)
a_0 = 1
a1 = 1 + 1/(2j)
a2 = 0.5 * np.exp(1j*np.pi/4)

mag_a_2 = np.abs(a_2)
phase_a_2 = np.angle(a_2)

mag_a_1 = np.abs(a_1)
phase_a_1 = np.angle(a_1)

mag_a_0 = np.abs(a_0)
phase_a_0 = np.angle(a_0)

mag_a1 = np.abs(a1)
phase_a1 = np.angle(a1)

mag_a2 = np.abs(a2)
phase_a2 = np.angle(a2)

fig, axs = plt.subplots(2, 1, figsize=(8, 6))

axs[0].stem(['a$_{-2}$', 'a$_{-1}$', 'a$_0$', 'a$_1$', 'a$_2$'],
           [ mag_a_2, mag_a_1, mag_a_0, mag_a1, mag_a2 ])
axs[0].set_ylabel('Magnitude')
axs[0].set_title('Magnitude plot |a$_{k}$|')

axs[1].stem(['a$_{-2}$', 'a$_{-1}$', 'a$_0$', 'a$_1$', 'a$_2$'],
            [phase_a_2, phase_a_1, phase_a_0, phase_a1, phase_a2])
axs[1].set_ylabel('Phase (radians)')
axs[1].set_title('Phase plot <a$_{k}$')

plt.show()
#save as pdf image
fig.savefig('q4.pdf', bbox_inches='tight')