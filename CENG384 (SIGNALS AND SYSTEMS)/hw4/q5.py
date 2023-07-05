import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile as wavfile

def fft(x):
    N = int(len(x))

    if N <= 1:
        return x
    
    even = fft(x[::2])
    odd = fft(x[1::2])


    X = np.zeros(N, dtype=np.complex128)
    for k in range(int(N/2)):
        factor = np.exp(-2j * np.pi * (k-1) / N)
        X[k] = odd[k] + factor * even[k]
        if k == 0:
            X[k + int (N/2)] = odd[k] + np.exp(-2j * np.pi * (int (N/2) -1) / N) * even [k]
        else:    
            X[k + int (N/2)] = odd[k] - factor * even [k]

    return X


def ifft(x):
    inverse = fft(np.conj(x))/len(x)
    return np.real(np.conj(inverse))
    

if __name__ == '__main__':

    # read encoded.wav
    sample_rate, data = wavfile.read('encoded.wav')

    print('sample rate: ', sample_rate)

    duration = len(data) / sample_rate
    time = np.linspace(0, duration, len(data))

    # plot the encoded signal in time domain
    fig1 = plt.figure()
    plt.plot(time,data)
    plt.title('Encoded Signal in Time Domain')
    plt.xlabel('Time(s)')
    plt.ylabel('Amplitude')
    plt.show()
    fig1.savefig('encoded_time.pdf')



    frequency_domain = fft(data)
    frequencies = np.linspace(-len(data)//2, len(data)//2, len(data))

    # plot the magnitude of the frequency domain
    fig2 = plt.figure()
    plt.plot(frequencies,np.abs(frequency_domain))
    plt.title('Encoded Signal in Frequency Domain')
    plt.xlabel('Frequency(Hz)')
    plt.ylabel('Amplitude')
    plt.show()
    #save as pdf
    fig2.savefig('encoded_freq.pdf')

    modified_freq = np.concatenate((np.flip(frequency_domain[:len(frequency_domain)//2]), np.flip(frequency_domain[len(frequency_domain)//2:]))) #solves the secret

    # plot the magnitude of the modified frequency domain
    fig3 = plt.figure()
    plt.plot(frequencies,np.abs(modified_freq))
    plt.title('Decoded Signal in Frequency Domain')
    plt.xlabel('Frequency()')
    plt.ylabel('Amplitude')
    plt.show()
    fig3.savefig('decoded_freq.pdf')

    modified_time = ifft(modified_freq)

    # plot the decoded signal in time domain
    fig4 = plt.figure()
    plt.plot(time, modified_time)
    plt.title('Decoded Signal in Time Domain')
    plt.xlabel('Time(s)')
    plt.ylabel('Amplitude')
    plt.show()
    fig4.savefig('decoded_time.pdf')

    # write the modified time domain to a wav file
    wavfile.write('decoded.wav', sample_rate, modified_time.real.astype(data.dtype))

