import matplotlib.pyplot as plt

def part_b(filename):
    with open(filename, 'r') as f: #get and arrange the data

        data = f.read().split(",")  
        starting_index = int(data[0])
        a =int(float(data[1]))
        b =int(float(data[2]))

        data = [float(i) for i in data[3:]]

    xx = [] #new time values
    shifted_signal = [] #new signal amplitude

    for n in range(starting_index, starting_index+len(data)):
        n_shifted = (n - b)/a   # compute the shifted index

        if(int(n_shifted)==n_shifted): #if the shifted index is not integer, it will disapper.
            shifted_signal.append(data[n]) 
            xx.append(n_shifted)
    fig = plt.figure(figsize=(16, 8))
    fig.set_size_inches(8.27, 5.5)
    
    plt.stem(xx,shifted_signal,markerfmt="")  # plot the shifted and scaled signal
    plt.xlabel('Time index (n)')
    plt.ylabel('Amplitude')
    plt.title(f'Shifted and scaled signal x[an+b] with a={a} and b={b} for {filename[:-11]}')
    plt.savefig(f"7b_{filename}.pdf", format="pdf", bbox_inches="tight"),

    plt.show()

part_b('sine_part_b.csv')
part_b('chirp_part_b.csv')
part_b('shifted_sawtooth_part_b.csv')