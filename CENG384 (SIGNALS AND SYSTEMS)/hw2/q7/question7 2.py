import matplotlib.pyplot as plt
import numpy as np

def convolution(x0,s0,x1,s1):

    dif = abs(s0)-abs(s1)
    if dif<0:
        for i in range(-dif):
            x0.insert(0,0)
    elif dif>0:
        for i in range(dif):
            x1.insert(0,0)


    #convolution operation
    n0 = len(x0)
    n1 = len(x1)
    conv = [0]*(n0+n1-1)
    for i in range(s0,s0+n0):
        for j in range(s1,s1+n1):
            conv[i+j-s0-s1] += x0[i-s0]*x1[j-s1]
    
    #plot the convolution
    fig1, (ax1, ax2,ax3) = plt.subplots(3, 1, figsize=(16, 8))
    fig1.subplots_adjust(hspace=0.5, wspace=0.5)
    fig1.set_size_inches(8.27, 5.5)
    ax1.stem(list(range(s0,s0+n0)),x0,markerfmt=' ')
    ax1.set_title("x[n]")
    ax2.stem(list(range(s1,s1+n1)),x1,markerfmt=' ')
    ax2.set_title("h[n]")
    newlist = list(range(min(s0,s1),min(s0,s1) + len(conv)))
    for q in range(len(newlist)):
        newlist[q] += s0
    ax3.stem(newlist[:200],conv[:200],markerfmt=' ')
    ax3.set_title("x[n] * h[n]")
    plt.xlabel('n')
    plt.ylabel('Amplitude')
    fig1.suptitle('Convolution of two functions')
   
    plt.show()




if __name__ == "__main__":
    with open("hw2_signal.csv", 'r') as f:
        data = f.read().split(",")
        s0 = int(data[0])
        #print(s0)
        data0 = [float(i) for i in data[1:]]
    
    #Part a
    # data1 = [0.]*len(data0)
    # data1[5-s0] = 1.
    # s1=s0
    # convolution(data0,s0,data1,s1)

    # #Part b
    h = lambda n, N: 1/N if (n>=0 and n<=N-1) else 0

    for N in [40]:
        data1 = [h(n,N) for n in range(s0,s0+len(data0))]
        convolution(data0,s0,data1,s0)