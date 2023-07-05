import matplotlib.pyplot as plt

def part_a(filename):
    with open(filename, 'r') as f:

        data = f.read().split(",")
        starting_index = int(data[0])
        data = data[1:]
        data = [float(i) for i in data]
    
    ending_index = starting_index+len(data) -1
    x = list(range(starting_index, ending_index + 1))

    even_data = []
    odd_data = []

    k = abs(x[0])-abs(x[-1])
    if k<starting_index:
        for i in range(-k):
            x.insert(0,starting_index-i-1)
            data.insert(0,0)
    elif k>ending_index:
        for i in range(k):
            x.append(ending_index+i+1)
            data.insert(0,0)
   
    for i in range(len(data)):
        fx = data[i]
        fnegx = data[len(data)-i-1]

        even_data.append((fx + fnegx)/2) 
        odd_data.append((fx - fnegx)/2) 
    
    if k<starting_index:
        x = x[-k:]
        data = data[-k:]
        even_data = even_data[-k:]
        odd_data = odd_data[-k:]
    elif k>ending_index:
        x = x[:k]
        data = data[:k]
        even_data = even_data[:k]
        odd_data = odd_data[:k]

    
    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(16, 8))
    fig.set_size_inches(8.27, 5.5)

    ax1.stem(x, data,markerfmt='')
    ax1.set_title("x[n]")
    ax2.stem(x, even_data,markerfmt='')
    ax2.set_title("Even part")
    ax3.stem(x, odd_data,markerfmt='')
    ax3.set_title("Odd part")
    
    plt.xlabel('n')
    plt.ylabel('Amplitude')
    
    fig.suptitle('Even and Odd Parts of The Signal')
    plt.savefig(f"7a_{filename}.pdf", format="pdf", bbox_inches="tight"),
    plt.show()


part_a('sine_part_a.csv')
part_a('chirp_part_a.csv')
part_a('shifted_sawtooth_part_a.csv')
